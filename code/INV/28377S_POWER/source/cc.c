#include "F2837xS_device.h"
#include "F2837xS_Examples.h"
#include "cc.h"
#include "F2837xS_da.h"
#include <math.h>
#include "Filter.h"
#include "comp.h"

int cc_cnt = 0;
int spi_cnt = 0;
int sync_cnt = 0;
int test_cnt = 0;
int test_cnt2 = 0;
int test_val1 = 0;
int test_val2 = 0;
int isSwitchOn = false;

int gptest = 0;

long sync_count = 0;
long sync_count2 = 0;
long sync_count3 = 0;

long ccTimer0start;
long spiTimer0start;
float ccTime;
float spiTime;
float test_d;
float temp_float = 0.;
int pin_pin = 1;

int DIST_mode = OVERALL_MODE_INIT;
int DIST_status = MODE_STATUS_CHECKING;

double Idse_ref_CC = 0., Iqse_ref_CC = 0.;

void ready_SPI(float Ia, float Vdc);
void convert_float_to_binary(float* float_data, unsigned long* int_data_h,
		unsigned long* int_data_l);
void convert_binary_to_float(float* float_data, int int_data_h, int int_data_l);

__interrupt void SPI_RXINT(void) {
	spi_cnt++;
	spiTimer0start = ReadCpuTimer1Counter();
	disconnect_cnt = 0;

	SPI_data[0] = SpibRegs.SPIRXBUF;
	SPI_data[1] = SpibRegs.SPIRXBUF;
	SPI_data[2] = SpibRegs.SPIRXBUF;
	SPI_data[3] = SpibRegs.SPIRXBUF;
	SPI_data[4] = SpibRegs.SPIRXBUF;
	delaycc(5e-6); // safe delay to move data; error occured for 1e-6 delay.

	SPI_DAT_FILL = false;

	//test_fault_a = SPI_data[0];
//	test_fault_b = SPI_data[1];
	//test_fault_c = SPI_data[2];

	DIST_mode = (SPI_data[0] & 0x00F0) >> 4;
	DIST_status = SPI_data[0] & 0x000F;

	if (Flag.OverallMode != DIST_mode) {
		Flag.OverallMode = DIST_mode;
		if (Flag.ModeStatus == MODE_STATUS_CHECKING
				|| Flag.ModeStatus == MODE_STATUS_OK) {
			Flag.ModeStatus = MODE_STATUS_CHECKING;
		}
		if (DIST_mode == OVERALL_MODE_INIT) {
			Flag.CC_mode = 1;
			Flag.Ready = 0;
			Flag.CurrentFault = false;
			Flag.VoltageFault = false;
		} else if (DIST_mode == OVERALL_MODE_INV_TEST) {
			Flag.Ready = 1; // set to 0 when coil test is finished
			Flag.CC_mode = 2; // set to 1 when coil test is finished

			INV.Ls_iden = 0.;
			INV.iden_cnt = 0;
			INV.iden_Vdc = 0.;
			INV.iden_duty = iden_duty;
			Flag.ModeStatus = MODE_STATUS_CHECKING;
		} else if (DIST_mode == OVERALL_MODE_IDLE
				|| DIST_mode == OVERALL_MODE_RUN) {
			if (Flag.ModeStatus != MODE_STATUS_INV_FAULT) {
				Flag.Ready = 1;
				Flag.CC_mode = 1;
				Flag.ModeStatus = MODE_STATUS_OK;
			}
		} else if (DIST_mode == OVERALL_MODE_SAFETURNOFF) {
			Flag.OverallMode = OVERALL_MODE_SAFETURNOFF;
			Ih_ref = 0.;
			input_relay_on = 0;
		} else {
			Flag.OverallMode = OVERALL_MODE_INIT;
			Flag.ModeStatus = MODE_STATUS_CHECKING;
			Flag.CurrentFault = false;
			Flag.VoltageFault = false;
			Flag.Ready = 0;
			Ih_ref = 0.;
		}
	}

	if (Flag.OverallMode == OVERALL_MODE_INIT && SPI_data[1] != 0) {
		// get Kp, Ki from PC
		temp_sum = SPI_data[1] * 256 * 256;
		temp_sum = temp_sum + SPI_data[2];
		temp_float = *((float *) (&temp_sum));
		if (temp_float > 0 || temp_float < 1000) {
			INV.Kph = temp_float;
		}
		temp_sum = SPI_data[3] * 256 * 256;
		temp_sum = temp_sum + SPI_data[4];
		temp_float = *((float *) (&temp_sum));
		if (temp_float > 0 || temp_float < 100) {
			INV.Kih_T = temp_float;
		}
	}

	if (Flag.OverallMode == OVERALL_MODE_IDLE
			|| Flag.OverallMode == OVERALL_MODE_RUN) {
		//convert_binary_to_float(&Ih_ref, SPI_data[1], SPI_data[2]); // update current reference
		temp_sum = SPI_data[1] * 256 * 256;
		temp_sum = temp_sum + SPI_data[2];
		temp_float = *((float *) (&temp_sum));
		if (temp_float != 0) { // 0 might be recv error
			Ih_ref = temp_float;
		} else if (temp_float > INV.FaultLevel) {
			// Ih_ref = Ih_ref; // pass
		}
		//if (Ih_ref > 4.5) Ih_ref = 0;

		//convert_binary_to_float(&V_ff, SPI_data[3], SPI_data[4]); // update voltage feedforward
		//temp_sum = ((unsigned long)(SPI_data[3])) << 16 + (unsigned long)(SPI_data[4]);
		//V_ff = *((float *)(&temp_sum));
	}

	// clear SPI BUF for safe operation
	SpibRegs.SPIFFRX.bit.RXFIFORESET = 0;
	SpibRegs.SPIFFTX.bit.TXFIFO = 0;
	delaycc(1e-6);
	SpibRegs.SPIFFRX.bit.RXFIFORESET = 1;
	SpibRegs.SPIFFTX.bit.TXFIFO = 1;
	delaycc(1e-6);

	if (Flag.OverallMode == OVERALL_MODE_INIT) {
		Flag.CC_mode = 1;
		Flag.Ready = 0;
		Flag.CurrentFault = false;
		Flag.VoltageFault = false;
		if (SPI_DAT_FILL == false) {
			Flag.ModeStatus = MODE_STATUS_OK;
			SpibRegs.SPITXBUF = 0xAAAA; // connection test
			SpibRegs.SPITXBUF = 0x5555; // connection test
			SpibRegs.SPITXBUF = 0x0000; // dummy
			SpibRegs.SPITXBUF = 0x0000; // dummy
			SpibRegs.SPITXBUF = 0x0000; // dummy
			SPI_DAT_FILL = true;
		}
		SwitchOff();
		ResetHINV();
	} else if (Flag.OverallMode == OVERALL_MODE_INV_TEST) {
		// do current test
		if (SPI_DAT_FILL == false) {
			if (Flag.CurrentFault) {
				SpibRegs.SPITXBUF = 0x1009; // current fault / voltage fault / dummy / inv status
			} else if (Flag.VoltageFault) {
				SpibRegs.SPITXBUF = 0x0109; // current fault / voltage fault / dummy / inv status
			} else {
				SpibRegs.SPITXBUF = Flag.ModeStatus; // current fault / voltage fault / dummy / inv status
			}
			//SpibRegs.SPITXBUF = 0x0002;
			SpibRegs.SPITXBUF = 0x0000; // dummy
			SpibRegs.SPITXBUF = 0x0000; // dummy
			SpibRegs.SPITXBUF = 0x0000; // dummy
			SpibRegs.SPITXBUF = 0x0000; // dummy
			SPI_DAT_FILL = true;
		}
	} else if (Flag.OverallMode == OVERALL_MODE_IDLE
			|| Flag.OverallMode == OVERALL_MODE_RUN) { // follow given current reference
		if (Flag.ModeStatus == MODE_STATUS_CHECKING
				|| Flag.ModeStatus == MODE_STATUS_OK) {
			Flag.ModeStatus = MODE_STATUS_OK;
		}

		// fill SPI with current data
		if (!SPI_DAT_FILL) {
			//ready_SPI(INV.Ib, INV.Vdc); // fill SPI TX with current data
			temp_sum = *(unsigned long *) (&(INV.Ih));
			temp_sum_h = temp_sum / 256 / 256;
			temp_sum_l = temp_sum - temp_sum_h * 256 * 256;

			//SpibRegs.SPITXBUF = ((Flag.CurrentFault)?0x1000:0) + ((Flag.VoltageFault)?0x0100:0) + (Flag.ModeStatus);
			if (Flag.CurrentFault) {
				SpibRegs.SPITXBUF = 0x1009;
			} else if (Flag.VoltageFault) {
				SpibRegs.SPITXBUF = 0x0109;
			} else {
				SpibRegs.SPITXBUF = Flag.ModeStatus;
			}
			SpibRegs.SPITXBUF = temp_sum_h;
			SpibRegs.SPITXBUF = temp_sum_l;
			SpibRegs.SPITXBUF = 0x0000; // dummy
			SpibRegs.SPITXBUF = 0x0000; // dummy

			SPI_DAT_FILL = true;
		}
		//Current_Transform();
	}

	spiTime = (spiTimer0start - ReadCpuTimer1Counter()) * SYS_CLK_PRD;

	SpibRegs.SPIFFRX.bit.RXFFINTCLR = 1;
	//SpibRegs.SPIFFRX.bit.RXFIFORESET=1;

	PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;
}
__interrupt void cc(void) {
	// single sampling
	cc_cnt++;
	ccTimer0start = ReadCpuTimer1Counter();

	//disconnect_cnt++;
	if (disconnect_cnt > 100) {
		Flag.OverallMode = OVERALL_MODE_INIT;
		Flag.ModeStatus = MODE_STATUS_OK;
		Flag.Ready = 0;
		Ih_ref = 0.;
	}

	AD_Process();

	INV.Vdc = ScaleAin_adc_B[1]
			* (double) (((long) AdcbResultRegs.ADCRESULT1)
					& Mode_12bit - OffsetAin_adc_B[1]); // ADCA_SOC1 : (Vdc_ADC)

	if (test_fault_a < INV.Vdc)
		test_fault_a = INV.Vdc;

	if (INV.Vdc > 500) {
		Flag.Ready = 0;
		Flag.ModeStatus = MODE_STATUS_INV_FAULT;
		Flag.VoltageFault = true;
		fault_cnt = 44;
	}

	half_Vdc = 0.5 * INV.Vdc;
	INV_Vdc = 1 / INV.Vdc;

	if (INV.Vdc > 280 && input_relay_on == 1) {
		RELAY_ON();
	} else if (input_relay_on == 0) {
		RELAY_OFF();
	}

//		Ia_present = ScaleAin_adc_A[0]*(double)((int)(AdcaResultRegs.ADCRESULT0&Mode_16bit) - (int)OffsetAin_adc_A[0] );   // ADCA_SOC0 : INVa_shunt_ADC_P/N
	Ib_present = ScaleAin_adc_A[1]
			* (double) ((int) (AdcaResultRegs.ADCRESULT1 & Mode_16bit)
					- (int) OffsetAin_adc_A[1]); // ADCA_SOC1 : INVb_shunt_ADC_P/N
	Ic_present = ScaleAin_adc_A[2]
			* (double) ((int) (AdcaResultRegs.ADCRESULT2 & Mode_16bit)
					- (int) OffsetAin_adc_A[2]); // ADCA_SOC2 : INVc_shunt_ADC_P/N
	//INV.Ia = ScaleAin_adc_A[0]*(double)((int)(AdcaResultRegs.ADCRESULT0&Mode_12bit) - (int)OffsetAin_adc_A[0] );   // ADCA_SOC0 : INVa_shunt_ADC_P/N
	//INV.Ib = ScaleAin_adc_A[1]*(double)((int)(AdcaResultRegs.ADCRESULT1&Mode_12bit) - (int)OffsetAin_adc_A[1] );   // ADCA_SOC1 : INVb_shunt_ADC_P/N
	//INV.Ic = ScaleAin_adc_A[2]*(double)((int)(AdcaResultRegs.ADCRESULT2&Mode_12bit) - (int)OffsetAin_adc_A[2] );   // ADCA_SOC2 : INVc_shunt_ADC_P/N

//		INV.Ia = Ia_present * present_current_ratio + INV.Ia * (1-present_current_ratio);
//		if (Ib_present != 0) { // 0 might be error
//			INV.Ib = Ic_present * present_current_ratio + INV.Ib * (1-present_current_ratio);
//		}
//		INV.Ic = Ic_present * present_current_ratio + INV.Ic * (1-present_current_ratio);

	if (Ib_present != 0) { // 0 might be error
		INV.Ih = (Ib_present - Ic_present) / 2 * present_current_ratio
				+ INV.Ih * (1 - present_current_ratio);
	}

//		if (fabs(INV.Ia) > INV.FaultLevel) {
//			test_fault_a = INV.Ia;
//			//Flag.Ready=0;
//			Flag.ModeStatus = MODE_STATUS_INV_FAULT;
//			Flag.CurrentFault = true;
//			fault_cnt = 11;
//		}
//		if (fabs(INV.Ib) > INV.FaultLevel) {
//			test_fault_b = INV.Ib;
//			Flag.Ready=0;
//			Flag.ModeStatus = MODE_STATUS_INV_FAULT;
//			Flag.CurrentFault = true;
//			fault_cnt = 22;
//		}
//		if (fabs(INV.Ic) > INV.FaultLevel){
//			test_fault_c = INV.Ic;
//			Flag.Ready=0;
//			Flag.ModeStatus = MODE_STATUS_INV_FAULT;
//			Flag.CurrentFault = true;
//			fault_cnt = 33;
//		}

	if (fabs(INV.Ih) > INV.FaultLevel) {
		test_fault_a = INV.Ih;
		//Flag.Ready=0;
		Flag.ModeStatus = MODE_STATUS_INV_FAULT;
		Flag.CurrentFault = true;
		fault_cnt = 11;
	}

	if (Flag.OverallMode == OVERALL_MODE_INV_TEST && INV.Ls_iden == 0.) {
		INV.iden_cnt++;
		INV.iden_Vdc = (INV.iden_Vdc * (INV.iden_cnt - 1) + INV.Vdc)
				/ INV.iden_cnt;
		if (INV.Ih > 10.) {
			INV.Ls_iden = INV.iden_cnt * INV.iden_Vdc * INV.iden_duty
					* (Tsamp * 2) / INV.Ih;
			if (INV.Ls_iden > 0.001 && INV.Ls_iden < 0.1) {
				Flag.ModeStatus = MODE_STATUS_OK;
			} else {
				Flag.ModeStatus = MODE_STATUS_INV_FAULT;
			}
			INV.iden_duty = 0.;
			Flag.Ready = 0;
			Flag.CC_mode = 1;
			INV.Ih_ref = 0.;
			SwitchOff();
			ResetHINV();
		} else if (INV.iden_cnt > 1000) { // coil connection problem
			Flag.ModeStatus = MODE_STATUS_INV_FAULT;
			INV.iden_duty = 0.;
			Flag.Ready = 0;
			Flag.CC_mode = 1;
			INV.Ih_ref = 0.;
			SwitchOff();
			ResetHINV();
		}
	}

	if (Flag.Ready == 1) {
		if (Flag.CC_mode == 1) {
			SwitchOn();
			//INV.Idse_ref = Idse_ref_CC;
			//INV.Iqse_ref = Iqse_ref_CC;
			if (EPwm2Regs.TBSTS.bit.CTRDIR == TB_DOWN) {
				//INV.Ih_ref = 0.; // for test
				INV.Ih_ref = Ih_ref; // follow given reference
				HINV_Process();
			} else {
				//PwmUpdate();
			}
			HPwmUpdate();
		} else if (Flag.CC_mode == 2) {
			SwitchOn();
			if (EPwm2Regs.TBSTS.bit.CTRDIR == TB_DOWN) {
				//INV.Ih_ref = Ih_ref_CC;
				//Ih_ref_theta += Ih_ref_w * Tsamp * 2;
				//if (Ih_ref_theta > 2 * PI) Ih_ref_theta -= 2 * PI;
				//INV.Ih_ref = Ih_ref_amp * cos(Ih_ref_theta) + Ih_ref_offset;
				HINV_Process();
			} else {
				//PwmUpdate();
			}
			HPwmUpdate();
		} else {
			SwitchOff();
			ResetHINV();
			//DUTY_OFF();
		}
	} else {
		//DUTY_OFF();
		//ResetINV();

		SwitchOff();
		ResetHINV();
	}

	/*
	 } else {
	 Flag.OverallMode = OVERALL_MODE_INIT;
	 Flag.ModeStatus = MODE_STATUS_CHECKING;
	 }
	 */

	/*
	 //DAC
	 da[0] = &(INV.Ih_ref);
	 da_type[0] = 0;
	 da_scale[0] = 512.;
	 da_mid[0] = 0;

	 da[1] = &(INV.Ih_integ);
	 da_type[1] = 0;
	 da_scale[1] = 128.;
	 da_mid[1] = 0;

	 SpiDacOut();
	 */

	ccTime = (ccTimer0start - ReadCpuTimer1Counter()) * SYS_CLK_PRD;

	// Clear INT flag for this timer
	EPwm2Regs.ETCLR.bit.INT = 1;
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP3 | PIEACK_GROUP6;
}

void AD_Process(void) {
	AdcaRegs.ADCSOCPRICTL.bit.RRPOINTER = 0x10; // Roundrobbin으로 결정되지만 혹시 모르니 priority SOC0으로 reset (32)
	AdcbRegs.ADCSOCPRICTL.bit.RRPOINTER = 0x10;

	AdcaRegs.ADCSOCFRC1.all = 0x0007; //SOC0, SOC1, SOC2 forced start
	while (AdcaRegs.ADCINTFLG.bit.ADCINT1 == 0)
		; // Conversion finish 기다림.
	AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; // ADC Flag clear

	AdcbRegs.ADCSOCFRC1.all = 0x0002; //SOC1 forced start
	while (AdcbRegs.ADCINTFLG.bit.ADCINT1 == 0)
		; // Conversion finish 기다림.
	AdcbRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; // ADC Flag clear
}

void ready_SPI(float Ib, float Vdc) {
	//unsigned long Ib_h, Ib_l, Vdc_h, Vdc_l;
	unsigned long Ib_h, Ib_l;

	//convert_float_to_binary(&Vdc, &Vdc_h, &Vdc_l);
	//convert_float_to_binary(&Ib, &Ib_h, &Ib_l);
	temp_sum = *(unsigned long *) (&Ib);
	Ib_h = temp_sum / 256 / 256;
	Ib_l = temp_sum - Ib_h * 256 * 256;

	/*
	 //if (SpibRegs.SPIFFTX.bit.TXFFST != 0) {
	 SpibRegs.SPIFFTX.bit.TXFIFO = 0; // reset
	 SpibRegs.SPIFFTX.bit.TXFIFO = 1; // reset release
	 delaycc(10e-6);
	 //}

	 if (!SPI_DAT_FILL) {
	 SpibRegs.SPITXBUF = ((Flag.CurrentFault)?0x1000:0) + ((Flag.VoltageFault)?0x0100:0) + (Flag.ModeStatus);
	 SPI_DAT_FILL = true;
	 }
	 test_fault_b = Ib_h;
	 SpibRegs.SPITXBUF = Ib_h;
	 SpibRegs.SPITXBUF = Ib_l;
	 //SpibRegs.SPITXBUF = Vdc_h;
	 //SpibRegs.SPITXBUF = Vdc_l;
	 SpibRegs.SPITXBUF = 0x0000; // dummy
	 SpibRegs.SPITXBUF = 0x0000; // dummy
	 test_spi_a = Vdc_h;
	 test_spi_b = Vdc_l;
	 test_spi_c = Ib_h;
	 test_spi_d = Ib_l;
	 */

	//SpibRegs.SPIFFTX.bit.TXFIFO = 0; // reset
	//SpibRegs.SPIFFTX.bit.TXFIFO = 1; // reset release
	//delaycc(5e-6);
	if (Flag.CurrentFault) {
		SpibRegs.SPITXBUF = 0x1009;
	} else if (Flag.VoltageFault) {
		SpibRegs.SPITXBUF = 0x0109;
	} else {
		SpibRegs.SPITXBUF = Flag.ModeStatus;
	}
	//SpibRegs.SPITXBUF = ((Flag.CurrentFault)?0x1000:0) + ((Flag.VoltageFault)?0x0100:0) + (Flag.ModeStatus);
	//delaycc(1e-6);
	SpibRegs.SPITXBUF = Ib_h;
	//delaycc(1e-6);
	SpibRegs.SPITXBUF = Ib_l;
	//delaycc(1e-6);
	//SpibRegs.SPITXBUF = Vdc_h;
	//SpibRegs.SPITXBUF = Vdc_l;
	SpibRegs.SPITXBUF = 0x0000; // dummy
	//delaycc(1e-6);
	SpibRegs.SPITXBUF = 0x0000; // dummy
	//delaycc(1e-6);
}

void convert_float_to_binary(float* float_data, unsigned long* int_data_h,
		unsigned long* int_data_l) {
	*int_data_h = ((*(unsigned long*) (float_data)) & 0xFFFF0000) >> 16;
	*int_data_l = (*(unsigned long*) (float_data)) & 0xFFFF;
}
void convert_binary_to_float(float* float_data, int int_data_h, int int_data_l) {
	unsigned long sum = ((unsigned long) int_data_h) << 16 + int_data_l;
	*float_data = *((float *) (&sum));
}

void HINV_Process(void) {
	if (Flag.CC_mode == 1) {
		if (Ih_ref_old * INV.Ih_ref <= 0) { // ref zero crossing
			INV.Ih_integ = 0.;
		}
		Ih_ref_old = INV.Ih_ref;

		INV.Err_Ih = INV.Ih_ref - INV.Ih;
		INV.Ih_integ += INV.Kih_T * (INV.Err_Ih - INV.Kah * INV.Vh_anti);
		INV.Vh_ref_fb = INV.Ih_integ + INV.Kph * INV.Err_Ih;
		INV.Vh_ref_ff = 0;
		INV.Vh_ref = INV.Vh_ref_ff + INV.Vh_ref_fb;

		INV.Vh_ref_set =
				(INV.Vh_ref > half_Vdc) ?
						half_Vdc :
						((INV.Vh_ref < -half_Vdc) ? -half_Vdc : INV.Vh_ref);
		INV.Vh_anti = INV.Vh_ref - INV.Vh_ref_set;

		INV.Vhp = INV.Vh_ref_set;
		INV.Vhm = -INV.Vh_ref_set;

		if (d_ext != 0) {
			INV.Vhp = d_ext * half_Vdc;
			INV.Vhm = -d_ext * half_Vdc;
		}
	} else if (Flag.CC_mode == 2) {
		INV.Vhp = INV.iden_duty * half_Vdc;
		INV.Vhm = -INV.iden_duty * half_Vdc;
	}
	INV.CompP = (int) ((INV.Vhp + half_Vdc) * maxCount_ePWM * INV_Vdc);
	// already in safe range
	INV.CompP = (
			(INV.CompP > maxCount_ePWM_safe) ?
					maxCount_ePWM_safe :
					((INV.CompP < minCount_ePWM_safe) ?
							minCount_ePWM_safe : INV.CompP));
	INV.CompM = maxCount_ePWM - INV.CompP;

	test_cnt++;

	/*
	 if (PWM_style == UNIPOLAR_DPWM) {
	 if (d_ext > 0) {
	 //INV.CompP = INV.CompP - INV.CompM;
	 INV.CompP = maxCount_ePWM * d_ext;
	 INV.CompM = 0;
	 } else {
	 INV.CompM = maxCount_ePWM * (-d_ext);
	 INV.CompP = 0;
	 }
	 }
	 */
}

void HPwmUpdate(void) {
	if (Flag.DTS) {
		if (Flag.ZCC && (fabs(INV.Ib) < INV.ZCC_current)) {
			//INV.CompDB = INV_DEADTIME * 2. * Fsw * maxCount_ePWM * fabs(INV.Ib) / INV.ZCC_current;
			//INV.CompDB = (int)(INV_DEADTIME * 2. * Fsw * (float)maxCount_ePWM * fabs(INV.Ib)); // 1.0A
			INV.CompP_DB = (int) (INV.DB_cnt
					* pow(fabs(INV.Ib) * INV.ZCC_current_INV, INV.ZCC_power));
			INV.CompM_DB = INV.CompP_DB;
		} else {
			//INV.CompDB = (int)(INV_DEADTIME * 2. * Fsw * (float)maxCount_ePWM);
			INV.CompP_DB = INV.DB_cnt;
			INV.CompM_DB = INV.DB_cnt;
		}

		if (EPwm2Regs.TBSTS.bit.CTRDIR == TB_UP) { // on-sequence at next cc loop
			if (INV.Ib < 0) {
				INV.CompP_DB = 0;
				// keep INV.CompM_DB value
			} else {
				// keep INV.CompP_DB value
				INV.CompM_DB = 0;
			}
		} else { // off-sequence at next cc loop
			/*
			 if (INV.Ib > 0) {
			 INV.CompP_DB = 0;
			 INV.CompM_DB = -INV.CompM_DB;
			 } else {
			 INV.CompP_DB = -INV.CompP_DB;
			 INV.CompM_DB = 0;
			 }
			 */
			if (INV.Ib < 0) {
				// keep INV.CompP_DB value
				INV.CompM_DB = 0;
			} else {
				INV.CompP_DB = 0;
				// keep INV.CompM_DB value
			}

			INV.CompP += INV.CompP_DB;
			INV.CompM += INV.CompM_DB;

			INV.CompP = (
					(INV.CompP > (int) (maxCount_ePWM * 0.9)) ?
							(int) (maxCount_ePWM * 0.9) :
							((INV.CompP < 0) ? 0 : INV.CompP));
			INV.CompM = (
					(INV.CompM > (int) (maxCount_ePWM * 0.9)) ?
							(int) (maxCount_ePWM * 0.9) :
							((INV.CompM < 0) ? 0 : INV.CompM));
		}
	} else {
		INV.CompP_DB = 0;
		INV.CompM_DB = 0;
	}

	test_cnt2++;

	EPwm6Regs.CMPA.bit.CMPA = INV.CompP;
	EPwm7Regs.CMPA.bit.CMPA = INV.CompM;

	EPwm10Regs.CMPA.bit.CMPA = 2500;
}

void Current_Transform(void) {
//	INV.Thetar = BOUND_PI(INV.PP * INV.Thetarm);

	test_theta += test_f * 2 * PI * Tsamp;

	INV.cosThetar = __cos(test_theta);
	INV.sinThetar = __sin(test_theta);

	INV.Idss = (2. * INV.Ia - INV.Ib - INV.Ic) * INV_3;
	INV.Iqss = (INV.Ib - INV.Ic) * SQRT3THIRD;
	INV.Idse = INV.Idss * INV.cosThetar + INV.Iqss * INV.sinThetar;
	INV.Iqse = INV.Idss * (-INV.sinThetar) + INV.Iqss * INV.cosThetar;
}

void INV_Process(void) {
	float Iref, Ierr;
	float d, d_prop;

	//Iref = (float)(SPI_TEST_A[0] << 16 + SPI_TEST_A[1]);
	Iref = INV.Ih_ref;
	Ierr = Iref - INV.Ib;

	d_prop = Ierr * INV.Kph;
	INV.d_integ += Ierr * INV.Kih_T;

	d = LIMIT(d_prop + INV.d_integ, (-INV.d_limit), (INV.d_limit));
	if (Flag.CC_mode == 2) {
		d = d_ext;
	}
	test_d = d;

	//d = d_ext;

	/*
	 INV.Err_Idse = INV.Idse_ref-INV.Idse;
	 INV.Err_Iqse = INV.Iqse_ref-INV.Iqse;

	 INV.Idse_integ +=INV.Kid_T * (INV.Err_Idse- INV.Kad * INV.Vdse_anti);
	 INV.Iqse_integ +=INV.Kiq_T * (INV.Err_Iqse- INV.Kaq * INV.Vqse_anti);

	 INV.Vdse_ref_fb=INV.Idse_integ + INV.Kpd * INV.Err_Idse;
	 INV.Vqse_ref_fb=INV.Iqse_integ + INV.Kpq * INV.Err_Iqse;

	 INV.Vdse_ref_ff=0.;
	 INV.Vqse_ref_ff=0.;

	 INV.Vdse_ref = INV.Vdse_ref_fb + INV.Vdse_ref_ff;
	 INV.Vqse_ref = INV.Vqse_ref_fb + INV.Vqse_ref_ff;

	 INV.Vdss_ref=INV.Vdse_ref * INV.cosThetar - INV.Vqse_ref * INV.sinThetar;
	 INV.Vqss_ref=INV.Vdse_ref * INV.sinThetar + INV.Vqse_ref * INV.cosThetar;

	 INV.Vas_ref = INV.Vdss_ref;
	 INV.Vbs_ref = -0.5 * INV.Vdss_ref + SQRT3 * INV.Vqss_ref * 0.5;
	 INV.Vcs_ref = -0.5 * INV.Vdss_ref - SQRT3 * INV.Vqss_ref * 0.5;

	 if(INV.Vas_ref > INV.Vbs_ref)
	 {
	 INV.Vmax = INV.Vas_ref;
	 INV.Vmin = INV.Vbs_ref;
	 }
	 else
	 {
	 INV.Vmax = INV.Vbs_ref;
	 INV.Vmin = INV.Vas_ref;
	 }

	 if(INV.Vcs_ref > INV.Vmax)
	 {
	 INV.Vmax = INV.Vcs_ref;
	 }
	 if(INV.Vcs_ref < INV.Vmin)
	 {
	 INV.Vmin = INV.Vcs_ref;
	 }

	 INV.Vsn= -0.5 * (INV.Vmax + INV.Vmin);

	 INV.Van_ref = INV.Vas_ref + INV.Vsn;
	 INV.Vbn_ref = INV.Vbs_ref + INV.Vsn;
	 INV.Vcn_ref = INV.Vcs_ref + INV.Vsn;

	 INV.Van_ref_set = (INV.Van_ref > half_Vdc ) ? half_Vdc  : ((INV.Van_ref < -half_Vdc) ? -half_Vdc : INV.Van_ref);		// < ? a:b > true->a , false ->b
	 INV.Vbn_ref_set = (INV.Vbn_ref > half_Vdc ) ? half_Vdc  : ((INV.Vbn_ref < -half_Vdc) ? -half_Vdc : INV.Vbn_ref);
	 INV.Vcn_ref_set = (INV.Vcn_ref > half_Vdc ) ? half_Vdc  : ((INV.Vcn_ref < -half_Vdc) ? -half_Vdc : INV.Vcn_ref);

	 INV.Vdss_ref_set = INV.Van_ref_set * INV_2_3 - INV.Vbn_ref_set * INV_3 - INV.Vcn_ref_set * INV_3 ;//Vsn
	 INV.Vqss_ref_set = INV.Vbn_ref_set * INV_SQRT3 - INV.Vcn_ref_set * INV_SQRT3 ;

	 INV.Vdse_ref_set = INV.Vdss_ref_set * INV.cosThetar + INV.Vqss_ref_set * INV.sinThetar;
	 INV.Vqse_ref_set = -INV.Vdss_ref_set * INV.sinThetar + INV.Vqss_ref_set * INV.cosThetar;

	 INV.CompA = (int)((INV.Van_ref_set + half_Vdc) * maxCount_ePWM * INV_Vdc) ;
	 INV.CompB = (int)((INV.Vbn_ref_set + half_Vdc) * maxCount_ePWM * INV_Vdc) ;
	 INV.CompC = (int)((INV.Vcn_ref_set + half_Vdc) * maxCount_ePWM * INV_Vdc) ;

	 INV.CompA = ((INV.CompA > (int)maxCount_ePWM) ? maxCount_ePWM : ((INV.CompA < 0) ? 0  : INV.CompA));
	 INV.CompB = ((INV.CompB > (int)maxCount_ePWM) ? maxCount_ePWM : ((INV.CompB < 0) ? 0  : INV.CompB));
	 INV.CompC = ((INV.CompC > (int)maxCount_ePWM) ? maxCount_ePWM : ((INV.CompC < 0) ? 0  : INV.CompC));
	 */

	INV.CompA = 0; // U (Epwm2)
	INV.CompB = (int) ((float) maxCount_ePWM * (1 + d) / 2.); // V (Epwm6)
	INV.CompC = (int) ((float) maxCount_ePWM * (1 - d) / 2.); // W (Epwm7)
}

void PwmUpdate(void) {
	EPwm2Regs.CMPA.bit.CMPA = INV.CompA;
	EPwm6Regs.CMPA.bit.CMPA = INV.CompB;
	EPwm7Regs.CMPA.bit.CMPA = INV.CompC;
//	EPwm11Regs.CMPA.bit.CMPA = INV.CompC;
}

void ResetHINV(void) {
	Ih_ref_CC = 0;
	INV.Err_Ih = 0;
	INV.Ih_integ = 0;
	INV.clear_integ_cnt = 0;
	INV.Vh_ref_fb = 0;
	INV.Vh_ref_ff = 0;
	INV.Vh_ref_set = 0;
	INV.Vh_ref = 0;
	INV.Vhp = 0;
	INV.Vhm = 0;
	INV.Vh_anti = 0;

	INV.CompP = 0;
	INV.CompM = 0;
	INV.CompP_DB = 0;
	INV.CompM_DB = 0;
}

void SwitchOff(void) {
	if (isSwitchOn == true) {
		//EPwm6Regs.DBCTL.bit.POLSEL = DB_ACTV_HI;
		EPwm6Regs.AQCTLA.bit.CAD = AQ_CLEAR;
		//EPwm7Regs.DBCTL.bit.POLSEL = DB_ACTV_HI;
		EPwm7Regs.AQCTLA.bit.CAD = AQ_CLEAR;

		EPwm10Regs.AQCTLA.bit.CAD = AQ_CLEAR;

		EPwm6Regs.CMPA.bit.CMPA = 0;
		EPwm7Regs.CMPA.bit.CMPA = 0;

		EPwm10Regs.CMPA.bit.CMPA = 0;
		isSwitchOn = false;
	}
}

void SwitchOn(void) {
	if (isSwitchOn == false) {
		EPwm6Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
		EPwm6Regs.AQCTLA.bit.CAD = AQ_SET;
		EPwm7Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
		EPwm7Regs.AQCTLA.bit.CAD = AQ_SET;

		EPwm10Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
		EPwm10Regs.AQCTLA.bit.CAD = AQ_SET;
		isSwitchOn = true;
	}
}
