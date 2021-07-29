/*
 * modularityGroups module:
 *
 *  In this module we will create the groups P and O by the instructions of Algorithm 3 and create the groups:
 *
 *  Algorithm3  - Implementation of algorithm 3.
 *  divideG     - Divide group g to two groups - g1, g2 according to vector s.
 *
 */

#ifndef SP_PROJECT_MODULARITYGROUPS_H
#define SP_PROJECT_MODULARITYGROUPS_H

#include "community.h"
#include "group.h"

void divideG(community* C, group *g, group** g1, group** g2, double* s);
void Algorithm3 (community* C, char* outfile);

#endif
