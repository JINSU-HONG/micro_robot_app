#include "F2837xS_device.h"
#include "F2837xS_Examples.h"
#include "cc.h"
#include "F2837xS_da.h"
#include <math.h>
#include "Filter.h"
#include "comp.h"

#include "w5300.h"

#include "data_form_change.h"

#pragma CODE_SECTION(cc, "ramfuncs");

int cc_cnt = 0;
int cc_debug_cnt = 0;
long ccTimer1start;
float ccTime;
float a = 0;
uint8 iter;

// w5300
uint8 destip[4] = { 192, 168, 100, 100 };
//uint16 destport = 55056;
uint16 destport = 5000;
uint8 destip_veri[4] = { 0, 0, 0, 0 };
uint16 destport_veri = 0;
int UDP_RX_flag = 0;
int UDP_status = 0;
int send_fail = 0;
int recv_iter;
unsigned int recv_temp;
unsigned int recv_temp_h;
unsigned int recv_temp_l;

int i;

int PC_mode;
int PC_status;
unsigned int temp_sum_h=0, temp_sum_l=0;
unsigned long temp_sum = 0;
float temp_float = 0.;


int coil_num = 0;
int is_debug_mode = 0;
int sen_mode = 0;
int is_ready = 0;
int error_cnt[8] = {0,};

int ref_gen_mode = 0;
int ref_num = 0;


__interrupt void cc(void) {
	ccTimer1start = ReadCpuTimer1Counter();
	cc_cnt++;

	if(is_debug_mode&&Flag.init_charge_done){
	    EALLOW;
	    PieVectTable.EPWM2_INT = &cc_debug;
	    EDIS;
	}





	if (reset_inv_num >= 2 * Fsw) {
		if (Flag.OverallMode == OVERALL_MODE_INIT) {
			init_mode_spi_func();
		} else if (Flag.OverallMode == OVERALL_MODE_INV_TEST) {
			inv_test_mode_spi_func();
		} else if (Flag.OverallMode == OVERALL_MODE_IDLE) {
			idle_mode_spi_func();
		} else if (Flag.OverallMode == OVERALL_MODE_RUN) {
			run_mode_spi_func();
			//convert_binary_to_float(&test_fault_a, UDP_data[0], UDP_data[1]);
			//convert_binary_to_float(&test_fault_b, UDP_data[2], UDP_data[3]);
		} else if (Flag.OverallMode == OVERALL_MODE_SAFETURNOFF) {
			run_mode_spi_func();
			//convert_binary_to_float(&test_fault_a, UDP_data[0], UDP_data[1]);
			//convert_binary_to_float(&test_fault_b, UDP_data[2], UDP_data[3]);
		} else if (Flag.OverallMode == OVERALL_MODE_INVRESET) {
			if (mode_changed) {
				reset_inv_num = 1;//all inv reset
				reset_inv_list[0] = 0;
				reset_inv_list[1] = 0;
				reset_inv_list[2] = 0;
				reset_inv_list[3] = 0;
				reset_inv_list[4] = 0;
				reset_inv_list[5] = 0;
				reset_inv_list[6] = 0;
				reset_inv_list[7] = 0;

			}else {
				init_mode_spi_func();
			}
		} else {
			Flag.OverallMode = OVERALL_MODE_INIT;
			Flag.ModeStatus = MODE_STATUS_CHECKING;
			//init_mode_spi_func();
			mode_changed = true;
		}
	} else {
			Flag.OverallMode = OVERALL_MODE_INIT;
		Flag.ModeStatus = MODE_STATUS_CHECKING;
		//init_mode_spi_func();
		//mode_changed = true;
	}

	if (reset_inv_num < 1) {
		reset_inv_num++; // count -100000 to 0 -> wait 10 secs
	} else if (reset_inv_num <= using_inv_num) {
		reset_INV_boards(); // reset INV 1~8
		Flag.init_charge_done = true;
	} else if (reset_inv_num < 3 * Fsw) { // wait 2 more seconds after reset inverters
		reset_inv_num++;
		if (reset_inv_num == Fsw) { // release reset signals again
			GpioDataRegs.GPASET.bit.GPIO20 = 0x1;
			GpioDataRegs.GPASET.bit.GPIO14 = 0x1;
			GpioDataRegs.GPBSET.bit.GPIO63 = 0x1;
			GpioDataRegs.GPBSET.bit.GPIO62 = 0x1;
			GpioDataRegs.GPBSET.bit.GPIO59 = 0x1;
			GpioDataRegs.GPBSET.bit.GPIO57 = 0x1;
			GpioDataRegs.GPASET.bit.GPIO12 = 0x1;
			GpioDataRegs.GPASET.bit.GPIO10 = 0x1;
		}
	}

	disconnect_cnt++;
	if (disconnect_cnt == Fsw) {
		Flag.OverallMode = OVERALL_MODE_INIT;
		Flag.ModeStatus = MODE_STATUS_CHECKING;
		mode_changed = true;
		disconnect_cnt = 0;
	}

	if (UDP_status == SOCK_UDP) {
		recv_len = getSn_RX_RSR(SOCK_1); // header 포함한 길이
		if (UDP_RX_flag == 0 && recv_len > 0) { // RX check -> send
			UDP_RX_flag = 1;

			send_len = 0;

			AddSendHeaderData(send_buf, Flag.OverallMode, Flag.ModeStatus,
					&send_len);

			if (Flag.OverallMode == OVERALL_MODE_INIT) {
				AddSendShortBinaryData(send_buf, UDP_data[0], &send_len); // CON_LOST INVs
				AddSendShortBinaryData(send_buf, UDP_data[1], &send_len); // CON wrong INVs
			} else if (Flag.OverallMode == OVERALL_MODE_INV_TEST) {
				AddSendShortBinaryData(send_buf, UDP_data[0], &send_len); // current fault
				AddSendShortBinaryData(send_buf, UDP_data[1], &send_len); // voltage fault
			} else if (Flag.OverallMode == OVERALL_MODE_IDLE
					|| Flag.OverallMode == OVERALL_MODE_RUN) {
				AddSendShortBinaryData(send_buf, UDP_data[0], &send_len); // current fault
				AddSendShortBinaryData(send_buf, UDP_data[1], &send_len); // voltage fault
				for (i = 0; i < using_inv_num; i++) {
					AddSendBinaryData(send_buf, UDP_data[2 * i + 2],
							UDP_data[2 * i + 3], &send_len); // Ii_H, Ii_L
				}
			}

			if (send_len
					!= sendto(SOCK_1, send_buf, send_len, destip, destport)) { // send
				send_fail++;
				//main();

				_close(SOCK_1);  // close SOCK_1
				socket(SOCK_1, Sn_MR_UDP, SOCK_1_PORT, 0); // open SOCK_1 within UDP mode;
			}

			for (i = 0; i < 50; i++) {
				send_buf[i] = 0;
			}
		} else if (UDP_RX_flag == 1) { // recv
			/*
			 if (Flag.OverallMode == OVERALL_MODE_INIT) {
			 recv_len = UDP_HEADER_LEN + INIT_RECV_LEN;
			 } else if (Flag.OverallMode == OVERALL_MODE_INV_TEST) {
			 recv_len = UDP_HEADER_LEN + INV_TEST_RECV_LEN;
			 } else if (Flag.OverallMode == OVERALL_MODE_IDLE) {
			 recv_len = UDP_HEADER_LEN + IDLE_RECV_LEN;
			 } else if (Flag.OverallMode == OVERALL_MODE_INV_TEST) {
			 recv_len = UDP_HEADER_LEN + RUN_RECV_LEN;
			 }
			 */

			recv_len = recvfrom(SOCK_1, recv_buf, recv_len, destip, &destport); // recv 1바이트씩 읽은 길이 반환
			recv_iter = 0;

			recv_temp = ReadRecvShortData(recv_buf, &recv_iter); // 0-3
			recv_temp_h = recv_temp >> 8; // 0, 1
			recv_temp_l = recv_temp & 0x00FF; // 2, 3

			PC_mode = recv_temp_h;
			PC_status = recv_temp_l;

			recv_temp = ReadRecvShortData(recv_buf, &recv_iter); // 4-7
			if (recv_temp != 0xAA55) {
				Flag.OverallMode = OVERALL_MODE_INIT;
				Flag.ModeStatus = MODE_STATUS_CON_ERROR;
				mode_changed = true;
			} else if (PC_mode == OVERALL_MODE_INIT) { // force mode change (from error status)
				if (Flag.ModeStatus != MODE_STATUS_OK) {
					Flag.ModeStatus = MODE_STATUS_CHECKING;
				}
				if (recv_len == 8) {
					recv_temp = ReadRecvShortData(recv_buf, &recv_iter); // 8-11
					recv_temp = ReadRecvShortData(recv_buf, &recv_iter); // 12-15
					if (recv_temp > 0 && recv_temp < 9
							&& recv_temp != using_inv_num) {
						using_inv_num = recv_temp;
						reset_inv_num =
								(Flag.init_charge_done) ? -Fsw : -Fsw * 10; //wait before reset
					}
				} else if (recv_len == 16) {
					recv_temp = ReadRecvShortData(recv_buf, &recv_iter); // 8-11
					recv_temp = ReadRecvShortData(recv_buf, &recv_iter); // 12-15
					if (recv_temp > 0 && recv_temp < 9
							&& recv_temp != using_inv_num) {
						using_inv_num = recv_temp;
						reset_inv_num =
								(Flag.init_charge_done) ? -Fsw : -Fsw * 10; //wait before reset
					}
					Kp_H = ReadRecvShortData(recv_buf, &recv_iter); // Kp_H
					Kp_L = ReadRecvShortData(recv_buf, &recv_iter); // Kp_L
					Kp_ulong = (unsigned long) (Kp_H) * 256 * 256 + Kp_L;
					Kp = *(float *) (&Kp_ulong);
					if (Kp <= 0 || Kp > 10000) {
						Kp = default_Kp;
						Kp_H = 0;
						Kp_L = 0;
					}
					Ki_H = ReadRecvShortData(recv_buf, &recv_iter); // Kp_H
					Ki_L = ReadRecvShortData(recv_buf, &recv_iter); // Ii_L
					Ki_ulong = (unsigned long) (Ki_H) * 256 * 256 + Ki_L;
					Ki = *(float *) (&Ki_ulong);
					if (Ki <= 0 || Ki > 100) {
						Ki = default_Ki;
						Ki_H = 0;
						Ki_L = 0;
					}
				}
				Flag.OverallMode = OVERALL_MODE_INIT;
				// mode_changed = true;
			} else if (PC_mode == OVERALL_MODE_INV_TEST) {
				if (Flag.ModeStatus == MODE_STATUS_OK) {
					if (Flag.OverallMode != OVERALL_MODE_INV_TEST) {
						mode_changed = true;
					}
					Flag.OverallMode = OVERALL_MODE_INV_TEST;
					Flag.ModeStatus = MODE_STATUS_OK;
				} else if (Flag.ModeStatus != MODE_STATUS_CHECKING) {
					Flag.OverallMode = OVERALL_MODE_INIT;
					Flag.ModeStatus = MODE_STATUS_CHECKING;
				}
				/* else if (PC_status == MODE_STATUS_CON_ERROR || PC_status == MODE_STATUS_CON_LOST || PC_status == MODE_STATUS_ERROR) {
				 Flag.ModeStatus = MODE_STATUS_SUP_ERROR;
				 } else if (PC_status != MODE_STATUS_CHECKING && PC_status != MODE_STATUS_OK) {
				 Flag.ModeStatus = MODE_STATUS_ERROR;
				 } else if (Flag.ModeStatus != MODE_STATUS_CHECKING && Flag.ModeStatus != MODE_STATUS_OK) {
				 Flag.ModeStatus = MODE_STATUS_CHECKING;
				 } */
			} else if (PC_mode == OVERALL_MODE_IDLE) {
				if (Flag.ModeStatus == MODE_STATUS_OK
						|| Flag.ModeStatus == MODE_STATUS_CHECKING) {
					if (Flag.OverallMode != OVERALL_MODE_IDLE) {
						mode_changed = true;
					}
					Flag.OverallMode = OVERALL_MODE_IDLE;
					Flag.ModeStatus = MODE_STATUS_OK;

					recv_temp = ReadRecvShortData(recv_buf, &recv_iter); // 8-11
					recv_temp = ReadRecvShortData(recv_buf, &recv_iter); // 12-15
					if (recv_temp == CC_IDLE_MODE_KEEP) {
						Flag.CCIdleMode = CC_IDLE_MODE_KEEP;
					} else {
						Flag.CCIdleMode = CC_IDLE_MODE_ZERO;
						for (i = 0; i < 16; i++) {
							current_reference[i] = 0x0000;
						}
					}
				} else if (Flag.ModeStatus != MODE_STATUS_CHECKING) {
					Flag.OverallMode = OVERALL_MODE_INIT;
					Flag.ModeStatus = MODE_STATUS_CHECKING;
					// handle the error
					for (i = 0; i < 16; i++) {
						current_reference[i] = 0x0000;
					}
				}
			} else if (PC_mode == OVERALL_MODE_RUN) {
				if (Flag.ModeStatus == MODE_STATUS_OK) {
					if (Flag.OverallMode != OVERALL_MODE_RUN) {
						mode_changed = true;
					}
					Flag.OverallMode = OVERALL_MODE_RUN;
					Flag.ModeStatus = MODE_STATUS_OK;

					// update SPI data
					for (i = 0; i < using_inv_num; i++) {
						current_reference[2 * i] = ReadRecvShortData(recv_buf,
								&recv_iter); // Ii_H
						current_reference[2 * i + 1] = ReadRecvShortData(
								recv_buf, &recv_iter); // Ii_L
					}
					// calc feedforward voltages and send them
					//voltage_reference[0] = 0x0000; // V1_H
					//voltage_reference[1] = 0x0000; // V1_L...
				} else if (Flag.ModeStatus != MODE_STATUS_CHECKING) {
					Flag.OverallMode = OVERALL_MODE_INIT;
					Flag.ModeStatus = MODE_STATUS_CHECKING;
					// handle the error
					for (i = 0; i < 16; i++) {
						current_reference[i] = 0x0000;
					}
				}
			} else if (PC_mode == OVERALL_MODE_SAFETURNOFF) {
				if (Flag.ModeStatus == MODE_STATUS_OK) {
					if (Flag.OverallMode != OVERALL_MODE_SAFETURNOFF) {
						mode_changed = true;
					}
					Flag.OverallMode = OVERALL_MODE_SAFETURNOFF;
					Flag.ModeStatus = MODE_STATUS_OK;

					// update SPI data
					for (i = 0; i < using_inv_num; i++) {
						current_reference[2 * i] = ReadRecvShortData(recv_buf,
								&recv_iter); // Ii_H
						current_reference[2 * i + 1] = ReadRecvShortData(
								recv_buf, &recv_iter); // Ii_L
					}
					// calc feedforward voltages and send them
					//voltage_reference[0] = 0x0000; // V1_H
					//voltage_reference[1] = 0x0000; // V1_L...
				} else if (Flag.ModeStatus != MODE_STATUS_CHECKING) {
					Flag.OverallMode = OVERALL_MODE_SAFETURNOFF;
					Flag.ModeStatus = MODE_STATUS_CHECKING;
					// handle the error
					for (i = 0; i < 16; i++) {
						current_reference[i] = 0x0000;
					}
				}
			} else if (PC_mode == OVERALL_MODE_INVRESET) {
				if (Flag.ModeStatus == MODE_STATUS_OK) {
					if (Flag.OverallMode != OVERALL_MODE_INVRESET&&Flag.OverallMode !=OVERALL_MODE_INIT){
						mode_changed = true;
					}
					Flag.OverallMode = OVERALL_MODE_INVRESET;
					Flag.ModeStatus = MODE_STATUS_OK;

					// update SPI data
					for (i = 0; i < using_inv_num; i++) {
						current_reference[2 * i] = ReadRecvShortData(recv_buf,
								&recv_iter); // Ii_H
						current_reference[2 * i + 1] = ReadRecvShortData(
								recv_buf, &recv_iter); // Ii_L
					}
					// calc feedforward voltages and send them
					//voltage_reference[0] = 0x0000; // V1_H
					//voltage_reference[1] = 0x0000; // V1_L...
				} else if (Flag.ModeStatus != MODE_STATUS_CHECKING) {
					Flag.OverallMode = OVERALL_MODE_INVRESET;
					test_fault_a = Flag.ModeStatus;
					Flag.ModeStatus = MODE_STATUS_CHECKING;

					// handle the error
					for (i = 0; i < 16; i++) {
						current_reference[i] = 0x0000;
					}
				}
			} else { // escape
				Flag.OverallMode = OVERALL_MODE_INIT;
				Flag.ModeStatus = MODE_STATUS_CHECKING;
				mode_changed = true;
			}

			UDP_RX_flag = 0;
			disconnect_cnt = 0;

			// empty the recv_buf
			//for (i=0; i<recv_iter; i++) {
			//for (i=0; i<=recv_len; i++) {
			//	recv_buf[i] = 0;
			//}

		}
	} else { // check UDP status
		UDP_status = getSn_SSR(SOCK_1);
		if (UDP_status != SOCK_UDP) {
			_close(SOCK_1);  // close SOCK_1
			socket(SOCK_1, Sn_MR_UDP, SOCK_1_PORT, 0); // open SOCK_1 within UDP mode;
		}
	}

	if (FanCon == 1) {
		FAN_ON();
	} else {
		FAN_OFF();
	}

	//da[0] = &test_fault_c;
	//da_type[0] = 0;
	//da_scale[0] = 2048./4;
	//da_mid[0] = 0;

	/*
	 da[1] = &INV.Ia;
	 da_type[1] = 0;
	 da_scale[1] = 2048./1;
	 da_mid[1] = 0;

	 da[2] = &test_fault_c;
	 da_type[2] = 0;
	 da_scale[2] = 2048./4;
	 da_mid[2] = 0;

	 da[3] = &test_fault_c;
	 da_type[3] = 0;
	 da_scale[3] = 2048./4;
	 da_mid[3] = 0;
	 */

	//SpiDacOut();
	test_fault_b = (ccTimer1start - ReadCpuTimer1Counter()) * SYS_CLK_PRD;
	if (ccTime < test_fault_b) {
		ccTime = test_fault_b;
	}

	// Clear INT flag for this timer
	EPwm2Regs.ETCLR.bit.INT = 1;
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}

__interrupt void cc_debug(void) {

    static int time_cnt = 0;
    ccTimer1start = ReadCpuTimer1Counter();
    cc_debug_cnt++;

    if(!is_debug_mode){
        EALLOW;
        PieVectTable.EPWM2_INT = &cc;
        EDIS;
    }





    if (!is_ready)
    {
        Flag.OverallMode = OVERALL_MODE_INIT;
        init_mode_spi_func();
    }
    else
    {
        if (sen_mode)
        {
            for (i = 0; i < 8; i++)
            {
                current_ref_set[i] = 0.0;
            }
            time_cnt++;
            if(time_cnt == 5000*2){
                coil_num++;
                time_cnt=0;
            }
            if(coil_num<8){
                current_ref_set[coil_num] = 10.0;
            }else if(coil_num<9){

            }else{
                coil_num=0;
            }

        }
        else
        {
            coil_num = 0;
            time_cnt = 0;

        }

        for (i = 0; i < 8; i++)
        {

            current_ref[i] =
                    ((current_ref_set[i] >= 10) ?
                            10 :
                            ((current_ref_set[i] <= -10) ? -10 : current_ref_set[i]));
            if (current_ref_set[i] == 0.0)
            {
                current_ref[i] = 0.00000000001;
            }
        }



        for (i = 0; i < 8; i++)
        {
            temp_sum = *(unsigned long *) (&(current_ref[i]));
            temp_sum_h = temp_sum >> 16;
            temp_sum_l = temp_sum - temp_sum_h * 65536;

            current_reference[2 * i] = temp_sum_h;
            current_reference[2 * i + 1] = temp_sum_l;
        }

        Flag.OverallMode = OVERALL_MODE_RUN;
        debug_mode_spi_func();

        for (i = 0; i < 8; i++)
        {
            temp_sum = current_sen_debug[2 * i] * 65536;
            temp_sum = temp_sum + current_sen_debug[2 * i + 1];
            temp_float = *((float *) (&temp_sum));

            current_sen[i] = temp_float;
        }

        for (i = 0; i < 8; i++)
        {
//            if (fabs(current_sen[i] - current_ref[i]) > 2)
//            {
//
//                if (error_cnt[i]++ > 5000)
//                {
//                    is_ready = 0;
//                }
//            }
//            else
//            {
//                if (error_cnt[i]-- < 0)
//                {
//                    error_cnt[i] = 0;
//                }
//            }

    }
}








    test_fault_b = (ccTimer1start - ReadCpuTimer1Counter()) * SYS_CLK_PRD;
    if (ccTime < test_fault_b) {
        ccTime = test_fault_b;
    }

    // Clear INT flag for this timer
    EPwm2Regs.ETCLR.bit.INT = 1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}


void reset_INV_boards(void) {
	// INV 1
	if (reset_inv_num == 1) {
		if (reset_inv_list[0] == 1) {
			reset_inv_num++;
		} else if (reset_inv_waiting == 0) {
			GpioDataRegs.GPACLEAR.bit.GPIO20 = 0x1;
			reset_inv_waiting = Fsw / 20; // 50ms
			reset_inv_total_cnt++;
		} else {
			reset_inv_waiting--;
			if (reset_inv_waiting == 0) {
				GpioDataRegs.GPASET.bit.GPIO20 = 0x1;
				reset_inv_num++;
				reset_inv_list[0] = 1;
			}
		}
	}
	// INV 2
	else if (reset_inv_num == 2) {
		if (reset_inv_list[1] != 0) {
			reset_inv_num++;
		} else if (reset_inv_waiting == 0) {
			GpioDataRegs.GPACLEAR.bit.GPIO14 = 0x1;
			reset_inv_waiting = Fsw / 20; // 50ms
			reset_inv_total_cnt++;
		} else {
			reset_inv_waiting--;
			if (reset_inv_waiting == 0) {
				GpioDataRegs.GPASET.bit.GPIO14 = 0x1;
				reset_inv_num++;
				reset_inv_list[1] = 1;
			}
		}
	}
	// INV 3
	else if (reset_inv_num == 3) {
		if (reset_inv_list[2] != 0) {
			reset_inv_num++;
		} else if (reset_inv_waiting == 0) {
			GpioDataRegs.GPBCLEAR.bit.GPIO63 = 0x1;
			reset_inv_waiting = Fsw / 20; // 50ms
			reset_inv_total_cnt++;
		} else {
			reset_inv_waiting--;
			if (reset_inv_waiting == 0) {
				GpioDataRegs.GPBSET.bit.GPIO63 = 0x1;
				reset_inv_num++;
				reset_inv_list[2] = 1;
			}
		}
	}
	// INV 4
	else if (reset_inv_num == 4) {
		if (reset_inv_list[3] != 0) {
			reset_inv_num++;
		} else if (reset_inv_waiting == 0) {
			GpioDataRegs.GPBCLEAR.bit.GPIO62 = 0x1;
			reset_inv_waiting = Fsw / 20; // 50ms
			reset_inv_total_cnt++;
		} else {
			reset_inv_waiting--;
			if (reset_inv_waiting == 0) {
				GpioDataRegs.GPBSET.bit.GPIO62 = 0x1;
				reset_inv_num++;
				reset_inv_list[3] = 1;
			}
		}
	}
	// INV 5
	else if (reset_inv_num == 5) {
		if (reset_inv_list[4] != 0) {
			reset_inv_num++;
		} else if (reset_inv_waiting == 0) {
			GpioDataRegs.GPBCLEAR.bit.GPIO59 = 0x1;
			reset_inv_waiting = Fsw / 20; // 50ms
			reset_inv_total_cnt++;
		} else {
			reset_inv_waiting--;
			if (reset_inv_waiting == 0) {
				GpioDataRegs.GPBSET.bit.GPIO59 = 0x1;
				reset_inv_num++;
				reset_inv_list[4] = 1;
			}
		}
	}
	// INV 6
	else if (reset_inv_num == 6) {
		if (reset_inv_list[5] != 0) {
			reset_inv_num++;
		} else if (reset_inv_waiting == 0) {
			GpioDataRegs.GPBCLEAR.bit.GPIO57 = 0x1;
			reset_inv_waiting = Fsw / 20; // 50ms
			reset_inv_total_cnt++;
		} else {
			reset_inv_waiting--;
			if (reset_inv_waiting == 0) {
				GpioDataRegs.GPBSET.bit.GPIO57 = 0x1;
				reset_inv_num++;
				reset_inv_list[5] = 1;
			}
		}
	}
	// INV 7
	else if (reset_inv_num == 7) {
		if (reset_inv_list[6] != 0) {
			reset_inv_num++;
		} else if (reset_inv_waiting == 0) {
			GpioDataRegs.GPACLEAR.bit.GPIO12 = 0x1;
			reset_inv_waiting = Fsw / 20; // 50ms
			reset_inv_total_cnt++;
		} else {
			reset_inv_waiting--;
			if (reset_inv_waiting == 0) {
				GpioDataRegs.GPASET.bit.GPIO12 = 0x1;
				reset_inv_num++;
				reset_inv_list[6] = 1;
			}
		}
	}
	// INV 8
	else if (reset_inv_num == 8) {
		if (reset_inv_list[7] != 0) {
			reset_inv_num++;
		} else if (reset_inv_waiting == 0) {
			GpioDataRegs.GPACLEAR.bit.GPIO10 = 0x1;
			reset_inv_waiting = Fsw / 20; // 50ms
			reset_inv_total_cnt++;
		} else {
			reset_inv_waiting--;
			if (reset_inv_waiting == 0) {
				GpioDataRegs.GPASET.bit.GPIO10 = 0x1;
				reset_inv_num++;
				reset_inv_list[7] = 1;
			}
		}
	}
}
