#ifndef CC_H
#define CC_H

#include "F28x_Project.h"
#include "F2837xS_variable.h"

__interrupt void cc(void);

void AD_Process(void);
void PLL_Process(void);
void PFC_Process(void);
void BUCK_Process(void);
void PwmUpdate(void);

#endif
