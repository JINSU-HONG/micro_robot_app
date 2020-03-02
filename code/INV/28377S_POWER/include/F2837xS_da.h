/*
 * F2837xS_da.h
 *
 *  Created on: 2015. 8. 26.
 *      Author: CHG
 */

#ifndef JUSTEK_INVERTER_INCLUDE_F2837XS_DA_H_
#define JUSTEK_INVERTER_INCLUDE_F2837XS_DA_H_

// DAC reference

/*
#define REFERENCE_VDAC     0
#define REFERENCE_VREF     1

#define DAC_VREF	3

extern void InitIntDac(void);
extern void IntDacOut(float vals);


extern long *da[4];
extern long *test_tw[1];

extern int  da_type[4], da_data[4];
extern float da_scale[4], da_mid[4], da_temp[4];

void InitSerialDac(void);
void SerialDacOut(void);


#define DACOUT(x)	{da_temp[(x)] = da_type[(x)] ? (float)(*da[(x)]) : *(float *)(da[(x)]);\
	da_data[(x)] = (int)(((long)(- da_scale[(x)] * (da_temp[(x)] - da_mid[(x)]))) & 0x0FFF);\
	SpidRegs.SPITXBUF = 0x1000|((x)<<9) ;  SpidRegs.SPITXBUF =(int)(da_data[(x)]<<4)&0xFF00;\
	SpidRegs.SPITXBUF =(int)(da_data[(x)]<<12)&0xFF00; }

*/


extern int *da[4], da_type[4], da_data[4];
extern float da_scale[4], da_mid[4], da_temp[4];


extern void InitIntDac(void);
extern void IntDacOut(float vals);
extern void SpitIntDac(void);
extern void SpiDacOut(void);






#endif /* JUSTEK_INVERTER_INCLUDE_F2837XS_DA_H_ */
