#include "F2837xS_fault.h"
#include "F2837xS_variable.h"

FAULT Fault;

//Define Fault level

// 3.3 * (10k + 24k) / 10k = 0.97
#define Fault_Level_A_SOC_Center 0.97
#define Fault_Level_A_SOC_Resistor 0.01
#define Fault_Level_A_SOC_Current 2.0
//#define Fault_Level_A_SOC_Current 25.0

#define Fault_Level_A_SOC0_H (Fault_Level_A_SOC_Center + \
		Fault_Level_A_SOC_Resistor * Fault_Level_A_SOC_Current)	//ADCINA0 (INVa_shunt_ADC_P)
#define Fault_Level_A_SOC0_L (Fault_Level_A_SOC_Center - \
		Fault_Level_A_SOC_Resistor * Fault_Level_A_SOC_Current)	//ADCINA1 (INVa_shunt_ADC_N)
#define Fault_Level_A_SOC1_H (Fault_Level_A_SOC_Center + \
		Fault_Level_A_SOC_Resistor * Fault_Level_A_SOC_Current)	//ADCINA2 (INVb_shunt_ADC_P)
#define Fault_Level_A_SOC1_L (Fault_Level_A_SOC_Center - \
		Fault_Level_A_SOC_Resistor * Fault_Level_A_SOC_Current)	//ADCINA3 (INVb_shunt_ADC_N)
#define Fault_Level_A_SOC2_H (Fault_Level_A_SOC_Center + \
		Fault_Level_A_SOC_Resistor * Fault_Level_A_SOC_Current)	//ADCINA4 (INVc_shunt_ADC_P)
#define Fault_Level_A_SOC2_L (Fault_Level_A_SOC_Center - \
		Fault_Level_A_SOC_Resistor * Fault_Level_A_SOC_Current)	//ADCINA5 (INVc_shunt_ADC_N)

//#define Fault_Level_A_SOC0_H 1.22	//ADCINA0 (INVa_shunt_ADC_P) :  25 A
//#define Fault_Level_A_SOC0_L 0.72	//ADCINA1 (INVa_shunt_ADC_N) : -25 A
//#define Fault_Level_A_SOC1_H 1.22	//ADCINA2 (INVb_shunt_ADC_P) :  25 A
//#define Fault_Level_A_SOC1_L 0.72	//ADCINA3 (INVb_shunt_ADC_N) : -25 A
//#define Fault_Level_A_SOC2_H 1.22	//ADCINA4 (INVc_shunt_ADC_P) :  25 A
//#define Fault_Level_A_SOC2_L 0.72	//ADCINA5 (INVc_shunt_ADC_N) : -25 A

// 350 * 604 / (33200*4 + 604) = 1.585
#define Fault_Level_B_SOC1_H 1.585   //ADCINB2 (Vdc_ADC) : 350V

//ADC Fault Level
Uint16 Fault_ADC_A_SOC_H[3] = {	(Uint16)( 65536. * (Fault_Level_A_SOC0_H + 3.3) / 3.3 / 2. ),	//ADCINA0 (INVa_shunt_ADC_P)
								(Uint16)( 65536. * (Fault_Level_A_SOC1_H + 3.3) / 3.3 / 2. ),	//ADCINA2 (INVb_shunt_ADC_P)
								(Uint16)( 65536. * (Fault_Level_A_SOC2_H + 3.3) / 3.3 / 2. )		//ADCINA4 (INVc_shunt_ADC_P)
							 };

Uint16 Fault_ADC_A_SOC_L[3] = {	(Uint16)( 65536. * (Fault_Level_A_SOC0_L + 3.3) / 3.3 / 2. ),	//ADCINA0 (INVa_shunt_ADC_N)
								(Uint16)( 65536. * (Fault_Level_A_SOC1_L + 3.3) / 3.3 / 2. ),	//ADCINA2 (INVb_shunt_ADC_N)
								(Uint16)( 65536. * (Fault_Level_A_SOC2_L + 3.3) / 3.3 / 2. )		//ADCINA4 (INVc_shunt_ADC_N)
	 	 	 	 	 	 	 };

Uint16 Fault_ADC_B_SOC_H[1] = {	(Uint16)( Fault_Level_B_SOC1_H*4096./3.3 ),	//ADCINB2 (Vdc_ADC)
							 };

void InitFault(void)
{
	Fault.HW_Prot.all=0x0000;
	Fault.SW_Prot.all=0x0000;

	//forced SW ADC SOC -------------------------------------------
	AdcaRegs.ADCSOCFRC1.all = 0x0007; //SOC0, SOC1, SOC2 forced start
	AdcbRegs.ADCSOCFRC1.all = 0x0002; //SOC1 forced start
	delaycc(1e-5);
	//DELAY_US(10);

	AdcaRegs.ADCINTFLGCLR.all = 0x0007;
	AdcbRegs.ADCINTFLGCLR.all = 0x0002;

    EALLOW;
    /*
	//Set PPB Interrupt fault value
	AdcaRegs.ADCPPB1TRIPHI.bit.LIMITHI = Fault_ADC_A_SOC_H[0];
	//AdcaRegs.ADCPPB1TRIPLO.bit.LSIGN = 1;
	AdcaRegs.ADCPPB1TRIPLO.bit.LIMITLO = Fault_ADC_A_SOC_L[0];
	AdcaRegs.ADCPPB2TRIPHI.bit.LIMITHI = Fault_ADC_A_SOC_H[1];
	//AdcaRegs.ADCPPB2TRIPLO.bit.LSIGN = 1;
	AdcaRegs.ADCPPB2TRIPLO.bit.LIMITLO = Fault_ADC_A_SOC_L[1];
	AdcaRegs.ADCPPB3TRIPHI.bit.LIMITHI = Fault_ADC_A_SOC_H[2];
	//AdcaRegs.ADCPPB3TRIPLO.bit.LSIGN = 1;
	AdcaRegs.ADCPPB3TRIPLO.bit.LIMITLO = Fault_ADC_A_SOC_L[2];
	*/
	AdcaRegs.ADCPPB1TRIPHI.bit.LIMITHI = OffsetAin_adc_A[0] + \
		Fault_Level_A_SOC_Resistor * Fault_Level_A_SOC_Current * 65536. / 3.3 / 2. / 5.1 * 16;
	AdcaRegs.ADCPPB1TRIPLO.bit.LIMITLO = OffsetAin_adc_A[0] - \
		Fault_Level_A_SOC_Resistor * Fault_Level_A_SOC_Current * 65536. / 3.3 / 2. / 5.1 * 16;
	AdcaRegs.ADCPPB2TRIPHI.bit.LIMITHI = OffsetAin_adc_A[1] + \
		Fault_Level_A_SOC_Resistor * Fault_Level_A_SOC_Current * 65536. / 3.3 / 2. / 5.1 * 16;
	AdcaRegs.ADCPPB2TRIPLO.bit.LIMITLO = OffsetAin_adc_A[1] - \
		Fault_Level_A_SOC_Resistor * Fault_Level_A_SOC_Current * 65536. / 3.3 / 2. / 5.1 * 16;
	AdcaRegs.ADCPPB3TRIPHI.bit.LIMITHI = OffsetAin_adc_A[2] + \
		Fault_Level_A_SOC_Resistor * Fault_Level_A_SOC_Current * 65536. / 3.3 / 2. / 5.1 * 16;
	AdcaRegs.ADCPPB3TRIPLO.bit.LIMITLO = OffsetAin_adc_A[2] - \
		Fault_Level_A_SOC_Resistor * Fault_Level_A_SOC_Current * 65536. / 3.3 / 2. / 5.1 * 16;

	AdcbRegs.ADCPPB1TRIPHI.bit.LIMITHI = Fault_ADC_B_SOC_H[0];
	EDIS;

    ADCEVT_PPB_CLEAR();

    //enable ADEVT ISR (FAULT INT)
    EALLOW;
    AdcaRegs.ADCEVTSEL.all = 0x0333; 	//0b 0000 0011 0011 0011 high, low int
    AdcaRegs.ADCEVTINTSEL.all = 0x0333; //0b 0000 0011 0011 0011

    AdcbRegs.ADCEVTSEL.all = 0x0001; 	//0b 0000 0000 0000 0001 high int
    AdcbRegs.ADCEVTINTSEL.all = 0x0001; //0b 0000 0000 0000 0001
	EDIS;
}

__interrupt void FaultISR(void)
{
	PieCtrlRegs.PIEIER3.bit.INTx2 = 0; //EPWM2 OFF

	fault_cnt++;
	Flag.ModeStatus = MODE_STATUS_INV_FAULT;

	//EALLOW;
	//EPwm2Regs.TZFRC.bit.OST = 1;
	//EPwm6Regs.TZFRC.bit.OST = 1;
	//EPwm7Regs.TZFRC.bit.OST = 1;
	//EDIS;

    // Acknowledge this interrupt to receive more interrupts from group 2
	//while (test_fault_a == 0) {
	//    delaycc(10e-6); // change test_fault_a through JTAG
	//}
	//test_fault_a = 0;

	test_fault_a = AdcaRegs.ADCEVTSTAT.all;

	AdcaRegs.ADCEVTCLR.all = 0x0333; // clear high, low adc evt at PPB1,2,3
	AdcbRegs.ADCEVTCLR.all = 0x0001; // clear high adc evt at PPB1
	AdcaRegs.ADCINTFLGCLR.all = 0x0007; // to receive ADC INT repeately
	AdcbRegs.ADCINTFLGCLR.all = 0x0002; // to receive ADC INT repeately
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;

	PieCtrlRegs.PIEIER3.bit.INTx2 = 1; //EPWM2 ON
}


void ADCEVT_PPB_CLEAR(void){
	AdcaRegs.ADCEVTCLR.all = 0x3333;
	AdcbRegs.ADCEVTCLR.all = 0x3333;
}
