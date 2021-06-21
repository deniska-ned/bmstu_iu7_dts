#include <assert.h>
#include "../inc/error_codes.h"
#include "../inc/statistics.h"

#define UNSORTED_DATA                   1
#define SORTED_DATA                     2

#define BUFFER_FILENAME "buffer.txt"

int gen_file(char *file_name, size_t num_count, int file_type)
{
    FILE *f = fopen(file_name, "w");
    if (!f)
        return OPEN_ERROR;

    for (size_t i = 0; i < num_count; i++)
    {
        elem_t elem;
        if (SORTED_DATA == file_type)
            elem = (long) i;
        else
        {
            elem = get_random_long();
        }
        print_elem_to_source(f, elem);
        fprintf(f, "\n");
    }

    fclose(f);

    return EXIT_SUCCESS;
}

elem_t *fread_in_array(char *file_name, size_t elems)
{
    FILE *f = fopen(file_name, "r");
    if (!f)
        return NULL;
    
    elem_t *ptr = malloc(elems * sizeof(elem_t));

    size_t i = 0;
    while (!scan_elem_from_source(f, ptr + i))
    {
        i++;
    }

    fclose(f);

    return ptr;
}

int file_stat(char *file_name, size_t *memory, size_t elems,
size_t *ticks_add, size_t *ticks_search, double *avg_cmp)
{
    elem_t *a = fread_in_array(file_name, elems);
    if (!a)
        return EXIT_FAILURE;

    // add
    *ticks_add = curr_ticks();
    for (size_t i = 0; i < ITERATION_COUNT; i++)
    {
        file_make_empty(BUFFER_FILENAME);
        for (size_t i = 0; i < elems; i++)
            file_add(BUFFER_FILENAME, a[i]);
    }
    *ticks_add = (curr_ticks() - *ticks_add) / ITERATION_COUNT;

    // search
    size_t cmp;
    int find;
    *ticks_search = curr_ticks();
    for (size_t i = 0; i < ITERATION_COUNT; i++)
    {
        for (size_t i = 0; i < elems; i++)
        {
            file_search(BUFFER_FILENAME, a[i], &cmp, &find);
        }
    }
    *ticks_search = (curr_ticks() - *ticks_search) / ITERATION_COUNT;

    // avg_cmp
    double cmp_sum = 0;
    for (size_t i = 0; i < elems; i++)
    {
        file_search(BUFFER_FILENAME, a[i], &cmp, &find);
        cmp_sum += (double) cmp;
    }
    *avg_cmp = cmp_sum / (double) elems;

    //memory
    *memory = sizeof(FILE *) + sizeof(FILE);

    free(a);

    return EXIT_SUCCESS;
}

int tree_stat(char *file_name, size_t *memory, size_t elems,
size_t *ticks_add, size_t *ticks_search, double *avg_cmp)
{
    elem_t *a = fread_in_array(file_name, elems);
    if (!a)
        return EXIT_FAILURE;
    
    // add
    *ticks_add = 0;
    for (size_t i = 0; i < ITERATION_COUNT; i++)
    {
        tc_node_t *root = NULL;

        size_t start = curr_ticks();

        for (size_t i = 0; i < elems; i++)
        {
            tree_add_elem(&root, a[i]);
        }
        *ticks_add += (curr_ticks() - start) / ITERATION_COUNT;
        tree_free(root);
    }

    // search
    size_t cmp;
    tc_node_t *root = NULL;
    tree_add_from_file(file_name, &root);
    *ticks_search = curr_ticks();
    for (size_t i = 0; i < ITERATION_COUNT; i++)
    {
        for (size_t i = 0; i < elems; i++)
        {
            tree_is_elem_found(root, a[i], &cmp);
        }
    }
    *ticks_search = (curr_ticks() - *ticks_search) / ITERATION_COUNT;

    // avg_cmp
    double cmp_sum = 0;
    for (size_t i = 0; i < elems; i++)
    {
        tree_is_elem_found(root, a[i], &cmp);
        cmp_sum += (double) cmp;
    }
    *avg_cmp = cmp_sum / (double) elems;

    //memory
    *memory = elems * sizeof(tc_node_t);

    tree_free(root);
    free(a);

    return EXIT_SUCCESS;
}

int btree_stat(char *file_name, size_t *memory, size_t elems,
size_t *ticks_add, size_t *ticks_search, double *avg_cmp)
{
    elem_t *a = fread_in_array(file_name, elems);
    if (!a)
        return EXIT_FAILURE;
    
    // add
    *ticks_add = 0;
    for (size_t i = 0; i < ITERATION_COUNT; i++)
    {
        tb_node_t *root = NULL;
        size_t start = curr_ticks();
        for (size_t i = 0; i < elems; i++)
        {
            btree_add(&root, a[i]);
        }
        *ticks_add += (curr_ticks() - start) / ITERATION_COUNT;
        btree_free(root);
    }

    // search
    size_t cmp;
    tb_node_t *root = NULL;
    btree_add_from_file(file_name, &root);
    *ticks_search = curr_ticks();
    for (size_t i = 0; i < ITERATION_COUNT; i++)
    {
        for (size_t i = 0; i < elems; i++)
        {
            btree_is_elem_found(root, a[i], &cmp);
        }
    }
    *ticks_search = (curr_ticks() - *ticks_search) / ITERATION_COUNT;

    // avg_cmp
    double cmp_sum = 0;
    for (size_t i = 0; i < elems; i++)
    {
        btree_is_elem_found(root, a[i], &cmp);
        cmp_sum += (double) cmp;
    }
    *avg_cmp = cmp_sum / (double) elems;

    //memory
    *memory = elems * sizeof(tb_node_t);

    btree_free(root);
    free(a);

    return EXIT_SUCCESS;
}

int find_best_hash_func(hash_table_t *table, char *file_name, size_t table_len,
double max_cmp)
{
    int rc = hash_table_create(table, table_len, hash_func_mod);
    if (rc)
        return rc;
    rc = hash_table_add_from_file(file_name, table);
    if (rc)
        return rc;

    while (hash_table_avg_comp(table) > max_cmp)
    {
        hash_func_t hash_func = hash_func_mod == table->hash_func ? hash_func_mlt : hash_func_mod;
        rc = hash_table_restruct(table, table->len, hash_func);
        assert(EXIT_SUCCESS == rc);

        if (hash_table_avg_comp(table) > max_cmp)
        {
            rc = hash_table_restruct(table, get_next_prime_num(table->len), table->hash_func);
            assert(EXIT_SUCCESS == rc);
        }
    }

    return EXIT_SUCCESS;
}

int hash_table_stat(char *file_name, double max_cmp, size_t *memory,
size_t elem_count, size_t *ticks_add, size_t *ticks_search, double *avg_cmp)
{
    hash_table_t perfect_table;
    int rc = find_best_hash_func(&perfect_table, file_name, elem_count, max_cmp);
    assert(!rc);

    elem_t *a = fread_in_array(file_name, elem_count);
    if (!a)
        return EXIT_FAILURE;
    
    // add
    *ticks_add = 0;
    for (size_t i = 0; i < ITERATION_COUNT; i++)
    {
        hash_table_t table;
        int rc = hash_table_create(&table, perfect_table.len,
                                   perfect_table.hash_func);
        assert(!rc);
        size_t start = curr_ticks();
        for (size_t i = 0; i < elem_count; i++)
        {
            hash_table_add(&table, a[i]);
        }
        *ticks_add = (curr_ticks() - start) / ITERATION_COUNT;
        hash_table_free(&table);
    }

    // search
    size_t cmp;
    *ticks_search = curr_ticks();
    for (size_t i = 0; i < ITERATION_COUNT; i++)
    {
        for (size_t i = 0; i < elem_count; i++)
        {
            hash_table_is_elem_found(&perfect_table, a[i], &cmp);
        }
    }
    *ticks_search = (curr_ticks() - *ticks_search) / ITERATION_COUNT;

    // avg_cmp
    double cmp_sum = 0;
    for (size_t i = 0; i < elem_count; i++)
    {
        hash_table_is_elem_found(&perfect_table, a[i], &cmp);
        cmp_sum += (double) cmp;
    }
    *avg_cmp = cmp_sum / (double) elem_count;

    //memory
    *memory = perfect_table.len * sizeof(hash_table_item_t) + sizeof(perfect_table);

    hash_table_free(&perfect_table);
    free(a);

    return EXIT_SUCCESS;
}

int statistics_show()
{
    printf("\n" MESS_MENU_DATA_TYPE MESS_MENU_CHOICE);
    int file_type;
    if (1 != scanf("%d", &file_type))
    {
        printf(MESS_INCORRECT_INPUT);
        return EXIT_FAILURE;
    }

    printf(MESS_INPUT_NUM_COUNT_RANGE);
    size_t min_elem_count, max_elem_count, elems_step;
    if (3 != scanf("%zu %zu %zu", &min_elem_count, &max_elem_count, &elems_step))
    {
        printf(MESS_INCORRECT_INPUT);
        return EXIT_FAILURE;
    }

    printf(MESS_INPUT_MAX_CMP);
    double max_cmp;
    if (1 != scanf("%lf", &max_cmp))
    {
        printf(MESS_INCORRECT_INPUT);
        return EXIT_FAILURE;
    }

    printf("\n");
    printf("|  Тип данных  | Кол-во эл. | Добавление | Поиск       | Число сравнений | Память  |\n");
    printf("|--------------|------------|------------|-------------|-----------------|---------|\n");

    for (size_t elem_count = min_elem_count; elem_count <= max_elem_count; elem_count += elems_step)
    {
        int rc = gen_file(FILE_NAME, elem_count, file_type);
        if (rc)
        {
            printf("Невозможно создать файла\n");
            return rc;
        }

        size_t memory;
        size_t ticks_add, ticks_search;
        double avg_cmp;

        // binary tree
        rc = tree_stat(FILE_NAME, &memory, elem_count, &ticks_add, &ticks_search, &avg_cmp);
        if (rc)
        {
            printf(MESS_ERROR);
            return rc;
        }
        printf("| %s | %10zu | %10zu | %11zu | %15.2lf | %7zu |\n",
               "ДДП         ", elem_count, ticks_add, ticks_search, avg_cmp, memory);

        //balance tree
        rc = btree_stat(FILE_NAME, &memory, elem_count, &ticks_add, &ticks_search, &avg_cmp);
        if (rc)
        {
            printf(MESS_ERROR);
            return rc;
        }
        printf("| %s | %10zu | %10zu | %11zu | %15.2lf | %7zu |\n",
               "АВЛ         ", elem_count, ticks_add, ticks_search, avg_cmp, memory);

        // hash table
        rc = hash_table_stat(FILE_NAME, max_cmp, &memory, elem_count, &ticks_add, &ticks_search, &avg_cmp);
        if (rc)
        {
            printf(MESS_ERROR);
            return rc;
        }
        printf("| %s | %10zu | %10zu | %11zu | %15.2lf | %7zu |\n",
               "Хеш таблица ", elem_count, ticks_add, ticks_search, avg_cmp, memory);

        // file
        rc = file_stat(FILE_NAME, &memory, elem_count, &ticks_add, &ticks_search, &avg_cmp);
        if (rc)
        {
            printf(MESS_ERROR);
            return rc;
        }
        printf("| %s | %10zu | %10zu | %11zu | %15.2lf | %7zu |\n",
               "Файл        ", elem_count, ticks_add, ticks_search, avg_cmp, memory);
    }

    printf("\nВремя изменяется в тактах, память в байтах\n");

    return EXIT_SUCCESS;
}
