

/*
 * divisionTwo Summery:
 *
 * Implementation of Algorithm 2     - divide group g to two groups by using Power Iteration and Algorithm 4
 *                   calculateDeltaQ - compute delta Q
 *
 */


#ifndef SP_PROJECT_DIVISIONTWO_H
#define SP_PROJECT_DIVISIONTWO_H

#include "community.h"

double* Algorithm2 (community* C, group* g);
double calculateDeltaQ(community* C, double* s, group* g);

#endif
