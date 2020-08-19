#ifndef UDP_FUNC_H
#define UDP_FUNC_H

void AddSendHeaderData();

void init_mode_udp_send_func();
void inv_test_mode_udp_send_func(); 
void idle_mode_udp_send_func();
void run_mode_udp_send_func();

void init_mode_udp_recv_func();
void inv_test_mode_udp_recv_func(); 
void idle_mode_udp_recv_func();
void run_mode_udp_recv_func();

void read_udp_header();
// void print_fault_INVs();
// void read_current_sen();
void copy_current_ref_to_sen();

#endif // UDP_FUNC_H
