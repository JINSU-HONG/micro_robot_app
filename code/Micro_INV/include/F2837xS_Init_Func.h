/**********************************************************************
* File: SNU_28377D__Init_Func_Prototypes.h
* Device: TMS320F2837xD
* Author: Technical Training Organization (TTO), Texas Instruments
* Description: Include file for C28x workshop labs.  Include this
* file in all C-source files.
**********************************************************************/

#ifndef F2837xS_INIT_FUNC_H
#define F2837xS_INIT_FUNC_H

#include "F2837xS_Device.h"
#include "F2837xS_Adc_defines.h"
#include "F2837xS_DefaultIsr.h"
#include "F2837xS_Pie_defines.h"

extern void Gpio_setup(void);
extern void InitAdc(void);
extern void Config_12bit_AdcA(void);
extern void Config_12bit_AdcB(void);
extern void InitXbar(void);
extern void InitFault(void);
extern void InitEPwm(void);


#endif  // end of F2837xS_INIT_FUNC_H definition
