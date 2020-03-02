#include "F2837xS_variable.h"
#include "Filter.h"
#include "comp.h"

#define ADCb_fix_ratio 0.95

//Switching frequency
double Fsw = 5e3;
double Fsamp = 5e3;
long reset_inv_num = -5e4; // count to 0 to wait 10 sec; 10 * Fsw
int reset_inv_waiting = 0;

Uint16 maxCount_ePWM = 0.;
double Tsamp = 0.;
double INV_Tsamp = 0.;
double half_Vdc=0.;
double INV_Vdc=0. ;

double test_f=0;
float test_fault_a=0, test_fault_b=0, test_fault_c=0;
double test_theta=0;
unsigned short cnt_delay;

int SPI_TEST0=0, SPI_TEST1=0, SPI_TEST2=0, SPI_TEST3=0, SPI_TEST4=0;

int Dout1=0;
int Dout2=0;
int Dout3=1;
int FanCon=1;

//w5300
uint8 recv_buf[200] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint8 send_buf[200] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
unsigned int Kp_H = 0;
unsigned int Kp_L = 0;
unsigned int Ki_H = 0;
unsigned int Ki_L = 0;
unsigned long Kp_ulong = 0;
unsigned long Ki_ulong = 0;
double default_Kp = 1.;
double default_Ki = 0.015;
double Kp = 1.;
double Ki = 0.015;
int test3 = 0;
int check_header_flag = 0;
int write_info=0;
int read_info=0;
int W5300_MODE = W5300_MODE_UDP;
int recv_cnt=0;
uint32 recv_len=0; // it should be defined within uint32 !!! do not use int !!!
uint32 send_len=0; // it should be defined within uint32 !!! do not use int !!!
uint8 ip_set[4] = {192, 168, 100, 200};                   // for setting SIP register
uint8 gw_set[4] = {192, 168, 100, 1};                     // for setting GAR register
uint8 sn_set[4] = {255,255,255,0};                     // for setting SUBR register
uint8 mac_set[6] = {0x00,0x08,0xDC,0x00,0x6F,0xC8}; 	   // for setting SHAR register
uint8 tx_mem_conf[8] = {32,16,16,0,0,0,0,0};          // for setting TMSR regsiter
uint8 rx_mem_conf[8] = {32,16,16,0,0,0,0,0};          // for setting RMSR regsiter

// data stack
unsigned int current_reference[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // H, L * 8
unsigned int voltage_reference[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // H, L * 8
unsigned int UDP_data[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
unsigned int INV_status[4] = {0, 0, 0, 0};
unsigned int INV_data_buf[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int disconnect_cnt = 0;
bool mode_changed = true;
//int using_inv_num = 1;
//int using_inv_num = 4;
int using_inv_num = 8;
int reset_inv_list[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int reset_inv_total_cnt = 0;

/* DAC */
int *da[4] = {0, 0, 0, 0};
int	 da_type[4] = {0, 0, 0, 0}, da_data[4] ={0,0,0,0};

float da_scale[4] = {5., 5., 5., 5.}, da_mid[4] = {0., 0., 0., 0.}, da_temp[4] = {0., 0., 0., 0.};
int DacOffset=0;


INV_ INV;
FLAG_ Flag;

// Scale & Offset ADCA
double ScaleAin_adc_A[3] = {
							100. * 3.3 * 2. * 5.1 / 16. / 65536.,		//ADCINA0 (INVa_shunt_ADC_P/N) : SOC0
							100. * 3.3 * 2. * 5.1 / 16. / 65536.,		//ADCINA1 (INVb_shunt_ADC_P/N) : SOC1
							100. * 3.3 * 2. * 5.1 / 16. / 65536.		//ADCINA2 (INVc_shunt_ADC_P/N) : SOC2
						 };
long OffsetAin_adc_A[3] = {
							0.,		//ADCINA0 (INVa_shunt_ADC_P/N) : SOC0
							0.,		//ADCINA1 (INVb_shunt_ADC_P/N) : SOC1
							0.,		//ADCINA2 (INVc_shunt_ADC_P/N) : SOC2
						  };

double ScaleAin_adc_B[5] = {
							1.,		//ADCINB0 (DSP_AD2) : SOC0
							(33200*4+604.)/(604.)/4096 * 3.3 * ADCb_fix_ratio,		//ADCINB2 (Vdc_ADC) : SOC1
							1.,		//ADCINB3 (Filt_a_AD) : SOC2
							1.,		//ADCINB4 (Filt_b_AD) : SOC3
							1.,		//ADCINB5 (Filt_c_AD) : SOC4
						 };
long OffsetAin_adc_B[5] = {
							0.,		//ADCINB0 (DSP_AD2) : SOC0
							0.,		//ADCINB2 (Vdc_ADC) : SOC1
							0.,		//ADCINB3 (Filt_a_AD) : SOC2
							0.,		//ADCINB4 (Filt_b_AD) : SOC3
							0.,		//ADCINB5 (Filt_c_AD) : SOC4
						  };

void DUTY_OFF(void)
{
	EPwm2Regs.CMPA.bit.CMPA = 0;
	EPwm6Regs.CMPA.bit.CMPA = 0;
	EPwm7Regs.CMPA.bit.CMPA = 0;
}

void delaycc(float time)
{
	cnt_delay=(unsigned short)(time*SYS_CLK);
	asm(" RPT @_cnt_delay	|| NOP ");
	asm(" NOP		");
}

void InitFlags(void)
{
	Flag.OverallMode = OVERALL_MODE_INIT;
	Flag.ModeStatus = MODE_STATUS_CHECKING;
	Flag.Ready    = 0;
	Flag.INV_Run  = 0;
	Flag.CC_mode  = 0;
	Flag.CCIdleMode = CC_IDLE_MODE_ZERO;
	Flag.Fault    = 0;
	Flag.init_charge_done = false;
}

void InitParameters(void)
{
	INV.Pole = 8.;
	INV.PolePair = INV.Pole * 0.5;
	INV.InvPolePair = 1./INV.PolePair;

	INV.Rs = 12;
	INV.Ls = 0.0266;
	INV.INV_Ls = 1./INV.Ls;
	INV.INV_Ls_Tsw=INV.INV_Ls * Tsamp;
	INV.Lds = INV.Ls;
	INV.Lqs = INV.Ls;
	INV.Ls_Fs= INV.Ls * Fsw;

	INV.Ke = 0.263;
	INV.LAMpm = INV.Ke;
	INV.INV_LAMpm = 1./INV.LAMpm;

	INV.Wr = 0.;
	INV.Wrm = 0.;
	INV.Wrpm = 0.;
	INV.ThetaOffset = 0.;
	INV.Thetar = 0.;
	INV.Thetar_num = 0.;


	INV.Fcc = 300.;
	INV.Wc_cc = 2. * PI * INV.Fcc;
}

void InitController(void)
{
	//////////////////// INVERTER ////////////////////
	INV.Wc_cc = INV.Fcc * 2 * PI;

	INV.Kpd = INV.Ls * INV.Wc_cc;
	INV.Kpq = INV.Ls * INV.Wc_cc;

	INV.Kid_T = INV.Rs * INV.Wc_cc * Tsamp;
	INV.Kiq_T = INV.Rs * INV.Wc_cc * Tsamp;

	INV.Kad = 1 / INV.Kpd;
	INV.Kaq = 1 / INV.Kpq;
}
