#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "community.h"
#include "modularityMaximization.h"
#include "matrixCalculation.h"
#include "error.h"

#define ZERO 0.00001


void Algorithm4(group* g, community* C, double* s) {
    int *unmoved, *indices;
    double deltaQ, *score, *improve, *tmp_s;
    int i, j, size = g->size, maxScore_index , maxImprove, indexImprove, flag = 0;

    /*Allocate memory*/
    unmoved = (int*)malloc(size * sizeof(int));
    indices = (int*)malloc(size * sizeof(int));
    score = (double*)malloc(size * sizeof(double));
    improve = (double*)malloc(size * sizeof(double));
    tmp_s = (double*)malloc(size * sizeof(double));
    if(unmoved == NULL || indices == NULL || score == NULL || improve == NULL || tmp_s == NULL) MallocFailed

    memcpy(tmp_s, s, sizeof(double) * size);

    do {
        /* initializes Unmoved */
        for (i = 0; i < size; i++) {
            unmoved[i] = i;
        }


        for (i = 0; i < size; i++) {
            /*calculate deltaQ for the move of unmoved vertex i
             *  storing the result in score[i] */
            maxScore_index = calculateScore(score, s, unmoved, size, C, g);
            s[maxScore_index] = -s[maxScore_index];
            indices[i] = maxScore_index;
            if (i == 0) {
                improve[i] = score[maxScore_index];
                maxImprove = improve[i];
                indexImprove = i;
            }
            else {
                improve[i] = improve[i - 1] + score[maxScore_index];
                if (maxImprove < improve[i]) {
                    maxImprove = improve[i];
                    indexImprove = i;
                }
            }
            unmoved[maxScore_index] = -1;
        }

        for (i = size - 1; i > indexImprove; i--) {
            j = indices[i];
            s[j] = -s[j];
        }

        if (indexImprove == size - 1) {
            deltaQ = 0;
        }
        else {
            deltaQ = improve[indexImprove];
        }
        flag ++;
    } while (deltaQ > ZERO);

    if(flag == 1)
        memcpy(s, tmp_s, sizeof(double) * size);

    free(score);
    free(unmoved);
    free(indices);
    free(improve);
    free(tmp_s);

}
int calculateScore(double* score, double* s, int* unmoved, int size, community* C ,group* g) {
    int j, i, k, maxIndex = 0, first = 1, *colind, start, end;
    double valD, sum, value, max;

    colind = C->sm->colind;

    for (i = 0; i < size; i++) {
        /* if unmoved[i] == -1 than k isn't in unmoved */
        if (unmoved[i] != -1) {
            s[i] = -s[i];
            /* calculation of value: */
            sum = 0;
            /*the value that help us know how much vertex to move in colind*/
            start = C->sm->rowptr[g->arr[i]];
            end = start + C->kVec[g->arr[i]];
            for (j = start; j < end; j++) {
                if(g->map_g[colind[j]] != -1)
                    sum +=  s[g->map_g[colind[j]]];
            }
            for(k = 0; k < size; k ++) {
                valD = (kProd(C, g->arr[i], g->arr[k]));
                sum -= (valD * s[k]);
            }
            value = (4 * s[i] * sum) + (4 * kProd(C,g->arr[i],g->arr[i] ));
            score[i] = value;
            if (first) {
                max = value;
                maxIndex = i;
                first = 0;
            }
            else if (value > max) {
                max = value;
                maxIndex = i;
            }
            s[i] = -s[i];
        }
    }
    return maxIndex;
}




