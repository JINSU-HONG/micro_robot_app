#include "types.h"

#pragma CODE_SECTION(AddSendHeaderData, "ramfuncs");
#pragma CODE_SECTION(AddSendFloatData, "ramfuncs");
#pragma CODE_SECTION(AddSendShortBinaryData, "ramfuncs");
#pragma CODE_SECTION(AddSendBinaryData, "ramfuncs");
#pragma CODE_SECTION(ReadRecvFloatData, "ramfuncs");
#pragma CODE_SECTION(ReadRecvIntData, "ramfuncs");
#pragma CODE_SECTION(ReadRecvFloatData, "ramfuncs");
#pragma CODE_SECTION(ReadRecvShortData, "ramfuncs");
#pragma CODE_SECTION(convert_float_to_binary, "ramfuncs");
#pragma CODE_SECTION(convert_binary_to_float, "ramfuncs");

void AddSendHeaderData(uint8* buf, int mode, int status, int* len) {
	int buf_iter = *len / 2;
	//buf[buf_iter] = (mode << 8) + status;
	buf[buf_iter] = mode * 256 + status;
	buf[buf_iter+1] = 0xAA55;
	*len = *len + 4;
}

void AddSendFloatData(uint8* buf, float new_data, int* len) {
	int buf_iter = *len / 2;
	//buf[buf_iter] = ((*(long *)(&new_data)) >> 16) & 0xFFFF;
	buf[buf_iter] = (*(unsigned long *)(&new_data)) / 256 / 256;
	buf[buf_iter+1] = (*(long *)(&new_data)) & 0xFFFF;
	*len = *len + 4;
}
void AddSendShortBinaryData(uint8* buf, int new_data, int* len) {
	int buf_iter = *len / 2;
	buf[buf_iter] = new_data;
	*len = *len + 2;
}
void AddSendBinaryData(uint8* buf, int new_data_h, int new_data_l, int* len) {
	int buf_iter = *len / 2;
	buf[buf_iter] = new_data_h;
	buf[buf_iter+1] = new_data_l;
	*len = *len + 4;
}

float ReadRecvFloatData(uint8* buf, int* iter) {
	//int reading_data = (((uint32)(buf[*iter])) << 16) + ((uint32)(buf[(*iter)+1]));
	int reading_data = ((uint32)(buf[*iter])) * 256 * 256 + ((uint32)(buf[(*iter)+1]));
	*iter = *iter + 2;
	return *(float *)(&reading_data);
}
int ReadRecvIntData(uint8* buf, int* iter) {
	//int reading_data = (((uint32)(buf[*iter])) << 16) + ((uint32)(buf[(*iter)+1]));
	int reading_data = ((uint32)(buf[*iter])) * 256 * 256 + ((uint32)(buf[(*iter)+1]));
	*iter = *iter + 2;
	return reading_data;
}
short ReadRecvShortData(uint8* buf, int* iter) {
	int reading_data = buf[*iter];
	*iter = *iter + 1;
	return reading_data;
}

void convert_float_to_binary(float* float_data, unsigned long* int_data_h,
        unsigned long* int_data_l) {
    *int_data_h = ((*(unsigned long*) (float_data)) & 0xFFFF0000) >> 16;
    *int_data_l = (*(unsigned long*) (float_data)) & 0xFFFF;
}
void convert_binary_to_float(float* float_data, int int_data_h, int int_data_l) {
    unsigned long sum = ((unsigned long) int_data_h) << 16 + int_data_l;
    *float_data = *((float *) (&sum));
}
