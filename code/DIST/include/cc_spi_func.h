/*
 * cc_spi_func.h
 *
 *  Created on: 2015. 12. 21.
 *      Author: Jun Lee
 */

#ifndef CC_SPI_FUNC_H
#define CC_SPI_FUNC_H

void init_mode_spi_func();
void inv_test_mode_spi_func();
void idle_mode_spi_func();
unsigned int CalcChecksum(unsigned int *data, int leng);

#endif /* CC_SPI_FUNC_H */
