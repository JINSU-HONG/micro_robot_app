#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <vector>

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

// typedef int SOCKET;
#define NET_INVALID_SOCKET -1
#define NET_SOCKET_ERROR -1

#include "variables.h"
#include "rt_setting.h"

using std::vector;

// Runing condition
int OverallMode = OVERALL_MODE_INIT;
int ModeStatus = MODE_STATUS_CHECKING;
int CCIdleMode = CC_IDLE_MODE_ZERO;

int DIST_status = OVERALL_MODE_INIT;
int DIST_mode = MODE_STATUS_CHECKING;

/* periodic operation variables */
long time_start;
long time_end;
long time_a;
long time_b;
long time_delta;
long time_delta_sum = 0;

int period_count;
int retval;

int task_iter = 0;
//int task_period = 200000000;
//int task_period = 10000;
int task_period = -1;
int wait_udp_recovery = 0;

bool keep_on_running = true;
/* end of periodic operation variables */

/* pinv variables */
vector<vector<double> > *B_LUT1 = new vector<vector<double> >(TOTAL_RESOL, vector<double>(3));
vector<vector<double> > *B_LUT2 = new vector<vector<double> >(TOTAL_RESOL, vector<double>(3));
vector<vector<double> > *B_LUT3 = new vector<vector<double> >(TOTAL_RESOL, vector<double>(3));
vector<vector<double> > *B_LUT4 = new vector<vector<double> >(TOTAL_RESOL, vector<double>(3));
vector<vector<double> > *B_LUT5 = new vector<vector<double> >(TOTAL_RESOL, vector<double>(3));
vector<vector<double> > *B_LUT6 = new vector<vector<double> >(TOTAL_RESOL, vector<double>(3));
vector<vector<double> > *B_LUT7 = new vector<vector<double> >(TOTAL_RESOL, vector<double>(3));
vector<vector<double> > *B_LUT8 = new vector<vector<double> >(TOTAL_RESOL, vector<double>(3));

vector<double> Position(3);
vector<double> Magnetization(3);
vector<double> Velocity(3);
vector<double> AngularVelocity(3);
vector<double> BF_ref(6);
vector<double> Current_ref(8);
vector<double> Current_sen(8);
vector<double> Current_real_sen(8);
double Current_ref_old[10][8];
double manual_F[2];

bool ref_mode = REF_MODE_BF; // false
int B_ref_mode = B_REF_Z;
int F_ref_mode = F_REF_ZERO;
bool gravity_compensation_mode = GRAVITY_COMPENSATION_OFF;
bool gravity_in_net_force = GRAVITY_IN_NET_FORCE_OFF;
float BF_ref_frequency = 1;
float BF_ref_ang_vel = BF_ref_frequency * 2 * 3.1416;
bool update_PM_with_ref = true;
bool update_magnetization_with_torque = false; // false : follow magnetic field direction
bool fix_Position = true;
int using_inv_num = 8;
int use_ref_for_sen = 100;
int soft_ref_cnt = 0;
bool stop_sending_at_timeout = true;

/* udp variables */
// UDP configuration
int pc_port = 5000;
int dest_port = 3000;
//char dest_addr_string[] = "127.0.0.1";
//char dest_addr_string[] = "192.168.100.5";
char dest_addr_string[] = "192.168.100.200";

int udp_work_mode = WORK_MODE_SEND;

unsigned char recv_buf[BUF_SIZE + 5];
unsigned char send_buf[BUF_SIZE];
int recv_iter;
int send_len;
int data_size, data_size_tmp;

int sock;
// SOCKET sock;
socklen_t client_addr_size;

struct sockaddr_in server_addr, client_addr, dest_addr;

fd_set read_fds;
timeval timeout, temp_timeout;

int recv_remain_cnt = 0;
int timeout_cnt = 0;
int timeout_cnt_acc = 0;
int timeout_flag = 0;
int send_skip_cnt = 0;
int old_ref_delay = 1;
/* end of udp variables */

int testing_coil = 0;
