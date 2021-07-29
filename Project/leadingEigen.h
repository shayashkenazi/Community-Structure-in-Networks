/*
 * leadingEigen module:
 *  This module helps us to calculate the leading eigen vector and the leading eigen value:
 *
 *  power_iteration     - the called function from Algorithm2 who updates the leading eigen vector
 *                        and the leading eigen value.
 *
 *  leading_eigen       - the function creates the random vector and the second vector according it.
 *
 *  createRandVec       - creates the first vector randomly
 *
 *  calculateTheNewVec  - calculating the next vector by the current vector in the equation:
 *                        b_k * B_hat[g] / ||b_k * b_k||
 *
 *  createEigen         - the implement of power iteration algorithm
 *
 * leading_eigenValue   - calculate the leading eigen value according to :
 *                        (b_k * A *b_k) / (b_k * b_k)
 *
 *
 */


#ifndef SP_PROJECT_LEADINGEIGEN_H
#define SP_PROJECT_LEADINGEIGEN_H

void power_iteration(community* C, double* eigenValue,double** eigenVector,group* g);
void leading_eigen (community* C, double** b1,group* g);
void createRandVec (double*  b0, int n);
void calculateTheNewVec (int n, double* bk, double** next_bk, community* C, group* g);
void createEigen (int n, double* bk, double* next_bk, community* C, group* g);
void leading_eigenValue(community* C, double* eigenValue,double* eigenVector, group* g);


#endif
