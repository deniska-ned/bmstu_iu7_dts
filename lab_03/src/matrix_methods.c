#include "../inc/matrix_methods.h"

size_t calculate_nonzero_elements(size_t n, size_t m, double cover)
{
    LOG_INFO(">> n == %zu; m == %zu; cover == %lf", n, m, cover);

    size_t nonzero_count;

    if (0 > cover)
    {
        LOG_WARNING("%s", "Cover is negative. It rounded to 0.0");

        cover = 0.0;
    }

    nonzero_count = (size_t) ceil(cover * (double) n * (double) m / 100.0);

    if (nonzero_count > n * m)
    {
        LOG_WARNING("Nonzero elements count exceed = %zu -> round to %zu",
        nonzero_count, n * m);

        nonzero_count = n * m;
    }
    
    LOG_INFO("<< Nonzero elements count = %zu", nonzero_count);

    return nonzero_count;
}

void matrix_autofill(matrix_t *matrix, double cover)
{
    size_t n = matrix->row_count, m = matrix->column_count;
    size_t num_count = n * m;

    size_t nonzero_count = calculate_nonzero_elements(n, m, cover);

    for (size_t i = 0; i < n * m; ++i)
        matrix_set_int_at(matrix, i / m, i % m, 0);

    for (size_t i = 0; i < nonzero_count; ++i)
    {
        size_t el_i = rand_uint64_slow() % num_count;

        while (0 != matrix_get_int_at(matrix, el_i / m, el_i % m))
            el_i = (el_i + 1) % num_count;

        int value = rand() % RAND_MAX % 999 + 1;
        matrix_set_int_at(matrix, el_i / m, el_i % m, value);
    }
}

matrix_t *matrix_by_column_product(matrix_t *matrix, matrix_t *column)
{
    assert(NULL != matrix);
    assert(NULL != column);

    assert(matrix->column_count == column->row_count);
    assert(matrix->el_size == sizeof(int));
    assert(column->el_size == sizeof(int));
    assert(1 == column->column_count);

    matrix_t *product = matrix_allocate(matrix->row_count,
    column->column_count, sizeof(int));

    if (0 == product->row_count * product->column_count)
        return product;

    if (NULL == product)
    {
        LOG_ERROR("%s", "<< Unable to allocate memory for product matrix");

        return NULL;
    }

    for (size_t product_i = 0; product_i < product->row_count; ++product_i)
    {
        int el = 0;
        for (size_t j = 0; j < matrix->column_count; ++j)
            el += (matrix_get_int_at(matrix, product_i, j) *
            matrix_get_int_at(column, j, 0));

        matrix_set_int_at(product, product_i, 0, el);
    }

    return product;
}

int matrix_by_column_product_stat_show(matrix_t *matrix, matrix_t *column,
bool print_matrixes, matrix_stat_t *stat)
{
    size_t start = curr_ticks();
    matrix_t *product = matrix_by_column_product(matrix, column);
    size_t end = curr_ticks();

    if (NULL == product)
    {
        LOG_DEBUG("%s", "<< Unable to get product matrix");
        return UNABLE_T0_ALLOCATE_MEMORY;
    }

    if (true == print_matrixes &&
    matrix->row_count <= MAX_PRINTABLE_ROW_COUNT &&
    matrix->column_count <= MAX_PRINTABLE_COL_COUNT)
    {
        LOG_INFO("%s", "print product");
        printf("\nMatrix by column product\n");
        matrix_print(matrix, "Matrix");
        matrix_print(column, "Column");
        matrix_print(product, "Product");
        printf("\n");
    }

    stat->matrix_size = matrix_get_size(matrix);
    stat->column_size = matrix_get_size(column);
    stat->product_size = matrix_get_size(product);
    stat->ticks = end - start;

    matrix_free(product);

    return OKAY;
}

void matrix_print(matrix_t *matrix, char *header)
{
    if (strlen(header))
        printf("\n%s\n", header);

    if (0 == matrix->row_count * matrix->column_count)
        printf("Matrix zero len\n");

    for (size_t i = 0; i < matrix->row_count; ++i)
    {
        for (size_t j = 0; j < matrix->column_count; ++j)
            printf("%3d ", matrix_get_int_at(matrix, i, j));

        printf("\n");
    }
}

size_t matrix_count_nonzero_elems(matrix_t *matrix)
{
    size_t count = 0;

    for (size_t i = 0; i < matrix->row_count; ++i)
        for (size_t j = 0; j < matrix->column_count; ++j)
            if (0 != matrix_get_int_at(matrix, i, j))
                ++count;

    return count;
}

