//###########################################################################
//
// FILE:   F2837xS_Emif.c
//
// TITLE:  F2837xS EMIF Initialization & Support Functions.
//
//###########################################################################
// $TI Release: F2837xS Support Library v160 $
// $Release Date: Mon Jun 15 14:14:46 CDT 2015 $
// $Copyright: Copyright (C) 2014-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#include "F2837xS_device.h"     // F2837xS Headerfile Include File
#include "F2837xS_Examples.h"   // F2837xS Examples Include File
#include "F2837xS_Init_Func.h"

//
// This function initializes the EMIF1 to a known state.
//
void Emif1Initialize(void)
{
    EALLOW;
    // Perform a Module soft reset on EMIF
    #ifdef CPU1
    DevCfgRegs.SOFTPRES1.all = 0x1;
   __asm (" nop");
    DevCfgRegs.SOFTPRES1.all = 0x0;
	#endif

    ClkCfgRegs.PERCLKDIVSEL.bit.EMIF1CLKDIV = 0x1;      //EMIF1CLK=200MHz/2=100MHz

    EDIS;
}



//
//Async wait config function
//
void ASync_wait_config(Uint16 inst, Uint16 wait_count, Uint16 wait_polarity)
{
    if (inst == 0) 
    {
        Emif1Regs.ASYNC_WCCR.bit.MAX_EXT_WAIT = wait_count;       // 7:0 Maximum Extended Wait cycles.
        Emif1Regs.ASYNC_WCCR.bit.WP0 = wait_polarity;             // 28 Wait Polarity for pad_wait_i[0].
	}
	else 
    {
        Emif2Regs.ASYNC_WCCR.bit.MAX_EXT_WAIT = wait_count;       // 7:0 Maximum Extended Wait cycles.
        Emif2Regs.ASYNC_WCCR.bit.WP0 = wait_polarity;             // 28 Wait Polarity for pad_wait_i[0].
	}
}


///EMIF1CLK=200MHz/2=100MHz
////FPGA
void ASync_cs2_config(void)
{
	Emif1Regs.ASYNC_CS2_CR.all =  (EMIF_ASYNC_ASIZE_16  	| // 16Bit Memory Interface
			  	  	  	  	  	  	 EMIF_ASYNC_TA_1 		| // Turn Around time of 2 Emif Clock
			  	  	  	  	  	  	 EMIF_ASYNC_RHOLD_1 	| // Read Hold time of 1 Emif Clock
			  	  	  	  	  	  	 EMIF_ASYNC_RSTROBE_3 	| // Read Strobe time of 4 Emif Clock
			  	  	  	  	  	  	 EMIF_ASYNC_RSETUP_1 	| // Read Setup time of 1 Emif Clock
			  	  	  	  	  	  	 EMIF_ASYNC_WHOLD_1 	| // Write Hold time of 1 Emif Clock
			  	  	  	  	  	  	 EMIF_ASYNC_WSTROBE_3 	| // Write Strobe time of 1 Emif Clock
			  	  	  	  	  	  	 EMIF_ASYNC_WSETUP_1 	| // Write Setup time of 1 Emif Clock
			  	  	  	  	  	  	 EMIF_ASYNC_EW_DISABLE 	| // Extended Wait Disable.
			  	  	  	  	  	  	 EMIF_ASYNC_SS_DISABLE    // Strobe Select Mode Disable.
			  	  	  	  	  	  	);
}

///UDP
void ASync_cs3_config(void)
{
	Emif1Regs.ASYNC_CS3_CR.all =  (EMIF_ASYNC_ASIZE_16  	| // 16Bit Memory Interface
										 EMIF_ASYNC_TA_2 		| // Turn Around time of 2 Emif Clock
				  	  	  	  	  	  	 EMIF_ASYNC_RHOLD_2 	| // Read Hold time of 1 Emif Clock
				  	  	  	  	  	  	 EMIF_ASYNC_RSTROBE_8 	| // Read Strobe time of 4 Emif Clock
				  	  	  	  	  	  	 EMIF_ASYNC_RSETUP_2 	| // Read Setup time of 1 Emif Clock
				  	  	  	  	  	  	 EMIF_ASYNC_WHOLD_2 	| // Write Hold time of 1 Emif Clock
				  	  	  	  	  	  	 EMIF_ASYNC_WSTROBE_8	| // Write Strobe time of 1 Emif Clock
				  	  	  	  	  	  	 EMIF_ASYNC_WSETUP_2 	| // Write Setup time of 1 Emif Clock
				  	  	  	  	  	  	 EMIF_ASYNC_EW_DISABLE 	| // Extended Wait Disable.
				  	  	  	  	  	  	 EMIF_ASYNC_SS_DISABLE    // Strobe Select Mode Disable.
				  	  	  	  	  	  	);
	
}

void ASync_cs4_config(void)
{
	Emif1Regs.ASYNC_CS3_CR.all =  (EMIF_ASYNC_ASIZE_16  	| // 16Bit Memory Interface
				  	  	  	  	  	  	 EMIF_ASYNC_TA_1 		| // Turn Around time of 2 Emif Clock
				  	  	  	  	  	  	 EMIF_ASYNC_RHOLD_1 	| // Read Hold time of 1 Emif Clock
				  	  	  	  	  	  	 EMIF_ASYNC_RSTROBE_6 	| // Read Strobe time of 4 Emif Clock
				  	  	  	  	  	  	 EMIF_ASYNC_RSETUP_1 	| // Read Setup time of 1 Emif Clock
				  	  	  	  	  	  	 EMIF_ASYNC_WHOLD_1 	| // Write Hold time of 1 Emif Clock
				  	  	  	  	  	  	 EMIF_ASYNC_WSTROBE_1 	| // Write Strobe time of 1 Emif Clock
				  	  	  	  	  	  	 EMIF_ASYNC_WSETUP_1 	| // Write Setup time of 1 Emif Clock
				  	  	  	  	  	  	 EMIF_ASYNC_EW_DISABLE 	| // Extended Wait Disable.
				  	  	  	  	  	  	 EMIF_ASYNC_SS_DISABLE    // Strobe Select Mode Disable.
				  	  	  	  	  	  	);
}


