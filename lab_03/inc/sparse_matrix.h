#ifndef __SPARSE_MATRIX_H__

#define __SPARSE_MATRIX_H__

#include <stdlib.h>
#include <assert.h>

#include "macrologger.h"

#include "vector.h"

typedef struct
{
    vector_t *values;
    vector_t *columns;
    vector_t *pointers;

    size_t row_count;
    size_t column_count;

    size_t num_count;
} smatrix_t;

/**
 * @brief Create dynamic sparse matrix
 *
 * @return Pointer to sparse matrix if success;
 * NULL if unable to allocate matrix;
 */
smatrix_t *smatrix_allocate(size_t row_count, size_t column_count,
const size_t num_count);

/**
 * @brief Free dymanic matrix data
 */
void smatrix_free(smatrix_t *matrix);

/**
 * @brief Return row count of matrix
 *
 * @return Row count of matrix
 */
size_t smatrix_get_row_count(smatrix_t *matrix);

/**
 * @brief Return column count of matrix
 *
 * @return Column count of matrix
 */
size_t smatrix_get_column_count(smatrix_t *matrix);

/**
 * @brief Return number count of matrix
 *
 * @return Number count of matrix
 */
size_t smatrix_get_num_count(smatrix_t *matrix);

/**
 * @return Num count of sparse matrix
 */
size_t smatrix_get_size(smatrix_t *matrix);

#endif // __SPARSE_MATRIX_H__
