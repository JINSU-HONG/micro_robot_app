#include "F28x_Project.h"
#include "easy2837xS_sci_v8.4.h"
#include "F2837xS_Init_Func.h"
#include "F2837xS_fault.h"
#include "F2837xS_offset.h"
#include "F2837xS_variable.h"
#include "F2837xS_da.h"
#include "cc.h"

long loopCnt = 0;
int ePWMinit=0;

void main(void)
{
	InitSysCtrl();

	DINT;
	InitPieCtrl();

	IER = 0x0000;
	IFR = 0x0000;

	InitPieVectTable();
	EALLOW;
	//PieVectTable.EPWM8_TZ_INT = &FaultISR;
	PieVectTable.EPWM2_INT = &offset;
	PieVectTable.SPIB_RX_INT = &SPI_RXINT;

	//PieVectTable.ADCA_EVT_INT = &FaultISR; // bind in offset.c
	//PieVectTable.ADCB_EVT_INT = &FaultISR; // bind in offset.c
	EDIS;

	InitGpio();
	Gpio_setup();

	InitSpiGpio();
	InitXbar();
	InitAdc();
	//InitIntDac();
//	InitSpiDac();

	//InitFault(); // initialize fault in offset.c
	InitEPwm();
	InitCpuTimers();

	easyDSP_SCI_Init();

	ConfigCpuTimer(&CpuTimer1, 200, 1000000);
	CpuTimer1Regs.TCR.all = 0x4000; // Use write-only instruction to set TSS bit = 0

	// IER flag
	IER |= M_INT1|M_INT2|M_INT3|M_INT10|M_INT6;

	// Enable PIE
	PieCtrlRegs.PIEIER1.bit.INTx7 = 1;//CPUTimer0
//	PieCtrlRegs.PIEIER2.bit.INTx2 = 1;//EPWM2_TZ
	PieCtrlRegs.PIEIER3.bit.INTx2 = 1;//EPWM2_INT

	PieCtrlRegs.PIEIER6.bit.INTx3 = 1;//SPIBRX_INT

//	PieCtrlRegs.PIEIER10.bit.INTx1 = 1;//ADCA_EVT_INT
//	PieCtrlRegs.PIEIER10.bit.INTx5 = 1;//ADCB_EVT_INT

    EALLOW;
	PieCtrlRegs.PIECTRL.bit.ENPIE = 1;
	EDIS;

	EINT;
	ERTM;

	// Sampling time
	Tsamp = 1.*maxCount_ePWM * SYS_CLK_PRD; // 1.* for double sampling 2.* for single sampling
	INV_Tsamp = 1./Tsamp;
	maxCount_ePWM_safe = (int)(maxCount_ePWM*0.9);
	minCount_ePWM_safe = (int)(maxCount_ePWM*0.1);


	InitFlags();
	InitParameters();
	//InitController();

	while(1)
	{
		loopCnt++;
		if (ePWMinit) {
			EPwm6Regs.TZCLR.bit.CBC = 1;
			EPwm6Regs.TZCLR.bit.INT = 1;
			EPwm6Regs.TZCLR.bit.OST = 1;
			EPwm7Regs.TZCLR.bit.CBC = 1;
			EPwm7Regs.TZCLR.bit.INT = 1;
			EPwm7Regs.TZCLR.bit.OST = 1;
			ePWMinit=0;


		}
	}
}
