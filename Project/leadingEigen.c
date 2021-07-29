#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "community.h"
#include "leadingEigen.h"
#include "matrixCalculation.h"
#include "error.h"
#define ZERO 0.00001
#define FIN 150000


void power_iteration(community* C, double* eigenValue,double** eigenVector,group* g)
{
    leading_eigen(C,eigenVector,g);
    leading_eigenValue(C,eigenValue, *eigenVector, g);
}

void leading_eigen (community* C, double** b1,group* g)
{
    int size;
    double* b0 = NULL;

    size = g->size;

    /*calculate the first vector randomly*/
    b0 = (double*)malloc(size * sizeof(double));
    if(b0 == NULL) MallocFailed

    createRandVec(b0,size);

    /*calculate the second vector according to the equation*/
    calculateTheNewVec (size, b0,b1, C, g);

    /*create the eigen vector*/
    createEigen (size, b0, *b1, C,g);

}


/*calculate the first vector*/
void createRandVec (double*  b0, int n)
{
    int i;
    for (i = 0;i < n;i++){
        b0[i] =(double) rand();
    }
}


/*calculate the next vector by the given equation*/
void calculateTheNewVec (int n, double* bk, double** next_bk, community* C, group* g)
{
    double normAbk , sum = 0;
    int i;

    calculate_B_hat_mult_v(C, g, bk, *next_bk, 1);

    for (i = 0; i < n; i++) {
        (*next_bk)[i] += (C->norm1 * bk[i]);
    }

    for(i = 0;i < n; i++){
        sum += ((*next_bk)[i]) * ((*next_bk)[i]);
    }

    normAbk = sqrt(sum);

    if(fabs(normAbk) < ZERO) DivideByZero

    for(i = 0;i < n; i++){
        (*next_bk)[i] = (double) ((*next_bk)[i] / normAbk);
    }
}

/*create the eigen vector*/
void createEigen (int n, double* bk, double* next_bk, community* C, group* g)
{
    int i = 0, k, cnt_infinity = 0;


    while(i < n){
        cnt_infinity ++;
        if(fabs(bk[i]-next_bk[i]) > ZERO){
            for(k = 0;k < n;k++)
                bk[k] = next_bk[k];
            calculateTheNewVec (n, bk, &next_bk, C, g);
            i = 0;
        }
        i++;
       if (cnt_infinity > FIN * C->sm->n) InfinityLoop
    }

    free(bk);
}

/*calculate the eigenValue*/
void leading_eigenValue(community* C, double* eigenValue, double* eigenVector, group* g)
{
    int n, i;
    double* B_v;
    double numerator = 0, denominator = 0;

    n = g->size;
    B_v = (double*)malloc(n * sizeof(double));
    if(B_v == NULL) MallocFailed

    calculate_B_hat_mult_v(C, g, eigenVector, B_v, 1);

    for (i = 0; i < n; i++) {
        B_v[i] += (C->norm1 * B_v[i]);
    }

    /*calculate bk*bk*/
    for(i = 0;i < n; ++i){
        numerator += B_v[i]* eigenVector [i];
        denominator += eigenVector[i] * eigenVector[i];
    }

    free(B_v);

    *eigenValue = ((double) numerator/denominator)-(C->norm1);

}
