#ifndef FAULT_H
#define FAULT_H

#include "F28x_Project.h"

__interrupt void FaultISR(void);

void InitFault(void);
void ADCEVT_PPB_CLEAR(void);

typedef union
{
	Uint16 all;
	struct
	{
		Uint16 OC			:1;
		Uint16 OV			:1;
		Uint16 nFLT_15V		:1;
		Uint16 nFLT_GATE	:1;
		Uint16 rsvd			:12;
	}bit;
}HW_Fault;

typedef union
{
	Uint16 all;
	struct
	{
		Uint16 OV_350			:1;
		Uint16 OV_96			:1;
		Uint16 OC_grid		:1;
		Uint16 OC_buck		:1;
		Uint16 OV_grid		:1;
		Uint16 OC_U			:1;
		Uint16 OC_V			:1;
		Uint16 OC_W			:1;
		Uint16 rsvd			:8;
	}bit;
}SW_Fault;

typedef struct
{
	SW_Fault	SW_Prot;
	HW_Fault	HW_Prot;
}FAULT;
extern FAULT Fault;

#endif
