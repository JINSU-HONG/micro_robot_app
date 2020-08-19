#include <vector>
#include <math.h>

#include "variables.h"
#include "rt_setting.h"
#include "actuation_matrix_calc.h"
#include "matrix.h"

using std::vector;

void bound_floor(int *floor_val)
{
    if ((*floor_val) >= GRID_RESOL - 1)
    {
        (*floor_val) = GRID_RESOL - 2;
    }
    else if ((*floor_val) < 0)
    {
        (*floor_val) = 0;
    }
}

void calc_b(vector<vector<double> > *B_LUT, Matrix *Act, Matrix *Act_temp, int nth_col,
    int x_floor, int y_floor, int z_floor,
    double x_ratio, double y_ratio, double z_ratio)
{
    vector<double> B_floor(3);
    vector<double> B_ceil(3);
    vector<double> Bd(3);
    int i, j;

    B_floor = (*B_LUT)[x_floor*GRID_RESOL*GRID_RESOL + y_floor*GRID_RESOL + z_floor];
    B_ceil = (*B_LUT)[(x_floor + 1)*GRID_RESOL*GRID_RESOL + (y_floor + 1)*GRID_RESOL + (z_floor + 1)];

    (*Act_temp)(0, nth_col) = B_floor[0] * (1 - x_ratio) + B_ceil[0] * x_ratio;
    (*Act_temp)(1, nth_col) = B_floor[1] * (1 - y_ratio) + B_ceil[1] * y_ratio;
    (*Act_temp)(2, nth_col) = B_floor[2] * (1 - z_ratio) + B_ceil[2] * z_ratio;

    i = (x_floor + 1)*GRID_RESOL*GRID_RESOL + y_floor*GRID_RESOL + z_floor;
    j = x_floor*GRID_RESOL*GRID_RESOL + (y_floor + 1)*GRID_RESOL + (z_floor + 1);
    Bd[0] = (((*B_LUT)[i][0] - B_floor[0]) * (1 - x_ratio) + (B_ceil[0] - (*B_LUT)[j][0]) * x_ratio) / GRID_INTERVAL;
    Bd[1] = (((*B_LUT)[i][1] - B_floor[1]) * (1 - y_ratio) + (B_ceil[1] - (*B_LUT)[j][1]) * y_ratio) / GRID_INTERVAL;
    Bd[2] = (((*B_LUT)[i][2] - B_floor[2]) * (1 - z_ratio) + (B_ceil[2] - (*B_LUT)[j][2]) * z_ratio) / GRID_INTERVAL;
    (*Act)(3, nth_col) = Magnetization[0] * Bd[0] + Magnetization[1] * Bd[1] + Magnetization[2] * Bd[2];

    i = x_floor*GRID_RESOL*GRID_RESOL + (y_floor + 1)*GRID_RESOL + z_floor;
    j = (x_floor + 1)*GRID_RESOL*GRID_RESOL + y_floor*GRID_RESOL + (z_floor + 1);
    Bd[0] = (((*B_LUT)[i][0] - B_floor[0]) * (1 - x_ratio) + (B_ceil[0] - (*B_LUT)[j][0]) * x_ratio) / GRID_INTERVAL;
    Bd[1] = (((*B_LUT)[i][1] - B_floor[1]) * (1 - y_ratio) + (B_ceil[1] - (*B_LUT)[j][1]) * y_ratio) / GRID_INTERVAL;
    Bd[2] = (((*B_LUT)[i][2] - B_floor[2]) * (1 - z_ratio) + (B_ceil[2] - (*B_LUT)[j][2]) * z_ratio) / GRID_INTERVAL;
    (*Act)(4, nth_col) = Magnetization[0] * Bd[0] + Magnetization[1] * Bd[1] + Magnetization[2] * Bd[2];

    i = x_floor*GRID_RESOL*GRID_RESOL + y_floor*GRID_RESOL + (z_floor + 1);
    j = (x_floor + 1)*GRID_RESOL*GRID_RESOL + (y_floor + 1)*GRID_RESOL + z_floor;
    Bd[0] = (((*B_LUT)[i][0] - B_floor[0]) * (1 - x_ratio) + (B_ceil[0] - (*B_LUT)[j][0]) * x_ratio) / GRID_INTERVAL;
    Bd[1] = (((*B_LUT)[i][1] - B_floor[1]) * (1 - y_ratio) + (B_ceil[1] - (*B_LUT)[j][1]) * y_ratio) / GRID_INTERVAL;
    Bd[2] = (((*B_LUT)[i][2] - B_floor[2]) * (1 - z_ratio) + (B_ceil[2] - (*B_LUT)[j][2]) * z_ratio) / GRID_INTERVAL;
    (*Act)(5, nth_col) = Magnetization[0] * Bd[0] + Magnetization[1] * Bd[1] + Magnetization[2] * Bd[2];
}

void get_actuation_mtx(Matrix *Act, bool get_act_mat_ref_mode) {
    Matrix *Act_temp = new Matrix(3, 8);
    Matrix Act_temp2(3, 8);
    Matrix skew_M(3,3);
    vector<double> scaled_position(3);
    double x_ratio, y_ratio, z_ratio;
    int x_floor, y_floor, z_floor;

    scaled_position[0] = (Position[0] / CONTROL_REGION_WIDTH + 0.5) * (GRID_RESOL-1);
    scaled_position[1] = (Position[1] / CONTROL_REGION_WIDTH + 0.5) * (GRID_RESOL-1);
    scaled_position[2] = (Position[2] / CONTROL_REGION_WIDTH + 0.5) * (GRID_RESOL-1);

    x_floor = (int)floor(scaled_position[0]);
    y_floor = (int)floor(scaled_position[1]);
    z_floor = (int)floor(scaled_position[2]);
    bound_floor(&x_floor);
    bound_floor(&y_floor);
    bound_floor(&z_floor);
    x_ratio = scaled_position[0] - x_floor;
    y_ratio = scaled_position[1] - y_floor;
    z_ratio = scaled_position[2] - z_floor;

    calc_b(B_LUT1, Act, Act_temp, 0, x_floor, y_floor, z_floor, x_ratio, y_ratio, z_ratio);
    calc_b(B_LUT2, Act, Act_temp, 1, x_floor, y_floor, z_floor, x_ratio, y_ratio, z_ratio);
    calc_b(B_LUT3, Act, Act_temp, 2, x_floor, y_floor, z_floor, x_ratio, y_ratio, z_ratio);
    calc_b(B_LUT4, Act, Act_temp, 3, x_floor, y_floor, z_floor, x_ratio, y_ratio, z_ratio);
    calc_b(B_LUT5, Act, Act_temp, 4, x_floor, y_floor, z_floor, x_ratio, y_ratio, z_ratio);
    calc_b(B_LUT6, Act, Act_temp, 5, x_floor, y_floor, z_floor, x_ratio, y_ratio, z_ratio);
    calc_b(B_LUT7, Act, Act_temp, 6, x_floor, y_floor, z_floor, x_ratio, y_ratio, z_ratio);
    calc_b(B_LUT8, Act, Act_temp, 7, x_floor, y_floor, z_floor, x_ratio, y_ratio, z_ratio);

    if (get_act_mat_ref_mode) {
        skew_M(0,1) = -Magnetization[2];
        skew_M(0,2) = Magnetization[1];
        skew_M(1,0) = Magnetization[2];
        skew_M(1,2) = -Magnetization[0];
        skew_M(2,0) = -Magnetization[1];
        skew_M(2,1) = Magnetization[0];

        Act_temp2 = skew_M * (*Act_temp);
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 8; j++) {
                (*Act)(i,j) = Act_temp2(i,j); // torque
            }
        }
    } else {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 8; j++) {
                (*Act)(i,j) = (*Act_temp)(i,j); // magnetic field
            }
        }
    }

    delete Act_temp;
}

void get_current_ref() {
    Matrix *Act = new Matrix(6,8);
    Matrix BF_ref_matrix(6,1);
    Matrix I_matrix(8,1);
    double soft_ref_coeff;

    BF_ref_matrix(0, 0) = BF_ref[0];
    BF_ref_matrix(1, 0) = BF_ref[1];
    BF_ref_matrix(2, 0) = BF_ref[2];
    BF_ref_matrix(3, 0) = BF_ref[3];
    BF_ref_matrix(4, 0) = BF_ref[4];
    BF_ref_matrix(5, 0) = BF_ref[5];

    get_actuation_mtx(Act, ref_mode); // false : BF ; true : TF

    try {
        I_matrix = BF_ref_matrix / (*Act); // this dividing uses pseudo inverse
    } catch (int e) {
        printf("Catched an error while calculating current. Error : %d\n", e);
        // use the last reference
        I_matrix(0, 0) = Current_ref[0];
        I_matrix(1, 0) = Current_ref[1];
        I_matrix(2, 0) = Current_ref[2];
        I_matrix(3, 0) = Current_ref[3];
        I_matrix(4, 0) = Current_ref[4];
        I_matrix(5, 0) = Current_ref[5];
        I_matrix(6, 0) = Current_ref[6];
        I_matrix(7, 0) = Current_ref[7];
    }

    if (OverallMode == OVERALL_MODE_RUN) {
        if (soft_ref_cnt < SOFT_REF_CNT) {
            soft_ref_cnt = soft_ref_cnt + 1;
        }
        soft_ref_coeff = (double)soft_ref_cnt / (double)SOFT_REF_CNT;
    } else {
        soft_ref_cnt = 0;
        soft_ref_coeff = 1.;
    }

    Current_ref[0] = I_matrix(0, 0) * soft_ref_coeff;
    Current_ref[1] = I_matrix(1, 0) * soft_ref_coeff;
    Current_ref[2] = I_matrix(2, 0) * soft_ref_coeff;
    Current_ref[3] = I_matrix(3, 0) * soft_ref_coeff;
    Current_ref[4] = I_matrix(4, 0) * soft_ref_coeff;
    Current_ref[5] = I_matrix(5, 0) * soft_ref_coeff;
    Current_ref[6] = I_matrix(6, 0) * soft_ref_coeff;
    Current_ref[7] = I_matrix(7, 0) * soft_ref_coeff;

    //Current_ref[0] = Current_ref[0] * 0.8; // 보정

    //for (int i=0; i<8; i++) {
    //    Current_ref[i] = 0.;
    //}
    //Current_ref[testing_coil] = 3.;
    
    // shift old current
    for (int i=old_ref_delay; i>=0; i--) {
        if (i>0) {
            for (int j=0; j<8; j++) {
                Current_ref_old[i][j] = Current_ref_old[i-1][j];
            }
        } else {
            for (int j=0; j<8; j++) {
                Current_ref_old[0][j] = Current_ref[j];
            }
        }
    }

    // confirm
    // BF_ref_matrix = (*Act) * I_matrix;
    // printf("ref B ; B0 : %.4e, %.4e\n", BF_ref_matrix(0,0), BF_ref_matrix(2,0));

    delete Act;
}

void update_PM() {
    Matrix *Act = new Matrix(6,8);
    Matrix TF_sen_matrix(6,1);
    Matrix I_matrix(8,1);
    Matrix Rot_phi_inv(3,3);
    Matrix Rot_phi(3,3);
    Matrix Rot_theta_inv(3,3);
    Matrix Rot_theta(3,3);
    Matrix Rot_z(3,3);
    Matrix Rot_matrix(3,3);
    Matrix Magnetization_mat(3,1);
    Matrix Magnetization_mat_new(3,1);
    vector<double> w_hat(3);
    double norm_v = 1., norm_w = 1., norm_B = 1.;
    double theta, phi, delta;
    //double task_peri_div_J = TASK_PERIOD / J_robot;
    //double J_div_task_peri = J_robot / TASK_PERIOD;
    //double m_div_task_peri = m_robot / TASK_PERIOD;

    if (update_magnetization_with_torque) {
        get_actuation_mtx(Act, REF_MODE_TF); // get torque act mat
    } else {
        get_actuation_mtx(Act, REF_MODE_BF);
    }

    I_matrix(0, 0) = Current_sen[0];
    I_matrix(1, 0) = Current_sen[1];
    I_matrix(2, 0) = Current_sen[2];
    I_matrix(3, 0) = Current_sen[3];
    I_matrix(4, 0) = Current_sen[4];
    I_matrix(5, 0) = Current_sen[5];
    I_matrix(6, 0) = Current_sen[6];
    I_matrix(7, 0) = Current_sen[7];

    TF_sen_matrix = (*Act) * I_matrix;
    if (gravity_in_net_force) {
        TF_sen_matrix(5,0) = TF_sen_matrix(5,0) - GRAVITY_FORCE;
    }

    // update Position
    // s = (z-1)/Ts
    //Velocity[0] = Velocity[0] + (TF_sen_matrix(3, 0) - drag_translation * Velocity[0]) / m_robot * TASK_PERIOD;
    //Velocity[1] = Velocity[1] + (TF_sen_matrix(4, 0) - drag_translation * Velocity[2]) / m_robot * TASK_PERIOD;
    //Velocity[2] = Velocity[2] + (TF_sen_matrix(5, 0) - drag_translation * Velocity[2]) / m_robot * TASK_PERIOD;

    // s = (z-1)/(zTs)
    //Velocity[0] = m_div_task_peri / (drag_translation + m_div_task_peri) * Velocity[0] + TF_sen_matrix(3,0) / (drag_translation + m_div_task_peri);
    //Velocity[1] = m_div_task_peri / (drag_translation + m_div_task_peri) * Velocity[1] + TF_sen_matrix(4,0) / (drag_translation + m_div_task_peri);
    //Velocity[2] = m_div_task_peri / (drag_translation + m_div_task_peri) * Velocity[2] + TF_sen_matrix(5,0) / (drag_translation + m_div_task_peri);
    Velocity[0] = Velocity[0] * exp(-drag_translation/m_robot*TASK_PERIOD) + TF_sen_matrix(3,0) / drag_translation*(1-exp(-drag_translation/m_robot*TASK_PERIOD));
    Velocity[1] = Velocity[1] * exp(-drag_translation/m_robot*TASK_PERIOD) + TF_sen_matrix(4,0) / drag_translation*(1-exp(-drag_translation/m_robot*TASK_PERIOD));
    Velocity[2] = Velocity[2] * exp(-drag_translation/m_robot*TASK_PERIOD) + TF_sen_matrix(5,0) / drag_translation*(1-exp(-drag_translation/m_robot*TASK_PERIOD));

    for (int i=0; i<3; i++) {
        if (isnan(Velocity[i])) {
            Velocity[i] = 0.;
        }
    }

    norm_v = sqrt(pow(Velocity[0],2) + pow(Velocity[1],2) + pow(Velocity[2],2));

    if (norm_v > 10) { // prevent divergence
        Velocity[0] = Velocity[0] * 10. / norm_v;
        Velocity[1] = Velocity[1] * 10. / norm_v;
        Velocity[2] = Velocity[2] * 10. / norm_v;
    }

    if (!fix_Position) {
        Position[0] = Position[0] + Velocity[0] * TASK_PERIOD;
        Position[1] = Position[1] + Velocity[1] * TASK_PERIOD;
        Position[2] = Position[2] + Velocity[2] * TASK_PERIOD;

        if (Position[0] > x_top) {
            Position[0] = x_top;
        } else if (Position[0] < x_bottom) {
            Position[0] = x_bottom;
        }
        if (Position[1] > y_top) {
            Position[1] = y_top;
        } else if (Position[1] < y_bottom) {
            Position[1] = y_bottom;
        }
        if (Position[2] > z_top) {
            Position[2] = z_top;
        } else if (Position[2] < z_bottom) {
            Position[2] = z_bottom;
        }
    }

    // update Magnetization
    // s = (z-1)/Ts
    //AngularVelocity[0] = AngularVelocity[0] + (TF_sen_matrix(0, 0) - drag_rotation * AngularVelocity[0]) * task_peri_div_J;
    //AngularVelocity[1] = AngularVelocity[1] + (TF_sen_matrix(1, 0) - drag_rotation * AngularVelocity[1]) * task_peri_div_J;
    //AngularVelocity[2] = AngularVelocity[2] + (TF_sen_matrix(2, 0) - drag_rotation * AngularVelocity[2]) * task_peri_div_J;

    // s = (z-1)/(zTs)
    //AngularVelocity[0] = J_div_task_peri / (drag_rotation + J_div_task_peri) * AngularVelocity[0] + TF_sen_matrix(0,0) / (drag_rotation + J_div_task_peri);
    //AngularVelocity[1] = J_div_task_peri / (drag_rotation + J_div_task_peri) * AngularVelocity[1] + TF_sen_matrix(1,0) / (drag_rotation + J_div_task_peri);
    //AngularVelocity[2] = J_div_task_peri / (drag_rotation + J_div_task_peri) * AngularVelocity[2] + TF_sen_matrix(2,0) / (drag_rotation + J_div_task_peri);

    if (update_magnetization_with_torque) {
        AngularVelocity[0] = AngularVelocity[0] * exp(-drag_rotation/J_robot*TASK_PERIOD) + TF_sen_matrix(0,0) / drag_rotation * (1-exp(-drag_rotation/J_robot*TASK_PERIOD));
        AngularVelocity[1] = AngularVelocity[1] * exp(-drag_rotation/J_robot*TASK_PERIOD) + TF_sen_matrix(1,0) / drag_rotation * (1-exp(-drag_rotation/J_robot*TASK_PERIOD));
        AngularVelocity[2] = AngularVelocity[2] * exp(-drag_rotation/J_robot*TASK_PERIOD) + TF_sen_matrix(2,0) / drag_rotation * (1-exp(-drag_rotation/J_robot*TASK_PERIOD));
        
        for (int i=0; i<3; i++) {
            if (isnan(Velocity[i])) {
                AngularVelocity[i] = 0.;
            }
        }

        norm_w = sqrt(pow(AngularVelocity[0],2) + pow(AngularVelocity[1],2) + pow(AngularVelocity[2],2));

        if (norm_w > 500) { // prevent divergence
            AngularVelocity[0] = AngularVelocity[0] * 500. / norm_w;
            AngularVelocity[1] = AngularVelocity[1] * 500. / norm_w;
            AngularVelocity[2] = AngularVelocity[2] * 500. / norm_w;
        }

        if (norm_w == 0) {
            w_hat[0] = 0.;
            w_hat[1] = 1.;
            w_hat[2] = 0.;
        } else {
            w_hat[0] = AngularVelocity[0] / norm_w * 0.999;
            w_hat[1] = AngularVelocity[1] / norm_w * 0.999;
            w_hat[2] = AngularVelocity[2] / norm_w * 0.999;
        }

        theta = acos(w_hat[2]);

        if (w_hat[2] == 1. || w_hat[2] == -1.) {
            phi = 0;
        } else {
            phi = acos(w_hat[0] / sin(theta));
            if (asin(w_hat[1]) / sin(theta) < 0) {
                phi = -phi;
            }
        }

        delta = norm_w * TASK_PERIOD;

        Rot_phi_inv(0,0) = cos(phi); Rot_phi_inv(0,1) = sin(phi); Rot_phi_inv(0,2) = 0.;
        Rot_phi_inv(1,0) = -sin(phi); Rot_phi_inv(1,1) = cos(phi); Rot_phi_inv(1,2) = 0.;
        Rot_phi_inv(2,0) = 0.; Rot_phi_inv(2,1) = 0.; Rot_phi_inv(2,2) = 1.;

        Rot_phi(0,0) = cos(phi); Rot_phi(0,1) = -sin(phi); Rot_phi(0,2) = 0.;
        Rot_phi(1,0) = sin(phi); Rot_phi(1,1) = cos(phi); Rot_phi(1,2) = 0.;
        Rot_phi(2,0) = 0.; Rot_phi(2,1) = 0.; Rot_phi(2,2) = 1.;

        Rot_theta_inv(0,0) = cos(theta); Rot_theta_inv(0,1) = 0.; Rot_theta_inv(0,2) = -sin(theta);
        Rot_theta_inv(1,0) = 0.; Rot_theta_inv(1,1) = 1.; Rot_theta_inv(1,2) = 0.;
        Rot_theta_inv(2,0) = sin(theta); Rot_theta_inv(2,1) = 0.; Rot_theta_inv(2,2) = cos(theta);

        Rot_theta(0,0) = cos(theta); Rot_theta(0,1) = 0.; Rot_theta(0,2) = sin(theta);
        Rot_theta(1,0) = 0.; Rot_theta(1,1) = 1.; Rot_theta(1,2) = 0.;
        Rot_theta(2,0) = -sin(theta); Rot_theta(2,1) = 0.; Rot_theta(2,2) = cos(theta);

        Rot_z(0,0) = cos(delta); Rot_z(0,1) = -sin(delta); Rot_z(0,2) = 0.;
        Rot_z(1,0) = sin(delta); Rot_z(1,1) = cos(delta); Rot_z(1,2) = 0.;
        Rot_z(2,0) = 0.; Rot_z(2,1) = 0.; Rot_z(2,2) = 1.;

        Rot_matrix = Rot_phi * Rot_theta * Rot_z * Rot_theta_inv * Rot_phi_inv;

        Magnetization_mat(0,0) = Magnetization[0];
        Magnetization_mat(1,0) = Magnetization[1];
        Magnetization_mat(2,0) = Magnetization[2];

        Magnetization_mat_new = Rot_matrix * Magnetization_mat;

        Magnetization[0] = Magnetization_mat_new(0,0);
        Magnetization[1] = Magnetization_mat_new(1,0);
        Magnetization[2] = Magnetization_mat_new(2,0);

        // Magnitude of Magnetization variable may be changed during rotation.
        // Add magnitude fix code here if needed.
    } else {
        // follow magnetic field direction
        norm_B = sqrt(pow(TF_sen_matrix(0,0),2) + pow(TF_sen_matrix(1,0),2) + pow(TF_sen_matrix(2,0),2));
        if (norm_B != 0) {
            Magnetization[0] = M_robot * TF_sen_matrix(0,0) / norm_B;
            Magnetization[1] = M_robot * TF_sen_matrix(1,0) / norm_B;
            Magnetization[2] = M_robot * TF_sen_matrix(2,0) / norm_B;
        }
    }
    
    delete Act;
}
