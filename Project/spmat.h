/*
 * spmat module:
 * This module implements a data structure to represent a sparse matrix.
 * This module is used to store the input graph.
 * We used a row implementation, which represents a matrix sm by three:
 *      1. n - the size of the matrix
 *      2. values
 *      3. colind - represent the corresponding col for each member who's different from zero.
 *      4. rowptr - represent for each row how many non-zeros there are before the current row.
 *
 *
 * add_row_array            - Add a new row to the sparse matrix.
 * freeSpmat                - Frees the sparse matrix.
 * spmat_allocate_array     - Allocating a new sparse matrix.
 *
 */


#ifndef _SPMAT_H
#define _SPMAT_H

typedef struct _spmat {
    /* Matrix size (n*n) */
    int	n;
    int *values, *colind, *rowptr;

    /* Adds row i the matrix. Called before any other call,
     * exactly n times in order (i = 0 to n-1) */
    void	(*add_row)(struct _spmat *A, const double *row, int i);

} spmat;


/* Allocates a new arrays sparse matrix of size n with nnz non-zero elements */
spmat* spmat_allocate_array(int n, int nnz);

void freeSpmat (struct _spmat *A);

#endif
