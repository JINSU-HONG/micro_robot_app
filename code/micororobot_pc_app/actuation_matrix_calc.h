#ifndef ACTUATION_MATRIX_CALC_H
#define ACTUATION_MATRIX_CALC_H

#include <vector>

#include "matrix.h"

using std::vector;

void bound_floor(int *floor_val);

void calc_b(vector<vector<double> > *B_LUT, Matrix *Act, Matrix *Act_temp, int nth_col, int x_floor, int y_floor, int z_floor, double x_ratio, double y_ratio, double z_ratio);

void get_actuation_mtx(Matrix *Act);

void get_current_ref();

void update_PM();

#endif // ACTUATION_MATRIX_CALC_H
