#include <math.h>
#include <vector>

#include "variables.h"

void gen_BF_ref(unsigned long time_ns) {
    float time_s = time_ns / 1000000000.;

    switch (B_ref_mode) {
        case B_REF_X:
            BF_ref[0] = B_max;
            BF_ref[1] = 0.;
            BF_ref[2] = 0.;
            break;
        case B_REF_Y:
            BF_ref[0] = 0.;
            BF_ref[1] = B_max;
            BF_ref[2] = 0.;
            break;
        case B_REF_Z:
            BF_ref[0] = 0.;
            BF_ref[1] = 0.;
            BF_ref[2] = B_max;
            break;
        case B_REF_X_UPDOWN:
            BF_ref[0] = ((int)(time_s * BF_ref_ang_vel * 2) % 2 == 0) ? -B_max : B_max;
            BF_ref[1] = 0.;
            BF_ref[2] = 0.;
            break;
        case B_REF_XY_CIRCLE:
            BF_ref[0] = sin(time_s * BF_ref_ang_vel) * B_max;
            BF_ref[1] = cos(time_s * BF_ref_ang_vel) * B_max;
            BF_ref[2] = 0.;
            break;
        default: break;
    }

    switch (F_ref_mode) {
        case F_REF_ZERO:
            BF_ref[3] = 0.;
            BF_ref[4] = 0.;
            BF_ref[5] = 0.;
            break;
        case F_REF_X:
            BF_ref[3] = -F_max;
            BF_ref[4] = 0.;
            BF_ref[5] = 0.;
            break;
        case F_REF_Y:
            BF_ref[3] = 0.;
            BF_ref[4] = F_max;
            BF_ref[5] = 0.;
            break;
        case F_REF_Z:
            BF_ref[3] = 0.;
            BF_ref[4] = 0.;
            BF_ref[5] = F_max;
            break;
        case F_REF_X_UPDOWN:
            BF_ref[3] = ((int)(time_s * BF_ref_ang_vel * 2) % 2 == 0) ? -F_max : F_max;
            BF_ref[4] = 0.;
            BF_ref[5] = 0.;
            break;
        case F_REF_X_SINE:
            BF_ref[3] = sin(time_s * BF_ref_ang_vel) * F_max;
            BF_ref[4] = 0.;
            BF_ref[5] = 0.;
            break;
        case F_REF_XY_CIRCLE:
            BF_ref[3] = sin(time_s * BF_ref_ang_vel) * F_max;
            BF_ref[4] = cos(time_s * BF_ref_ang_vel) * F_max;
            BF_ref[5] = 0.;
            break;
        default: break;
    }

    if (gravity_compensation_mode) {
        BF_ref[5] = BF_ref[5] + m_robot_buoyant * GRAVITY_ACC;
    }

    BF_ref[3] += manual_F[0];
    BF_ref[4] += manual_F[1];
}
