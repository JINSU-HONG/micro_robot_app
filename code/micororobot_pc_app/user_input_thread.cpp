#include <stdio.h>

#include "variables.h"

void *user_input_thr_func(void *arg) {
    char user_input;
    char user_input_long[5];

    while (1) {
        gets(user_input_long);
        user_input = user_input_long[0];
        if (user_input == '0') {
            keep_on_running = false;
        } else if (user_input == '1') {
            OverallMode = OVERALL_MODE_INIT;
            ModeStatus = MODE_STATUS_CHECKING;
        } else if (user_input == '2') {
            //if (OverallMode == OVERALL_MODE_IDLE || OverallMode == OVERALL_MODE_RUN) {
            if (0) {
                printf("INV_TEST mode should be changed from INIT mode.\n");
            //} else if (ModeStatus != MODE_STATUS_OK) {
            } else if (0) {
                printf("The status is not 'OK'. (now:%d)\n", ModeStatus);
            } else {
                OverallMode = OVERALL_MODE_INV_TEST;
                ModeStatus = MODE_STATUS_CHECKING;
            }
        } else if (user_input == '3') {
            if (OverallMode == OVERALL_MODE_INIT) {
                printf("Inverters should be tested first in INV_TEST mode.\n");
            //} else if (ModeStatus != MODE_STATUS_OK) {
            } else if (0) {
                printf("The status is not 'OK'. (now:%d)\n", ModeStatus);
            } else {
                OverallMode = OVERALL_MODE_IDLE;
                ModeStatus = MODE_STATUS_CHECKING;
            }
        } else if (user_input == '4') {
            if (OverallMode == OVERALL_MODE_INIT || OverallMode == OVERALL_MODE_INV_TEST) {
                printf("RUN mode should be changed from IDLE mode.\n");
            } else if (ModeStatus != MODE_STATUS_OK) {
                printf("The status is not 'OK'. (now:%d)\n", ModeStatus);
            } else {
                OverallMode = OVERALL_MODE_RUN;
                ModeStatus = MODE_STATUS_OK; // MODE_STATUS_CHECKING
            }
        } else if (user_input == 'B' || user_input == 'b') {
            printf("X : 0\nY : 1\nZ : 2\n");
            printf("X-UpDown : 3\nXY-Circle : 4\n");
            gets(user_input_long);
            user_input = user_input_long[0];
            if (user_input == '0') B_ref_mode = B_REF_X;
            else if (user_input == '1') B_ref_mode = B_REF_Y;
            else if (user_input == '2') B_ref_mode = B_REF_Z;
            else if (user_input == '3') B_ref_mode = B_REF_X_UPDOWN;
            else if (user_input == '4') B_ref_mode = B_REF_XY_CIRCLE;
        } else if (user_input == 'F' || user_input == 'f') {
            printf("Zero : 0\nX : 1\nY : 2\nZ : 3\n");
            printf("X-UpDown : 4\nX-Sine : 5\nXY-Circle : 6\n");
            gets(user_input_long);
            user_input = user_input_long[0];
            if (user_input == '0') F_ref_mode = F_REF_ZERO;
            else if (user_input == '1') F_ref_mode = F_REF_X;
            else if (user_input == '2') F_ref_mode = F_REF_Y;
            else if (user_input == '3') F_ref_mode = F_REF_Z;
            else if (user_input == '4') F_ref_mode = F_REF_X_UPDOWN;
            else if (user_input == '5') F_ref_mode = F_REF_X_SINE;
            else if (user_input == '6') F_ref_mode = F_REF_XY_CIRCLE;
        } else if (user_input == 'C' || user_input == 'c') {
            printf("Zero current in IDLE mode : 0\n");
            printf("Keep current in IDLE mode : 1\n");
            gets(user_input_long);
            user_input = user_input_long[0];
            if (user_input == '0') CCIdleMode = CC_IDLE_MODE_ZERO;
            else if (user_input == '1') CCIdleMode == CC_IDLE_MODE_KEEP;
        } else if (user_input == 'W' || user_input =='w') {
            printf("Input F, B angular velocity.\n");
            scanf("%f", &BF_ref_ang_vel);
        } else if (user_input == 'O' || user_input == 'o') {
            printf("Input old ref delay number.\n");
            scanf("%d", &old_ref_delay);
        } else if (user_input == 'N' || user_input == 'n') {
            printf("Input controlled INV board number.\n");
            scanf("%d", &using_inv_num);
        } else if (user_input == 'T' || user_input == 't') {
            printf("Input controlled INV board number.\n");
            scanf("%d", &testing_coil);
        } else if (user_input == 'L' || user_input == 'l') {
            manual_F[0] += F_max * 0.5;
            printf("current manual force : %f, %f\n", manual_F[0], manual_F[1]);
        } else if (user_input == 'J' || user_input == 'j') {
            manual_F[0] -= F_max * 0.5;
            printf("current manual force : %f, %f\n", manual_F[0], manual_F[1]);
        } else if (user_input == 'I' || user_input == 'i') {
            manual_F[1] += F_max * 0.5;
            printf("current manual force : %f, %f\n", manual_F[0], manual_F[1]);
        } else if (user_input == 'K' || user_input == 'k') {
            manual_F[1] -= F_max * 0.5;
            printf("current manual force : %f, %f\n", manual_F[0], manual_F[1]);
        }
    }
    return (void *)NULL;
}
