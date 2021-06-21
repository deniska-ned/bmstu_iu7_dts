#include "../inc/sparse_matrix.h"

smatrix_t *smatrix_allocate(size_t row_count, size_t column_count,
const size_t num_count)
{
    LOG_INFO(">> row_count = %zu; column_count = %zu; num_count = %zu",
    row_count, column_count, num_count);

    assert(num_count <= row_count * column_count);

    if (0 == row_count || 0 == column_count)
    {
        row_count = 0;
        column_count = 0;
    }

    smatrix_t *smatrix = malloc(sizeof(smatrix_t));

    if (NULL != smatrix)
    {
        smatrix->values = vector_allocate(num_count, sizeof(int));

        if (NULL != smatrix->values)
        {
            smatrix->columns = vector_allocate(num_count, sizeof(size_t));

            if (NULL != smatrix->columns)
            {

                smatrix->pointers = vector_allocate(row_count + 1,
                        sizeof(size_t));

                if (NULL != smatrix->pointers)
                {
                    smatrix->row_count = row_count;
                    smatrix->column_count = column_count;
                    smatrix->num_count = num_count;

                    return smatrix;
                }

                vector_free(smatrix->columns);
            }

            vector_free(smatrix->values);
        }

        free(smatrix);
    }

    LOG_ERROR("%s", "<< Some error with allocation memory");

    return NULL;
}

void smatrix_free(smatrix_t *matrix)
{
    if (NULL == matrix)
    {
        LOG_WARNING("%s", "<< NULL == matrix");
        return;
    }

    vector_free(matrix->values);
    vector_free(matrix->columns);
    vector_free(matrix->pointers);

    free((void *) matrix);

    matrix = NULL;
}

size_t smatrix_get_row_count(smatrix_t *matrix)
{
    return matrix->row_count;
}

size_t smatrix_get_column_count(smatrix_t *matrix)
{
    return matrix->column_count;
}

size_t smatrix_get_num_count(smatrix_t *matrix)
{
    return matrix->num_count;
}

size_t smatrix_get_size(smatrix_t *matrix)
{
    size_t size = 0;

    size += vector_get_size(matrix->values);
    size += vector_get_size(matrix->columns);
    size += vector_get_size(matrix->pointers);

    size += sizeof(smatrix_t);

    return size;
}
