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
extern double Fsw;
extern double Fsamp;
extern double Tsamp;
extern double INV_Tsamp;
extern Uint16 maxCount_ePWM;
extern Uint16 maxCount_ePWM_safe;
extern Uint16 minCount_ePWM_safe;

//for ADC result calculation
extern double ScaleAin_adc_A[3];
extern long OffsetAin_adc_A[3];

extern double ScaleAin_adc_B[5];
extern long OffsetAin_adc_B[5];

//DUTY OFF
extern void DUTY_OFF(void);

//Init Parameters
extern void InitParameters(void);
extern void InitController(void);

//test
extern int PWM_style;
extern double half_Vdc;
extern double INV_Vdc;
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
extern unsigned int temp_sum_h, temp_sum_l;

extern float Ia_present;
extern float Ib_present;
extern float Ic_present;
extern float present_current_ratio;

extern double test_f;
extern float test_fault_a,test_fault_b,test_fault_c;
extern double test_theta;
extern int test_spi_a, test_spi_b, test_spi_c, test_spi_d;

extern bool SPI_DAT_FILL;
extern unsigned int SPI_test, SPI_test1, SPI_test2;
extern unsigned long SPI_data[16];

extern int fault_cnt;
extern unsigned long temp_sum;

extern int input_relay_on;

extern double iden_duty;

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
	double	Ls_iden;
	int		iden_cnt;
	double	iden_Vdc;
	double 	iden_duty;
	double	FaultLevel;

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


	double  Err_Ih, Ih_integ;
	double	Kph, Kah, Kih_T;
	double	Vhp, Vhm;
	double  Ih, Ih_ref;
	double  Vh_ref_ff, Vh_ref_fb, Vh_ref, Vh_ref_set, Vh_anti;

	int		CompP, CompM;
	int		CompP_DB, CompM_DB;
	double	ZCC_current;
	double	ZCC_current_INV;
	double	ZCC_power;
	int		DB_cnt;
	int		clear_integ_cnt;

	double	Err_Idse, Err_Iqse;
	double 	Idse_integ,Iqse_integ;
	double	Kpd, Kpq, Kad, Kaq, Kid_T, Kiq_T;
	double  Kp, Ki; // micro robot
	double  d_integ; // micro robot
	double  d_limit; // micro robot

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

//Speed Observer
typedef struct _SPD_OBS
{
	double	Theta_est,Thetar_est, Err_Theta, Err_Theta_integ;
	double	Te_est_old, Te_est, Te_ff, Tl_est;
	double	Ki_so, Kp_so, Kd_so, Wc_so;
	double	K1, K2, K3;
	double	Wrm_est_d, Wr_est, Wrm_est_old, Wrm_est;
	double	Theta_est_d;
	double	Tl_est_d;
	double	Jm, B, Inv_Jm;
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
