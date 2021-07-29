#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "spmat.h"
#include "community.h"
#include "modularityGroups.h"
#include "error.h"

#define ZERO 0.00001


int main(int argc, char* argv[])
{
    FILE* file = NULL;
    char* inputFileName, *outputFileName;
    int n, t, i, j, l, M, k_i, *kVec;
    double* rowVec;
    spmat* A;
    community* C;
    clock_t startP,endP;
    (void)argc;

    inputFileName = argv[1];
    outputFileName = argv[2];

    startP = clock();

    file = fopen(inputFileName, "rb");
    if (file == NULL) FailedOpen


    /*n = |V|, i.e., the number of vertices in the graph*/
    t = fread(&n, sizeof(int), 1, file);
    if (t != 1) FailedRead
    if (n == 0) ZeroNodes


    /*iterate over the input graph to calculate:
     *  'kVec' = vector that contains the degrees of the vertices in the graph
     *  'M' = sum of k_i = the number of non-zero elements in the adjacency matrix*/

    kVec = (int*) malloc(n * sizeof(int));
    if(kVec == NULL) MallocFailed

    M = 0;
    for (i = 0; i < n; i++)
    {
        /*k_i = the degree of vertex i in the graph*/
        t = fread(&k_i, sizeof(int), 1, file);
        if (t != 1) FailedRead

        kVec[i] = k_i;
        M += k_i;

        /*skip to the next k_i in the file*/
        t = fseek(file, k_i*sizeof(int) ,SEEK_CUR);
        if (t != 0) FailedFseek
    }

    /*if M=0, then (k_i*k_j)/M is Undefined*/
    if (M == 0) ZeroEdges

    /*iterate again over the input graph to calculate:
     * 'sm' = the sparse matrix corresponding the graph
     * */
    rewind(file);
    t = fseek(file, sizeof(int) ,SEEK_CUR);
    if (t != 0) FailedFseek

    A = spmat_allocate_array(n, M);
    rowVec = (double*) malloc(n * sizeof(double));
    if(rowVec == NULL) MallocFailed

    for (i = 0; i < n; i++)
    {
        /*k_i = the degree of vertex i in the graph*/
        t = fread(&k_i, sizeof(int), 1, file);
        if (t != 1) FailedRead

        /*calculate row i of the matrix and adding it to the sparse matrix*/
        for (j = 0; j < n; j++)
        {
            rowVec[j] = 0;

        }
        for (j = 0; j < k_i; j++)
        {
            t = fread(&l, sizeof(int), 1, file);
            if (t != 1) FailedRead
            rowVec[l] = 1;
        }
        A->add_row(A, rowVec, i);
    }
    free(rowVec);
    fclose(file);
    /* -finished reading from the file- */

    C = create_community(A, kVec, M);
    Algorithm3(C, outputFileName);

    free_community(C);

    endP = clock();
    printf("Execution took %f seconds\n", ((double)(endP-startP)/CLOCKS_PER_SEC));

    /*On a successful execution the main function return 0*/
    return 0;
}




