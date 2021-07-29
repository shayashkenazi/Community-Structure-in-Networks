#include <stdlib.h>
#include <stdio.h>
#include "divisionTwo.h"
#include "community.h"
#include "leadingEigen.h"
#include "modularityMaximization.h"
#include "matrixCalculation.h"
#include "error.h"

#define ZERO 0.00001

double* Algorithm2 (community* C, group* g)
{
    int i, n;
    double eigenValue, Q, *eigenVector  = NULL, *s = NULL;

    n = g->size;

    s = (double*)malloc(n * sizeof(double));
    eigenVector = (double*)malloc(n * sizeof(double));

    if(s == NULL || eigenVector == NULL) MallocFailed

    power_iteration(C, &eigenValue, &eigenVector, g);


    if(eigenValue <= ZERO){
        for(i = 0; i < n; i++)
            s[i] = 1;
        free(eigenVector);
        return s;
    }
    else {
        /*initialize vector s*/
        for (i = 0; i < n; ++i) {
            if (eigenVector[i] > ZERO) {
                s[i] = 1;
            } else {
                s[i] = -1;
            }
        }
        free(eigenVector);
    }

    Q = calculateDeltaQ(C, s, g) ;

    if(Q <= ZERO){
        for(i = 0; i < n; i++)
            s[i] = 1;
        return s;
    }

    Algorithm4(g, C, s);

    return s;
}

double calculateDeltaQ(community* C, double * s, group* g)
{
    double Q = 0, *B_v;
    int i, n;

    n = g->size;
    B_v = (double*) malloc(n * sizeof(double));
    if(B_v == NULL) MallocFailed

    calculate_B_hat_mult_v(C, g, s, B_v, 0);

    for (i = 0; i < g -> size; ++i) {
        Q += (s[i] * B_v[i]);
    }

    free(B_v);
    return Q;

}