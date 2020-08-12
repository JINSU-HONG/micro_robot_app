#ifndef VARIABLE_H
#define VARIABLE_H

#include "F28x_Project.h"
#include "comp.h"
#include "Filter.h"

//system setting
#define SYS_CLK			((float)200e6)
#define SYS_CLK_HALF	((float)100e6)
#define SYS_CLK_PRD		((float)5.0e-9)

#define UNIPOLAR_SV 0
#define UNIPOLAR_DPWM 1

#define INV_DEADTIME 2e-6

extern void delaycc(float time);
extern unsigned short cnt_delay;

#define RELAY_ON()	GpioDataRegs.GPBSET.bit.GPIO43 	= 0x1
#define RELAY_OFF()	GpioDataRegs.GPBCLEAR.bit.GPIO43 = 0x1


#define DOUT3_ON()	GpioDataRegs.GPASET.bit.GPIO19 	= 0x1
#define DOUT3_OFF()	GpioDataRegs.GPACLEAR.bit.GPIO19 = 0x1

// PWM Master/Slave
#define PWM_MASTER  0
#define PWM_SLAVE  1

//ADC
#define Mode_12bit	0x0FFF
#define Mode_16bit	0xFFFF


// Switchcing frequency
extern float Fsw;
extern float Fsamp;
extern float Tsamp;
extern float INV_Tsamp;
extern Uint16 maxCount_ePWM;
extern Uint16 maxCount_ePWM_safe;
extern Uint16 minCount_ePWM_safe;

//for ADC result calculation
extern float ScaleAin_adc_A[3];
extern long OffsetAin_adc_A[3];

extern float ScaleAin_adc_B[5];
extern long OffsetAin_adc_B[5];

//DUTY OFF
extern void DUTY_OFF(void);

//Init Parameters
extern void InitParameters(void);
extern void InitController(void);

//test
extern int PWM_style;
extern float half_Vdc;
extern float INV_Vdc;
extern float Ih_ref_CC;
extern float d_ext;
extern float Ih_ref_amp;
extern float Ih_ref_offset;
extern float Ih_ref_w;
extern float Ih_ref_theta;
extern float Ih_ref;
extern float V_ff;
extern float Ih_ref_old;
extern int disconnect_cnt;
extern int checksum_fail_cnt;
extern unsigned int temp_sum_h, temp_sum_l;

extern float Ia_present;
extern float Ib_present;
extern float Ic_present;
extern float present_current_ratio;

extern float test_f;
extern float test_fault_a,test_fault_b,test_fault_c;
extern float test_theta;
extern int test_spi_a, test_spi_b, test_spi_c, test_spi_d;

extern bool SPI_DAT_FILL;
extern unsigned int SPI_test, SPI_test1, SPI_test2;
extern unsigned int SPI_data_TX[16];
extern unsigned int SPI_data_RX[16];

extern int fault_cnt;
extern unsigned long temp_sum;

extern int input_relay_on;

extern float iden_duty;

extern int debug_mode;

// Inverter Parameter
typedef struct _INV_
{
	//Motor parameter
	int 	Pole, PolePair;
	float 	InvPolePair;
	float 	Rs, Ls, INV_Ls, Ke, Lds, Lqs, LAMpm, INV_LAMpm, INV_Ls_Tsw, Ls_Fs;
	float 	Idss, Iqss, Idse, Iqse;
	float 	Thetar, Thetarm, ThetaAdv, ThetaOffset;
	float 	Wr, Wrm, Wrpm;
	float	Ls_iden;
	int		iden_cnt;
	float	iden_Vdc;
	float 	iden_duty;
	float	FaultLevel;

	//current controller
	float   R_comp,L_comp;
	float	Idse_ref, Iqse_ref ;
	float 	Idse_ref_tmp, Iqse_ref_tmp ;
	float	Idss_ref, Iqss_ref ;
	float	Idse_ref_set, Iqse_ref_set ;
	float   Ias_ref, Ibs_ref, Ics_ref;
	float   Idse_old, Iqse_old;
	float   sinThetar, cosThetar, Theta_sq;

	float 	Ia, Ib, Ic;


	float  Err_Ih, Ih_integ;
	float	Kph, Kah, Kih_T;
	float	Vhp, Vhm;
	float  Ih, Ih_ref;
	float  Vh_ref_ff, Vh_ref_fb, Vh_ref, Vh_ref_set, Vh_anti;

	int		CompP, CompM;
	int		CompP_DB, CompM_DB;
	float	ZCC_current;
	float	ZCC_current_INV;
	float	ZCC_power;
	int		DB_cnt;
	int		clear_integ_cnt;

	float	Err_Idse, Err_Iqse;
	float 	Idse_integ,Iqse_integ;
	float	Kpd, Kpq, Kad, Kaq, Kid_T, Kiq_T;
	float  Kp, Ki; // micro robot
	float  d_integ; // micro robot
	float  d_limit; // micro robot

	float  	Vdse, Vqse;
	float   Vdse_ref, Vqse_ref;
	float   Vdse_ref_fb, Vqse_ref_fb;
	float   Vdse_ref_ff, Vqse_ref_ff;
	float   Vdss_ref, Vqss_ref, Vdss_ref_old, Vqss_ref_old;
	float   Vdse_ref_set, Vqse_ref_set;
	float   Vdss_ref_set, Vqss_ref_set;
	float   Vas_ref, Vbs_ref, Vcs_ref;
	float   Vas, Vbs, Vcs;
	float   Vdss, Vqss;
	float   Van_ref_set, Vbn_ref_set, Vcn_ref_set;
	float   Vdqse_ref;
	float   Vdc;

	float	Vdse_ref_lim,Vqse_ref_lim;
	float	Vdse_ref_set_old,Vqse_ref_set_old;
	float	Vdss_ref_set_old,Vqss_ref_set_old;

	float 	Vdse_anti, Vqse_anti;

	float	Van_ref, Vbn_ref, Vcn_ref;

	float	alpha, Wc_cc, Fcc;
	float	Idqse_ref, Te_real;

	float 	Rv;
	float	Vmax, Vmin, Vmid, Vsn, Vsn_max, Vsn_min;
	float   Thetar_num;

	unsigned int		CompA, CompB, CompC;

	IIR2 Vdse_ref_NCF, Vqse_ref_NCF;
} INV_;
extern INV_ INV;

//Speed Observer
typedef struct _SPD_OBS
{
    float	Theta_est,Thetar_est, Err_Theta, Err_Theta_integ;
    float	Te_est_old, Te_est, Te_ff, Tl_est;
    float	Ki_so, Kp_so, Kd_so, Wc_so;
    float	K1, K2, K3;
    float	Wrm_est_d, Wr_est, Wrm_est_old, Wrm_est;
    float	Theta_est_d;
    float	Tl_est_d;
    float	Jm, B, Inv_Jm;
} SpdObs_;
extern SpdObs_ SpdObs;

#define OVERALL_MODE_INIT 1
#define OVERALL_MODE_INV_TEST 2
#define OVERALL_MODE_IDLE 3
#define OVERALL_MODE_RUN 4
#define OVERALL_MODE_SAFETURNOFF 6

#define MODE_STATUS_CHECKING 1
#define MODE_STATUS_OK 2
#define MODE_STATUS_CON_ERROR 3
#define MODE_STATUS_CON_LOST 4
#define MODE_STATUS_SUB_CON_ERROR 5
#define MODE_STATUS_SUB_CON_LOST 6
#define MODE_STATUS_SUP_ERROR 7
#define MODE_STATUS_ERROR 8
#define MODE_STATUS_INV_FAULT 9

// Flags
typedef struct 	_FLAGS_
{
	int OverallMode;
	int ModeStatus;
	int Ready;
	int	INV_Run;
	int CC_mode;
	bool CurrentFault;
	bool VoltageFault;
	bool DTS;
	bool ZCC;
} FLAG_;
extern FLAG_ Flag;

extern void InitFlags(void);

#endif
