#include <stdio.h>
#include <math.h>

#include "variables.h"
#include "data_form_change.h"

void read_udp_header();
void print_fault_INVs();
void read_current_sen();
void copy_current_ref_to_sen();

void AddSendHeaderData() {
    send_buf[send_len] = OverallMode;
    send_buf[send_len+1] = ModeStatus;
    send_buf[send_len+2] = 0xAA;
    send_buf[send_len+3] = 0x55;
    send_len = send_len + 4;
}

void init_mode_udp_send_func() {
    // pass
}

void inv_test_mode_udp_send_func() {
    // pass
}

void idle_mode_udp_send_func() {
    send_buf[send_len] = 0x00;
    send_buf[send_len+1] = 0x00;
    send_buf[send_len+2] = 0x00;
    send_buf[send_len+3] = CCIdleMode;
    send_len = send_len + 4;
}

void run_mode_udp_send_func() {
    //for (int i=0; i<8; i++) {
    //   Current_ref[i] = 0.;
    //}
    //Current_ref[testing_coil] = 3.;
    //Current_ref[5] = 1.;
    
    AddSendFloatData(Current_ref[0]);
    AddSendFloatData(Current_ref[1]);
    //AddSendFloatData(Current_ref[1]/10);
    //AddSendFloatData(sin((float)task_iter / 1000. * 2 * 3.1416 * 10));
    AddSendFloatData(Current_ref[2]);
    AddSendFloatData(Current_ref[3]);
    AddSendFloatData(Current_ref[4]);
    AddSendFloatData(Current_ref[5]);
    AddSendFloatData(Current_ref[6]);
    AddSendFloatData(Current_ref[7]);
}

void init_mode_udp_recv_func() {
    recv_iter = recv_iter + 1; // dummy data
    if (ModeStatus == MODE_STATUS_SUB_CON_LOST) {
        /*
        if (recv_buf[recv_iter] & 0x01 != 0) printf("INV 1 connection lost\n");
        if (recv_buf[recv_iter] & 0x02 != 0) printf("INV 2 connection lost\n");
        if (recv_buf[recv_iter] & 0x04 != 0) printf("INV 3 connection lost\n");
        if (recv_buf[recv_iter] & 0x08 != 0) printf("INV 4 connection lost\n");
        if (recv_buf[recv_iter] & 0x10 != 0) printf("INV 5 connection lost\n");
        if (recv_buf[recv_iter] & 0x20 != 0) printf("INV 6 connection lost\n");
        if (recv_buf[recv_iter] & 0x40 != 0) printf("INV 7 connection lost\n");
        if (recv_buf[recv_iter] & 0x80 != 0) printf("INV 8 connection lost\n");
        */

        // copy Current_ref for SUB_CON_LOST
        //if (task_iter % 1000 == 0) {
        //    printf("connection lost : %x\n", recv_buf[recv_iter]);
        //}
    }
    recv_iter = recv_iter + 1;
    recv_iter = recv_iter + 1;
    if (ModeStatus == MODE_STATUS_SUB_CON_ERROR) {
        /*
        if (recv_buf[recv_iter] & 0x01 != 0) printf("INV 1 connection wrong\n");
        if (recv_buf[recv_iter] & 0x02 != 0) printf("INV 2 connection wrong\n");
        if (recv_buf[recv_iter] & 0x04 != 0) printf("INV 3 connection wrong\n");
        if (recv_buf[recv_iter] & 0x08 != 0) printf("INV 4 connection wrong\n");
        if (recv_buf[recv_iter] & 0x10 != 0) printf("INV 5 connection wrong\n");
        if (recv_buf[recv_iter] & 0x20 != 0) printf("INV 6 connection wrong\n");
        if (recv_buf[recv_iter] & 0x40 != 0) printf("INV 7 connection wrong\n");
        if (recv_buf[recv_iter] & 0x80 != 0) printf("INV 8 connection wrong\n");
        */
        if (task_iter % 1000 == 0) {
            printf("connection wrong : %x\n", recv_buf[recv_iter]);
        }
    }
    recv_iter = recv_iter + 1;
}

void inv_test_mode_udp_recv_func() {
    if (ModeStatus == MODE_STATUS_INV_FAULT) {
        print_fault_INVs();
    } else {
        recv_iter = recv_iter + 4;
    }
}

void idle_mode_udp_recv_func() {
    if (ModeStatus == MODE_STATUS_INV_FAULT) {
        print_fault_INVs();
    } else {
        recv_iter = recv_iter + 4;
    }
    if (ModeStatus == MODE_STATUS_SUB_CON_LOST && ModeStatus == MODE_STATUS_SUB_CON_ERROR) {
        copy_current_ref_to_sen();
    } else {
        read_current_sen();
    }
}

void run_mode_udp_recv_func() {
    idle_mode_udp_recv_func();
}

// send, recv util functions
void read_udp_header() {
    bool connection_test_OK = true;
    //recv_iter = 0;
    DIST_mode = recv_buf[recv_iter];
    DIST_status = recv_buf[recv_iter+1];
    if (DIST_mode == 0 || DIST_status == 0 || recv_buf[recv_iter+2] != 0xAA || recv_buf[recv_iter+3] != 0x55) {
        connection_test_OK = false;
        ModeStatus = MODE_STATUS_CON_LOST;
        wait_udp_recovery = 1000;
        printf("UDP connection lost. Reconnecting...\n");
    }

    if (!connection_test_OK) {
        ModeStatus = MODE_STATUS_CON_ERROR;
    } else if (DIST_status == MODE_STATUS_CON_ERROR) {
        ModeStatus = MODE_STATUS_SUB_CON_ERROR;
    } else if (DIST_status == MODE_STATUS_CON_LOST) {
        ModeStatus = MODE_STATUS_SUB_CON_LOST;
    } else if (DIST_status == MODE_STATUS_OK || DIST_status == MODE_STATUS_CHECKING || DIST_status == MODE_STATUS_INV_FAULT) {
        ModeStatus = DIST_status;
    } else { // } else if (DIST_mode != MODE_STATUS_SUP_ERROR) {
        ModeStatus = MODE_STATUS_ERROR;
        printf("Unexpected error occured. DIST status : %x\n", DIST_status);
    }

    if ((OverallMode == OVERALL_MODE_IDLE || OverallMode == OVERALL_MODE_RUN) && DIST_mode == OVERALL_MODE_INIT) {
        // con lost
        //printf("DIST turned into INIT mode. Try to continue...\n");
        //OverallMode = OVERALL_MODE_INIT;
    }

    recv_iter = recv_iter + 4;
}

void print_fault_INVs() {
    recv_iter = recv_iter + 1;
    if (recv_buf[recv_iter] & 0x01) printf("INV 1 current fault\n");
    if (recv_buf[recv_iter] & 0x02) printf("INV 2 current fault\n");
    if (recv_buf[recv_iter] & 0x04) printf("INV 3 current fault\n");
    if (recv_buf[recv_iter] & 0x08) printf("INV 4 current fault\n");
    if (recv_buf[recv_iter] & 0x10) printf("INV 5 current fault\n");
    if (recv_buf[recv_iter] & 0x20) printf("INV 6 current fault\n");
    if (recv_buf[recv_iter] & 0x40) printf("INV 7 current fault\n");
    if (recv_buf[recv_iter] & 0x80) printf("INV 8 current fault\n");
    recv_iter = recv_iter + 1;
    recv_iter = recv_iter + 1;
    if (recv_buf[recv_iter] & 0x01 != 0) printf("INV 1 voltage fault\n");
    if (recv_buf[recv_iter] & 0x02 != 0) printf("INV 2 voltage fault\n");
    if (recv_buf[recv_iter] & 0x04 != 0) printf("INV 3 voltage fault\n");
    if (recv_buf[recv_iter] & 0x08 != 0) printf("INV 4 voltage fault\n");
    if (recv_buf[recv_iter] & 0x10 != 0) printf("INV 5 voltage fault\n");
    if (recv_buf[recv_iter] & 0x20 != 0) printf("INV 6 voltage fault\n");
    if (recv_buf[recv_iter] & 0x40 != 0) printf("INV 7 voltage fault\n");
    if (recv_buf[recv_iter] & 0x80 != 0) printf("INV 8 voltage fault\n");
    recv_iter = recv_iter + 1;
}

void read_current_sen() {
    if (OverallMode == OVERALL_MODE_IDLE || use_ref_for_sen > 0) {
        for (int i=0; i<8; i++) {
            Current_real_sen[i] = Current_ref_old[old_ref_delay][i];
            Current_sen[i] = Current_real_sen[i];
        }
        if (OverallMode == OVERALL_MODE_RUN) {
            use_ref_for_sen--;
        } else {
            use_ref_for_sen = 100;
        }
    } else {
        for (int i=0; i<8; i++) {
            if (i < using_inv_num) {
                Current_real_sen[i] = ReadRecvFloatData();
            } else { // copy ref for unsensed currents
                Current_real_sen[i] = Current_ref_old[old_ref_delay][i];
            }
            if (Current_real_sen[i] > 100 || Current_real_sen[i] == 0) { // recv error
                Current_real_sen[i] = Current_ref_old[old_ref_delay][i];
                timeout_flag = 2;
            }

            if ((i < using_inv_num) && (!update_PM_with_ref)) {
                Current_sen[i] = Current_real_sen[i];
            } else {
                Current_sen[i] = Current_ref_old[old_ref_delay][i];
            }
        }
    }
}

void copy_current_ref_to_sen() {
    for (int i=0; i<8; i++) {
        Current_real_sen[i] = Current_ref_old[old_ref_delay][i];
        Current_sen[i] = Current_ref_old[old_ref_delay][i];
    }
}
