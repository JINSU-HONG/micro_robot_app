#ifndef CC_H
#define CC_H

#include "F28x_Project.h"
#include "F2837xS_variable.h"

__interrupt void cc(void);

__interrupt void SPI_RXINT(void);



void AD_Process(void);
void PLL_Process(void);
void PFC_Process(void);
void BUCK_Process(void);
void PwmUpdate(void);
void ResetHINV(void);
void ResetINV(void);
void HINV_Process(void);
void HPwmUpdate(void);
void INV_Process(void);
void SwitchOn(void);
void SwitchOff(void);



#endif
