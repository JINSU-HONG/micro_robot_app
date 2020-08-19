#include <stdio.h>
#include "variables.h"
#include "data_form_change.h"

void AddSendFloatData(float num_f) {
    unsigned int num = *(unsigned int *)(&num_f);
    send_buf[send_len] = (num >> 24) & 0xFF;
    send_buf[send_len+1] = (num >> 16) & 0xFF;
    send_buf[send_len+2] = (num >> 8) & 0xFF;
    send_buf[send_len+3] = num & 0xFF;
    send_len = send_len + 4;
}

int ReadRecvIntData() {
    int reading_data = (((unsigned long)(recv_buf[recv_iter])) << 24) + (((unsigned long)(recv_buf[recv_iter+1])) << 16) + (((unsigned long)(recv_buf[recv_iter+2])) << 8) + recv_buf[recv_iter+3];
    recv_iter = recv_iter + 4;
    return reading_data;
}

float ReadRecvFloatData() {
    int reading_data = ReadRecvIntData();
    return *(float *)(&reading_data);
}
