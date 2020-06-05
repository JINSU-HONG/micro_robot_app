//###########################################################################
//
// FILE:   F2837xS_EPwm.c
//
// TITLE:  F2837xS EPwm Initialization & Support Functions.
//
//###########################################################################
// $TI Release: F2837xS Support Library v150 $
// $Release Date: Thu Mar  5 14:49:36 CST 2015 $
// $Copyright: Copyright (C) 2014-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#include "F2837xS_device.h"     // F2837xS Headerfile Include File
#include "F2837xS_Examples.h"   // F2837xS Examples Include File
#include "F2837xS_variable.h"

void ConfigureEPWM(volatile struct EPWM_REGS *EPwmXRegs, Uint16 Fsw, Uint16 maxCount_ePWM, Uint16 Initial_CMP, float Deadband, Uint16 Counter_mode, Uint16 Sampling_mode);
void EPwm1_MasterSetup(void);

void InitEPwm(void)
{
	ClkCfgRegs.PERCLKDIVSEL.bit.EPWMCLKDIV = 0; // EPWM clock = SYS_CLK
	CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0; // All PWM counting stop

	maxCount_ePWM =	(Uint16)(0.5*(SYS_CLK*0.5)/Fsw); // Master carrier
	maxCount_ePWM = ((maxCount_ePWM>>1)<<1);

	InitEPwm2Gpio();
	InitEPwm6Gpio();
	InitEPwm7Gpio();
	InitEPwm10Gpio();

	EPwm1_MasterSetup();

	//ConfigureEPWM(&EPwm2Regs, Fsw, maxCount_ePWM, 0, 2e-6, TB_COUNT_UPDOWN, ET_CTR_PRD);
	//ConfigureEPWM(&EPwm2Regs, Fsw, maxCount_ePWM, 0, 2e-6, TB_COUNT_UPDOWN, ET_CTR_ZERO);
	ConfigureEPWM(&EPwm2Regs, Fsw, maxCount_ePWM, 0, INV_DEADTIME, TB_COUNT_UPDOWN, ET_CTR_PRD);

	ConfigureEPWM(&EPwm6Regs, Fsw, maxCount_ePWM, 0, INV_DEADTIME, TB_COUNT_UPDOWN, ET_CTR_PRD);
	ConfigureEPWM(&EPwm7Regs, Fsw, maxCount_ePWM, 0, INV_DEADTIME, TB_COUNT_UPDOWN, ET_CTR_PRD);
	ConfigureEPWM(&EPwm10Regs, Fsw, maxCount_ePWM, 0, INV_DEADTIME, TB_COUNT_UPDOWN, ET_CTR_PRD);

	//ConfigureEPWM(&EPwm11Regs, Fsw, maxCount_ePWM, 0, INV_DEADTIME, TB_COUNT_UPDOWN, ET_CTR_PRD);

	TrigRegs.SYNCSELECT.bit.EPWM4SYNCIN = 0; // sync EPWM 4,5,6 to EPWM1SYNCOUT
	TrigRegs.SYNCSELECT.bit.EPWM7SYNCIN = 0; // sync EPWM 7,8,9 to EPWM1SYNCOUT
	TrigRegs.SYNCSELECT.bit.EPWM10SYNCIN = 0; // sync EPWM 10,11,12 to EPWM1SYNCOUT

	CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1; // All PWM counting start
}

void InitEPwm2Gpio(void)
{
	GPIO_SetupPinMux(2, GPIO_MUX_CPU1, 1);
	GPIO_SetupPinMux(3, GPIO_MUX_CPU1, 1);
	GpioCtrlRegs.GPAPUD.bit.GPIO2 = 1; // Pull-up disable
	GpioCtrlRegs.GPAPUD.bit.GPIO3 = 1; // Pull-up disable
}
void InitEPwm6Gpio(void)
{
	GPIO_SetupPinMux(10, GPIO_MUX_CPU1, 1);
	GPIO_SetupPinMux(11, GPIO_MUX_CPU1, 1);
	GpioCtrlRegs.GPAPUD.bit.GPIO10 = 1; // Pull-up disable
	GpioCtrlRegs.GPAPUD.bit.GPIO11 = 1; // Pull-up disable
}

void InitEPwm7Gpio(void)
{
	GPIO_SetupPinMux(12, GPIO_MUX_CPU1, 1);
	GPIO_SetupPinMux(13, GPIO_MUX_CPU1, 1);
	GpioCtrlRegs.GPAPUD.bit.GPIO12 = 1; // Pull-up disable
	GpioCtrlRegs.GPAPUD.bit.GPIO13 = 1; // Pull-up disable
}

void InitEPwm10Gpio(void)
{
	GPIO_SetupPinMux(18, GPIO_MUX_CPU1, 5);
	GPIO_SetupPinMux(19, GPIO_MUX_CPU1, 5);
	GpioCtrlRegs.GPAPUD.bit.GPIO18 = 1; // Pull-up disable
	GpioCtrlRegs.GPAPUD.bit.GPIO19 = 1; // Pull-up disable
}

void EPwm1_MasterSetup(void)
{
	EALLOW;
	// Setup Counter
	EPwm1Regs.TBPRD = maxCount_ePWM;			// Set Period
	EPwm1Regs.TBCTR = 0x0000;               	// Clear counter

	// Setup Compare value
	EPwm1Regs.CMPA.bit.CMPA = 0;
	EPwm1Regs.CMPB.bit.CMPB = maxCount_ePWM;

	// Setup counter mode
	EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;

	// Setup counter clock
	EPwm1Regs.TBCTL.bit.HSPCLKDIV =TB_DIV1;  	//TBCLK = EPWMCLK/(HSPCLKDIV * CLKDIV)
	EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;

	// SyncIN
	EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_CTR_CMPB; // self; CTR_CMPB = CTR_PRD
	//EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE; // self
	//EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN; // dist board
	EPwm1Regs.TBCTL.bit.PHSEN = TB_ENABLE; // dist board

	// EPwm1Regs.TBCTL.bit.PRDLD = TB_SHADOW;
	EPwm1Regs.TBCTL.bit.PHSDIR = TB_UP;
	EPwm1Regs.TBPHS.bit.TBPHS = 0x0000;

	EDIS;
}

void ConfigureEPWM(volatile struct EPWM_REGS *EPwmXRegs, Uint16 Fsw, Uint16 maxCount_ePWM, Uint16 Initial_CMP, float Deadband, Uint16 Counter_mode, Uint16 Sampling_mode)
{
	EALLOW;
	// Setup Counter
	EPwmXRegs->TBPRD = maxCount_ePWM;			// Set Period
	EPwmXRegs->TBCTR = 0x0000;               	// Clear counter

	// Setup Compare value
	EPwmXRegs->CMPA.bit.CMPA = Initial_CMP;
	EPwmXRegs->CMPB.bit.CMPB = Initial_CMP;

	// Setup counter mode
	EPwmXRegs->TBCTL.bit.CTRMODE = Counter_mode;

	// Setup counter clock
	EPwmXRegs->TBCTL.bit.HSPCLKDIV =TB_DIV1;  	//TBCLK = EPWMCLK/(HSPCLKDIV * CLKDIV)
	EPwmXRegs->TBCTL.bit.CLKDIV = TB_DIV1;

	// Sync
	EPwmXRegs->TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
	EPwmXRegs->TBPHS.bit.TBPHS = 0x0000;
	EPwmXRegs->TBCTL.bit.PHSDIR = TB_UP;
	EPwmXRegs->TBCTL.bit.PHSEN = TB_ENABLE;

	// Setup Shawdowing
	EPwmXRegs->TBCTL.bit.PRDLD = TB_IMMEDIATE;  	//Load TBPRD from shadow register

	//Setup shadowing
	EPwmXRegs->CMPCTL.bit.SHDWAMODE = CC_SHADOW; // Set shadow mode
	EPwmXRegs->CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwmXRegs->CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD;
	EPwmXRegs->CMPCTL.bit.LOADBMODE = CC_CTR_ZERO_PRD;

	//Set actions
	EPwmXRegs->AQCTLA.bit.CAU = AQ_CLEAR;
	EPwmXRegs->AQCTLA.bit.CAD = AQ_SET;
	//EPwmXRegs->AQCTLA.bit.PRD = AQ_NO_ACTION;
	//EPwmXRegs->AQCTLA.bit.ZRO = AQ_NO_ACTION;

	//Dead Band
	EPwmXRegs->DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
	EPwmXRegs->DBCTL.bit.POLSEL = DB_ACTV_HIC;  // Active high complementary
	EPwmXRegs->DBCTL.bit.IN_MODE = DBA_ALL;		// Deadband input mode
	EPwmXRegs->DBRED = (Uint16)(Deadband*SYS_CLK*0.5);
	EPwmXRegs->DBFED = (Uint16)(Deadband*SYS_CLK*0.5);

	//Trip Zone Selection.
//	EPwmXRegs->TZSEL.bit.OSHT1 = TZ_ENABLE; // Enable TZ1 as a OST trip source for this ePWM module
//	EPwmXRegs->TZSEL.bit.OSHT2 = TZ_ENABLE; // Enable TZ2 as a OST trip source for this ePWM module
	//EPwmXRegs->TZSEL.bit.OSHT3 = TZ_ENABLE; // Enable TZ3 as a OST trip source for this ePWM module
	//EPwmXRegs->TZSEL.bit.OSHT4 = TZ_ENABLE; // Enable TZ4 as a OST trip source for this ePWM module

	EPwmXRegs->TZCTL.bit.TZA =  TZ_FORCE_LO;
	EPwmXRegs->TZCTL.bit.TZB =  TZ_FORCE_LO;

	//Enable TZ interrupt
//	EPwmXRegs->TZEINT.bit.OST = 1;

	//CLEAR FLAG
	EPwmXRegs->TZCLR.bit.OST = 1;
	EPwmXRegs->TZCLR.bit.INT = 1;

	//Interrupt
	EPwmXRegs->ETSEL.bit.INTSEL = Sampling_mode;
	EPwmXRegs->ETSEL.bit.INTEN = 1;              	// Enable INT
	EPwmXRegs->ETPS.bit.INTPRD = ET_1ST;    		// Generate INT on 1st event
	EDIS;
}
