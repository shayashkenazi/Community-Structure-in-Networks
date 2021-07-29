#include <stdio.h>
#include <stdlib.h>
#include "group.h"
#include "error.h"



/* initialize group containing the array g*/
group* init_group(community* C, int* arr, int n) {
    group* g = (group*)malloc(sizeof(group));
    if(g == NULL) MallocFailed

    g->arr = arr;
    g->size = n;
    g->next = NULL;
    g->prev = NULL;
    g->map_g = initMapG(C, g);
    return g;
}


void freeGroup(group* g){
    free(g->arr);
    free(g->map_g);
    free(g);
}

int* initMapG(community* C, group* g)
{
    int i, n, *map_g = NULL;

    n = C->sm->n;
    map_g = (int*)malloc( n * sizeof(int));
    if (map_g == NULL) MallocFailed

    for(i = 0; i < n; i++)
        map_g [i] = -1;

    for(i = 0; i < g->size; i++)
        map_g[(g->arr)[i]] = i;


    return map_g;

}


int isEmpty (modularityGroups* groups)
{
    if(groups->head == NULL && groups->tail == NULL)
        return 1;
    return 0;
}

modularityGroups* init(community* C, int size)
{
    modularityGroups* groups;
    int i;
    int* arr = NULL;

    /* create array  with elements {0,1,...,n-1} */
    arr = (int*)malloc(size*sizeof(int));
    if (arr == NULL) MallocFailed

    for(i = 0; i < size; i++)
    {
        arr[i] = i;
    }

    /* insert group containing array arr to the beginning of the modularityGroups, and return it */
    groups = (modularityGroups*)malloc(sizeof(modularityGroups));
    if(groups == NULL) MallocFailed

    groups->head = init_group(C, arr, size);
    groups->tail = groups->head;
    groups->tail->next = NULL;
    groups->head->prev = NULL;

    groups->sizeOfGroups = 1;
    return groups;

}

void freeModularityGroups(modularityGroups* groups){
    group* g, *tmp;

    g = groups->head;
    tmp = g;

    while (g != NULL){
        g = g->next;
        freeGroup(tmp);
        tmp = g;
    }
    free(groups);

}

modularityGroups* initEmpty ()
{
    modularityGroups* groups;
    groups = (modularityGroups*)malloc(sizeof(modularityGroups));
    if (groups == NULL) MallocFailed

    groups->head = groups->tail = NULL;
    groups->sizeOfGroups = 0;

    return groups;

}

void insert(modularityGroups* groups, group* g)
{
    if(groups->tail == NULL){
        groups->head = g;
        groups->head->prev = NULL;
        groups->tail = g;
    }
    else{
        groups->tail->next = g;
        g->prev=groups->tail;
        groups->tail = g;
    }
    groups->tail->next = NULL;
    groups->sizeOfGroups ++;
}

group* pop (modularityGroups* groups)
{
    group* g;
    g = groups->tail;

    groups->tail = groups->tail->prev;
    if(groups->tail != NULL)
        groups->tail->next = NULL;
    else
        groups->head = NULL;

   groups->sizeOfGroups --;

    return g;
}