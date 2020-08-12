/*
 * check_CRC.h
 *
 *  Created on: 2020. 8. 12.
 *      Author: HALAB_G
 */

#ifndef INCLUDE_CHECK_CRC_H_
#define INCLUDE_CHECK_CRC_H_

#include "stdint.h"


extern uint16_t table_CRC_16[256];

extern uint16_t CRC_8_calc(uint16_t* arr, uint32_t size);

extern uint16_t Calc_CRC_16_CCITT(uint16_t *DataArray, uint16_t Length);

extern uint16_t byte1(uint16_t data, uint16_t select);

#endif /* INCLUDE_CHECK_CRC_H_ */
