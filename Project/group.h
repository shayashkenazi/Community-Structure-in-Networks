/*gorup Summery:
 *
 * This module holds all the data for the group g:
 *      1. arr - holds the appropriate indexes for the group g
 *      2. size - holds the size of the group i.e. the number of indexes in g
 *      3. map_g - a map for the arr in g in size of n (the original nodes of the graph),
 *                 such that every element in the map will keep the place according to the number
 *                 of members in g and -1 otherwise
 *      4. next - connecting the current group to the next group in the data structure - modularityGroups
 *      5. prev - connecting the current group to the previous group in the data structure - modularityGroups
 *
 *      initGroup - initialize the group with a given arr and size
 *      freeGroup - Frees all resources used by group g
 *      initMapG  - initialize map_g according to the arr in g
 *
 * modularityGroups Summery:
 *
 * This module holds groups:
 *      1. head - the first group
 *      2. tail - the last group
 *      3. sizeOfGroups - the total number of groups
 *
 *      isEmpty               - returns 0 if the modularityGroups is not empty and 1 otherwise
 *      init                  - creates a modularityGroups contains a group with array intialize from {0,...,n-1}
 *                              according to the n ew get
 *      initEmpty             - creates an empty modularityGroups
 *      freeModularityGroups  - Frees all resources used by modularityGroups
 *      insert                - insert a group g to modularityGroups
 *      pop                   - remove the last group in modularityGroups and return it
 *
 *
 */


#ifndef SP_PROJECT_GROUP_H
#define SP_PROJECT_GROUP_H
#include "community.h"

typedef struct group{
    int* arr;
    int size;
    int* map_g;
    struct group* next;
    struct group* prev;
}group;

group* init_group(community* C, int* arr, int size);

void freeGroup(group* g);

int* initMapG(community* C, group* g);

typedef struct modularityGroups{
    group* head;
    group* tail;
    int sizeOfGroups;
}modularityGroups;

int isEmpty (modularityGroups* groups);

modularityGroups* init(community* C, int size);

void freeModularityGroups(modularityGroups* groups);

modularityGroups* initEmpty ();

void insert(modularityGroups* groups, group* g);

group* pop (modularityGroups* groups);



#endif
