#include "types.h"

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

void convert_binary_to_float(float* float_p, unsigned int int_data_h, unsigned int int_data_l) {
	unsigned long total_data;
	total_data = ((unsigned long)int_data_h << 16) + (unsigned long)int_data_l;
	*float_p = *(float *)(&total_data);
}
