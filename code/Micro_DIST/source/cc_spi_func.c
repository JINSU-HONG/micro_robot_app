#include "F2837xS_variable.h"
#include "cc_spi_func.h"

//#pragma CODE_SECTION(init_mode_spi_func, "ramfuncs");
//#pragma CODE_SECTION(inv_test_mode_spi_func, "ramfuncs");
#pragma CODE_SECTION(idle_mode_spi_func, "ramfuncs");
#pragma CODE_SECTION(CalcChecksum, "ramfuncs");



int check_sum_cnt[8] = {0,};
int check_sum_fail[8] = {0,};

unsigned int debug_val[10] = {0,};



void init_mode_spi_func(void)
{
    int mode_plus_status = Flag.OverallMode * 16 + Flag.ModeStatus;

    // connection test
    INV_data_buf[0] = mode_plus_status;
    INV_data_buf[1] = 0;
    INV_data_buf[2] = 0;
    INV_data_buf[3] = 0;
    INV_data_buf[4] = CalcChecksum(INV_data_buf, 4);

    if (using_inv_num >= 1)
    {
        INV0_CS_0 = INV_data_buf[0];
        INV0_CS_1 = INV_data_buf[1];
        INV0_CS_2 = INV_data_buf[2];
        INV0_CS_3 = INV_data_buf[3];
        INV0_CS_4 = INV_data_buf[4];
    }

    if (using_inv_num >= 2)
    {
        INV1_CS_0 = INV_data_buf[0];
        INV1_CS_1 = INV_data_buf[1];
        INV1_CS_2 = INV_data_buf[2];
        INV1_CS_3 = INV_data_buf[3];
        INV1_CS_4 = INV_data_buf[4];
    }

    if (using_inv_num >= 3)
    {
        INV2_CS_0 = INV_data_buf[0];
        INV2_CS_1 = INV_data_buf[1];
        INV2_CS_2 = INV_data_buf[2];
        INV2_CS_3 = INV_data_buf[3];
        INV2_CS_4 = INV_data_buf[4];
    }

    if (using_inv_num >= 4)
    {
        INV3_CS_0 = INV_data_buf[0];
        INV3_CS_1 = INV_data_buf[1];
        INV3_CS_2 = INV_data_buf[2];
        INV3_CS_3 = INV_data_buf[3];
        INV3_CS_4 = INV_data_buf[4];
    }

    if (using_inv_num >= 5)
    {
        INV4_CS_0 = INV_data_buf[0];
        INV4_CS_1 = INV_data_buf[1];
        INV4_CS_2 = INV_data_buf[2];
        INV4_CS_3 = INV_data_buf[3];
        INV4_CS_4 = INV_data_buf[4];
    }

    if (using_inv_num >= 6)
    {
        INV5_CS_0 = INV_data_buf[0];
        INV5_CS_1 = INV_data_buf[1];
        INV5_CS_2 = INV_data_buf[2];
        INV5_CS_3 = INV_data_buf[3];
        INV5_CS_4 = INV_data_buf[4];
    }

    if (using_inv_num >= 7)
    {
        INV6_CS_0 = INV_data_buf[0];
        INV6_CS_1 = INV_data_buf[1];
        INV6_CS_2 = INV_data_buf[2];
        INV6_CS_3 = INV_data_buf[3];
        INV6_CS_4 = INV_data_buf[4];
    }

    if (using_inv_num >= 8)
    {
        INV7_CS_0 = INV_data_buf[0];
        INV7_CS_1 = INV_data_buf[1];
        INV7_CS_2 = INV_data_buf[2];
        INV7_CS_3 = INV_data_buf[3];
        INV7_CS_4 = INV_data_buf[4];
    }

    delaycc(1e-6);
    CS2_TEST_SEND = 0; // send-SPI signal to FPGA
    delaycc(30e-6);

    INV_status[0] = 0; // wrong data
    INV_status[1] = 0; // no reply
    //INV_status[2] = 0;
    //INV_status[3] = 0;

    INV_data_buf[0] = INV0_CS_0; // connection test
    INV_data_buf[1] = INV0_CS_1; // CON_LOST INVs
    INV_data_buf[2] = INV0_CS_2; // dummy
    INV_data_buf[3] = INV0_CS_3; // dummy
    INV_data_buf[4] = INV0_CS_4; // dummy

    if (using_inv_num >= 1 && CalcChecksum(INV_data_buf, 5) == 0)
    {
        check_sum_cnt[0]++;
        if (INV_data_buf[0] == 0xFFFF || INV_data_buf[1] == 0xFFFF)
        { // CON_LOST
            INV_status[1] += 1;
            if (reset_inv_num
                    == 3 * Fsw&& reset_inv_total_cnt < RESET_INV_MAX_TRIAL)
            {
                if (reset_inv_list[0] <= 5)
                {
                    reset_inv_list[0]++;
                }
                else
                {
                    reset_inv_num = 1;
                    reset_inv_list[0] = 0;
                }
            }
        }
        else if (INV_data_buf[0] != 0xAAAA || INV_data_buf[1] != 0x5555)
        { // data check
            INV_status[0] += 1;
            if (reset_inv_num
                    == 3 * Fsw&& reset_inv_total_cnt < RESET_INV_MAX_TRIAL)
            {
                if (reset_inv_list[0] <= 5)
                {
                    reset_inv_list[0]++;
                }
                else
                {
                    reset_inv_num = 1;
                    reset_inv_list[0] = 0;
                }
            }
        }
        else
        {
            reset_inv_list[0] = 1;
        }

    }
    else
    {

    }

    INV_data_buf[0] = INV1_CS_0; // connection test
    INV_data_buf[1] = INV1_CS_1; // CON_LOST INVs
    INV_data_buf[2] = INV1_CS_2; // dummy
    INV_data_buf[3] = INV1_CS_3; // dummy
    INV_data_buf[4] = INV1_CS_4; // dummy

    if (using_inv_num >= 2 && CalcChecksum(INV_data_buf, 5) == 0)
    {
        check_sum_cnt[1]++;
        if (INV_data_buf[0] == 0xFFFF || INV_data_buf[1] == 0xFFFF)
        { // CON_LOST
            INV_status[1] += 2;
            if (reset_inv_num
                    == 3 * Fsw&& reset_inv_total_cnt < RESET_INV_MAX_TRIAL)
            {
                if (reset_inv_list[1] <= 5)
                {
                    reset_inv_list[1]++;
                }
                else
                {
                    reset_inv_num = 2;
                    reset_inv_list[1] = 0;
                }
            }
        }
        else if (INV_data_buf[0] != 0xAAAA || INV_data_buf[1] != 0x5555)
        { // data check
            INV_status[0] += 2;
            if (reset_inv_num
                    == 3 * Fsw&& reset_inv_total_cnt < RESET_INV_MAX_TRIAL)
            {
                if (reset_inv_list[1] <= 5)
                {
                    reset_inv_list[1]++;
                }
                else
                {
                    reset_inv_num = 2;
                    reset_inv_list[1] = 0;
                }
            }
        }
        else
        {
            reset_inv_list[1] = 1;
        }
    }
    else
    {

    }

    INV_data_buf[0] = INV2_CS_0; // connection test
    INV_data_buf[1] = INV2_CS_1; // CON_LOST INVs
    INV_data_buf[2] = INV2_CS_2; // dummy
    INV_data_buf[3] = INV2_CS_3; // dummy
    INV_data_buf[4] = INV2_CS_4; // dummy

    if (using_inv_num >= 3 && CalcChecksum(INV_data_buf, 5) == 0)
    {
        check_sum_cnt[2]++;
        if (INV_data_buf[0] == 0xFFFF || INV_data_buf[1] == 0xFFFF)
        { // CON_LOST
            INV_status[1] += 4;
            if (reset_inv_num
                    == 3 * Fsw&& reset_inv_total_cnt < RESET_INV_MAX_TRIAL)
            {
                if (reset_inv_list[2] <= 5)
                {
                    reset_inv_list[2]++;
                }
                else
                {
                    reset_inv_num = 3;
                    reset_inv_list[2] = 0;
                }
            }
        }
        else if (INV_data_buf[0] != 0xAAAA || INV_data_buf[1] != 0x5555)
        { // data check
            INV_status[0] += 4;
            if (reset_inv_num
                    == 3 * Fsw&& reset_inv_total_cnt < RESET_INV_MAX_TRIAL)
            {
                if (reset_inv_list[2] <= 5)
                {
                    reset_inv_list[2]++;
                }
                else
                {
                    reset_inv_num = 3;
                    reset_inv_list[2] = 0;
                }
            }
        }
        else
        {
            reset_inv_list[2] = 1;
        }
    }
    else
    {

    }
    INV_data_buf[0] = INV3_CS_0; // connection test
    INV_data_buf[1] = INV3_CS_1; // CON_LOST INVs
    INV_data_buf[2] = INV3_CS_2; // dummy
    INV_data_buf[3] = INV3_CS_3; // dummy
    INV_data_buf[4] = INV3_CS_4; // dummy

    if (using_inv_num >= 4 && CalcChecksum(INV_data_buf, 5) == 0)
    {
        check_sum_cnt[3]++;
        if (INV_data_buf[0] == 0xFFFF || INV_data_buf[1] == 0xFFFF)
        { // CON_LOST
            INV_status[1] += 8;
            if (reset_inv_num
                    == 3 * Fsw&& reset_inv_total_cnt < RESET_INV_MAX_TRIAL)
            {
                if (reset_inv_list[3] <= 5)
                {
                    reset_inv_list[3]++;
                }
                else
                {
                    reset_inv_num = 4;
                    reset_inv_list[3] = 0;
                }
            }
        }
        else if (INV_data_buf[0] != 0xAAAA || INV_data_buf[1] != 0x5555)
        { // data check
            INV_status[0] += 8;
            if (reset_inv_num
                    == 3 * Fsw&& reset_inv_total_cnt < RESET_INV_MAX_TRIAL)
            {
                if (reset_inv_list[3] <= 5)
                {
                    reset_inv_list[3]++;
                }
                else
                {
                    reset_inv_num = 4;
                    reset_inv_list[3] = 0;
                }
            }
        }
        else
        {
            reset_inv_list[3] = 1;
        }
    }

    INV_data_buf[0] = INV4_CS_0; // connection test
    INV_data_buf[1] = INV4_CS_1; // CON_LOST INVs
    INV_data_buf[2] = INV4_CS_2; // dummy
    INV_data_buf[3] = INV4_CS_3; // dummy
    INV_data_buf[4] = INV4_CS_4; // dummy

    if (using_inv_num >= 5 && CalcChecksum(INV_data_buf, 5) == 0)
    {
        check_sum_cnt[4]++;
        if (INV_data_buf[0] == 0xFFFF || INV_data_buf[1] == 0xFFFF)
        { // CON_LOST
            INV_status[1] += 16;
            if (reset_inv_num
                    == 3 * Fsw&& reset_inv_total_cnt < RESET_INV_MAX_TRIAL)
            {
                if (reset_inv_list[4] <= 5)
                {
                    reset_inv_list[4]++;
                }
                else
                {
                    reset_inv_num = 5;
                    reset_inv_list[4] = 0;
                }
            }
        }
        else if (INV_data_buf[0] != 0xAAAA || INV_data_buf[1] != 0x5555)
        { // data check
            INV_status[0] += 16;
            if (reset_inv_num
                    == 3 * Fsw&& reset_inv_total_cnt < RESET_INV_MAX_TRIAL)
            {
                if (reset_inv_list[4] <= 5)
                {
                    reset_inv_list[4]++;
                }
                else
                {
                    reset_inv_num = 5;
                    reset_inv_list[4] = 0;
                }
            }
        }
        else
        {
            reset_inv_list[4] = 1;
        }
    }

    INV_data_buf[0] = INV5_CS_0; // connection test
    INV_data_buf[1] = INV5_CS_1; // CON_LOST INVs
    INV_data_buf[2] = INV5_CS_2; // dummy
    INV_data_buf[3] = INV5_CS_3; // dummy
    INV_data_buf[4] = INV5_CS_4; // dummy

    if (using_inv_num >= 6 && CalcChecksum(INV_data_buf, 5) == 0)
    {
        check_sum_cnt[5]++;
        if (INV_data_buf[0] == 0xFFFF || INV_data_buf[1] == 0xFFFF)
        { // CON_LOST
            INV_status[1] += 32;
            if (reset_inv_num
                    == 3 * Fsw&& reset_inv_total_cnt < RESET_INV_MAX_TRIAL)
            {
                if (reset_inv_list[5] <= 5)
                {
                    reset_inv_list[5]++;
                }
                else
                {
                    reset_inv_num = 6;
                    reset_inv_list[5] = 0;
                }
            }
        }
        else if (INV_data_buf[0] != 0xAAAA || INV_data_buf[1] != 0x5555)
        { // data check
            INV_status[0] += 32;
            if (reset_inv_num
                    == 3 * Fsw&& reset_inv_total_cnt < RESET_INV_MAX_TRIAL)
            {
                if (reset_inv_list[5] <= 5)
                {
                    reset_inv_list[5]++;
                }
                else
                {
                    reset_inv_num = 6;
                    reset_inv_list[5] = 0;
                }
            }
        }
        else
        {
            reset_inv_list[5] = 1;
        }
    }

    INV_data_buf[0] = INV6_CS_0; // connection test
    INV_data_buf[1] = INV6_CS_1; // CON_LOST INVs
    INV_data_buf[2] = INV6_CS_2; // dummy
    INV_data_buf[3] = INV6_CS_3; // dummy
    INV_data_buf[4] = INV6_CS_4; // dummy

    if (using_inv_num >= 7 && CalcChecksum(INV_data_buf, 5) == 0)
    {
        check_sum_cnt[6]++;
        if (INV_data_buf[0] == 0xFFFF || INV_data_buf[1] == 0xFFFF)
        { // CON_LOST
            INV_status[1] += 64;
            if (reset_inv_num
                    == 3 * Fsw&& reset_inv_total_cnt < RESET_INV_MAX_TRIAL)
            {
                if (reset_inv_list[6] <= 5)
                {
                    reset_inv_list[6]++;
                }
                else
                {
                    reset_inv_num = 7;
                    reset_inv_list[6] = 0;
                }
            }
        }
        else if (INV_data_buf[0] != 0xAAAA || INV_data_buf[1] != 0x5555)
        { // data check
            INV_status[0] += 64;
            if (reset_inv_num
                    == 3 * Fsw&& reset_inv_total_cnt < RESET_INV_MAX_TRIAL)
            {
                if (reset_inv_list[6] <= 5)
                {
                    reset_inv_list[6]++;
                }
                else
                {
                    reset_inv_num = 7;
                    reset_inv_list[6] = 0;
                }
            }
        }
        else
        {
            reset_inv_list[6] = 1;
        }
    }

    INV_data_buf[0] = INV7_CS_0; // connection test
    INV_data_buf[1] = INV7_CS_1; // CON_LOST INVs
    INV_data_buf[2] = INV7_CS_2; // dummy
    INV_data_buf[3] = INV7_CS_3; // dummy
    INV_data_buf[4] = INV7_CS_4; // dummy

    if (using_inv_num >= 8 && CalcChecksum(INV_data_buf, 5) == 0)
    {
        check_sum_cnt[7]++;
        if (INV_data_buf[0] == 0xFFFF || INV_data_buf[1] == 0xFFFF)
        { // CON_LOST
            INV_status[1] += 128;
            if (reset_inv_num
                    == 3 * Fsw&& reset_inv_total_cnt < RESET_INV_MAX_TRIAL)
            {
                if (reset_inv_list[7] <= 5)
                {
                    reset_inv_list[7]++;
                }
                else
                {
                    reset_inv_num = 8;
                    reset_inv_list[7] = 0;
                }
            }
        }
        else if (INV_data_buf[0] != 0xAAAA || INV_data_buf[1] != 0x5555)
        { // data check
            INV_status[0] += 128;
            if (reset_inv_num
                    == 3 * Fsw&& reset_inv_total_cnt < RESET_INV_MAX_TRIAL)
            {
                if (reset_inv_list[7] <= 5)
                {
                    reset_inv_list[7]++;
                }
                else
                {
                    reset_inv_num = 8;
                    reset_inv_list[7] = 0;
                }
            }
        }
        else
        {
            reset_inv_list[7] = 1;
        }
    }

    if (mode_changed)
    {
        mode_changed = false; // pass; INV may be at different mode
    }
    else
    {
        if (INV_status[1] != 0x00)
        {
            // handle connection error
            Flag.ModeStatus = MODE_STATUS_CON_LOST;
        }
        else if (INV_status[0] != 0x00)
        {
            Flag.ModeStatus = MODE_STATUS_CON_ERROR;
        }
        else if (Flag.ModeStatus == MODE_STATUS_CHECKING
                || Flag.ModeStatus == MODE_STATUS_OK)
        {
            // CON_LOST between PC may happen
            Flag.ModeStatus = MODE_STATUS_OK;
        }
    }

    //Flag.ModeStatus = MODE_STATUS_OK; // pass for test

    UDP_data[0] = INV_status[1]; // CON LOST INVs
    UDP_data[1] = INV_status[0]; // CON wrong INVs
}

void inv_test_mode_spi_func(void)
{
    int mode_plus_status = Flag.OverallMode * 16 + Flag.ModeStatus;
    int i;

    // connection test
    INV_data_buf[0] = mode_plus_status;
    INV_data_buf[1] = 0;
    INV_data_buf[2] = 0;
    INV_data_buf[3] = 0;
    INV_data_buf[4] = CalcChecksum(INV_data_buf, 4);

    if (using_inv_num >= 1)
    {
        INV0_CS_0 = INV_data_buf[0];
        INV0_CS_1 = INV_data_buf[1];
        INV0_CS_2 = INV_data_buf[2];
        INV0_CS_3 = INV_data_buf[3];
        INV0_CS_4 = INV_data_buf[4];
    }

    if (using_inv_num >= 2)
    {
        INV1_CS_0 = INV_data_buf[0];
        INV1_CS_1 = INV_data_buf[1];
        INV1_CS_2 = INV_data_buf[2];
        INV1_CS_3 = INV_data_buf[3];
        INV1_CS_4 = INV_data_buf[4];
    }

    if (using_inv_num >= 3)
    {
        INV2_CS_0 = INV_data_buf[1];
        INV2_CS_1 = INV_data_buf[2];
        INV2_CS_2 = INV_data_buf[3];
        INV2_CS_3 = INV_data_buf[4];
        INV2_CS_4 = INV_data_buf[5];
    }

    if (using_inv_num >= 4)
    {
        INV3_CS_0 = INV_data_buf[0];
        INV3_CS_1 = INV_data_buf[1];
        INV3_CS_2 = INV_data_buf[2];
        INV3_CS_3 = INV_data_buf[3];
        INV3_CS_4 = INV_data_buf[4];
    }

    if (using_inv_num >= 5)
    {
        INV4_CS_0 = INV_data_buf[0];
        INV4_CS_1 = INV_data_buf[1];
        INV4_CS_2 = INV_data_buf[2];
        INV4_CS_3 = INV_data_buf[3];
        INV4_CS_4 = INV_data_buf[4];
    }

    if (using_inv_num >= 6)
    {
        INV5_CS_0 = INV_data_buf[0];
        INV5_CS_1 = INV_data_buf[1];
        INV5_CS_2 = INV_data_buf[2];
        INV5_CS_3 = INV_data_buf[3];
        INV5_CS_4 = INV_data_buf[4];
    }

    if (using_inv_num >= 7)
    {
        INV6_CS_0 = INV_data_buf[0];
        INV6_CS_1 = INV_data_buf[1];
        INV6_CS_2 = INV_data_buf[2];
        INV6_CS_3 = INV_data_buf[3];
        INV6_CS_4 = INV_data_buf[4];
    }

    if (using_inv_num >= 8)
    {
        INV7_CS_0 = INV_data_buf[0];
        INV7_CS_1 = INV_data_buf[1];
        INV7_CS_2 = INV_data_buf[2];
        INV7_CS_3 = INV_data_buf[3];
        INV7_CS_4 = INV_data_buf[4];
    }

    delaycc(1e-6);
    CS2_TEST_SEND = 0; // send-SPI signal to FPGA
    delaycc(30e-6);

    INV_status[0] = 0; // current fault
    INV_status[1] = 0; // voltage fault
    INV_status[2] = 0; // inv_test OK
    INV_status[3] = 0; // CON_LOST

    INV_data_buf[0] = INV0_CS_0; // current fault / voltage fault / dummy / inv status
    INV_data_buf[1] = INV0_CS_1; // I1_H
    INV_data_buf[2] = INV0_CS_2; // I1_L
    INV_data_buf[3] = INV0_CS_3; // dummy
    INV_data_buf[4] = INV0_CS_4; // dummy

    if (using_inv_num >= 1 && CalcChecksum(INV_data_buf, 5) == 0)
    {
        check_sum_cnt[0]++;
        if (INV_data_buf[0] == 0xFFFF)
        { // CON_LOST
            INV_status[3] += 1;
        }
        else if (INV_data_buf[0] == 0x1009)
        { // current fault
            INV_status[0] += 1;
        }
        else if (INV_data_buf[0] == 0x0109)
        { // voltage fault
            INV_status[1] += 1;
        }
        else if (INV_data_buf[0] != 0x0002)
        { // inv status
            INV_status[2] += 1;
        }
    }

    INV_data_buf[0] = INV1_CS_0; // current fault / voltage fault / dummy / inv status
    INV_data_buf[1] = INV1_CS_1; // I2_H
    INV_data_buf[2] = INV1_CS_2; // I2_L
    INV_data_buf[3] = INV1_CS_3; // dummy
    INV_data_buf[4] = INV1_CS_4; // dummy

    if (using_inv_num >= 2 && CalcChecksum(INV_data_buf, 5) == 0)
    {
        check_sum_cnt[1]++;
        if (INV_data_buf[0] == 0xFFFF)
        { // CON_LOST
            INV_status[3] += 2;
        }
        else if (INV_data_buf[0] == 0x1009)
        { // current fault
            INV_status[0] += 2;
        }
        else if (INV_data_buf[0] == 0x0109)
        { // voltage fault
            INV_status[1] += 2;
        }
        else if (INV_data_buf[0] != 0x0002)
        { // inv status
            INV_status[2] += 2;
        }
    }

    INV_data_buf[0] = INV2_CS_0; // current fault / voltage fault / dummy / inv status
    INV_data_buf[1] = INV2_CS_1; // I3_H
    INV_data_buf[2] = INV2_CS_2; // I3_L
    INV_data_buf[3] = INV2_CS_3; // dummy
    INV_data_buf[4] = INV2_CS_4; // dummy

    if (using_inv_num >= 3 && CalcChecksum(INV_data_buf, 5) == 0)
    {
        check_sum_cnt[2]++;
        if (INV_data_buf[0] == 0xFFFF)
        { // CON_LOST
            INV_status[3] += 4;
        }
        else if (INV_data_buf[0] == 0x1009)
        { // current fault
            INV_status[0] += 4;
        }
        else if (INV_data_buf[0] == 0x0109)
        { // voltage fault
            INV_status[1] += 4;
        }
        else if (INV_data_buf[0] != 0x0002)
        { // inv status
            INV_status[2] += 4;
        }
    }

    INV_data_buf[0] = INV3_CS_0; // current fault / voltage fault / dummy / inv status
    INV_data_buf[1] = INV3_CS_1; // I4_H
    INV_data_buf[2] = INV3_CS_2; // I4_L
    INV_data_buf[3] = INV3_CS_3; // dummy
    INV_data_buf[4] = INV3_CS_4; // dummy

    if (using_inv_num >= 4 && CalcChecksum(INV_data_buf, 5) == 0)
    {
        check_sum_cnt[3]++;
        if (INV_data_buf[0] == 0xFFFF)
        { // CON_LOST
            INV_status[3] += 8;
        }
        else if (INV_data_buf[0] == 0x1009)
        { // current fault
            INV_status[0] += 8;
        }
        else if (INV_data_buf[0] == 0x0109)
        { // voltage fault
            INV_status[1] += 8;
        }
        else if (INV_data_buf[0] != 0x0002)
        { // inv status
            INV_status[2] += 8;
        }
    }

    INV_data_buf[0] = INV4_CS_0; // current fault / voltage fault / dummy / inv status
    INV_data_buf[1] = INV4_CS_1; // I5_H
    INV_data_buf[2] = INV4_CS_2; // I5_L
    INV_data_buf[3] = INV4_CS_3; // dummy
    INV_data_buf[4] = INV4_CS_4; // dummy

    if (using_inv_num >= 5 && CalcChecksum(INV_data_buf, 5) == 0)
    {
        check_sum_cnt[4]++;
        if (INV_data_buf[0] == 0xFFFF)
        { // CON_LOST
            INV_status[3] += 16;
        }
        else if (INV_data_buf[0] == 0x1009)
        { // current fault
            INV_status[0] += 16;
        }
        else if (INV_data_buf[0] == 0x0109)
        { // voltage fault
            INV_status[1] += 16;
        }
        else if (INV_data_buf[0] != 0x0002)
        { // inv status
            INV_status[2] += 16;
        }
    }

    INV_data_buf[0] = INV5_CS_0; // current fault / voltage fault / dummy / inv status
    INV_data_buf[1] = INV5_CS_1; // I6_H
    INV_data_buf[2] = INV5_CS_2; // I6_L
    INV_data_buf[3] = INV5_CS_3; // dummy
    INV_data_buf[4] = INV5_CS_4; // dummy

    if (using_inv_num >= 6 && CalcChecksum(INV_data_buf, 5) == 0)
    {
        check_sum_cnt[5]++;
        if (INV_data_buf[0] == 0xFFFF)
        { // CON_LOST
            INV_status[3] += 32;
        }
        else if (INV_data_buf[0] == 0x1009)
        { // current fault
            INV_status[0] += 32;
        }
        else if (INV_data_buf[0] == 0x0109)
        { // voltage fault
            INV_status[1] += 32;
        }
        else if (INV_data_buf[0] != 0x0002)
        { // inv status
            INV_status[2] += 32;
        }
    }

    INV_data_buf[0] = INV6_CS_0; // current fault / voltage fault / dummy / inv status
    INV_data_buf[1] = INV6_CS_1; // I7_H
    INV_data_buf[2] = INV6_CS_2; // I7_L
    INV_data_buf[3] = INV6_CS_3; // dummy
    INV_data_buf[4] = INV6_CS_4; // dummy

    if (using_inv_num >= 7 && CalcChecksum(INV_data_buf, 5) == 0)
    {
        check_sum_cnt[6]++;
        if (INV_data_buf[0] == 0xFFFF)
        { // CON_LOST
            INV_status[3] += 64;
        }
        else if (INV_data_buf[0] == 0x1009)
        { // current fault
            INV_status[0] += 64;
        }
        else if (INV_data_buf[0] == 0x0109)
        { // voltage fault
            INV_status[1] += 64;
        }
        else if (INV_data_buf[0] != 0x0002)
        { // inv status
            INV_status[2] += 64;
        }
    }

    INV_data_buf[0] = INV7_CS_0; // current fault / voltage fault / dummy / inv status
    INV_data_buf[1] = INV7_CS_1; // I8_H
    INV_data_buf[2] = INV7_CS_2; // I8_L
    INV_data_buf[3] = INV7_CS_3; // dummy
    INV_data_buf[4] = INV7_CS_4; // dummy

    if (using_inv_num >= 8 && CalcChecksum(INV_data_buf, 5) == 0)
    {
        check_sum_cnt[7]++;
        if (INV_data_buf[0] == 0xFFFF)
        { // CON_LOST
            INV_status[3] += 128;
        }
        else if (INV_data_buf[0] == 0x1009)
        { // current fault
            INV_status[0] += 128;
        }
        else if (INV_data_buf[0] == 0x0109)
        { // voltage fault
            INV_status[1] += 128;
        }
        else if (INV_data_buf[0] != 0x0002)
        { // inv status
            INV_status[2] += 128;
        }
    }

    if (mode_changed)
    {
        mode_changed = false; // pass; INV may be at different mode

        UDP_data[0] = 0x00; // current fault
        UDP_data[1] = 0x00; // voltage fault
    }
    else
    {
        if (INV_status[0] != 0x00 || INV_status[1] != 0x00)
        {
            Flag.ModeStatus = MODE_STATUS_INV_FAULT;
        }
        else if (INV_status[3] != 0x00)
        {
            Flag.ModeStatus = MODE_STATUS_CON_LOST;
        }
        else if (INV_status[2] != 0x00)
        {
            Flag.ModeStatus = MODE_STATUS_CHECKING;
        }
        else
        {
            Flag.ModeStatus = MODE_STATUS_OK;
        }

        // Flag.ModeStatus = MODE_STATUS_OK; // pass for test

        UDP_data[0] = INV_status[0]; // current fault
        UDP_data[1] = INV_status[1]; // voltage fault
    }

    for (i = 2; i < 18; i++)
    {
        UDP_data[i] = 0x00; // I1_H ~ I8_L
    }
}

void idle_mode_spi_func()
{
    int mode_plus_status = Flag.OverallMode * 16 + Flag.ModeStatus;
    int i;



    if (using_inv_num >= 1)
    {
        INV_data_buf[0] = mode_plus_status;
        INV_data_buf[1] = current_reference[0]; // I1_ref_H
        INV_data_buf[2] = current_reference[1]; // I1_ref_L
        INV_data_buf[3] = 0x0000;
        INV_data_buf[4] = CalcChecksum(INV_data_buf, 4);

        INV0_CS_0 = INV_data_buf[0];
        INV0_CS_1 = INV_data_buf[1];
        INV0_CS_2 = INV_data_buf[2];
        INV0_CS_3 = INV_data_buf[3];
        INV0_CS_4 = INV_data_buf[4];
    }

    if (using_inv_num >= 2)
    {
        INV_data_buf[0] = mode_plus_status;
        INV_data_buf[1] = current_reference[2]; // I1_ref_H
        INV_data_buf[2] = current_reference[3]; // I1_ref_L
        INV_data_buf[3] = 0x0000;
        INV_data_buf[4] = CalcChecksum(INV_data_buf, 4);

        INV1_CS_0 = INV_data_buf[0];
        INV1_CS_1 = INV_data_buf[1];
        INV1_CS_2 = INV_data_buf[2];
        INV1_CS_3 = INV_data_buf[3];
        INV1_CS_4 = INV_data_buf[4];
    }

    if (using_inv_num >= 3)
    {
        INV_data_buf[0] = mode_plus_status;
        INV_data_buf[1] = current_reference[4]; // I1_ref_H
        INV_data_buf[2] = current_reference[5]; // I1_ref_L
        INV_data_buf[3] = 0x0000;
        INV_data_buf[4] = CalcChecksum(INV_data_buf, 4);

        INV2_CS_0 = INV_data_buf[0];
        INV2_CS_1 = INV_data_buf[1];
        INV2_CS_2 = INV_data_buf[2];
        INV2_CS_3 = INV_data_buf[3];
        INV2_CS_4 = INV_data_buf[4];
    }

    if (using_inv_num >= 4)
    {
        INV_data_buf[0] = mode_plus_status;
        INV_data_buf[1] = current_reference[6]; // I1_ref_H
        INV_data_buf[2] = current_reference[7]; // I1_ref_L
        INV_data_buf[3] = 0x0000;
        INV_data_buf[4] = CalcChecksum(INV_data_buf, 4);

        INV3_CS_0 = INV_data_buf[0];
        INV3_CS_1 = INV_data_buf[1];
        INV3_CS_2 = INV_data_buf[2];
        INV3_CS_3 = INV_data_buf[3];
        INV3_CS_4 = INV_data_buf[4];
    }

    if (using_inv_num >= 5)
    {
        INV_data_buf[0] = mode_plus_status;
        INV_data_buf[1] = current_reference[8]; // I1_ref_H
        INV_data_buf[2] = current_reference[9]; // I1_ref_L
        INV_data_buf[3] = 0x0000;
        INV_data_buf[4] = CalcChecksum(INV_data_buf, 4);

        INV4_CS_0 = INV_data_buf[0];
        INV4_CS_1 = INV_data_buf[1];
        INV4_CS_2 = INV_data_buf[2];
        INV4_CS_3 = INV_data_buf[3];
        INV4_CS_4 = INV_data_buf[4];
    }

    if (using_inv_num >= 6)
    {
        INV_data_buf[0] = mode_plus_status;
        INV_data_buf[1] = current_reference[10]; // I1_ref_H
        INV_data_buf[2] = current_reference[11]; // I1_ref_L
        INV_data_buf[3] = 0x0000;
        INV_data_buf[4] = CalcChecksum(INV_data_buf, 4);

        INV5_CS_0 = INV_data_buf[0];
        INV5_CS_1 = INV_data_buf[1];
        INV5_CS_2 = INV_data_buf[2];
        INV5_CS_3 = INV_data_buf[3];
        INV5_CS_4 = INV_data_buf[4];
    }

    if (using_inv_num >= 7)
    {
        INV_data_buf[0] = mode_plus_status;
        INV_data_buf[1] = current_reference[12]; // I1_ref_H
        INV_data_buf[2] = current_reference[13]; // I1_ref_L
        INV_data_buf[3] = 0x0000;
        INV_data_buf[4] = CalcChecksum(INV_data_buf, 4);

        INV6_CS_0 = INV_data_buf[0];
        INV6_CS_1 = INV_data_buf[1];
        INV6_CS_2 = INV_data_buf[2];
        INV6_CS_3 = INV_data_buf[3];
        INV6_CS_4 = INV_data_buf[4];
    }

    if (using_inv_num == 8)
    {
        INV_data_buf[0] = mode_plus_status;
        INV_data_buf[1] = current_reference[14]; // I1_ref_H
        INV_data_buf[2] = current_reference[15]; // I1_ref_L
        INV_data_buf[3] = 0x0000;
        INV_data_buf[4] = CalcChecksum(INV_data_buf, 4);

        INV7_CS_0 = INV_data_buf[0];
        INV7_CS_1 = INV_data_buf[1];
        INV7_CS_2 = INV_data_buf[2];
        INV7_CS_3 = INV_data_buf[3];
        INV7_CS_4 = INV_data_buf[4];
    }

    delaycc(1e-6);
    CS2_TEST_SEND = 0; // send-SPI signal to FPGA
    delaycc(30e-6);

    INV_status[0] = 0; // current fault
    INV_status[1] = 0; // voltage fault
    INV_status[2] = 0; // inv fault
    INV_status[3] = 0; // CON_LOST

    INV_data_buf[0] = INV0_CS_0; // current fault / voltage fault / dummy / inv status
    INV_data_buf[1] = INV0_CS_1; // I1_H
    INV_data_buf[2] = INV0_CS_2; // I1_L
    INV_data_buf[3] = INV0_CS_3; // dummy
    INV_data_buf[4] = INV0_CS_4; // dummy

    if (using_inv_num >= 1 /*&& CalcChecksum(INV_data_buf, 5) == 0*/)
    {
        check_sum_cnt[0]++;
        if (INV_data_buf[0] == 0xFFFF)
        { // CON_LOST
            INV_status[3] += 1;
        }
        else if (INV_data_buf[0] == 0x1009)
        { // current fault
            INV_status[0] += 1;
        }
        else if (INV_data_buf[0] == 0x0109)
        { // voltage fault
            INV_status[1] += 1;
        }
        else if (INV_data_buf[0] != 0x0002)
        { // inv status
            INV_status[2] += 1;
        }
        UDP_data[2] = INV_data_buf[1]; // I1_H
        UDP_data[3] = INV_data_buf[2]; // I1_L
    }

    INV_data_buf[0] = INV1_CS_0; // current fault / voltage fault / dummy / inv status
    INV_data_buf[1] = INV1_CS_1; // I2_H
    INV_data_buf[2] = INV1_CS_2; // I2_L
    INV_data_buf[3] = INV1_CS_3; // dummy
    INV_data_buf[4] = INV1_CS_4; // dummy

    if (using_inv_num >= 2 /*&& CalcChecksum(INV_data_buf, 5) == 0*/)
    {
        check_sum_cnt[1]++;
        if (INV_data_buf[0] == 0xFFFF)
        { // CON_LOST
            INV_status[3] += 2;
        }
        else if (INV_data_buf[0] == 0x1009)
        { // current fault
            INV_status[0] += 2;
        }
        else if (INV_data_buf[0] == 0x0109)
        { // voltage fault
            INV_status[1] += 2;
        }
        else if (INV_data_buf[0] != 0x0002)
        { // inv status
            INV_status[2] += 2;
        }
        UDP_data[4] = INV_data_buf[1]; // I2_H
        UDP_data[5] = INV_data_buf[2]; // I2_L
    }

    INV_data_buf[0] = INV2_CS_0; // current fault / voltage fault / dummy / inv status
    INV_data_buf[1] = INV2_CS_1; // I3_H
    INV_data_buf[2] = INV2_CS_2; // I3_L
    INV_data_buf[3] = INV2_CS_3; // dummy
    INV_data_buf[4] = INV2_CS_4; // dummy

    if (using_inv_num >= 3 /*&& CalcChecksum(INV_data_buf, 5) == 0*/)
    {
        check_sum_cnt[2]++;
        if (INV_data_buf[0] == 0xFFFF)
        { // CON_LOST
            INV_status[3] += 4;
        }
        else if (INV_data_buf[0] == 0x1009)
        { // current fault
            INV_status[0] += 4;
        }
        else if (INV_data_buf[0] == 0x0109)
        { // voltage fault
            INV_status[1] += 4;
        }
        else if (INV_data_buf[0] != 0x0002)
        { // inv status
            INV_status[2] += 4;
        }
        UDP_data[6] = INV_data_buf[1]; // I3_H
        UDP_data[7] = INV_data_buf[2]; // I3_L
    }

    INV_data_buf[0] = INV3_CS_0; // current fault / voltage fault / dummy / inv status
    INV_data_buf[1] = INV3_CS_1; // I4_H
    INV_data_buf[2] = INV3_CS_2; // I4_L
    INV_data_buf[3] = INV3_CS_3; // dummy
    INV_data_buf[4] = INV3_CS_4; // dummy

    if (using_inv_num >= 4 /*&& CalcChecksum(INV_data_buf, 5) == 0*/)
    {
        check_sum_cnt[3]++;
        if (INV_data_buf[0] == 0xFFFF)
        { // CON_LOST
            INV_status[3] += 8;
        }
        else if (INV_data_buf[0] == 0x1009)
        { // current fault
            INV_status[0] += 8;
        }
        else if (INV_data_buf[0] == 0x0109)
        { // voltage fault
            INV_status[1] += 8;
        }
        else if (INV_data_buf[0] != 0x0002)
        { // inv status
            INV_status[2] += 8;
        }
        UDP_data[8] = INV_data_buf[1]; // I4_H
        UDP_data[9] = INV_data_buf[2]; // I4_L
    }

    INV_data_buf[0] = INV4_CS_0; // current fault / voltage fault / dummy / inv status
    INV_data_buf[1] = INV4_CS_1; // I5_H
    INV_data_buf[2] = INV4_CS_2; // I5_L
    INV_data_buf[3] = INV4_CS_3; // dummy
    INV_data_buf[4] = INV4_CS_4; // dummy

    if (using_inv_num >= 5 /*&& CalcChecksum(INV_data_buf, 5) == 0*/)
    {
        check_sum_cnt[4]++;
        if (INV_data_buf[0] == 0xFFFF)
        { // CON_LOST
            INV_status[3] += 16;
        }
        else if (INV_data_buf[0] == 0x1009)
        { // current fault
            INV_status[0] += 16;
        }
        else if (INV_data_buf[0] == 0x0109)
        { // voltage fault
            INV_status[1] += 16;
        }
        else if (INV_data_buf[0] != 0x0002)
        { // inv status
            INV_status[2] += 16;
        }
        UDP_data[10] = INV_data_buf[1]; // I5_H
        UDP_data[11] = INV_data_buf[2]; // I5_L
    }

    INV_data_buf[0] = INV5_CS_0; // current fault / voltage fault / dummy / inv status
    INV_data_buf[1] = INV5_CS_1; // I6_H
    INV_data_buf[2] = INV5_CS_2; // I6_L
    INV_data_buf[3] = INV5_CS_3; // dummy
    INV_data_buf[4] = INV5_CS_4; // dummy

    if (using_inv_num >= 6 /*&& CalcChecksum(INV_data_buf, 5) == 0*/)
    {
        check_sum_cnt[5]++;
        if (INV_data_buf[0] == 0xFFFF)
        { // CON_LOST
            INV_status[3] += 32;
        }
        else if (INV_data_buf[0] == 0x1009)
        { // current fault
            INV_status[0] += 32;
        }
        else if (INV_data_buf[0] == 0x0109)
        { // voltage fault
            INV_status[1] += 32;
        }
        else if (INV_data_buf[0] != 0x0002)
        { // inv status
            INV_status[2] += 32;
        }
        UDP_data[12] = INV_data_buf[1]; // I6_H
        UDP_data[13] = INV_data_buf[2]; // I6_L
    }

    INV_data_buf[0] = INV6_CS_0; // current fault / voltage fault / dummy / inv status
    INV_data_buf[1] = INV6_CS_1; // I7_H
    INV_data_buf[2] = INV6_CS_2; // I7_L
    INV_data_buf[3] = INV6_CS_3; // dummy
    INV_data_buf[4] = INV6_CS_4; // dummy

    if (using_inv_num >= 7 /*&& CalcChecksum(INV_data_buf, 5) == 0*/)
    {
        check_sum_cnt[6]++;
        if (INV_data_buf[0] == 0xFFFF)
        { // CON_LOST
            INV_status[3] += 64;
        }
        else if (INV_data_buf[0] == 0x1009)
        { // current fault
            INV_status[0] += 64;
        }
        else if (INV_data_buf[0] == 0x0109)
        { // voltage fault
            INV_status[1] += 64;
        }
        else if (INV_data_buf[0] != 0x0002)
        { // inv status
            INV_status[2] += 64;
        }
        UDP_data[14] = INV_data_buf[1]; // I7_H
        UDP_data[15] = INV_data_buf[2]; // I7_L
    }

    INV_data_buf[0] = INV7_CS_0; // current fault / voltage fault / dummy / inv status
    INV_data_buf[1] = INV7_CS_1; // I8_H
    INV_data_buf[2] = INV7_CS_2; // I8_L
    INV_data_buf[3] = INV7_CS_3; // dummy
    INV_data_buf[4] = INV7_CS_4; // dummy

    if (using_inv_num >= 8 /*&& CalcChecksum(INV_data_buf, 5) == 0*/)
    {
        check_sum_cnt[7]++;
        if (INV_data_buf[0] == 0xFFFF)
        { // CON_LOST
            INV_status[3] += 128;
        }
        else if (INV_data_buf[0] == 0x1009)
        { // current fault
            INV_status[0] += 128;
        }
        else if (INV_data_buf[0] == 0x0109)
        { // voltage fault
            INV_status[1] += 128;
        }
        else if (INV_data_buf[0] != 0x0002)
        { // inv status
            INV_status[2] += 128;
        }
        UDP_data[16] = INV_data_buf[1]; // I8_H
        UDP_data[17] = INV_data_buf[2]; // I8_L
    }

    if (mode_changed)
    {
        mode_changed = false; // pass; INV may be at different mode
        UDP_data[0] = 0x00;
        UDP_data[1] = 0x00;
        for (i = 2; i < 18; i++)
        {
            UDP_data[i] = 0; // I1_H ~ I8_L
        }
    }
    else
    {
        if (INV_status[0] != 0x00 || INV_status[1] != 0x00)
        {
            Flag.ModeStatus = MODE_STATUS_INV_FAULT;
        }
        else if (INV_status[3] != 0x00)
        {
            Flag.ModeStatus = MODE_STATUS_CON_LOST;
            INV_status[0] = 0x00;
            INV_status[1] = 0x00;
            for (i = 2; i < 18; i++)
            {
                UDP_data[i] = 0; // I1_H ~ I8_L
            }
        }
        else if (INV_status[2] == 0x00)
        {
            Flag.ModeStatus = MODE_STATUS_OK;
        }
        else
        {
            Flag.ModeStatus = MODE_STATUS_OK;
            //Flag.ModeStatus = MODE_STATUS_CHECKING;
        }

        // Flag.ModeStatus = MODE_STATUS_OK; // pass for test

        UDP_data[0] = INV_status[0]; // current fault
        UDP_data[1] = INV_status[1]; // voltage fault
    }
}

void run_mode_spi_func()
{
    idle_mode_spi_func();
}

void debug_mode_spi_func()
{
    int mode_plus_status = Flag.OverallMode * 16 + Flag.ModeStatus;
    int i;

    if (using_inv_num >= 1)
     {
         INV_data_buf[0] = mode_plus_status;
         INV_data_buf[1] = current_reference[0]; // I1_ref_H
         INV_data_buf[2] = current_reference[1]; // I1_ref_L
         INV_data_buf[3] = 0x0000;
         INV_data_buf[4] = CalcChecksum(INV_data_buf, 4);

         INV0_CS_0 = INV_data_buf[0];
         INV0_CS_1 = INV_data_buf[1];
         INV0_CS_2 = INV_data_buf[2];
         INV0_CS_3 = INV_data_buf[3];
         INV0_CS_4 = INV_data_buf[4];
     }

     if (using_inv_num >= 2)
     {
         INV_data_buf[0] = mode_plus_status;
         INV_data_buf[1] = current_reference[2]; // I1_ref_H
         INV_data_buf[2] = current_reference[3]; // I1_ref_L
         INV_data_buf[3] = 0x0000;
         INV_data_buf[4] = CalcChecksum(INV_data_buf, 4);

         INV1_CS_0 = INV_data_buf[0];
         INV1_CS_1 = INV_data_buf[1];
         INV1_CS_2 = INV_data_buf[2];
         INV1_CS_3 = INV_data_buf[3];
         INV1_CS_4 = INV_data_buf[4];
     }

     if (using_inv_num >= 3)
     {
         INV_data_buf[0] = mode_plus_status;
         INV_data_buf[1] = current_reference[4]; // I1_ref_H
         INV_data_buf[2] = current_reference[5]; // I1_ref_L
         INV_data_buf[3] = 0x0000;
         INV_data_buf[4] = CalcChecksum(INV_data_buf, 4);

         INV2_CS_0 = INV_data_buf[0];
         INV2_CS_1 = INV_data_buf[1];
         INV2_CS_2 = INV_data_buf[2];
         INV2_CS_3 = INV_data_buf[3];
         INV2_CS_4 = INV_data_buf[4];
     }

     if (using_inv_num >= 4)
     {
         INV_data_buf[0] = mode_plus_status;
         INV_data_buf[1] = current_reference[6]; // I1_ref_H
         INV_data_buf[2] = current_reference[7]; // I1_ref_L
         INV_data_buf[3] = 0x0000;
         INV_data_buf[4] = CalcChecksum(INV_data_buf, 4);

         INV3_CS_0 = INV_data_buf[0];
         INV3_CS_1 = INV_data_buf[1];
         INV3_CS_2 = INV_data_buf[2];
         INV3_CS_3 = INV_data_buf[3];
         INV3_CS_4 = INV_data_buf[4];
     }

     if (using_inv_num >= 5)
     {
         INV_data_buf[0] = mode_plus_status;
         INV_data_buf[1] = current_reference[8]; // I1_ref_H
         INV_data_buf[2] = current_reference[9]; // I1_ref_L
         INV_data_buf[3] = 0x0000;
         INV_data_buf[4] = CalcChecksum(INV_data_buf, 4);

         INV4_CS_0 = INV_data_buf[0];
         INV4_CS_1 = INV_data_buf[1];
         INV4_CS_2 = INV_data_buf[2];
         INV4_CS_3 = INV_data_buf[3];
         INV4_CS_4 = INV_data_buf[4];
     }

     if (using_inv_num >= 6)
     {
         INV_data_buf[0] = mode_plus_status;
         INV_data_buf[1] = current_reference[10]; // I1_ref_H
         INV_data_buf[2] = current_reference[11]; // I1_ref_L
         INV_data_buf[3] = 0x0000;
         INV_data_buf[4] = CalcChecksum(INV_data_buf, 4);

         INV5_CS_0 = INV_data_buf[0];
         INV5_CS_1 = INV_data_buf[1];
         INV5_CS_2 = INV_data_buf[2];
         INV5_CS_3 = INV_data_buf[3];
         INV5_CS_4 = INV_data_buf[4];
     }

     if (using_inv_num >= 7)
     {
         INV_data_buf[0] = mode_plus_status;
         INV_data_buf[1] = current_reference[12]; // I1_ref_H
         INV_data_buf[2] = current_reference[13]; // I1_ref_L
         INV_data_buf[3] = 0x0000;
         INV_data_buf[4] = CalcChecksum(INV_data_buf, 4);

         INV6_CS_0 = INV_data_buf[0];
         INV6_CS_1 = INV_data_buf[1];
         INV6_CS_2 = INV_data_buf[2];
         INV6_CS_3 = INV_data_buf[3];
         INV6_CS_4 = INV_data_buf[4];
     }

     if (using_inv_num == 8)
     {
         INV_data_buf[0] = mode_plus_status;
         INV_data_buf[1] = current_reference[14]; // I1_ref_H
         INV_data_buf[2] = current_reference[15]; // I1_ref_L
         INV_data_buf[3] = 0x0000;
         INV_data_buf[4] = CalcChecksum(INV_data_buf, 4);

         INV7_CS_0 = INV_data_buf[0];
         INV7_CS_1 = INV_data_buf[1];
         INV7_CS_2 = INV_data_buf[2];
         INV7_CS_3 = INV_data_buf[3];
         INV7_CS_4 = INV_data_buf[4];
     }

    delaycc(1e-6);
    CS2_TEST_SEND = 0; // send-SPI signal to FPGA
    delaycc(30e-6);

    INV_status[0] = 0; // current fault
    INV_status[1] = 0; // voltage fault
    INV_status[2] = 0; // inv fault
    INV_status[3] = 0; // CON_LOST

    debug_val[0] = INV0_CS_0; // current fault / voltage fault / dummy / inv status
    debug_val[1] = INV0_CS_1; // I1_H
    debug_val[2] = INV0_CS_2; // I1_L
    debug_val[3] = INV0_CS_3;
    debug_val[4] = INV0_CS_4;

    debug_val[9] = CalcChecksum(debug_val, 5);


    if (CalcChecksum(debug_val, 5) == 0)
    {
        check_sum_cnt[0]++;
        if (INV_data_buf[0] == 0xFFFF)
        { // CON_LOST
            INV_status[3] += 1;
        }
        else if (INV_data_buf[0] == 0x1009)
        { // current fault
            INV_status[0] += 1;
        }
        else if (INV_data_buf[0] == 0x0109)
        { // voltage fault
            INV_status[1] += 1;
        }
        else if (INV_data_buf[0] != 0x0002)
        { // inv status
            INV_status[2] += 1;
        }
        current_sen_debug[0] = INV_data_buf[1]; // I1_H
        current_sen_debug[1] = INV_data_buf[2]; // I1_L
    }else{
        check_sum_fail[0]++;
    }


    INV_data_buf[0] = INV1_CS_0; // current fault / voltage fault / dummy / inv status
    INV_data_buf[1] = INV1_CS_1; // I2_H
    INV_data_buf[2] = INV1_CS_2; // I2_L
    INV_data_buf[3] = INV1_CS_3; // dummy
    INV_data_buf[4] = INV1_CS_4; // dummy

    if (CalcChecksum(INV_data_buf, 5) == 0)
    {
        check_sum_cnt[1]++;
        if (INV_data_buf[0] == 0xFFFF)
        { // CON_LOST
            INV_status[3] += 2;
        }
        else if (INV_data_buf[0] == 0x1009)
        { // current fault
            INV_status[0] += 2;
        }
        else if (INV_data_buf[0] == 0x0109)
        { // voltage fault
            INV_status[1] += 2;
        }
        else if (INV_data_buf[0] != 0x0002)
        { // inv status
            INV_status[2] += 2;
        }
        current_sen_debug[2] = INV_data_buf[1]; // I2_H
        current_sen_debug[3] = INV_data_buf[2]; // I2_L
    }else{
        check_sum_fail[1]++;
    }

    INV_data_buf[0] = INV2_CS_0; // current fault / voltage fault / dummy / inv status
    INV_data_buf[1] = INV2_CS_1; // I3_H
    INV_data_buf[2] = INV2_CS_2; // I3_L
    INV_data_buf[3] = INV2_CS_3; // dummy
    INV_data_buf[4] = INV2_CS_4; // dummy

    if (CalcChecksum(INV_data_buf, 5) == 0)
    {
        check_sum_cnt[2]++;
        if (INV_data_buf[0] == 0xFFFF)
        { // CON_LOST
            INV_status[3] += 4;
        }
        else if (INV_data_buf[0] == 0x1009)
        { // current fault
            INV_status[0] += 4;
        }
        else if (INV_data_buf[0] == 0x0109)
        { // voltage fault
            INV_status[1] += 4;
        }
        else if (INV_data_buf[0] != 0x0002)
        { // inv status
            INV_status[2] += 4;
        }
        current_sen_debug[4] = INV_data_buf[1]; // I3_H
        current_sen_debug[5] = INV_data_buf[2]; // I3_L
    }else{
        check_sum_fail[2]++;
    }

    INV_data_buf[0] = INV3_CS_0; // current fault / voltage fault / dummy / inv status
    INV_data_buf[1] = INV3_CS_1; // I4_H
    INV_data_buf[2] = INV3_CS_2; // I4_L
    INV_data_buf[3] = INV3_CS_3; // dummy
    INV_data_buf[4] = INV3_CS_4; // dummy

    if (CalcChecksum(INV_data_buf, 5) == 0)
    {
        check_sum_cnt[3]++;
        if (INV_data_buf[0] == 0xFFFF)
        { // CON_LOST
            INV_status[3] += 8;
        }
        else if (INV_data_buf[0] == 0x1009)
        { // current fault
            INV_status[0] += 8;
        }
        else if (INV_data_buf[0] == 0x0109)
        { // voltage fault
            INV_status[1] += 8;
        }
        else if (INV_data_buf[0] != 0x0002)
        { // inv status
            INV_status[2] += 8;
        }
        current_sen_debug[6] = INV_data_buf[1]; // I4_H
        current_sen_debug[7] = INV_data_buf[2]; // I4_L
    }
    else
    {
        check_sum_fail[3]++;
    }

    INV_data_buf[0] = INV4_CS_0; // current fault / voltage fault / dummy / inv status
    INV_data_buf[1] = INV4_CS_1; // I5_H
    INV_data_buf[2] = INV4_CS_2; // I5_L
    INV_data_buf[3] = INV4_CS_3; // dummy
    INV_data_buf[4] = INV4_CS_4; // dummy

    if (CalcChecksum(INV_data_buf, 5) == 0)
    {
        check_sum_cnt[4]++;
        if (INV_data_buf[0] == 0xFFFF)
        { // CON_LOST
            INV_status[3] += 16;
        }
        else if (INV_data_buf[0] == 0x1009)
        { // current fault
            INV_status[0] += 16;
        }
        else if (INV_data_buf[0] == 0x0109)
        { // voltage fault
            INV_status[1] += 16;
        }
        else if (INV_data_buf[0] != 0x0002)
        { // inv status
            INV_status[2] += 16;
        }
        current_sen_debug[8] = INV_data_buf[1]; // I5_H
        current_sen_debug[9] = INV_data_buf[2]; // I5_L
    }else{
        check_sum_fail[4]++;
    }

    INV_data_buf[0] = INV5_CS_0; // current fault / voltage fault / dummy / inv status
    INV_data_buf[1] = INV5_CS_1; // I6_H
    INV_data_buf[2] = INV5_CS_2; // I6_L
    INV_data_buf[3] = INV5_CS_3; // dummy
    INV_data_buf[4] = INV5_CS_4; // dummy

    if (CalcChecksum(INV_data_buf, 5) == 0)
    {
        check_sum_cnt[5]++;
        if (INV_data_buf[0] == 0xFFFF)
        { // CON_LOST
            INV_status[3] += 32;
        }
        else if (INV_data_buf[0] == 0x1009)
        { // current fault
            INV_status[0] += 32;
        }
        else if (INV_data_buf[0] == 0x0109)
        { // voltage fault
            INV_status[1] += 32;
        }
        else if (INV_data_buf[0] != 0x0002)
        { // inv status
            INV_status[2] += 32;
        }
        current_sen_debug[10] = INV_data_buf[1]; // I6_H
        current_sen_debug[11] = INV_data_buf[2]; // I6_L
    }else{
        check_sum_fail[5]++;
    }

    INV_data_buf[0] = INV6_CS_0; // current fault / voltage fault / dummy / inv status
    INV_data_buf[1] = INV6_CS_1; // I7_H
    INV_data_buf[2] = INV6_CS_2; // I7_L
    INV_data_buf[3] = INV6_CS_3; // dummy
    INV_data_buf[4] = INV6_CS_4; // dummy

    if (CalcChecksum(INV_data_buf, 5) == 0)
    {
        check_sum_cnt[6]++;
        if (INV_data_buf[0] == 0xFFFF)
        { // CON_LOST
            INV_status[3] += 64;
        }
        else if (INV_data_buf[0] == 0x1009)
        { // current fault
            INV_status[0] += 64;
        }
        else if (INV_data_buf[0] == 0x0109)
        { // voltage fault
            INV_status[1] += 64;
        }
        else if (INV_data_buf[0] != 0x0002)
        { // inv status
            INV_status[2] += 64;
        }
        current_sen_debug[12] = INV_data_buf[1]; // I7_H
        current_sen_debug[13] = INV_data_buf[2]; // I7_L
    }else{
        check_sum_fail[6]++;
    }

    INV_data_buf[0] = INV7_CS_0; // current fault / voltage fault / dummy / inv status
    INV_data_buf[1] = INV7_CS_1; // I8_H
    INV_data_buf[2] = INV7_CS_2; // I8_L
    INV_data_buf[3] = INV7_CS_3; // dummy
    INV_data_buf[4] = INV7_CS_4; // dummy

    if (CalcChecksum(INV_data_buf, 5) == 0)
    {
        check_sum_cnt[7]++;
        if (INV_data_buf[0] == 0xFFFF)
        { // CON_LOST
            INV_status[3] += 128;
        }
        else if (INV_data_buf[0] == 0x1009)
        { // current fault
            INV_status[0] += 128;
        }
        else if (INV_data_buf[0] == 0x0109)
        { // voltage fault
            INV_status[1] += 128;
        }
        else if (INV_data_buf[0] != 0x0002)
        { // inv status
            INV_status[2] += 128;
        }
        current_sen_debug[14] = INV_data_buf[1]; // I8_H
        current_sen_debug[15] = INV_data_buf[2]; // I8_L
    }else{
        check_sum_fail[7]++;
    }

    if (mode_changed)
    {
        mode_changed = false; // pass; INV may be at different mode
        UDP_data[0] = 0x00;
        UDP_data[1] = 0x00;
        for (i = 2; i < 18; i++)
        {
            UDP_data[i] = 0; // I1_H ~ I8_L
        }
    }
    else
    {
        if (INV_status[0] != 0x00 || INV_status[1] != 0x00)
        {
            Flag.ModeStatus = MODE_STATUS_INV_FAULT;
        }
        else if (INV_status[3] != 0x00)
        {
            Flag.ModeStatus = MODE_STATUS_CON_LOST;
            INV_status[0] = 0x00;
            INV_status[1] = 0x00;
            for (i = 2; i < 18; i++)
            {
                UDP_data[i] = 0; // I1_H ~ I8_L
            }
        }
        else if (INV_status[2] == 0x00)
        {
            Flag.ModeStatus = MODE_STATUS_OK;
        }
        else
        {
            Flag.ModeStatus = MODE_STATUS_OK;
            //Flag.ModeStatus = MODE_STATUS_CHECKING;
        }

    }
}

unsigned int CalcChecksum(unsigned int *data, int leng) //check sum uint 16
{
    unsigned int csum;

    csum = 0;
    for (; leng > 0; leng--)
        csum += *data++;

    return 0xFFFF - csum;
}

