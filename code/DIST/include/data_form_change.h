/*
 * data_form_change.h
 *
 *  Created on: 2015. 12. 21.
 *      Author: Jun Lee
 */

#ifndef DATA_FORM_CHAGNE_H
#define DATA_FORM_CHAGNE_H

void AddSendHeaderData(uint8* buf, int mode, int status, int* len);
void AddSendFloatData(uint8* buf, float new_data, int* len);
void AddSendShortBinaryData(uint8* buf, int new_data, int* len);
void AddSendBinaryData(uint8* buf, int new_data_h, int new_data_l, int* len);
float ReadRecvFloatData(uint8* buf, int* iter);
int ReadRecvIntData(uint8* buf, int* iter);
short ReadRecvShortData(uint8* buf, int* iter);
void convert_float_to_binary(float* float_data, unsigned long* int_data_h,
        unsigned long* int_data_l);
void convert_binary_to_float(float* float_data, int int_data_h, int int_data_l);

#endif /* DATA_FORM_CHAGNE_H */
