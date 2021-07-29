/*matrixCalculation module:
 *
 *  This module helps us to calculate the multiplication of B_hat[g] by a vector:
 *
 *  calculate_B_hat_mult_v - the function that we will call for the total calculation
 *
 *  mult_sm_with_v         - calculates the multiplication of the sparse matrix with a given vector
 *                           and keep it in vector result
 *
 *  mult_Kvec_with_v       - calculates the multiplication of the k_i*k_j / M  with a given vector and
 *                           update vector result
 *
 *  calculate_f_i_g        - if the group is not the whole graph we will calculate the sum of each row
 *                           in matrix B[g] and update the vector result
 *
 *
 *
 */

#ifndef SP_MATRIXCALCULATION_H
#define SP_MATRIXCALCULATION_H

#include "community.h"

void calculate_B_hat_mult_v (community* C, group* g, double* v, double* result, int flag);
void mult_sm_with_v(community* C, group* g, double* v, double* f_i, double* result);
void mult_Kvec_with_v(community* C, group* g, double* v, double* f_i, double* result, int flag);
void calculate_f_i_g(group* g, double* v, double* f_i, double* result);

#endif
