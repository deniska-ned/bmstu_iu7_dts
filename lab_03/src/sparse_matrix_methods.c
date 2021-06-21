#include "../inc/sparse_matrix_methods.h"

smatrix_t *matrix_to_smatrix(matrix_t *matrix)
{
    int el;

    size_t row_count = matrix->row_count;
    size_t column_count = matrix->column_count;
    size_t num_count = matrix_count_nonzero_elems(matrix);

    smatrix_t *smatrix = smatrix_allocate(row_count, column_count,
    num_count);

    if (NULL == smatrix)
    {
        LOG_ERROR("%s", "<< Unable allocate memory for sparse matrix");

        return NULL;
    }

    if (0 != row_count * column_count)
    {
        vector_t *values = smatrix->values;
        vector_t *columns = smatrix->columns;
        vector_t *pointers = smatrix->pointers;
    
        vector_set_size_t_at(pointers, row_count, num_count);
    
        for (size_t i = row_count - 1, num_i = num_count - 1; ; --i)
        {
            for (size_t j = column_count - 1; ; --j)
            {
                if (0 != (el = matrix_get_int_at(matrix, i, j)))
                {
                    vector_set_int_at(values, num_i, el);
                    vector_set_size_t_at(columns, num_i, j);
                    --num_i;
                }
                
                if (0 == j)
                    break;
            }
    
            vector_set_size_t_at(pointers, i, num_i + 1);
    
            if (0 == i)
            {
                assert((size_t) 0 - (size_t) 1 == num_i);
                break;
            }
        }
    }
    else
    {
        // For valgrind
        vector_set_size_t_at(smatrix->pointers, 0, 0);
    }

    return smatrix;
}

void smatrix_print(smatrix_t *matrix, char *header)
{
    vector_t *values = matrix->values;
    vector_t *columns = matrix->columns;
    vector_t *pointers = matrix->pointers;

    if (strlen(header))
        printf("%s\n", header);

    printf("Values:   ");

    if (0 == matrix->values->length)
        printf("vector zero len");

    for (size_t i = 0; i < matrix->num_count; ++i)
        printf("%3d ", vector_get_int_at(values, i));
    printf("\n");

    printf("Columns:  ");

    if (0 == matrix->columns->length)
        printf("vector zero len");

    for (size_t i = 0; i < matrix->num_count; ++i)
        printf("%3zu ", vector_get_size_t_at(columns, i));
    printf("\n");

    printf("Pointers: ");

    if (0 == matrix->pointers->length)
        printf("vector zero len");

    for (size_t i = 0; i < matrix->row_count + 1; ++i)
        printf("%3zu ", vector_get_size_t_at(pointers, i));
    printf("\n\n");
}

smatrix_t *smatrix_by_scolumn_product(smatrix_t *matrix, smatrix_t *column)
{
    smatrix_t *product;
    product  = smatrix_allocate(matrix->row_count, 1, matrix->row_count);

    if (NULL == product)
    {
        LOG_ERROR("%s", "<< smatrix_allocate for product failed");
        return NULL;
    }

    int p_el, matrix_value, column_value;
    size_t num_count = 0, begin_row_ptr, end_row_ptr, matrix_cur_row_ptr,
    column_row_ptr, column_next_row_ptr, matrix_value_col_i;

    for (size_t matrix_row_i = 0; matrix_row_i < product->row_count;
    ++matrix_row_i)
    {
        begin_row_ptr = vector_get_size_t_at(matrix->pointers,
        matrix_row_i);
        end_row_ptr = vector_get_size_t_at(matrix->pointers,
        matrix_row_i + 1);

        p_el = 0;
        for (matrix_cur_row_ptr = begin_row_ptr;
        matrix_cur_row_ptr < end_row_ptr; ++matrix_cur_row_ptr)
        {
            matrix_value = vector_get_int_at(matrix->values,
            matrix_cur_row_ptr);
            matrix_value_col_i = vector_get_size_t_at(matrix->columns,
            matrix_cur_row_ptr);

            column_row_ptr = vector_get_size_t_at(column->pointers,
            matrix_value_col_i);
            column_next_row_ptr = vector_get_size_t_at(column->pointers,
            matrix_value_col_i + 1);

            column_value = column_row_ptr == column_next_row_ptr ? 0 :
            vector_get_int_at(column->values, column_row_ptr);

            p_el += matrix_value * column_value;
        }

        vector_set_size_t_at(product->pointers, matrix_row_i, num_count);

        if (0 != p_el)
        {
            vector_set_int_at(product->values, num_count, p_el);
            vector_set_size_t_at(product->columns, num_count, 0);

            ++num_count;
        }
    }

    vector_set_size_t_at(product->pointers, product->row_count, num_count);
    
    product->num_count = num_count;

    bool realloc_corect = true;

    if (OKAY != vector_realloc(product->values, num_count))
    {
        LOG_ERROR("%s", "product->values realloc failed");
        realloc_corect = false;
    }

    if (OKAY != vector_realloc(product->columns, num_count))
    {
        LOG_ERROR("%s", "product->columns realloc failed");
        realloc_corect = false;
    }

    if (!realloc_corect)
    {
        smatrix_free(matrix);
        return NULL;
    }

    return product;
}

int smatrix_by_scolumn_product_stat_show(smatrix_t *matrix, smatrix_t *column,
bool print_matrixes, matrix_stat_t *stat)
{
    size_t start = curr_ticks();
    smatrix_t *product = smatrix_by_scolumn_product(matrix, column);
    size_t end = curr_ticks();

    if (NULL == product)
    {
        LOG_ERROR("%s", "Unable to get product smatrix");
        return UNABLE_T0_ALLOCATE_MEMORY;
    }

    if (true == print_matrixes &&
    matrix->row_count <= MAX_PRINTABLE_ROW_COUNT &&
    matrix->column_count <= MAX_PRINTABLE_COL_COUNT)
    {
        LOG_INFO("%s", "print product");
        printf("\nSparse matrix by sparse column product\n");
        smatrix_print(matrix, "--MATRIX--");
        smatrix_print(column, "--COLUMN--");
        smatrix_print(product, "--PRODUCT--");
        printf("\n");
    }

    stat->matrix_size = smatrix_get_size(matrix);
    stat->column_size = smatrix_get_size(column);
    stat->product_size = smatrix_get_size(product);
    stat->ticks = end - start;

    LOG_INFO("%s", "smatrix free for matrix product");
    smatrix_free(product);

    return OKAY;
}
