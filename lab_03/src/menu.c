#include "../inc/menu.h"

int run_calc(matrix_t *matrix, matrix_t *column, smatrix_t *smatrix,
smatrix_t *scolumn, double matrix_cover, double column_cover,
bool print_matrix, bool *is_header_printed, size_t test_index)
{
    matrix_stat_t matrix_stat, smatrix_stat;

    int rc_stat_1, rc_stat_2;
    rc_stat_1 = matrix_by_column_product_stat_show(matrix, column,
    print_matrix, &matrix_stat);

    rc_stat_2 = smatrix_by_scolumn_product_stat_show(smatrix, scolumn,
    print_matrix, &smatrix_stat);

    if (!*is_header_printed)
    {
        printf(TABLE_HEADER_STATICTICS);
        *is_header_printed = true;
    }

    if (OKAY == rc_stat_1)
    {
        printf("%6s│%2zu│%4zu│%4zu│%5.1lf%%│%5.1lf%%│%10zu│%10zu│%10zu│%10zu\n",
        "dense", test_index, matrix->row_count, matrix->column_count,
        matrix_cover, column_cover, matrix_stat.ticks, matrix_stat.matrix_size,
        matrix_stat.column_size, matrix_stat.product_size);
    }
    else
    {
        printf("%6s│ %s\n", "dense", "Error while counting");
    }

    if (OKAY == rc_stat_2)
    {
        printf("%6s│%2zu│%4zu│%4zu│%5.1lf%%│%5.1lf%%│%10zu│%10zu│%10zu│%10zu\n",
        "sparse", test_index, matrix->row_count, matrix->column_count,
        matrix_cover, column_cover, smatrix_stat.ticks,
        smatrix_stat.matrix_size, smatrix_stat.column_size,
        smatrix_stat.product_size);
    }
    else
    {
        printf("%6s│ %s\n", "sparse", "Error while counting");
    }

    smatrix_free(scolumn);
    smatrix_free(smatrix);
    matrix_free(column);
    matrix_free(matrix);

    return OKAY;
}

int init_array(size_t m_row_count, size_t m_col_count, double matrix_cover,
double column_cover, matrix_t **matrix, matrix_t **column, smatrix_t **smatrix,
smatrix_t **scolumn)
{
    int grc = OKAY;

    *matrix = matrix_allocate(m_row_count, m_col_count, sizeof(int));
    *column = matrix_allocate(m_col_count, 1, sizeof(int));

    if (NULL != matrix && NULL != column)
    {
        matrix_autofill(*matrix, matrix_cover);
        matrix_autofill(*column, column_cover);

        *smatrix = matrix_to_smatrix(*matrix);
        *scolumn = matrix_to_smatrix(*column);

        if (NULL != smatrix && NULL != scolumn)
        {
            grc = OKAY;
        }
        else
        {
            LOG_ERROR("Free Smatrix_ptr: %p; scolumn_ptr: %p",
            (void *) smatrix, (void *) scolumn);

            SMATRIX_FREE_IF_NOT_NULL(*scolumn);
            SMATRIX_FREE_IF_NOT_NULL(*smatrix);

            grc = ALLOCATION_FAILED;
        }
    }
    else
    {
        LOG_ERROR("Free Matrix_ptr: %p; column_ptr: %p",
        (void *) matrix, (void *) column);

        MATRIX_FREE_IF_NOT_NULL(*column);
        MATRIX_FREE_IF_NOT_NULL(*matrix);

        smatrix = NULL;
        scolumn = NULL;

        grc = ALLOCATION_FAILED;
    }

    LOG_INFO("<< grc = %d", grc);
    return grc;
}

int scanf_row_col_cover(size_t *row_count, size_t *col_count,
double *matrix_cover, double *column_cover)
{
    int rc;

    printf(MESS_ROW_COL_COUNT_INPUT);

    rc = scanf("%zu%zu", row_count, col_count);
    if (2 != rc || (0 == *row_count && 0 == *col_count))
    {
        LOG_ERROR("%s", "<< Incorrect user row col count input");
        printf(MESS_INCORRECT_INPUT);

        return INCORRECT_ROW_COL_INPUT;
    }
    goto_newline(stdin);

    printf(MESS_COVER_COUNT_INPUT);

    rc = scanf("%lf %lf", matrix_cover, column_cover);
    if (2 != rc || *matrix_cover < 0 || *matrix_cover > 100.0 ||
    *column_cover < 0.0 || *column_cover > 100.0)
    {
        LOG_ERROR("%s", "<< Incorrect user cover input");
        printf(MESS_INCORRECT_INPUT);

        return INCORRECT_COVER_INPUT;
    }
    goto_newline(stdin);

    LOG_INFO("<< row = %zu; col = %zu; mat_cover = %fl; col_cover = %lf",
    *row_count, *col_count, *matrix_cover, *column_cover);
    return OKAY;
}

int autofill_menu_case()
{
    int rc, grc;
    size_t m_row_count, m_col_count;
    double matrix_cover, column_cover;
    bool is_header_printed = false;

    rc = scanf_row_col_cover(&m_row_count, &m_col_count, &matrix_cover,
    &column_cover);

    if (OKAY != rc)
    {
        LOG_ERROR("%s", "<< Incorrect user row col count input");
        printf(MESS_INCORRECT_INPUT);

        return INCORRECT_ROW_COL_INPUT;
    }

    matrix_t *matrix, *column;
    smatrix_t *smatrix, *scolumn;

    rc = init_array(m_row_count, m_col_count, matrix_cover, column_cover,
    &matrix, &column, &smatrix, &scolumn);

    if (OKAY == rc)
    {
        run_calc(matrix, column, smatrix, scolumn, matrix_cover, column_cover,
        true, &is_header_printed, 0);
    }
    else
    {
        grc = rc;
    }

    return grc;
}

int stat_menu_case()
{
    int rc, grc;
    size_t m_row_count, m_col_count;

    bool is_header_printed = false;

    size_t m_row_count_arr[] = {100, 500, 1000};
    size_t m_row_count_arr_len = (sizeof(m_row_count_arr) /
    sizeof(m_row_count_arr[0]));

    double cover_arr[] = {0.0, 10.0, 40.0, 50.0, 100.0};
    size_t cover_arr_len = sizeof(cover_arr) / sizeof(cover_arr[0]);

    for (size_t m_row_count_i = 0; m_row_count_i < m_row_count_arr_len;
    ++m_row_count_i)
    {
        double matrix_cover, column_cover;
        m_row_count = m_col_count = m_row_count_arr[m_row_count_i];

        for (size_t cover_arr_i = 0; cover_arr_i < cover_arr_len;
        ++cover_arr_i)
        {
            matrix_cover = column_cover = cover_arr[cover_arr_i];

            m_col_count = m_row_count;

            matrix_t *matrix, *column;
            smatrix_t *smatrix, *scolumn;

            rc = init_array(m_row_count, m_col_count, matrix_cover,
            column_cover, &matrix, &column, &smatrix, &scolumn);

            if (OKAY == rc)
            {
                run_calc(matrix, column, smatrix, scolumn, matrix_cover,
                column_cover, false, &is_header_printed,
                m_row_count_i * cover_arr_len + cover_arr_i);
            }
            else
            {
                grc = rc;
            }
        }
    }

    return grc;
}

int manual_input_array(matrix_t **matrix, matrix_t **column,
smatrix_t **smatrix, smatrix_t **scolumn, double *matrix_cover,
double *column_cover)
{
    *matrix = NULL;
    *column = NULL;
    *smatrix = NULL;
    *scolumn = NULL;

    size_t m_row_count, m_col_count, num_count;

    printf(MESS_ROW_COL_NUMCOUNT_INPUT);
    if (3 != scanf("%zu%zu%zu", &m_row_count, &m_col_count, &num_count))
    {
        LOG_ERROR("%s", "<< Incorrect user row col count input");
        printf(MESS_INCORRECT_INPUT);

        return INCORRECT_ROW_COL_INPUT;
    }
    *matrix_cover = (100.0 * (double) num_count / (double) m_row_count /
    (double) m_col_count);

    *matrix = matrix_allocate(m_row_count, m_col_count, sizeof(int));
    *column = matrix_allocate(m_col_count, 1, sizeof(int));

    if (NULL != matrix && NULL != column)
    {
        for (size_t i = 0; i < m_row_count; ++i)
            for (size_t j = 0; j < m_col_count; ++j)
                matrix_set_int_at(*matrix, i, j, 0);

        for (size_t i = 0; i < m_col_count; ++i)
            matrix_set_int_at(*column, i, 0, 0);

        for (size_t i = 0; i < num_count; ++i)
        {
            size_t row_i, col_i;
            int value;

            printf(MESS_ROW_COL_VALUE_INPUT);
            if (3 == scanf("%zu%zu%d", &row_i, &col_i, &value) &&
            row_i < m_row_count && col_i < m_col_count)
                matrix_set_int_at(*matrix, row_i, col_i, value);
            else
                printf(MESS_INCORRECT_INPUT);
        }

        printf(MESS_NUM_COUNT);
        if (1 != scanf("%zu", &num_count))
        {
            LOG_ERROR("%s", "<< Incorrect data input");
            printf(MESS_INCORRECT_INPUT);

            return INCORRECT_INPUT;
        }
        *column_cover = 100.0 * (double) num_count / (double) m_row_count;

        for (size_t i = 0; i < num_count; ++i)
        {
            size_t row_i;
            int value;
            printf(MESS_ROW_VALUE_INPUT);
            if (2 == scanf("%zu%d", &row_i, &value) && row_i < m_col_count)
                matrix_set_int_at(*column, row_i, 0, value);
            else
                printf(MESS_INCORRECT_INPUT);
        }

        *smatrix = matrix_to_smatrix(*matrix);
        *scolumn = matrix_to_smatrix(*column);

        if (NULL != smatrix && NULL != scolumn)
        {
            return OKAY;
        }
        else
        {
            smatrix_free(*scolumn);
            smatrix_free(*smatrix);
            matrix_free(*column);
            matrix_free(*matrix);

            return ALLOCATION_FAILED;
        }
    }
    else
    {
        matrix_free(*matrix);
        matrix_free(*column);

        return ALLOCATION_FAILED;
    }
}

int manual_input_case()
{
    int rc, grc;
    double matrix_cover, column_cover;
    bool is_header_printed = false;

    matrix_t *matrix = NULL, *column = NULL;
    smatrix_t *smatrix = NULL, *scolumn = NULL;

    rc = manual_input_array(&matrix, &column, &smatrix, &scolumn,
    &matrix_cover, &column_cover);

    if (OKAY == rc)
    {
        run_calc(matrix, column, smatrix, scolumn, matrix_cover, column_cover,
        true, &is_header_printed, 0);
    }
    else
    {
        grc = rc;
    }

    return grc;
}

int menu_run()
{
    int rc, grc;

    printf(MESS_MENU "\n" MESS_MENU_CHOICE);

    int choise;

    rc = scanf("%d", &choise);

    if (1 != rc)
    {
        LOG_ERROR("%s", "Incorrect user menu input (NaN)");
        printf(MESS_INCORRECT_INPUT);

        return INCORRECT_INPUT;
    }

    printf("\n");
    switch (choise)
    {
        case 0:
            printf(MESS_EXIT);
            break;
        case 1:
            autofill_menu_case();
            break;
        case 2:
            manual_input_case();
            break;
        case 3:
            stat_menu_case();
            break;
        default:
            LOG_ERROR("%s", "Incorrect user menu input (NaN)");
            printf(MESS_INCORRECT_INPUT);

            grc = INCORRECT_MENU_INPUT;
            break;
    }

    return grc;
}
