/*
 * F2837xS_DA.c
 *
 *  Created on: 2015. 8. 26.
 *      Author: CHG
 */
#include "F2837xS_device.h"     // F2837xS Headerfile Include File
#include "F2837xS_Examples.h"   // F2837xS Examples Include File
#include "F2837xS_da.h"


/*
void InitIntDac(void)
{
	EALLOW;
	DaccRegs.DACCTL.bit.DACREFSEL  = REFERENCE_VREF;
	DaccRegs.DACOUTEN.bit.DACOUTEN = 1;	//Enable DAC output
	EDIS;
}

void IntDacOut(float vals)
{
	Uint16 da_temp;

	da_temp = (Uint16)(4096.*vals/DAC_VREF);
	DaccRegs.DACVALS.bit.DACVALS = da_temp & 0x0FFF;
}

*/

extern int *da[4], da_type[4], da_data[4];
extern float da_scale[4], da_mid[4], da_temp[4];

extern int DacOffset;

void InitSpiDac(void)
{
/*
	GpioCtrlRegs.GPBPUD.bit.GPIO58 = 0;   // Enable pull-up on GPIO16 (SPISIMOA)
    GpioCtrlRegs.GPBPUD.bit.GPIO59 = 0;   // Enable pull-up on GPIO17 (SPISOMIA)
    GpioCtrlRegs.GPBPUD.bit.GPIO60 = 0;   // Enable pull-up on GPIO18 (SPICLKA)
    GpioCtrlRegs.GPBPUD.bit.GPIO61 = 0;   // Enable pull-up on GPIO19 (SPISTEA)

    GpioCtrlRegs.GPBQSEL2.bit.GPIO58 = 3; // Asynch input GPIO16 (SPISIMOA)
    GpioCtrlRegs.GPBQSEL2.bit.GPIO59 = 3; // Asynch input GPIO17 (SPISOMIA)
    GpioCtrlRegs.GPBQSEL2.bit.GPIO60 = 3; // Asynch input GPIO18 (SPICLKA)
    GpioCtrlRegs.GPBQSEL2.bit.GPIO61 = 3; // Asynch input GPIO19 (SPISTEA)

    GpioCtrlRegs.GPBMUX2.bit.GPIO58 = 1; // Configure GPIO16 as SPISIMOA
    GpioCtrlRegs.GPBMUX2.bit.GPIO59 = 1; // Configure GPIO17 as SPISOMIA
    GpioCtrlRegs.GPBMUX2.bit.GPIO60 = 1; // Configure GPIO18 as SPICLKA
    GpioCtrlRegs.GPBMUX2.bit.GPIO61 = 1; // Configure GPIO19 as SPISTEA
*/



/*
	SpiaRegs.SPIFFTX.all=0xE040; //1110 0000 0100 0000
	SpiaRegs.SPIFFRX.all=0x2044; // 0010 0000 0100 0100
	SpiaRegs.SPIFFCT.all=0x0;
	SpidRegs.SPICCR.bit.SPISWRESET = 0;

	SpiaRegs.SPICCR.all =0x0007;	             // Reset on, rising edge, 8-bit char bits
	SpiaRegs.SPICTL.all =0x0006;    		     // Enable master mode, normal phase,
	                                             // enable talk, and SPI int disabled.
	SpiaRegs.SPIBRR.all =0x007F;
	SpiaRegs.SPICCR.all =0x009F;		         // Relinquish SPI from Reset
	SpiaRegs.SPIPRI.bit.FREE = 1;                // Set so breakpoints don't disturb xmission

*/

	SpiaRegs.SPICCR.bit.SPISWRESET = 0;
    SpiaRegs.SPICCR.all = 0x0047;			//char length 8bit		// Clock polarity = 1
    SpiaRegs.SPICCR.bit.HS_MODE = 0x1;
   SpiaRegs.SPICTL.all = 0x000E;			// Master mode, Enable transmission, Phase = 0

//	SpiaRegs.SPICCR.all =0x0007;	             // Reset on, rising edge, 8-bit char bits
//	SpiaRegs.SPICTL.all =0x0006;    		     // Enable master mode, normal phase,

    SpiaRegs.SPISTS.all = 0x0000;
    SpiaRegs.SPIBRR.all = 0x0001;				//LSPCLK/(4) = 25MHz
    SpiaRegs.SPIPRI.bit.FREE = 1;

    SpiaRegs.SPIFFTX.all= 0xC008;			// Enable FIFO's, set TX FIFO level to 8
    SpiaRegs.SPIFFRX.all= 0x001F;			// Set RX FIFO level to 8
    SpiaRegs.SPIFFCT.all= 0x00;
    SpiaRegs.SPIPRI.all=0x0010;

    SpiaRegs.SPICCR.bit.SPISWRESET = 1;


    SpiaRegs.SPIFFTX.bit.TXFIFO=1;
    SpiaRegs.SPIFFRX.bit.RXFIFORESET=1;


	GpioDataRegs.GPBSET.bit.GPIO61=0x1;  //ncs  low active
	while(SpiaRegs.SPIFFTX.bit.TXFFST);
	asm("	nop");
	asm("	nop");
	asm("	nop");
	GpioDataRegs.GPBCLEAR.bit.GPIO61=0x1;  //ncs  low active

	SpiaRegs.SPITXBUF = 0x0100;  //  WRITE AND loa4d data for CH0
	SpiaRegs.SPITXBUF = 0x1000;
	SpiaRegs.SPITXBUF = 0x0000;

	GpioDataRegs.GPBSET.bit.GPIO61=0x1;  //ncs  low active
	while(SpiaRegs.SPIFFTX.bit.TXFFST);
	asm("	nop");
	GpioDataRegs.GPBCLEAR.bit.GPIO61=0x1;  //ncs  low active



     /*
 	GpioDataRegs.GPCSET.bit.GPIO66=0x1;  //ncs  low active
 	while(SpibRegs.SPIFFTX.bit.TXFFST);
 	asm("	nop");
 	asm("	nop");
 	asm("	nop");
 	GpioDataRegs.GPCCLEAR.bit.GPIO66=0x1;  //ncs  low active

 	SpibRegs.SPITXBUF = 0x0100;  //  WRITE AND loa4d data for CH0
 	SpibRegs.SPITXBUF = 0x1000;
 	SpibRegs.SPITXBUF = 0x0000;

 	GpioDataRegs.GPCSET.bit.GPIO66=0x1;  //ncs  low active
 	while(SpibRegs.SPIFFTX.bit.TXFFST);
 	asm("	nop");
 	GpioDataRegs.GPCCLEAR.bit.GPIO66=0x1;  //ncs  low active
*/


}

void SpiDacOut(void)
{
	da_temp[0] = da_type[0] ? (float)(*da[0]) : *(float *)(da[0]);
	da_data[0] = ((int)(DacOffset - da_scale[0] * (da_temp[0] - da_mid[0])));

	SpiaRegs.SPITXBUF =0x1000;  //  WRITE AND load data for CH0
	SpiaRegs.SPITXBUF =(int)((da_data[0]<<4)&0xFF00);
	SpiaRegs.SPITXBUF =(int)((da_data[0]<<12)&0xFF00);

	//SpibRegs.SPITXBUF =0x1000;  //  WRITE AND load data for CH0
	//SpibRegs.SPITXBUF =(int)((da_data[0]<<4)&0xFF00);
	//SpibRegs.SPITXBUF =(int)((da_data[0]<<12)&0xFF00);

	delaycc(1e-6);

	da_temp[1] = da_type[1] ? (float)(*da[1]) : *(float *)(da[1]);
	da_data[1] = ((int)(DacOffset - da_scale[1] * (da_temp[1] - da_mid[1])));

	SpiaRegs.SPITXBUF =0x1200;  //  WRITE AND load data for CH0
	SpiaRegs.SPITXBUF =(int)((da_data[1]<<4)&0xFF00);
	SpiaRegs.SPITXBUF =(int)((da_data[1]<<12)&0xFF00);
/*
	delaycc(1e-6);

	da_temp[2] = da_type[2] ? (float)(*da[2]) : *(float *)(da[2]);
 	da_data[2] = ((int)(DacOffset - da_scale[2] * (da_temp[2] - da_mid[2])));

	SpiaRegs.SPITXBUF =0x1400;  //  WRITE AND load data for CH0
	SpiaRegs.SPITXBUF =(int)((da_data[2]<<4)&0xFF00);
	SpiaRegs.SPITXBUF =(int)((da_data[2]<<12)&0xFF00);

    delaycc(1e-6);

	da_temp[3] = da_type[3] ? (float)(*da[3]) : *(float *)(da[3]);
	da_data[3] = ((int)(DacOffset - da_scale[3] * (da_temp[3] - da_mid[3])));

	SpiaRegs.SPITXBUF =0x1600;  //  WRITE AND load data for CH0
	SpiaRegs.SPITXBUF =(int)((da_data[3]<<4)&0xFF00);
	SpiaRegs.SPITXBUF =(int)((da_data[3]<<12)&0xFF00);
*/
}




