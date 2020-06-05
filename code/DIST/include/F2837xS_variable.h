#ifndef VARIABLE_H
#define VARIABLE_H

#include "F28x_Project.h"
#include "comp.h"
#include "Filter.h"
#include "types.h"

//system setting
#define SYS_CLK			((float)200e6)
#define SYS_CLK_HALF	((float)100e6)
#define SYS_CLK_PRD		((float)5.0e-9)

//w5300
#define SOCK_0 0
#define SOCK_1 1
#define SOCK_2 2
#define SOCK_3 3
#define SOCK_4 4
#define SOCK_5 5
#define SOCK_6 6
#define SOCK_7 7
#define SOCK_0_PORT 5000
#define SOCK_0_DESTPORT 5001
#define SOCK_1_PORT 3000
//#define SOCK_1_DESTPORT 55056
#define SOCK_1_DESTPORT 5000

#define W5300_MODE_UDP 0
#define W5300_MODE_MACRAW 1

#define UDP_HEADER_LEN 4
#define INIT_RECV_LEN 0
#define INV_TEST_RECV_LEN 0
#define IDLE_RECV_LEN 2
#define RUN_RECV_LEN (4 * 8) // 8 currents

#define RESET_INV_MAX_TRIAL 10

#define FAN_ON()	GpioDataRegs.GPASET.bit.GPIO21 	= 0x1
#define FAN_OFF()	GpioDataRegs.GPACLEAR.bit.GPIO21	= 0x1

#define DOUT1_ON()	GpioDataRegs.GPASET.bit.GPIO29 	= 0x1
#define DOUT1_OFF()	GpioDataRegs.GPACLEAR.bit.GPIO29	= 0x1

#define DOUT2_ON()	GpioDataRegs.GPBSET.bit.GPIO32 	= 0x1
#define DOUT2_OFF()	GpioDataRegs.GPBCLEAR.bit.GPIO32	= 0x1

#define DOUT3_ON()	GpioDataRegs.GPASET.bit.GPIO23 	= 0x1
#define DOUT3_OFF()	GpioDataRegs.GPACLEAR.bit.GPIO23	= 0x1


#define DFPGA_ON()	GpioDataRegs.GPBSET.bit.GPIO54 	= 0x1
#define DFPGA_OFF()	GpioDataRegs.GPBCLEAR.bit.GPIO54	= 0x1

#define CS4BASE 0x380000
#define CS3BASE 0x300000
#define CS2BASE 0x100000

#define INV0_CS_0           (*(volatile int *)(CS2BASE + ((0x200)<<1)))
#define INV0_CS_1           (*(volatile int *)(CS2BASE + ((0x201)<<1)))
#define INV0_CS_2           (*(volatile int *)(CS2BASE + ((0x202)<<1)))
#define INV0_CS_3           (*(volatile int *)(CS2BASE + ((0x203)<<1)))
#define INV0_CS_4           (*(volatile int *)(CS2BASE + ((0x204)<<1)))
#define INV0_CS_5           (*(volatile int *)(CS2BASE + ((0x205)<<1)))
#define INV0_CS_6           (*(volatile int *)(CS2BASE + ((0x206)<<1)))
#define INV0_CS_7           (*(volatile int *)(CS2BASE + ((0x207)<<1)))

#define INV1_CS_0           (*(volatile int *)(CS2BASE + ((0x210)<<1)))
#define INV1_CS_1           (*(volatile int *)(CS2BASE + ((0x211)<<1)))
#define INV1_CS_2           (*(volatile int *)(CS2BASE + ((0x212)<<1)))
#define INV1_CS_3           (*(volatile int *)(CS2BASE + ((0x213)<<1)))
#define INV1_CS_4           (*(volatile int *)(CS2BASE + ((0x214)<<1)))
#define INV1_CS_5           (*(volatile int *)(CS2BASE + ((0x215)<<1)))
#define INV1_CS_6           (*(volatile int *)(CS2BASE + ((0x216)<<1)))
#define INV1_CS_7           (*(volatile int *)(CS2BASE + ((0x217)<<1)))

#define INV2_CS_0           (*(volatile int *)(CS2BASE + ((0x220)<<1)))
#define INV2_CS_1           (*(volatile int *)(CS2BASE + ((0x221)<<1)))
#define INV2_CS_2           (*(volatile int *)(CS2BASE + ((0x222)<<1)))
#define INV2_CS_3           (*(volatile int *)(CS2BASE + ((0x223)<<1)))
#define INV2_CS_4           (*(volatile int *)(CS2BASE + ((0x224)<<1)))
#define INV2_CS_5           (*(volatile int *)(CS2BASE + ((0x225)<<1)))
#define INV2_CS_6           (*(volatile int *)(CS2BASE + ((0x226)<<1)))
#define INV2_CS_7           (*(volatile int *)(CS2BASE + ((0x227)<<1)))

#define INV3_CS_0           (*(volatile int *)(CS2BASE + ((0x230)<<1)))
#define INV3_CS_1           (*(volatile int *)(CS2BASE + ((0x231)<<1)))
#define INV3_CS_2           (*(volatile int *)(CS2BASE + ((0x232)<<1)))
#define INV3_CS_3           (*(volatile int *)(CS2BASE + ((0x233)<<1)))
#define INV3_CS_4           (*(volatile int *)(CS2BASE + ((0x234)<<1)))
#define INV3_CS_5           (*(volatile int *)(CS2BASE + ((0x235)<<1)))
#define INV3_CS_6           (*(volatile int *)(CS2BASE + ((0x236)<<1)))
#define INV3_CS_7           (*(volatile int *)(CS2BASE + ((0x237)<<1)))

#define INV4_CS_0           (*(volatile int *)(CS2BASE + ((0x240)<<1)))
#define INV4_CS_1           (*(volatile int *)(CS2BASE + ((0x241)<<1)))
#define INV4_CS_2           (*(volatile int *)(CS2BASE + ((0x242)<<1)))
#define INV4_CS_3           (*(volatile int *)(CS2BASE + ((0x243)<<1)))
#define INV4_CS_4           (*(volatile int *)(CS2BASE + ((0x244)<<1)))
#define INV4_CS_5           (*(volatile int *)(CS2BASE + ((0x245)<<1)))
#define INV4_CS_6           (*(volatile int *)(CS2BASE + ((0x246)<<1)))
#define INV4_CS_7           (*(volatile int *)(CS2BASE + ((0x247)<<1)))

#define INV5_CS_0           (*(volatile int *)(CS2BASE + ((0x250)<<1)))
#define INV5_CS_1           (*(volatile int *)(CS2BASE + ((0x251)<<1)))
#define INV5_CS_2           (*(volatile int *)(CS2BASE + ((0x252)<<1)))
#define INV5_CS_3           (*(volatile int *)(CS2BASE + ((0x253)<<1)))
#define INV5_CS_4           (*(volatile int *)(CS2BASE + ((0x254)<<1)))
#define INV5_CS_5           (*(volatile int *)(CS2BASE + ((0x255)<<1)))
#define INV5_CS_6           (*(volatile int *)(CS2BASE + ((0x256)<<1)))
#define INV5_CS_7           (*(volatile int *)(CS2BASE + ((0x257)<<1)))

#define INV6_CS_0           (*(volatile int *)(CS2BASE + ((0x260)<<1)))
#define INV6_CS_1           (*(volatile int *)(CS2BASE + ((0x261)<<1)))
#define INV6_CS_2           (*(volatile int *)(CS2BASE + ((0x262)<<1)))
#define INV6_CS_3           (*(volatile int *)(CS2BASE + ((0x263)<<1)))
#define INV6_CS_4           (*(volatile int *)(CS2BASE + ((0x264)<<1)))
#define INV6_CS_5           (*(volatile int *)(CS2BASE + ((0x265)<<1)))
#define INV6_CS_6           (*(volatile int *)(CS2BASE + ((0x266)<<1)))
#define INV6_CS_7           (*(volatile int *)(CS2BASE + ((0x267)<<1)))

#define INV7_CS_0           (*(volatile int *)(CS2BASE + ((0x270)<<1)))
#define INV7_CS_1           (*(volatile int *)(CS2BASE + ((0x271)<<1)))
#define INV7_CS_2           (*(volatile int *)(CS2BASE + ((0x272)<<1)))
#define INV7_CS_3           (*(volatile int *)(CS2BASE + ((0x273)<<1)))
#define INV7_CS_4           (*(volatile int *)(CS2BASE + ((0x274)<<1)))
#define INV7_CS_5           (*(volatile int *)(CS2BASE + ((0x275)<<1)))
#define INV7_CS_6           (*(volatile int *)(CS2BASE + ((0x276)<<1)))
#define INV7_CS_7           (*(volatile int *)(CS2BASE + ((0x277)<<1)))

#define CS2_TEST_SEND    	(*(volatile int *)(CS2BASE + 0x20000))

#define	CS3_TEST_T1			(*(volatile int *)(CS3BASE + 0x0))
#define	CS3_TEST_T2			(*(volatile int *)(CS3BASE + 0x2))

#define	CS4_TEST_T1			(*(volatile int *)(CS4BASE + 0x0))
#define	CS4_TEST_T2			(*(volatile int *)(CS4BASE + 0x2))


// PWM Master/Slave
#define PWM_MASTER  0
#define PWM_SLAVE  1

//ADC
#define Mode_12bit	0x0FFF
#define Mode_16bit	0xFFFF

extern void delaycc(float time);
extern unsigned short cnt_delay;

// Switchcing frequency
extern double Fsw;
extern double Fsamp;
extern double Tsamp;
extern double INV_Tsamp;
extern Uint16 maxCount_ePWM;

//DUTY OFF
extern void DUTY_OFF(void);

//Init Parameters
extern void InitParameters(void);
extern void InitController(void);
extern void Current_Transform(void);

extern void ResetINV(void);

extern void INV_Process(void);

//test

extern double half_Vdc;
extern double INV_Vdc;

extern double test_f;
extern float test_fault_a, test_fault_b, test_fault_c;
extern double test_theta;

extern int SPI_TEST0, SPI_TEST1, SPI_TEST2, SPI_TEST3, SPI_TEST4;

extern int Dout1;
extern int Dout2;
extern int Dout3;
extern int FanCon;

extern long reset_inv_num;
extern int reset_inv_waiting;

// w5300
extern uint8 recv_buf[200];
extern uint8 send_buf[200];
extern unsigned int Kp_H;
extern unsigned int Kp_L;
extern unsigned int Ki_H;
extern unsigned int Ki_L;
extern unsigned long Kp_ulong;
extern unsigned long Ki_ulong;
extern double default_Kp;
extern double default_Ki;
extern double Kp;
extern double Ki;
extern int test3;
extern int write_info;
extern int read_info;
extern int check_header_flag;
extern int W5300_MODE;
extern int recv_cnt;
extern uint32 recv_len; // it should be defined within uint32 !!! do not use int !!!
extern uint32 send_len; // it should be defined within uint32 !!! do not use int !!!
extern uint8 ip_set[4];                   // for setting SIP register
extern uint8 gw_set[4];                     // for setting GAR register
extern uint8 sn_set[4];                     // for setting SUBR register
extern uint8 mac_set[6]; 	   // for setting SHAR register
extern uint8 tx_mem_conf[8];          // for setting TMSR regsiter
extern uint8 rx_mem_conf[8];          // for setting RMSR regsiter

// data stack
extern unsigned int current_reference[16]; // H, L * 8
extern unsigned int voltage_reference[16]; // H, L * 8
extern unsigned long current_sen_debug[16];
extern float current_ref[8];
extern float current_sen[8];
extern float current_ref_set[8];
extern int sen_mode;
extern unsigned int UDP_data[32];
extern unsigned int INV_status[4];
extern unsigned int INV_data_buf[16];
//extern bool current_fault_buf[8];
//extern bool voltage_fault_buf[8];
extern int disconnect_cnt;

extern bool mode_changed;
extern int using_inv_num;
extern int reset_inv_list[8]; // 0 : need reset, 1 : reset done, 2~5 : warning
extern int reset_inv_total_cnt;

// Inverter Parameter
typedef struct _INV_
{
	//Motor parameter
	int 	Pole, PolePair;
	double 	InvPolePair;
	double 	Rs, Ls, INV_Ls, Ke, Lds, Lqs, LAMpm, INV_LAMpm, INV_Ls_Tsw, Ls_Fs;
	double 	Idss, Iqss, Idse, Iqse;
	double 	Thetar, Thetarm, ThetaAdv, ThetaOffset;
	double 	Wr, Wrm, Wrpm;


	//current controller
	double   R_comp,L_comp;
	double	Idse_ref, Iqse_ref ;
	double 	Idse_ref_tmp, Iqse_ref_tmp ;
	double	Idss_ref, Iqss_ref ;
	double	Idse_ref_set, Iqse_ref_set ;
	double   Ias_ref, Ibs_ref, Ics_ref;
	double   Idse_old, Iqse_old;
	double   sinThetar, cosThetar, Theta_sq;

	double 	Ia, Ib, Ic;

	double	Err_Idse, Err_Iqse;
	double 	Idse_integ,Iqse_integ;
	double	Kpd, Kpq, Kad, Kaq, Kid_T, Kiq_T;

	double  	Vdse, Vqse;
	double   Vdse_ref, Vqse_ref;
	double   Vdse_ref_fb, Vqse_ref_fb;
	double   Vdse_ref_ff, Vqse_ref_ff;
	double   Vdss_ref, Vqss_ref, Vdss_ref_old, Vqss_ref_old;
	double   Vdse_ref_set, Vqse_ref_set;
	double   Vdss_ref_set, Vqss_ref_set;
	double   Vas_ref, Vbs_ref, Vcs_ref;
	double   Vas, Vbs, Vcs;
	double   Vdss, Vqss;
	double   Van_ref_set, Vbn_ref_set, Vcn_ref_set;
	double   Vdqse_ref;
	double   Vdc;

	double	Vdse_ref_lim,Vqse_ref_lim;
	double	Vdse_ref_set_old,Vqse_ref_set_old;
	double	Vdss_ref_set_old,Vqss_ref_set_old;

	double 	Vdse_anti, Vqse_anti;

	double	Van_ref, Vbn_ref, Vcn_ref;

	double	alpha, Wc_cc, Fcc;
	double	Idqse_ref, Te_real;

	double 	Rv;
	double	Vmax, Vmin, Vmid, Vsn, Vsn_max, Vsn_min;
	double   Thetar_num;

	unsigned int		CompA, CompB, CompC;


	IIR2 Vdse_ref_NCF, Vqse_ref_NCF;
} INV_;
extern INV_ INV;

#define OVERALL_MODE_INIT 1
#define OVERALL_MODE_INV_TEST 2
#define OVERALL_MODE_IDLE 3
#define OVERALL_MODE_RUN 4
#define OVERALL_MODE_SAFETURNOFF 6
#define OVERALL_MODE_INVRESET 7

#define MODE_STATUS_CHECKING 1
#define MODE_STATUS_OK 2
#define MODE_STATUS_CON_ERROR 3
#define MODE_STATUS_CON_LOST 4
#define MODE_STATUS_SUB_CON_ERROR 5
#define MODE_STATUS_SUB_CON_LOST 6
#define MODE_STATUS_SUP_ERROR 7
#define MODE_STATUS_ERROR 8
#define MODE_STATUS_INV_FAULT 9

#define CC_IDLE_MODE_ZERO 1
#define CC_IDLE_MODE_KEEP 2 // keep the last current references

// Flags
typedef struct 	_FLAGS_
{
	int OverallMode;
	int ModeStatus;
	int Ready;
	int	INV_Run;
	int CC_mode;
	int CCIdleMode;
	int Fault;
	bool init_charge_done;
} FLAG_;
extern FLAG_ Flag;

extern void InitFlags(void);

#endif
