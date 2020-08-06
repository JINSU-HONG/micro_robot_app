#include "F2837xS_offset.h"
#include "F2837xS_fault.h"
#include "F2837xS_variable.h"
#include "cc.h"

#define OFFSET_MAX_CNT 13 // 2^13 = 8192회

long offsetLoopCnt = 0, offsetMaxCnt = (1<<OFFSET_MAX_CNT);
long Offset_ADC_a[3]={0,0,0};
long Offset_ADC_b[1]={0};

int offset_cnt =0;

__interrupt void offset(void)
{
	int i=0;

	offset_cnt++;

	AdcaRegs.ADCSOCPRICTL.bit.RRPOINTER = 0x10; // Roundrobbin으로 결정되지만 혹시 모르니 priority SOC0으로 reset (32)
	AdcaRegs.ADCSOCPRICTL.bit.RRPOINTER = 0x10;

	//SOC0, SOC1, SOC2 forced start
	AdcaRegs.ADCSOCFRC1.all = 0x0007;
	while(AdcaRegs.ADCINTFLG.bit.ADCINT1 == 0); // Conversion finish 기다림.
	AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; // ADC Flag clear
	//SOC0 forced start
	AdcbRegs.ADCSOCFRC1.all = 0x0007;
	while(AdcbRegs.ADCINTFLG.bit.ADCINT1 == 0); // Conversion finish 기다림.
	AdcbRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; // ADC Flag clear

	//read ADC for SOC0
	Offset_ADC_a[0] += ((long)AdcaResultRegs.ADCRESULT0) & Mode_16bit;  // ADC_A_SOC0 (INVa_shunt_ADC_P/N)

	//read ADC for SOC1
	Offset_ADC_a[1] += ((long)AdcaResultRegs.ADCRESULT1) & Mode_16bit;  // ADC_A_SOC2 (INVb_shunt_ADC_P/N)

	//read ADC for SOC2
	Offset_ADC_a[2] += ((long)AdcaResultRegs.ADCRESULT2) & Mode_16bit;  // ADC_A_SOC4 (INVc_shunt_ADC_P/N)

	//read ADC for SOC1
	Offset_ADC_b[0] += ((long)AdcbResultRegs.ADCRESULT1) & Mode_12bit;  // ADC_B_SOC1 (Vdc_ADC)

	// Offset value calculation
	offsetLoopCnt++;
	if(offsetLoopCnt >= offsetMaxCnt)
	{
		for(i=0;i<3;i++)
			OffsetAin_adc_A[i] = Offset_ADC_a[i]>>OFFSET_MAX_CNT;

		OffsetAin_adc_B[0] = Offset_ADC_b[0]>>OFFSET_MAX_CNT;

		InitFault();
		EALLOW;
		PieVectTable.ADCA_EVT_INT = &FaultISR;
		PieVectTable.ADCB_EVT_INT = &FaultISR;
		EDIS;

		EALLOW;
		PieVectTable.EPWM2_INT = &cc;
		EDIS;
	}

    // Clear INT flag for this timer
    EPwm2Regs.ETCLR.bit.INT = 1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}
