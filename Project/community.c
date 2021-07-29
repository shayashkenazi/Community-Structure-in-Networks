#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "community.h"
#include "error.h"


community* create_community(spmat* sm, int* kVec, int M)
{
    community* C = (community*) malloc(sizeof(community));
    if (C == NULL) MallocFailed
    C->sm = sm;
    C->kVec = kVec;
    C->M = M;
    calculateNorm1(C);

    return C;
}

void free_community(community* C)
{
    freeSpmat (C->sm);
    free(C->kVec);
    free(C);
}


/*calculate the value of -((k_i*k_j) \ M) */
double kProd(struct _community *C, int i, int j)
{
    int M;
    M = C->M;
    return ((double)(C->kVec[i] * C->kVec[j]) / (double)M);
}


/* calculate the sum of row at B_hat- B_hat = B[g] - delta * f_i
 * which equal to : abs[sum{i!=j} A_ij - k_i*k_j/M] + sum{i!=j}[abs(A_ij - k_i*k_j/M)]*/
double SumRowBHat(community* C,int i)
{
    int j, n, start, end;
    double sum1 = 0, sum2 = 0, res;
    int* rowptr, *colind;

    n = C->sm->n;
    rowptr = C->sm->rowptr;
    colind = C->sm->colind;
    start = rowptr[i];
    end = C->kVec[i] + start;

    for(j = 0; j < n; j++){
        if(i == j) continue;
        if(start < end) {
            if (j == colind[start]){
                sum1 += 1 - (kProd(C,i,j));
                sum2 += fabs(1 - (kProd(C,i,j)));
                start ++;
            }
            else{
                sum1 -= (kProd(C,i,j));
                sum2 += fabs((kProd(C,i,j)));
            }
        }
        else{
            sum1 -= (kProd(C,i,j));
            sum2 += fabs((kProd(C,i,j)));
        }
    }
    res = fabs(sum1) + sum2;
    return res;

}


/*calculate norm1 for B_hat which is: max_j(sum{i}(|B_hat|)*/
void calculateNorm1(community* C)
{
    int i, n;
    double rowSum, maxSum;

    n = C->sm->n;
    maxSum = -1; /* since we sum absolute numbers the sum will be at least 0,
	 	 	 	 	 therefore in the first iteration of the for-loop maxSum's value will update to
	 	 	 	 	 of the sum in absolute numbers of the first column */
    for (i = 0; i < n; i++)
    {
        rowSum = SumRowBHat(C,i);
        if (rowSum > maxSum)
        {
            maxSum = rowSum;
        }
    }
    C->norm1 = maxSum;
}





