#include <stdlib.h>
#include <stdio.h>
#include "spmat.h"
#include "error.h"


void add_row_array (spmat *A, const double *row, int i) {

    int nnz_i; /*number of non-zero elements in the matrix until row i (excluding row i)*/
    int j;

    nnz_i = (i == 0) ? 0 : (A->rowptr)[i-1];
    while ((A->values)[nnz_i] != 0) {
        nnz_i ++;
    }
    (A->rowptr)[i] = nnz_i;

    for (j = 0; j < (A->n); j++) {
        if (row[j] == 0) {
            continue;
        }
        (A->values)[nnz_i] = row[j];
        (A->colind)[nnz_i] = j;
        nnz_i ++;
    }

}

void freeSpmat (struct _spmat *A) {
    free((A->values));
    free((A->colind));
    free((A->rowptr));
    free(A);
}

void mult_array (const struct _spmat *A, const double *v, double *result) {
    int i, j;
    double sum = 0;

    /*calculating the vector 'result'*/
    for(i = 0; i < (A->n); i++){
        sum = 0;
        for(j = (A->rowptr)[i]; j < (A->rowptr)[i+1]; j++){
            sum += (double) (A->values)[j] * v[(A->colind)[j]];
        }
        result[i] = sum;
    }
}



/* the 'values' array initiated to zeros (0,...,0),
 * the last element of the 'rowptr' array initiated to nnz */
spmat* spmat_allocate_array(int n, int nnz) {
    int i;

    spmat* s = (spmat*) malloc(sizeof(spmat));
    if(s == NULL) MallocFailed

    s->n = n;
    s->add_row = add_row_array;

    s->values = (int*) malloc(nnz * sizeof(int));
    if(s->values == NULL) MallocFailed
    for (i = 0; i < nnz ; i++)
    {
        (s->values)[i] = 0;
    }
    s->colind = (int*) malloc(nnz * sizeof(int));
    s->rowptr = (int*) malloc((n+1) * sizeof(int));
    if (s->colind == NULL || s->colind == NULL) MallocFailed
    (s->rowptr)[n] = nnz;

    return s;
}





