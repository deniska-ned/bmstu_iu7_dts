#ifndef __SPARSE_MATRIX_METHODS__

#define __SPARSE_MATRIX_METHODS__

#include <assert.h>
#include <string.h>

#include "vector.h"
#include "vector_methods.h"
#include "sparse_matrix.h"
#include "matrix.h"
#include "matrix_methods.h"

#include "random.h"

#define OKAY                            0
#define REALLOC_FAILED                  1
#define UNABLE_T0_CREATE_ARRAY          2

smatrix_t *matrix_to_smatrix(matrix_t *matrix);

void smatrix_print(smatrix_t *matrix, char *header);

smatrix_t *smatrix_by_scolumn_product(smatrix_t *matrix, smatrix_t *column);

int smatrix_by_scolumn_product_stat_show(smatrix_t *matrix, smatrix_t *column,
bool print_matrixes, matrix_stat_t *stat);

#endif // __SPARSE_MATRIX_METHODS__
