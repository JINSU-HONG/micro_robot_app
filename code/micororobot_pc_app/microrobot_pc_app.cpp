#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <sys/ioctl.h>
#include <vector>
#include <pthread.h>
#include <math.h>

#include <rtai_lxrt.h>

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

// typedef int SOCKET;
#define NET_INVALID_SOCKET -1
#define NET_SOCKET_ERROR -1

#include "variables.h"
#include "rt_setting.h"

#include "data_form_change.h"
#include "udp_func.h"
#include "actuation_matrix_calc.h"
#include "load_b_lut.h"
#include "gen_BF_ref.h"
#include "user_input_thread.h"

using std::vector;

int rt_setting();
int timer_precision_test();
int sock_setting();
void init_vectors();
void reset_current_ref();
void periodic_recv();
void periodic_send();
void mode_status_check();
// void gen_new_PM_BF_ref();
void clear_recv();
void *user_input_thr_func(void *arg);
void fprint_data();

pthread_t user_input_thr;

static RT_TASK* microrobot_task;

static cpu_set_t cpu_mask;
static int cpu_affinity = PINV_CPU_AFFINITY;

FILE *currentFile;

int main(int argc, char *argv[]) {
    //select CPU
    CPU_ZERO(&cpu_mask);
    CPU_SET(cpu_affinity, &cpu_mask);
    retval = sched_setaffinity(0, sizeof(cpu_mask), &cpu_mask);
    if (retval != 0) {
        printf("CPU select error\n");
        return -1;
    }

    //set timeout
    timeout.tv_sec = 0;
    timeout.tv_usec = RECV_TIMEOUT_uSEC;

    //RT setting
    if (rt_setting() != 0) return -1; // Error occured during rt_setting

    //do timer test
    //if (timer_precision_test() != 0) return -1; // Error occured during rt_setting

    // LOAD B LUT
    load_b_luts();

    // sock setting
    if (sock_setting() == -1) return -1; // Error occured during sock_setting

    // ready user input thread
    pthread_create(&user_input_thr, NULL, &user_input_thr_func, NULL);

    // init Position, Magnetization, Velocity, Angular Velocity, BF_ref, Current_ref, Current_sen
    init_vectors();
    
    currentFile = fopen("current_result.csv", "w+");
    if (currentFile == NULL) printf("Error opening current result csv file.");

    for (task_iter = 0; task_iter < 1000; task_iter++) {
        // wait 1 sec for safe period timer
        rt_task_wait_period();
    }
    task_iter = 0;
    
    time_start = rt_get_time_ns();
    while (keep_on_running) {
        if (wait_udp_recovery > 0) {
            if (wait_udp_recovery == 1000) {
                close(sock);
                sock_setting();
            }
            wait_udp_recovery--;
        } else if (udp_work_mode == WORK_MODE_RECV) {
            periodic_recv();

            task_iter++;
            if (task_iter == task_period) {
                udp_work_mode = WORK_MODE_TERM;
            } else {
                udp_work_mode = WORK_MODE_SEND;
            }

            if (DISCONNECT_ESCAPE_MODE) {
                if (recv_remain_cnt > DISCONNECT_ESCAPE_COUNT)  {
                    printf("UDP disconnected. Escape.\n");
                    break;
                }
            }
        } else if (udp_work_mode == WORK_MODE_SEND) {
            periodic_send();
            //if (OverallMode == OVERALL_MODE_RUN && task_iter % 5 == 0) {
            if (OverallMode == OVERALL_MODE_RUN) {
                fprint_data();
            }

            udp_work_mode = WORK_MODE_RECV;
            //udp_work_mode = WORK_MODE_TERM;
            if (SEND_RECV_COMB) continue; // no period wait before recv
        } else { // WORK_MODE_TERM
            break;
        }
        rt_task_wait_period();
    }
    time_end = rt_get_time_ns();
    
    printf("Task started at %luns\n", time_start);
    printf("Task ended at   %luns\n", time_end);
    printf("Task took %fms\n\n", (float)(time_end - time_start) / NS_PER_mSEC);
	
	printf("Timeout count : %d %d\n", timeout_cnt, timeout_cnt_acc);
    if (task_iter != timeout_cnt_acc) {
	    printf("Average SEND-RECV time : %fus\n\n", (float)time_delta_sum / NS_PER_uSEC / (task_iter-timeout_cnt_acc));
    }

    // recv left data to clear
    clear_recv();

    // task delete
    retval = rt_task_delete(microrobot_task);

    if (retval != 0) {
        if (retval == -EINVAL) {
            printf("task structure is invalid\n");
        } else {
            printf("error stopping task\n");
        }
    }

    // free LUT memory
    delete B_LUT1;
    delete B_LUT2;
    delete B_LUT3;
    delete B_LUT4;
    delete B_LUT5;
    delete B_LUT6;
    delete B_LUT7;
    delete B_LUT8;
    printf("\nFreed memory\n");

    fclose(currentFile);
    close(sock);

    // stop rt timer
    rt_make_soft_real_time();
    stop_rt_timer();
    printf("RT timer stopped\n");
    return 0;
}

int rt_setting() {
    rt_set_oneshot_mode();
    start_rt_timer(0);
    printf("RT timer started\n");
    
    period_count = nano2count(TASK_PERIOD_uSEC * NS_PER_uSEC);
    //printf("period count %d\n", period_count);

    if (!(microrobot_task = rt_task_init_schmod(RT_TASK_NUM, // Name
                                         2, // Priority
                                         0, // Stack Size
                                         0, // max_msg_size
                                         SCHED_FIFO, // Policy
                                         0))) {// cpus_allowed
        printf("Error. Cannot initialize main task\n");

        stop_rt_timer();
        printf("RT timer stopped\n");
        return -1;
    }

    mlockall(MCL_CURRENT | MCL_FUTURE);
    rt_make_hard_real_time();

    retval = rt_task_make_periodic(microrobot_task,
                                   rt_get_time() + period_count,
                                   period_count); //period in counts

    if (retval != 0) {
        if (retval == -EINVAL) {
            printf("task structure is invalid\n");
        } else {
            printf("error stacking task\n");
        }
        stop_rt_timer();
        printf("RT timer stopped\n");
        return retval;
    }

    printf("RT setting done\n\n");
    return 0;
}

int timer_precision_test() {
    long current_time, old_time;

    rt_task_wait_period();
    old_time = rt_get_time_ns();
    for (int i=0; i<10; i++) {
        rt_task_wait_period(); // 1ms
        current_time = rt_get_time_ns();
        if (current_time - old_time < 500000) { // 0.5ms
            printf("RTAI is not working properly. (period : %.2fms)\n", (float)(current_time - old_time)/1000000.);
            printf("Please reboot the system.\n");
            return -1;
        } else {
            old_time = current_time;
        }
    }

    return 0;
}

int sock_setting() {
    //if ((sock = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
    if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        printf("Error. socket creation fail\n");
        stop_rt_timer();
        printf("RT timer stopped\n");
        return -1;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(pc_port);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(dest_port);
    dest_addr.sin_addr.s_addr = inet_addr(dest_addr_string);
    
    if (bind(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == NET_SOCKET_ERROR) {
        printf("Error. Socket binding fail\n");
        close(sock);
        stop_rt_timer();
        printf("RT timer stopped\n");
        return -1;
    }

    printf("Server is ready!\n\n");
    return 0;
}

void init_vectors() {
    Position[0] = 0.;
    Position[1] = 0.;
    Position[2] = -0.005;
    Magnetization[0] = 0.;
    Magnetization[1] = 0.;
    Magnetization[2] = M_robot;
    Velocity[0] = 0.;
    Velocity[1] = 0.;
    Velocity[2] = 0.;
    AngularVelocity[0] = 0.;
    AngularVelocity[1] = 0.;
    AngularVelocity[2] = 0.;
    BF_ref[0] = 0.;
    BF_ref[1] = 0.;
    BF_ref[2] = 0.;
    BF_ref[3] = 0.;
    BF_ref[4] = 0.;
    BF_ref[5] = 0.;
    Current_ref[0] = 0.;
    Current_ref[1] = 0.;
    Current_ref[2] = 0.;
    Current_ref[3] = 0.;
    Current_ref[4] = 0.;
    Current_ref[5] = 0.;
    Current_ref[6] = 0.;
    Current_ref[7] = 0.;
    Current_sen[0] = 0.;
    Current_sen[1] = 0.;
    Current_sen[2] = 0.;
    Current_sen[3] = 0.;
    Current_sen[4] = 0.;
    Current_sen[5] = 0.;
    Current_sen[6] = 0.;
    Current_sen[7] = 0.;
    Current_real_sen[0] = 0.;
    Current_real_sen[1] = 0.;
    Current_real_sen[2] = 0.;
    Current_real_sen[3] = 0.;
    Current_real_sen[4] = 0.;
    Current_real_sen[5] = 0.;
    Current_real_sen[6] = 0.;
    Current_real_sen[7] = 0.;
    for (int i=0; i<old_ref_delay; i++) {
        for (int j=0; j<8; j++) {
            Current_ref_old[i][j] = 0.;
        }
    }
    manual_F[0] = 0.;
    manual_F[1] = 0.;
}

void reset_current_ref() {
    Current_ref[0] = 0.;
    Current_ref[1] = 0.;
    Current_ref[2] = 0.;
    Current_ref[3] = 0.;
    Current_ref[4] = 0.;
    Current_ref[5] = 0.;
    Current_ref[6] = 0.;
    Current_ref[7] = 0.;
    Current_sen[0] = 0.;
    Current_sen[1] = 0.;
    Current_sen[2] = 0.;
    Current_sen[3] = 0.;
    Current_sen[4] = 0.;
    Current_sen[5] = 0.;
    Current_sen[6] = 0.;
    Current_sen[7] = 0.;
    Current_real_sen[0] = 0.;
    Current_real_sen[1] = 0.;
    Current_real_sen[2] = 0.;
    Current_real_sen[3] = 0.;
    Current_real_sen[4] = 0.;
    Current_real_sen[5] = 0.;
    Current_real_sen[6] = 0.;
    Current_real_sen[7] = 0.;
    for (int i=0; i<old_ref_delay; i++) {
        for (int j=0; j<8; j++) {
            Current_ref_old[i][j] = 0.;
        }
    }
}

void periodic_recv() {
    if (PRINT_COMM_DATA) printf("-----------------------------\n");
    // clear the recv_buf
    memset(&recv_buf[0], 0, sizeof(recv_buf));
    if (PRINT_COMM_DATA) printf("Receiving data...\n");

    recv_remain_cnt++;

    // timeout using select function
    FD_ZERO(&read_fds);
    FD_SET(sock, &read_fds);

    memcpy(&temp_timeout, &timeout, sizeof(timeout));
    retval = select(sock+1, &read_fds, 0, 0, &temp_timeout);

    switch (retval) {
        case 0:
            //printf("timeout\n");
            timeout_cnt++;
            timeout_cnt_acc++;
            timeout_flag = 1;
            if (timeout_cnt == 1000) {
                printf("1000 connection lost in a row. Escape.\n");
                OverallMode = OVERALL_MODE_INIT;
                ModeStatus = MODE_STATUS_CHECKING;
                timeout_flag = 0; // try to send again
            }
            data_size = -1;
            if (UPDATE_PM_AT_TIMEOUT) {
                if (DIST_mode == OVERALL_MODE_IDLE || DIST_mode == OVERALL_MODE_RUN) {
                    copy_current_ref_to_sen();
                    update_PM(); // update Position, Magnetization with current_ref
                }
            }
            break;
        case -1:
            printf("timeout error\n");
            data_size = -1;
            break;
        default:
            while (1) {
                data_size = recvfrom(sock, recv_buf, BUF_SIZE, 0, (struct sockaddr*)&client_addr, &client_addr_size);
                time_b = rt_get_time_ns();
                //if (time_b - time_a > 350000) printf("big send-recv delta %ldns\n", time_b - time_a);
                recv_remain_cnt--;
                if (recv_remain_cnt > 0) { // try to read left data
                    FD_ZERO(&read_fds);
                    FD_SET(sock, &read_fds);
                    memcpy(&temp_timeout, &timeout, sizeof(timeout));
                    retval = select(sock+1, &read_fds, 0, 0, &temp_timeout);
                    if (retval > 0) continue;
                }
                recv_remain_cnt = 0;
                timeout_cnt = 0; // timeout_cnt_acc != 0
                timeout_flag = 0;
                break;
            }
            time_delta_sum += time_b - time_a;
            //time_b = rt_get_time_ns();
            //printf("delta %ld\n", time_b - time_a);
            
            // received data
            recv_iter = 0;
            read_udp_header();

            if (DIST_mode == OVERALL_MODE_INIT) {
                init_mode_udp_recv_func();
            } else if (DIST_mode == OVERALL_MODE_INV_TEST) {
                inv_test_mode_udp_recv_func();
            } else if (DIST_mode == OVERALL_MODE_IDLE) {
                idle_mode_udp_recv_func(); // current fault, voltage fault, current_sen
                update_PM(); // update Position, Magnetization with current_sen
            } else if (DIST_mode == OVERALL_MODE_RUN) {
                run_mode_udp_recv_func(); // current fault, voltage fault, current_sen
                update_PM(); // update Position, Magnetization with current_sen
            } else {
                // CON LOST
            }

            mode_status_check(); // escape(change mode to INIT) if it is not safe
    }
    if (PRINT_COMM_DATA) printf("Received data : %s\n", recv_buf);
    if (data_size == -1) {
        if (PRINT_COMM_DATA) printf("Error. Receiving fail\n");
    } else if (data_size == 1) {
        if (PRINT_COMM_DATA) printf("1 byte received.\n");
    } else {
        if (PRINT_COMM_DATA) printf("%d bytes received.\n", data_size);
    }
}

void periodic_send() {
    if (PRINT_COMM_DATA) printf("-----------------------------\n");
    memset(&send_buf[0], 0, sizeof(send_buf));
    send_len = 0;
    
    AddSendHeaderData();

    if (task_iter % 1000 == 0) {
        //printf("%f %f %f %f\n", Current_ref[0], Current_ref[1], Current_ref[4], Current_ref[5]);
        printf("\n%.0fs : Mode %d, Status %d\n", (rt_get_time_ns() - time_start) / 1000000000., OverallMode, ModeStatus);
        if (OverallMode == OVERALL_MODE_IDLE || OverallMode == OVERALL_MODE_RUN) {
            printf("Current 1 ref, sen : %.3eA %.3eA\n", Current_ref[0], Current_sen[0]);
            printf("Current 2 ref, sen : %.3eA %.3eA\n", Current_ref[1], Current_sen[1]);
        }
    }
    if (OverallMode == OVERALL_MODE_INIT) {
        init_mode_udp_send_func();
        reset_current_ref();
    } else if (OverallMode == OVERALL_MODE_INV_TEST) {
        inv_test_mode_udp_send_func();
    } else if (OverallMode == OVERALL_MODE_IDLE) {
        idle_mode_udp_send_func();
    } else if (OverallMode == OVERALL_MODE_RUN) {
        gen_BF_ref(rt_get_time_ns());
        time_a = rt_get_time_ns();
        get_current_ref(); // for Position, Magnetization, BF_ref
        time_b = rt_get_time_ns();
        if (time_delta < time_b - time_a) {
            time_delta = time_b - time_a;
        }
        if (time_b - time_a > 100000) {
            printf("big pinv delta : %ldns\n", time_b - time_a);
            //for (vector<double>::const_iterator i = I->begin(); i != I->end(); ++i)
            //    printf("%f\n", *i);
        }
        run_mode_udp_send_func();
    }

    if (EVEN_DATA_MODE && send_len % 2 == 1) {
        send_len = send_len + 1;
        send_buf[send_len] = '\0';
    }

    time_a = rt_get_time_ns(); // send-recv time start
    if (PRINT_COMM_DATA) printf("sending...\n");
    if (send_skip_cnt > 0) {
        send_skip_cnt--;
        data_size = 0;
    } else if ((!stop_sending_at_timeout) || (timeout_flag == 0))  { 
        data_size = sendto(sock, send_buf, send_len, 0, (struct sockaddr*)&dest_addr, sizeof(dest_addr));
    }
    if (data_size == -1) {
        // printf("Error. No data sent\n");
    } else if (data_size == 1) {
        if (PRINT_COMM_DATA) printf("1 byte sent\n");
    } else {
        if (PRINT_COMM_DATA) printf("%d bytes sent\n", data_size);
    }
}

void mode_status_check() {
    if (!= MODE_STATUS_CHECKING && ModeStatus != MODE_STATUS_OK && ModeStatus != MODE_STATUS_SUB_CON_LOST && ModeStatus != MODE_STATUS_SUB_CON_ERROR && OverallMode != OVERALL_MODE_INIT) {
        printf("System is not on CHECKING or OK status. Escape.\n");
        printf("Escaped from mode '");
        //if (OverallMode == OVERALL_MODE_INIT) printf("INIT");
        if (OverallMode == OVERALL_MODE_INV_TEST) printf("INV_TEST");
        else if (OverallMode == OVERALL_MODE_IDLE) printf("IDLE");
        else printf("RUN");
        printf("', status '");
        if (ModeStatus == MODE_STATUS_CON_ERROR) printf("CON_ERROR");
        else if (ModeStatus == MODE_STATUS_CON_LOST) printf("CON_LOST");
        //else if (ModeStatus == MODE_STATUS_SUB_CON_ERROR) printf("SUB_CON_ERROR");
        //else if (ModeStatus == MODE_STATUS_SUB_CON_LOST) printf("SUB_CON_LOST");
        else if (ModeStatus == MODE_STATUS_INV_FAULT) printf("INV_FAULT");
        else printf("ERROR (others : %d)", ModeStatus);
        printf("'.\n");

        OverallMode = OVERALL_MODE_INIT;
        ModeStatus = MODE_STATUS_CHECKING;
    }
}

void clear_recv() {
    printf("RECV remain count : %d\n", recv_remain_cnt);
    ioctl(sock, FIONREAD, &data_size_tmp);
    if (data_size_tmp != 0) printf("There exists left data. Receiving...\n");
    while (data_size_tmp != 0) {
        //printf("ioctl : %d\n", data_size_tmp);
        data_size = recvfrom(sock, recv_buf, BUF_SIZE, 0, (struct sockaddr*)&client_addr, &client_addr_size); 
        if (data_size == -1) {
            break;
        }
        ioctl(sock, FIONREAD, &data_size_tmp);
    }
    printf("Left data cleared\n");
}

void fprint_data() {
    //fprintf(currentFile, "%.3f\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f\n", (float)(rt_get_time_ns() - time_start) / 1000000000., Current_ref[1], Current_sen[1], Position[0]*100, Position[1]*100, Position[2]*100, Magnetization[0]*100, Magnetization[1]*100, Magnetization[2]*100);
    //fprintf(currentFile, "%.3f\t%.4f\t%.4f\n", (float)(rt_get_time_ns() - time_start) / 1000000000., sin((float)task_iter / 1000. * 2 * 3.1416 * 10), Current_sen[1]);
    fprintf(currentFile, "%.4f\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f\t\t", BF_ref[0]*10000, BF_ref[1]*10000, BF_ref[2]*10000, BF_ref[3]*10000, BF_ref[4]*10000, BF_ref[5]*10000);
    fprintf(currentFile, "%.4f\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f\t\t", Current_ref[0], Current_ref[1], Current_ref[2], Current_ref[3], Current_ref[4], Current_ref[5], Current_ref[6], Current_ref[7]);
    fprintf(currentFile, "%.4f\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f\t\t", Position[0]*10000, Position[1]*10000, Position[2]*10000, Magnetization[0]*10000, Magnetization[1]*10000, Magnetization[2]*10000);
    for (int i=0; i<using_inv_num; i++) {
        fprintf(currentFile, "%.4f\t%.4f\t", Current_ref[i], Current_real_sen[i]);
    }
    fprintf(currentFile, "%d\n", timeout_flag);
} 
