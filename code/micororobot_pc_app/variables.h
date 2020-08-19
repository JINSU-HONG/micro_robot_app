#ifndef VARIABLES_H
#define VARIABLES_H

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

#define BUF_SIZE 512

#define GRID_RESOL 10
#define TOTAL_RESOL (GRID_RESOL * GRID_RESOL * GRID_RESOL)
#define CONTROL_REGION_WIDTH 0.02 // not half value
#define GRID_INTERVAL (CONTROL_REGION_WIDTH / (GRID_RESOL-1.0))

#define WORK_MODE_TERM 0
#define WORK_MODE_RECV 1
#define WORK_MODE_SEND 2

//#define EVEN_DATA_MODE 0
#define EVEN_DATA_MODE 1

#define PRINT_COMM_DATA 0
//#define PRINT_COMM_DATA 1

#define PRINT_PINV_RES 0
//#define PRINT_PINV_RES 1

//#define SEND_RECV_COMB 0
#define SEND_RECV_COMB 1

#define RECV_TIMEOUT_uSEC 500

// #define UPDATE_PM_AT_TIMEOUT 0
#define UPDATE_PM_AT_TIMEOUT 1

#define DISCONNECT_ESCAPE_MODE 0
//#define DISCONNECT_ESCAPE_MODE 1
#define DISCONNECT_ESCAPE_COUNT 1000

// OVERALL_MODE
#define OVERALL_MODE_INIT 1
#define OVERALL_MODE_INV_TEST 2
#define OVERALL_MODE_IDLE 3
#define OVERALL_MODE_RUN 4

// STATUS
#define MODE_STATUS_CHECKING 1
#define MODE_STATUS_OK 2
#define MODE_STATUS_CON_ERROR 3
#define MODE_STATUS_CON_LOST 4
#define MODE_STATUS_SUB_CON_ERROR 5
#define MODE_STATUS_SUB_CON_LOST 6
#define MODE_STATUS_SUP_ERROR 7
#define MODE_STATUS_ERROR 8
#define MODE_STATUS_INV_FAULT 9

// CC_IDLE_MODE
#define CC_IDLE_MODE_ZERO 1
#define CC_IDLE_MODE_KEEP 2 // keep the last current references

// BF_ref settings
#define REF_MODE_BF 0 // magnetic field and force
#define REF_MODE_TF 1 // torque and force
#define B_REF_X 0
#define B_REF_Y 1
#define B_REF_Z 2
#define B_REF_X_UPDOWN 3
#define B_REF_XY_CIRCLE 4
#define GRAVITY_ACC 9.8
#define F_REF_ZERO 0
#define F_REF_X 1
#define F_REF_Y 2
#define F_REF_Z 3
#define F_REF_X_UPDOWN 4
#define F_REF_X_SINE 5
#define F_REF_XY_CIRCLE 6

#define SOFT_REF_CNT 100

// microrobot physics constant
#define MASS_DENSITY 7450
#define FLUID_DENSITY 1000
#define MAGNETIZATION_DENSITY 1000000

// #define eta 0.001 // water 20 degree Celcius
// #define eta 0.0035 // blood
// #define eta 0.97 // silicon oil 1000
// #define eta 2.91 // silicon oil 3000
#define eta 50.

#define x_robot 0.001
#define y_robot 0.001
#define z_robot 0.001
#define m_robot (x_robot * y_robot * z_robot * 0.5 * MASS_DENSITY)
#define m_robot_buoyant (x_robot * y_robot * z_robot * 0.5 * (MASS_DENSITY-FLUID_DENSITY))
#define J_robot (m_robot * 0.16667 * (x_robot * x_robot + z_robot * z_robot))
#define M_robot (x_robot * y_robot * z_robot * 0.5 * MAGNETIZATION_DENSITY)

#define GRAVITY_COMPENSATION_OFF 0
#define GRAVITY_COMPENSATION_ON 1
#define GRAVITY_IN_NET_FORCE_OFF 0
#define GRAVITY_IN_NET_FORCE_ON 1
#define GRAVITY_FORCE (GRAVITY_ACC * m_robot_buoyant)

#define drag_translation (6 * 3.1416 * eta * z_robot)
//#define drag_rotation (8 * 3.1416 * eta * z_robot * z_robot * z_robot)
#define drag_rotation (8 * 3.1416 * eta * z_robot * z_robot * z_robot) * 0.002

#define F_max (m_robot * GRAVITY_ACC * 5) // gravity acc.
//#define F_max (m_robot * GRAVITY_ACC * 1.5) // 1.5 gravity acc.
#define B_max 0.005// 1mT
//#define B_max 0.005 // 5mT

#define x_bottom -0.01
#define x_top 0.01
#define y_bottom -0.01
#define y_top 0.01
#define z_bottom -0.01
#define z_top 0.01

using std::vector;

// Running condition
extern int OverallMode;
extern int ModeStatus;
extern int CCIdleMode;

extern int DIST_mode;
extern int DIST_status;

/* periodic operation variables */
extern long time_start;
extern long time_end;
extern long time_a;
extern long time_b;
extern long time_delta;
extern long time_delta_sum;

extern int period_count;
extern int retval;

extern int task_iter;
extern int task_period;
extern int wait_udp_recovery;

extern bool keep_on_running;
/* end of periodic operation variables */

/* pinv variables */
extern vector<vector<double> > *B_LUT1;
extern vector<vector<double> > *B_LUT2;
extern vector<vector<double> > *B_LUT3;
extern vector<vector<double> > *B_LUT4;
extern vector<vector<double> > *B_LUT5;
extern vector<vector<double> > *B_LUT6;
extern vector<vector<double> > *B_LUT7;
extern vector<vector<double> > *B_LUT8;

extern vector<double> Position;
extern vector<double> Magnetization;
extern vector<double> Velocity;
extern vector<double> AngularVelocity;
extern vector<double> BF_ref;
extern vector<double> Current_sen;
extern vector<double> Current_real_sen;
extern vector<double> Current_ref;
extern double Current_ref_old[10][8];
extern double manual_F[2];

extern bool ref_mode;
extern int B_ref_mode; // T_ref_mode
extern int F_ref_mode;
extern bool gravity_compensation_mode;
extern bool gravity_in_net_force;
extern float BF_ref_frequency;
extern float BF_ref_ang_vel;
extern bool update_PM_with_ref;
extern bool update_magnetization_with_torque;
extern bool fix_Position;
extern int using_inv_num;
extern int use_ref_for_sen;
extern int soft_ref_cnt;
extern bool stop_sending_at_timeout;
/* end of pinv variables */

/* udp variables */
// UDP configuration
extern int pc_port;
extern int dest_port;
extern char dest_addr_string[];

extern int udp_work_mode;

extern unsigned char recv_buf[BUF_SIZE + 5];
extern unsigned char send_buf[BUF_SIZE];
extern int recv_iter;
extern int send_len;
extern int data_size, data_size_tmp;

extern int sock;
// SOCKET sock;
extern socklen_t client_addr_size;

extern struct sockaddr_in server_addr, client_addr, dest_addr;

extern fd_set read_fds;
extern timeval timeout, temp_timeout;

extern int recv_remain_cnt;
extern int timeout_cnt;
extern int timeout_cnt_acc;
extern int timeout_flag;
extern int send_skip_cnt;
extern int old_ref_delay;
/* end of udp variables */

extern int testing_coil;

#endif // VARIABLES_H
