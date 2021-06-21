#include "../inc/statistics.h"

#define T_C_SORT_TIME_I                 0
#define T_K_GEN_TIME_I                 1
#define T_K_SORT_TIME_I                 2

#define QSORT_I                         0
#define SEL_SORT_I                      1

typedef int (*comp_func_t)(const void *, const void *);

typedef void (*sort_func_t)(void *, size_t, size_t, comp_func_t);

void show_ticks_statistics(table_countries_t *table_countries)
{
    table_keys_t table_keys;

    sort_func_t sort_func_arr[SORT_NUM] = {
        qsort, selection_sort
    };

    size_t ticks[CONTENT_TYPE_NUM][SORT_NUM];
    for (int i = 0; i < CONTENT_TYPE_NUM; ++i)
        for (int j = 0; j < SORT_NUM; ++j)
            ticks[i][j] = 0.0;

    for (int i = 0; i < RUN_NUM; ++i)
        for (int sort_i = 0; sort_i < SORT_NUM; ++sort_i)
        {
            uint64_t ticks_b, ticks_e;
            size_t len, el_size;

            // Table sort

            table_countries_t copy_table_countries = *table_countries;

            country_t *ptr_c = copy_table_countries.data;
            len = copy_table_countries.length;
            el_size = sizeof(country_t);

            ticks_b = tick();
            sort_func_arr[sort_i](ptr_c, len, el_size, comp_countries);
            ticks_e = tick();

            // Adding country table sort time
            assert(ticks[T_C_SORT_TIME_I][sort_i] <
            ticks[T_C_SORT_TIME_I][sort_i] + (ticks_e - ticks_b));

            ticks[T_C_SORT_TIME_I][sort_i] += (ticks_e - ticks_b);

            // Key sort

            ticks_b = tick();
            gen_table_keys(table_countries, &table_keys);
            ticks_e = tick();

            // Adding key table generation time
            assert(ticks[T_K_GEN_TIME_I][sort_i] <
            ticks[T_K_GEN_TIME_I][sort_i] + (ticks_e - ticks_b));

            ticks[T_K_GEN_TIME_I][sort_i] += (ticks_e - ticks_b);

            key_name_t *ptr_k = table_keys.data;
            len = table_keys.length;
            el_size = sizeof(key_name_t);
            
            ticks_b = tick();
            sort_func_arr[sort_i](ptr_k, len, el_size, comp_keys);
            ticks_e = tick();

            // Adding key table sort time
            assert(ticks[T_K_SORT_TIME_I][sort_i] <
            ticks[T_K_SORT_TIME_I][sort_i] + (ticks_e - ticks_b));

            ticks[T_K_SORT_TIME_I][sort_i] += ticks_e - ticks_b;
        }

    for (int i = 0; i < CONTENT_TYPE_NUM; ++i)
        for (int j = 0; j < SORT_NUM; ++j)
            ticks[i][j] /= RUN_NUM;

    // Output results
    
    printf(TABLE_STAT_HEADER);

    printf("Сортировка таблицы стран │  %15zu │ %15zu\n",
    ticks[T_C_SORT_TIME_I][QSORT_I], ticks[T_C_SORT_TIME_I][SEL_SORT_I]);

    printf("Создание таблицы ключей  │  %15zu │ %15zu\n",
    ticks[T_K_GEN_TIME_I][QSORT_I], ticks[T_K_GEN_TIME_I][SEL_SORT_I]);

    printf("Сортировка таблицы ключей│  %15zu │ %15zu\n",
    ticks[T_K_SORT_TIME_I][QSORT_I], ticks[T_K_SORT_TIME_I][SEL_SORT_I]);

    size_t table_c_size = sizeof(table_countries_t);
    size_t table_k_size = sizeof(table_keys_t);
    double diff = (100.0 * (double) (table_k_size) / (double) table_c_size);

    printf("\nТаблица стран: %zu Б\n", table_c_size);
    printf("Таблица стран с ключами: %zu Б (%.2lf%%)\n", table_k_size, diff);
}

void show_clock_statistics(table_countries_t *table_countries,
table_keys_t *table_keys)
{
    sort_func_t sort_func_arr[SORT_NUM] = {
        qsort, selection_sort
    };

    double ticks[CONTENT_TYPE_NUM][SORT_NUM];
    for (int i = 0; i < CONTENT_TYPE_NUM; ++i)
        for (int j = 0; j < SORT_NUM; ++j)
            ticks[i][j] = 0.0;

    for (int i = 0; i < RUN_NUM; ++i)
        for (int sort_i = 0; sort_i < SORT_NUM; ++sort_i)
        {
            clock_t time;
            size_t count, size;

            // Table sort

            table_countries_t copy_table_countries = *table_countries;

            country_t *ptr_c = copy_table_countries.data;
            count = copy_table_countries.length;
            size = sizeof(country_t);

            time = clock();
            sort_func_arr[sort_i](ptr_c, count, size, comp_countries);
            time = clock() - time;

            ticks[0][sort_i] += (double) time / CLOCKS_PER_SEC;

            // Key sort

            time = clock();
            table_keys_t copy_table_keys = *table_keys;
            time = clock() - time;
            ticks[1][sort_i] += (double) time / CLOCKS_PER_SEC;

            key_name_t *ptr_k = copy_table_keys.data;
            count = copy_table_keys.length;
            size = sizeof(key_name_t);
            
            time = clock();
            sort_func_arr[sort_i](ptr_k, count, size, comp_keys);
            time = clock() - time;

            ticks[1][sort_i] += (double) time / CLOCKS_PER_SEC;
        }

    for (int i = 0; i < CONTENT_TYPE_NUM; ++i)
        for (int j = 0; j < SORT_NUM; ++j)
            ticks[i][j] /= RUN_NUM;

    // Output results
    
    double diff_1 = -100.0 * (1.0 - ticks[1][0] / ticks[0][0]);
    double diff_2 = -100.0 * (1.0 - ticks[1][1] / ticks[0][1]);

    printf(TABLE_STAT_HEADER);

    printf("Таблица стран │%.3g            │%.3g\n",
    ticks[0][0], ticks[0][1]);

    printf("Таблица ключей│%.3g (%7.2lf%%) │%.3g (%7.2lf%%)\n",
    ticks[1][0], diff_1, ticks[1][1], diff_2);

    size_t table_c_size = sizeof(table_countries_t);
    size_t table_k_size = sizeof(table_keys_t);
    double diff = (100.0 * (double) (table_k_size) / (double) table_c_size);

    printf("\n");
    printf("Таблица стран: %zu Б\nТаблица стран с ключами: %zu Б (%.2lf%%)\n",
    table_c_size, table_k_size, diff);
}
