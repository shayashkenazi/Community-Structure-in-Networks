#include <stdio.h>
#include <stdlib.h>
#include "modularityGroups.h"
#include "community.h"
#include "divisionTwo.h"
#include "readAndWrite.h"
#include "error.h"


void divideG(community* C, group *g, group** g1, group** g2, double* s) {
    int i, j1 = 0, j2 = 0, sum1 =0;
    int* arr1, *arr2;

    for(i = 0; i < g->size; i++){
        if(s[i] == 1)
            sum1++;
    }

    arr1 = (int*)malloc(sum1*sizeof(int));
    arr2 = (int*)malloc((g->size-sum1)*sizeof(int));
    if(arr1 == NULL || arr2 == NULL) MallocFailed

    for (i = 0; i < g -> size; i++) {
        if (s[i] == 1) {
            arr1[j1] = g->arr[i];
            j1++;
        } else {
            arr2[j2] = g->arr[i];
            j2++;
        }
    }

    *g1 = init_group(C, arr1, sum1);
    *g2 = init_group(C, arr2, g->size-sum1);
}


void Algorithm3 (community* C, char* outFile)
{
    int n;
    modularityGroups *P, *O;
    group *g, *g1, *g2;
    double* s;

    n = C->sm->n;
    P = init(C,n);
    O = initEmpty();

    while(!isEmpty(P))
    {
        g = pop(P);
        s = Algorithm2(C,g);

        divideG(C, g, &g1, &g2, s);

        if(g1->size == 0 || g2->size == 0) {
            insert(O, g);
            freeGroup(g1);
            freeGroup(g2);
        }
        else{
            freeGroup(g);
            if(g1->size == 1)
                insert(O,g1);
            else
                insert(P,g1);
            if(g2->size == 1)
                insert(O,g2);
            else
                insert(P,g2);
        }

        free(s);
    }

    free(P);
    writeToFile(O,outFile);

}



