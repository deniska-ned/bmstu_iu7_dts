#ifndef __MATRIX_METHODS__

#define __MATRIX_METHODS__

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

#include "matrix.h"
#include "random.h"
#include "math.h"
#include "timer.h"
#include "matrix_types.h"

#define OKAY                            0
#define UNABLE_T0_ALLOCATE_MEMORY       1

/**
 * @brief Calculate number of nonzero element for matrix
 *
 * Calculate number of nonzero element for matrix by matrix axis and cover
 * in percent. If get value move than n*m then return n*m. If get value less
 * that 0 then return 0;
 *
 * @return Nonzero element number
 */
size_t calculate_nonzero_elements(size_t n, size_t m, double cover);

/**
 * Autofill matrix with nonzero values based on cover. Values in range
 * [1, 1000]
 */
void matrix_autofill(matrix_t *matrix, double cover);

/**
 * @return Matrix by column product
 */
matrix_t *matrix_by_column_product(matrix_t *matrix, matrix_t *column);

/**
 * Calculate statistics and print matrix if print_matrix == true
 *
 * @return OKAY if no error; 
 * UNABLE_T0_ALLOCATE_MEMORY if unable to allocate memory for product
 */
int matrix_by_column_product_stat_show(matrix_t *matrix, matrix_t *column,
bool print_matrixes, matrix_stat_t *stat);

/**
 * @brief Print matrix
 *
 * Print matrix data with header. It header is empty line? then place for
 * header not printed
 */
void matrix_print(matrix_t *matrix, char *header);

/**
 * @return Nonzero elements count in matrix
 */
size_t matrix_count_nonzero_elems(matrix_t *matrix);

#endif // __MATRIX_METHODS__
