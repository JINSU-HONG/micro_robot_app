/**********************************************************************
* File: Xbar.c -- Lab File
* Devices: TMS320F28x7x
* Author: Technical Training Organization (TTO), Texas Instruments
**********************************************************************/

#include "F2837xS_Init_Func.h"
#include "F2837xS_output_xbar.h"


/**********************************************************************
* Function: InitXbar()
*
* Description: Initializes the Input, Output & ePWM X-Bar on the F28x7x
**********************************************************************/
void InitXbar(void)
{
	EALLOW;							// Enable EALLOW protected register access

	//Input X-Bar
	InputXbarRegs.INPUT1SELECT = 14;   // Iuvw Tz                 // Feed GPIO16(nFLTIO) to ePWM[TZ1, TRIP1], ePWM X-Bar, Output X-Bar via Input X-Bar
	InputXbarRegs.INPUT2SELECT = 69; // Vdc Tz                   // Feed GPIO21(nFLT15) to ePWM[TZ2, TRIP2], ePWM X-Bar, Output X-Bar via Input X-Bar
	//InputXbarRegs.INPUT3SELECT = 3;                    // Feed GPIO3(nFLTI_12V) to ePWM[TZ3, TRIP3], ePWM X-Bar, Output X-Bar via Input X-Bar

	//INPUTxSELECT lock register control
    InputXbarRegs.INPUTSELECTLOCK.all = 0x00000000;    // Write a 1 to lock (cannot be cleared once set)

    //EPwm X-Bar Lock register control
    EPwmXbarRegs.TRIPLOCK.all = 0x00000000;            // Write a 1 to lock (cannot be cleared once set)

     OutputXbarRegs.OUTPUT6MUX0TO15CFG.bit.MUX14= 3;
   	 OutputXbarRegs.OUTPUT6MUXENABLE.bit.MUX14= 0x1;

     OutputXbarRegs.OUTPUT4MUX0TO15CFG.bit.MUX14= 3;
  	 OutputXbarRegs.OUTPUT4MUXENABLE.bit.MUX14= 0x1;

     OutputXbarRegs.OUTPUT7MUX0TO15CFG.bit.MUX14= 3;
  	 OutputXbarRegs.OUTPUT7MUXENABLE.bit.MUX14= 0x1;

	/*
    //EPwm X-Bar
    //Polarity of trip to EPwm modules (default : 0)
    EPwmXbarRegs.TRIPOUTINV.bit.TRIP4 = 1;             // TRIPIN4    0=active high output   1=active low output

    //Group TRIPIN4 (ADC A(3), B(1), INPUT X-bar(3))
    EPwmXbarRegs.TRIP4MUX0TO15CFG.bit.MUX0 = 2;        // ADCAEVT1
    EPwmXbarRegs.TRIP4MUXENABLE.bit.MUX0 = 1;          // enable

    EPwmXbarRegs.TRIP4MUX0TO15CFG.bit.MUX2 = 2;        // ADCAEVT2
    EPwmXbarRegs.TRIP4MUXENABLE.bit.MUX2 = 1;          // enable

    EPwmXbarRegs.TRIP4MUX0TO15CFG.bit.MUX4 = 2;        // ADCAEVT3
    EPwmXbarRegs.TRIP4MUXENABLE.bit.MUX4 = 1;          // enable

    EPwmXbarRegs.TRIP4MUX0TO15CFG.bit.MUX8 = 2;        // ADCBEVT1
    EPwmXbarRegs.TRIP4MUXENABLE.bit.MUX8 = 1;          // enable

    EPwmXbarRegs.TRIP4MUX0TO15CFG.bit.MUX1 = 1;        // INPUTXBAR1
    EPwmXbarRegs.TRIP4MUXENABLE.bit.MUX1 = 1;          // enable

    EPwmXbarRegs.TRIP4MUX0TO15CFG.bit.MUX3 = 1;        // INPUTXBAR2
    EPwmXbarRegs.TRIP4MUXENABLE.bit.MUX3 = 1;          // enable
	*/

    //EPwmXbarRegs.TRIP4MUX0TO15CFG.bit.MUX5 = 1;        // INPUTXBAR3
    //EPwmXbarRegs.TRIP4MUXENABLE.bit.MUX5 = 1;          // enable
	EDIS;
}

//--- end of file -----------------------------------------------------
