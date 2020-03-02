//###########################################################################
// FILE:   F2837xS_Adc.c
// TITLE:  F2837xS Adc Support Functions.
//###########################################################################
// $TI Release: F2837xS Support Library v150 $
// $Release Date: Thu Mar  5 14:49:36 CST 2015 $
// $Copyright: Copyright (C) 2014-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

//1. SOCx -> ADC Channel 연결
//2. EOCx -> ADC INTx 연결 (사용안함)
//3. SOCx -> PPBx 연결
//4. PPB(지금은 Limit) option 설정

#include "F2837xS_device.h"     // F2837xS Headerfile Include File
#include "F2837xS_Examples.h"   // F2837xS Examples Include File
#include "F2837xS_Init_Func.h"

//28377S revision B 의 제기된 문제 (Erreta 참고)
//Random Conversion Errors의 확율을 낮추기 위해 해야 하는 것들
//1. S+H 시간 최소 : 320ns
//2. ADCCLK : 40MHz 이하 (전기적으로 최대 50MHz까지 쓸수 있지만, 확율을 낮추기 위해 40MHz로 사용 해야 함)
//3. ADCCLK의 prescale 을 정수로(ex : /1,/2,/3,/4,/5,/6,/7,/8)
//4. 메모리 0x0000743F, 0x000074BF, 0x0000753F, 0x000075BF 위치에 0X7000값을 쓴다

void InitAdc(void){
	EALLOW;
	DevCfgRegs.SOFTPRES13.all = 0x1;	// ADC is reset
	DevCfgRegs.SOFTPRES13.all = 0;	// ADC is released from reset
	EDIS;

	Config_16bit_AdcA();
	//Config_12bit_AdcA();
	Config_12bit_AdcB();
}

void Config_16bit_AdcA(void){
//void Config_12bit_AdcA(void){
	Uint16 acqps;

	EALLOW;
	//Configure the ADC base registers
	//AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 0;    //ADC power down: 0=powered down / 1=powered up
	AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1; //INT pulse generation: 0=start of conversion / 1=end of conversion
	AdcaRegs.ADCCTL2.bit.PRESCALE = 0x8;	//0x8=CPUCLK/5 : 40MHz to redue random conversion errors
	AdcaRegs.rsvd5[3] = 0x7000;  //for silicon revision B

	//ADC mode
    AdcSetMode(ADC_ADCA, ADC_RESOLUTION_16BIT, ADC_SIGNALMODE_DIFFERENTIAL);
    //AdcSetMode(ADC_ADCA, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);

    //SOC configuration
    acqps = 63; //63 : 320ns (16bit mode minimun duration time), 14 : 75ns (12bit minimun duration time)
    //acqps = 14; //63 : 320ns (16bit mode minimun duration time), 14 : 75ns (12bit minimun duration time)

    AdcaRegs.ADCSOC0CTL.bit.TRIGSEL = 0;		// Trigger : Software only
    AdcaRegs.ADCSOC0CTL.bit.CHSEL = 0x0;		// SOC0 Convert channel: ADCINA0,1 (INVa_shunt_ADC_P/N)
    AdcaRegs.ADCSOC0CTL.bit.ACQPS = acqps;		// Acquisition window

    AdcaRegs.ADCSOC1CTL.bit.TRIGSEL = 0;		// Trigger : Software only
    AdcaRegs.ADCSOC1CTL.bit.CHSEL = 0x2;		// SOC1 Convert channel: ADCINA 2,3 (INVb_shunt_ADC_P/N)
    AdcaRegs.ADCSOC1CTL.bit.ACQPS = acqps;		// Acquisition window

    AdcaRegs.ADCSOC2CTL.bit.TRIGSEL = 0;		// Trigger : Software only
    AdcaRegs.ADCSOC2CTL.bit.CHSEL = 0x4;		// SOC2 Convert channel: ADCINA 4,5 (INVc_shunt_ADC_P/N)
    AdcaRegs.ADCSOC2CTL.bit.ACQPS = acqps;		// Acquisition window

    //ADC interrupt configuration: INT Flag로 ADC 끝난지 알 수 있음. 마지막 Conversion INT flag만 활용. RRPOINTER로 SOC priority reset
    AdcaRegs.ADCINTSEL1N2.bit.INT1SEL = 2; // ADCINT1 -> EOC2
    AdcaRegs.ADCINTSEL1N2.bit.INT1E   = 1; // ADCINT1 Enable
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; // ensure INT1 flag is cleared

    //PPB configuration
    AdcaRegs.ADCPPB1CONFIG.bit.CONFIG = 0; // SOC0 (INVa_shunt_ADC)
    AdcaRegs.ADCPPB2CONFIG.bit.CONFIG = 1; // SOC2 (INVb_shunt_ADC)
    AdcaRegs.ADCPPB3CONFIG.bit.CONFIG = 2; // SOC3 (INVc_shunt_ADC)
    AdcaRegs.ADCPPB4CONFIG.bit.CONFIG = 3;

    //PPB offset 0 확인
    AdcaRegs.ADCPPB1OFFCAL.bit.OFFCAL = 0;
    AdcaRegs.ADCPPB2OFFCAL.bit.OFFCAL = 0;
    AdcaRegs.ADCPPB3OFFCAL.bit.OFFCAL = 0;
    AdcaRegs.ADCPPB4OFFCAL.bit.OFFCAL = 0;

    //ADC_offset trim 설정
    AdcaRegs.ADCOFFTRIM.all = 0x0;///*** 왜 안되지??

    //Finish up
    AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1;
	EDIS;

	delaycc(1e-3);
	//DELAY_US(1000);
}

void Config_12bit_AdcB(void){
	Uint16 acqps;

	EALLOW;
	//Configure the ADC base registers
	//AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 0;    //ADC power down: 0=powered down / 1=powered up
	AdcbRegs.ADCCTL1.bit.INTPULSEPOS = 1; //INT pulse generation: 0=start of conversion / 1=end of conversion
	AdcbRegs.ADCCTL2.bit.PRESCALE = 0x8;	//0x8=CPUCLK/5 : 40MHz to redue random conversion errors
	AdcbRegs.rsvd5[3] = 0x7000;  //for silicon revision B

	//ADC mode
    AdcSetMode(ADC_ADCB, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);

    //SOC configuration
    acqps = 14; //63 : 320ns (16bit mode minimun duration time), 14 : 75ns (12bit minimun duration time)

    AdcbRegs.ADCSOC0CTL.bit.TRIGSEL = 0;		// Trigger : Software only
    AdcbRegs.ADCSOC0CTL.bit.CHSEL = 0x0;		// SOC0 Convert channel: ADCINB0 (DSP_AD2)
    AdcbRegs.ADCSOC0CTL.bit.ACQPS = acqps;		// Acquisition window

    AdcbRegs.ADCSOC1CTL.bit.TRIGSEL = 0;		// Trigger : Software only
    AdcbRegs.ADCSOC1CTL.bit.CHSEL = 0x2;		// SOC1 Convert channel: ADCINB2 (Vdc_ADC)
    AdcbRegs.ADCSOC1CTL.bit.ACQPS = acqps;		// Acquisition window

    AdcbRegs.ADCSOC2CTL.bit.TRIGSEL = 0;		// Trigger : Software only
    AdcbRegs.ADCSOC2CTL.bit.CHSEL = 0x3;		// SOC2 Convert channel: ADCINB3 (Filt_a_AD)
    AdcbRegs.ADCSOC2CTL.bit.ACQPS = acqps;		// Acquisition window

    AdcbRegs.ADCSOC3CTL.bit.TRIGSEL = 0;		// Trigger : Software only
    AdcbRegs.ADCSOC3CTL.bit.CHSEL = 0x4;		// SOC3 Convert channel: ADCINB4 (Filt_b_AD)
    AdcbRegs.ADCSOC3CTL.bit.ACQPS = acqps;		// Acquisition window

    AdcbRegs.ADCSOC4CTL.bit.TRIGSEL = 0;		// Trigger : Software only
    AdcbRegs.ADCSOC4CTL.bit.CHSEL = 0x5;		// SOC4 Convert channel: ADCINB5 (Filt_c_AD)
    AdcbRegs.ADCSOC4CTL.bit.ACQPS = acqps;		// Acquisition window

    //ADC interrupt configuration: INT Flag로 ADC 끝난지 알 수 있음. 마지막 Conversion INT flag만 활용. RRPOINTER로 SOC priority reset
    AdcbRegs.ADCINTSEL1N2.bit.INT1SEL = 1; // ADCINT1 -> EOC1
    AdcbRegs.ADCINTSEL1N2.bit.INT1E   = 1; // ADCINT1 Enable
    AdcbRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; // make sure INT1 flag is cleared

    //PPB configuration
    AdcbRegs.ADCPPB1CONFIG.bit.CONFIG = 1; // SOC1 (Vdc_ADC)
    AdcbRegs.ADCPPB2CONFIG.bit.CONFIG = 2;
    AdcbRegs.ADCPPB3CONFIG.bit.CONFIG = 2;
    AdcbRegs.ADCPPB4CONFIG.bit.CONFIG = 2;

    //PPB offset 0 확인
    AdcbRegs.ADCPPB1OFFCAL.bit.OFFCAL = 0;
    AdcbRegs.ADCPPB2OFFCAL.bit.OFFCAL = 0;
    AdcbRegs.ADCPPB3OFFCAL.bit.OFFCAL = 0;
    AdcbRegs.ADCPPB4OFFCAL.bit.OFFCAL = 0;

    //ADC_offset trim 설정
    AdcbRegs.ADCOFFTRIM.all = 0x7F;///*** 왜 안되지??

    //Finish up
    AdcbRegs.ADCCTL1.bit.ADCPWDNZ = 1;
	EDIS;

	delaycc(1e-3);
	//DELAY_US(1000);
}

/* 
* Set the resolution and signalmode for a given ADC. This will ensure that
* the correct trim is loaded. 
*/
void AdcSetMode(Uint16 adc, Uint16 resolution, Uint16 signalmode)
{
	Uint16 adcOffsetTrimOTPIndex; //index into OTP table of ADC offset trims
	Uint16 adcOffsetTrim; //temporary ADC offset trim
	
	//re-populate INL trim
	CalAdcINL(adc);
	
	if(0xFFFF != *((Uint16*)GetAdcOffsetTrimOTP)){
		//offset trim function is programmed into OTP, so call it

		//calculate the index into OTP table of offset trims and call
		//function to return the correct offset trim
		adcOffsetTrimOTPIndex = 4*adc + 2*resolution + 1*signalmode;
		adcOffsetTrim = (*GetAdcOffsetTrimOTP)(adcOffsetTrimOTPIndex);
	}
	else {
		//offset trim function is not populated, so set offset trim to 0
		adcOffsetTrim = 0;
	}

	//Apply the resolution and signalmode to the specified ADC.
	//Also apply the offset trim and, if needed, linearity trim correction.
	switch(adc){
		case ADC_ADCA:
			AdcaRegs.ADCCTL2.bit.RESOLUTION = resolution;
			AdcaRegs.ADCCTL2.bit.SIGNALMODE = signalmode;
			AdcaRegs.ADCOFFTRIM.all = adcOffsetTrim;
			if(ADC_RESOLUTION_12BIT == resolution){

				//12-bit linearity trim workaround
				AdcaRegs.ADCINLTRIM1 &= 0xFFFF0000;
				AdcaRegs.ADCINLTRIM2 &= 0xFFFF0000;
				AdcaRegs.ADCINLTRIM4 &= 0xFFFF0000;
				AdcaRegs.ADCINLTRIM5 &= 0xFFFF0000;
			}
		break;
		case ADC_ADCB:
			AdcbRegs.ADCCTL2.bit.RESOLUTION = resolution;
			AdcbRegs.ADCCTL2.bit.SIGNALMODE = signalmode;
			AdcbRegs.ADCOFFTRIM.all = adcOffsetTrim;
			if(ADC_RESOLUTION_12BIT == resolution){

				//12-bit linearity trim workaround
				AdcbRegs.ADCINLTRIM1 &= 0xFFFF0000;
				AdcbRegs.ADCINLTRIM2 &= 0xFFFF0000;
				AdcbRegs.ADCINLTRIM4 &= 0xFFFF0000;
				AdcbRegs.ADCINLTRIM5 &= 0xFFFF0000;
			}
		break;
		case ADC_ADCC:
			AdccRegs.ADCCTL2.bit.RESOLUTION = resolution;
			AdccRegs.ADCCTL2.bit.SIGNALMODE = signalmode;
			AdccRegs.ADCOFFTRIM.all = adcOffsetTrim;
			if(ADC_RESOLUTION_12BIT == resolution){

				//12-bit linearity trim workaround
				AdccRegs.ADCINLTRIM1 &= 0xFFFF0000;
				AdccRegs.ADCINLTRIM2 &= 0xFFFF0000;
				AdccRegs.ADCINLTRIM4 &= 0xFFFF0000;
				AdccRegs.ADCINLTRIM5 &= 0xFFFF0000;
			}
		break;
		case ADC_ADCD:
			AdcdRegs.ADCCTL2.bit.RESOLUTION = resolution;
			AdcdRegs.ADCCTL2.bit.SIGNALMODE = signalmode;
			AdcdRegs.ADCOFFTRIM.all = adcOffsetTrim;
			if(ADC_RESOLUTION_12BIT == resolution){

				//12-bit linearity trim workaround
				AdcdRegs.ADCINLTRIM1 &= 0xFFFF0000;
				AdcdRegs.ADCINLTRIM2 &= 0xFFFF0000;
				AdcdRegs.ADCINLTRIM4 &= 0xFFFF0000;
				AdcdRegs.ADCINLTRIM5 &= 0xFFFF0000;
			}
		break;
	}
}

/* 
* Loads INL trim values from OTP into the trim registers of the specified ADC.
* Use only as part of AdcSetMode function, since linearity trim correction
* is needed for some modes.
*/
void CalAdcINL(Uint16 adc)
{
	switch(adc){
		case ADC_ADCA:
			if(0xFFFF != *((Uint16*)CalAdcaINL)){
				//trim function is programmed into OTP, so call it
				(*CalAdcaINL)();
			}
			else {
				//do nothing, no INL trim function populated
			}
			break;
		case ADC_ADCB:
			if(0xFFFF != *((Uint16*)CalAdcbINL)){
				//trim function is programmed into OTP, so call it
				(*CalAdcbINL)();
			}
			else {
				//do nothing, no INL trim function populated
			}
			break;
		case ADC_ADCC:
			if(0xFFFF != *((Uint16*)CalAdccINL)){
				//trim function is programmed into OTP, so call it
				(*CalAdccINL)();
			}
			else {
				//do nothing, no INL trim function populated
			}
			break;
		case ADC_ADCD:
			if(0xFFFF != *((Uint16*)CalAdcdINL)){
				//trim function is programmed into OTP, so call it
				(*CalAdcdINL)();
			}
			else {
				//do nothing, no INL trim function populated
			}
			break;
	}
}
