#include <stdio.h>
#include <stdlib.h>
#include "community.h"
#include "readAndWrite.h"
#include "error.h"


void writeToFile(modularityGroups *O,char* outputFileName)
{
    int i, t, N = O->sizeOfGroups, number_of_nodes, indices_k;
    group* cur;
    FILE* outFile;

    outFile = fopen(outputFileName, "w");

    /* represents the number of groups in the division*/
    t = fwrite(&N, sizeof(int), 1, outFile);
    if(t != 1) FailedWriting
    cur = O->head;

    while(cur != NULL) {
        number_of_nodes = cur->size;
        /*represents the number of nodes in the group*/
        t = fwrite(&number_of_nodes, sizeof(int), 1, outFile);
        if (t != 1) FailedWriting
        for (i = 0; i < number_of_nodes; i++) {
            indices_k = cur->arr[i];
            /*indices of the nodes in the group, in increasing order.*/
            t = fwrite(&indices_k, sizeof(int), 1, outFile);
            if (t != 1) FailedWriting
        }
        cur = cur->next;
    }
    fclose(outFile);
    freeModularityGroups(O);
}
