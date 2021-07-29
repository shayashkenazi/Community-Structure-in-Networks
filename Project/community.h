/*
 *community Summery:
 *
 *This module holds all the data for B[g] matrix:
 *      1. sm - pointer to the sparse matrix (A) implemented in spmat.h
 *      2. kVec - vector that contains the degrees of the vertices corresponding the matrix sm.
 *      3. M - the sum of k_i in kVec
 *      4. norm1 - this value equal to ||B^hat[g]||_1, i.e., the 1-norm of the matrix of the community.
 *
 *create_community         -Allocate the marix structure and updates all the parameters.
 * free_community          -Frees all resources used by community C
 * kProd                   -Return the product k_i*k_j \ M of the community
 * SumRowBHat              -Calculate and return the sum of row i in absolute values of matrix B^hat[g].
 * calculateNorm1          -Calculate ||B^hat[g]||_1, i.e., the 1-norm of the matrix of the community, and updating C->norm1 field accordingly
 */


#include "spmat.h"
#include "group.h"
#ifndef _COMMUNITY_H
#define _COMMUNITY_H


typedef struct _community {

    spmat* sm;
    int* kVec;
    int M;
    double norm1;
} community;

community* create_community(spmat* sm,int* kVec,int M);
void free_community(community* C);
double kProd(struct _community *C, int i, int j);
double SumRowBHat(community* C,int i);
void calculateNorm1(community* C);


#endif
