#include "matrixCalculation.h"
#include <stdlib.h>
#include <stdio.h>
#include "error.h"

void calculate_B_hat_mult_v (community* C, group* g, double* v, double* result, int flag)
{
    double* f_i;
    f_i = (double*)calloc(g->size, sizeof(double));
    if(f_i == NULL) MallocFailed

    mult_sm_with_v(C, g, v, f_i, result);
    mult_Kvec_with_v(C, g, v, f_i, result, flag);
    if(g->size != C->sm->n)
        calculate_f_i_g(g, v, f_i, result);

    free(f_i);
}


void mult_sm_with_v(community* C, group* g, double* v, double* f_i, double* result)
{
    int i, i_index, j, j_index, start, end, *colind, *rowptr, *arr, *map;
    double sum, sum_fi ;

    arr = g->arr;
    map = g->map_g;
    colind = C -> sm -> colind;
    rowptr = C->sm->rowptr;

    for (i = 0; i < g -> size; i++) {
        i_index = arr[i];
        start = rowptr[i_index];
        end = rowptr[i_index + 1];
        sum = 0, sum_fi = 0;

        for(j = start; j < end; j++) {
            j_index = map[colind[j]];
            if (j_index != -1) {
                sum += (v[j_index]);
                sum_fi += 1;
            }
        }
        result[i] = sum;
        f_i [i] = sum_fi;
    }
}

void mult_Kvec_with_v(community* C, group* g, double* v, double* f_i, double* result, int flag)
{
    int i, i_index, M, *g_arr;
    double sum = 0, sum_fi = 0;

    M = C -> M;
    g_arr = g -> arr;


    for (i = 0; i < g -> size; i++) {
        i_index = g_arr[i];
        sum += (C->kVec[i_index] * v[i]);
        sum_fi += C->kVec[i_index];
    }

    for (i = 0; i < g -> size; i++) {
        i_index = g_arr[i];
        result[i] -=  ((double) (sum / M) * C->kVec[i_index]);
        f_i [i] -=  ((double)(sum_fi / M) * C->kVec[i_index]);
        if(flag)
            result[i] += v[i] * C->norm1;

    }
}

void calculate_f_i_g(group* g, double* v, double* f_i, double* result)
{
    int i;

    for(i = 0; i < g->size; i++)
        result[i] -= f_i[i] * v[i];



}

