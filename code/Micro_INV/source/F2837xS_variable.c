#include "F2837xS_variable.h"
#include "Filter.h"
#include "comp.h"

#define ADCb_fix_ratio 0.95

//Switching frequency
//double Fsw = 16e3;
float Fsw = 10e3;

float Ih_ref_CC = 0.;
float d_ext = 0.;
float Ih_ref_amp = 1.;
float Ih_ref_offset = 0.;
float Ih_ref_w = 31.4159;
float Ih_ref_theta = 0.;
float Ih_ref = 0.;
float Ih_ref_old = 0.;
float V_ff = 0.;
int disconnect_cnt = 0;
int checksum_fail_cnt;
unsigned int temp_sum_h=0, temp_sum_l=0;

float Ia_present = 0.;
float Ib_present = 0.;
float Ic_present = 0.;
float present_current_ratio = 0.5;
//float present_current_ratio = 1.;

int PWM_style = UNIPOLAR_SV;
Uint16 maxCount_ePWM = 0.;
Uint16 maxCount_ePWM_safe = 0.;
Uint16 minCount_ePWM_safe = 0.;
float Fsamp = 10e3;
float Tsamp = 0.;
float INV_Tsamp = 0.;
float half_Vdc=0.;
float INV_Vdc=0. ;

float test_f=0;
float test_fault_a=0, test_fault_b=0, test_fault_c=0;
float test_theta=0;
unsigned short cnt_delay;

unsigned int SPI_test=0;
unsigned int SPI_test1=0;
unsigned int SPI_test2=0;

bool SPI_DAT_FILL = 0;
unsigned int SPI_data_RX[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
unsigned int SPI_data_TX[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int test_spi_a = 0, test_spi_b = 0, test_spi_c = 0, test_spi_d = 0;

int input_relay_on = 1;

float iden_duty = 0.25;

/* DAC */
int *da[4] = {0, 0, 0, 0};
int	 da_type[4] = {0, 0, 0, 0}, da_data[4] ={0,0,0,0};

float da_scale[4] = {5., 5., 5., 5.}, da_mid[4] = {0., 0., 0., 0.}, da_temp[4] = {0., 0., 0., 0.};
int DacOffset=0;

int fault_cnt = 0;
unsigned long temp_sum = 0;

int debug_mode = 0;

INV_ INV;
FLAG_ Flag;
SpdObs_ SpdObs;

// Scale & Offset ADCA
float ScaleAin_adc_A[3] = {
							100. * 3.3 * 2. * 5.1 / 16. / 65536.,		//ADCINA0 (INVa_shunt_ADC_P/N) : SOC0
							100. * 3.3 * 2. * 5.1 / 16. / 65536.,		//ADCINA1 (INVb_shunt_ADC_P/N) : SOC1
							100. * 3.3 * 2. * 5.1 / 16. / 65536.		//ADCINA2 (INVc_shunt_ADC_P/N) : SOC2
						 };
long OffsetAin_adc_A[3] = {
							0.,		//ADCINA0 (INVa_shunt_ADC_P/N) : SOC0
							0.,		//ADCINA1 (INVb_shunt_ADC_P/N) : SOC1
							0.,		//ADCINA2 (INVc_shunt_ADC_P/N) : SOC2
						  };

float ScaleAin_adc_B[5] = {
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
	Flag.CC_mode  = 1; // follow reference given by the distribution board
	Flag.CurrentFault = false;
	Flag.VoltageFault = false;
	Flag.DTS = false;
	Flag.ZCC = false;
}

void InitParameters(void)
{
	INV.Pole = 8.;
	INV.PolePair = INV.Pole * 0.5;
	INV.InvPolePair = 1./INV.PolePair;

	//INV.Ls = 0.0266;
	//INV.Ls = 0.01; // real value
	INV.Ls = 0.005; // for control
	//INV.Rs = 0.2; // real value
	INV.Rs = 0.5; // for control
	INV.INV_Ls = 1./INV.Ls;
	INV.INV_Ls_Tsw=INV.INV_Ls * Tsamp;
	INV.Lds = INV.Ls;
	INV.Lqs = INV.Ls;
	INV.Ls_Fs= INV.Ls * Fsw;
	INV.FaultLevel = 17.;

	INV.Ke = 0.263;
	INV.LAMpm = INV.Ke;
	INV.INV_LAMpm = 1./INV.LAMpm;

	INV.Wr = 0.;
	INV.Wrm = 0.;
	INV.Wrpm = 0.;
	INV.ThetaOffset = 0.;
	INV.Thetar = 0.;
	INV.Thetar_num = 0.;

	INV.ZCC_current = 1.;
	INV.ZCC_current_INV = 1. / INV.ZCC_current;
	INV.ZCC_power = 0.5;
	INV.DB_cnt = 300;

	INV.Fcc = 400.;
	//INV.Fcc = 1000.;

	INV.Wc_cc = INV.Fcc * 2 * PI;
	INV.Kph = INV.Ls * INV.Wc_cc;
	INV.Kih_T = INV.Rs * INV.Wc_cc * Tsamp;
	INV.Kah = 1 / INV.Kph;
}
