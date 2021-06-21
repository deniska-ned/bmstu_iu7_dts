#include "../inc/menu.h"

#define NUM_FOUND_MASK "Число %ld найдено\nЧисло сравнений: %zu\n"

int work_with_binary_tree()
{
    elem_t elem;
    int rc;
    int choice = 10;
    tc_node_t *root = NULL;

    while (choice)
    {
        printf(MESS_MENU_HEADER_TREE MESS_MENU_TREE MESS_MENU_CHOICE);

        rc = scanf("%d", &choice);
        goto_newline(stdin);
        if (1 != rc)
        {
            printf(MESS_INCORRECT_INPUT);
            continue;
        }

        switch (choice)
        {
            case MENU_SECONDARY_EXIT:
                printf(MESS_EXIT);
                break;
            case MENU_SECONDARY_ADD_FROM_FILE:
                {
                    char *filename = NULL;
                    size_t buffer_len = 0;
                    printf(MESS_INPUT_FILENAME);
                    ssize_t readed = getline(&filename, &buffer_len, stdin);

                    if (EOF == readed)
                    {
                        printf(MESS_INCORRECT_INPUT);
                        continue;
                    }

                    if ('\n' == filename[readed - 1])
                        filename[readed-- - 1] = '\0';

                    rc = tree_add_from_file(filename, &root);

                    if (EXIT_SUCCESS == rc)
                        printf(MESS_NUM_FROM_FILE_READED);
                    else
                        printf(MESS_FILE_READING_ERROR);

                    free(filename);
                }
                break;
            case MENU_SECONDARY_ADD:
                printf(MESS_INPUT_NUM);
                rc = scan_elem_from_source(stdin, &elem);
                if (rc)
                {
                    printf(MESS_INCORRECT_INPUT);
                    continue;
                }
                rc = tree_add_elem(&root, elem);
                assert(!rc);
                break;
            case MENU_SECONDARY_FIND:
                printf(MESS_INPUT_NUM);
                if (scan_elem_from_source(stdin, &elem))
                {
                    printf(MESS_INCORRECT_INPUT);
                    continue;
                }
                size_t comparisons = 0;
                if (tree_is_elem_found(root, elem, &comparisons))
                    printf(NUM_FOUND_MASK, elem, comparisons);
                else
                    printf(MESS_NUM_NOT_FOUND);
                break;
            case MENU_SECONDARY_DEL:
                printf(MESS_INPUT_NUM);
                rc = scan_elem_from_source(stdin, &elem);
                if (rc)
                {
                    printf(MESS_INCORRECT_INPUT);
                    continue;
                }
                tree_del_elem(&root, elem);
                break;
            case MENU_SECONDARY_PRINT:
                system("mkdir -p dot_files");
                tree_export_to_dot(root, GV_PATH, "tree");
                system("dot -Tpng dot_files/tree.gv -o dot_files/tree.png && kde-open5 dot_files/tree.png");
                break;
            default:
                printf(MESS_INCORRECT_INPUT);
        }
    }

    tree_free(root);

    return EXIT_SUCCESS;
}

int work_with_balance_tree()
{
    int rc;
    elem_t elem;
    size_t comparisons;

    int choice = 10;
    tb_node_t *root = NULL;

    while (choice)
    {
        printf(MESS_MENU_HEADER_BTREE MESS_MENU_TREE MESS_MENU_CHOICE);

        rc = scanf("%d", &choice);
        goto_newline(stdin);
        if (1 != rc)
        {
            printf(MESS_INCORRECT_INPUT);
            continue;
        }

        switch (choice)
        {
            case MENU_SECONDARY_EXIT:
                printf(MESS_EXIT);
                break;
            case MENU_SECONDARY_ADD_FROM_FILE:
                {
                    char *filename = NULL;
                    size_t buffer_len = 0;
                    printf(MESS_INPUT_FILENAME);
                    ssize_t readed = getline(&filename, &buffer_len, stdin);

                    if (EOF == readed)
                    {
                        printf(MESS_INCORRECT_INPUT);
                        continue;
                    }

                    if ('\n' == filename[readed - 1])
                        filename[readed-- - 1] = '\0';

                    rc = btree_add_from_file(filename, &root);

                    if (EXIT_SUCCESS == rc)
                        printf(MESS_NUM_FROM_FILE_READED);
                    else
                        printf(MESS_FILE_READING_ERROR);


                    free(filename);
                }
                break;
            case MENU_SECONDARY_ADD:
                printf(MESS_INPUT_NUM);
                rc = scan_elem_from_source(stdin, &elem);
                if (rc)
                {
                    printf(MESS_INCORRECT_INPUT);
                    continue;
                }
                rc = btree_add(&root, elem);
                assert(!rc);
                break;
            case MENU_SECONDARY_FIND:
                printf(MESS_INPUT_NUM);
                if (scan_elem_from_source(stdin, &elem))
                {
                    printf(MESS_INCORRECT_INPUT);
                    continue;
                }
                comparisons = 0;
                if (btree_is_elem_found(root, elem, &comparisons))
                    printf(NUM_FOUND_MASK, elem, comparisons);
                else
                    printf(MESS_NUM_NOT_FOUND);
                break;
            case MENU_SECONDARY_DEL:
                printf(MESS_INPUT_NUM);
                rc = scan_elem_from_source(stdin, &elem);
                if (rc)
                {
                    printf(MESS_INCORRECT_INPUT);
                    continue;
                }
                btree_del(&root, elem);
                break;
            case MENU_SECONDARY_PRINT:
                system("mkdir -p dot_files");
                btree_export_to_dot(root, GV_PATH, "tree");
                system("dot -Tpng dot_files/tree.gv -o dot_files/tree.png && kde-open5 dot_files/tree.png");
                break;
            default:
                printf(MESS_INCORRECT_INPUT);
        }
    }
#if false
    fread_btree();
#endif

    btree_free(root);

    return EXIT_SUCCESS;
}

int work_with_hash_table()
{
    int rc;
    elem_t elem;
    size_t comparisons = 0;

    size_t table_len;
    printf("\n" MESS_INPUT_TABLE_LEN);
    if (1 != scanf("%zu", &table_len))
        return EXIT_FAILURE;
    if (!is_num_prime(table_len))
    {
        LOG_DEBUG("%zu is not prime", table_len);
        table_len = get_next_prime_num(table_len);
        LOG_DEBUG("New table_len = %zu", table_len);
        printf("Длина таблицы должна быть простым числом. Изменена на %zu\n",
        table_len);
    }

    LOG_DEBUG("table_len = %zu", table_len);

    double max_avg_cmp;
    printf(MESS_INPUT_MAX_CMP);
    if (1 != scanf("%lf", &max_avg_cmp))
        return EXIT_FAILURE;

    hash_table_t table;
    rc = hash_table_create(&table, table_len, hash_func_mod);
    if (rc)
    {
        printf(MESS_UNABLE_CREATE_TABLE);
        return rc;
    }
    int choice = 1;

    while (choice)
    {
        printf(MESS_MENU_HEADER_HASH_TABLE MESS_MENU_HASH MESS_MENU_CHOICE);

        rc = scanf("%d", &choice);
        goto_newline(stdin);
        if (1 != rc)
        {
            printf(MESS_INCORRECT_INPUT);
            continue;
        }

        switch (choice)
        {
            case MENU_SECONDARY_ADD_FROM_FILE:
                {
                    char *filename = NULL;
                    size_t buffer_len = 0;
                    printf(MESS_INPUT_FILENAME);
                    ssize_t readed = getline(&filename, &buffer_len, stdin);

                    if (EOF == readed)
                    {
                        printf(MESS_INCORRECT_INPUT);
                        continue;
                    }

                    if ('\n' == filename[readed - 1])
                        filename[readed-- - 1] = '\0';

                    rc = hash_table_add_from_file(filename, &table);
                    if (EXIT_SUCCESS == rc)
                        printf(MESS_NUM_FROM_FILE_READED);
                    else
                        printf(MESS_FILE_READING_ERROR);

                    free(filename);


                    if (hash_table_avg_comp(&table) > max_avg_cmp)
                    {
                        hash_func_t hash_func = hash_func_mod == table.hash_func ?
                                                hash_func_mlt : hash_func_mod;

                        rc = hash_table_restruct(&table, table.len, hash_func);

                        if (rc) {
                            printf(MESS_ALLOCATION_FAILED);
                            break;
                        }

#if false
                        if (hash_table_avg_comp(&table) > max_avg_cmp)
                        {
                            size_t new_len = get_next_prime_num(table.len);
                            rc = hash_table_restruct(&table, new_len, table.hash_func);

                            if (rc) {
                                printf(MESS_ALLOCATION_FAILED);
                                break;
                            }
                        }
#endif

                        LOG_TRACE("%s", "here");
                    }
                }
                break;
            case MENU_SECONDARY_ADD:
                printf(MESS_INPUT_NUM);
                rc = scan_elem_from_source(stdin, &elem);
                if (rc)
                {
                    printf(MESS_INCORRECT_INPUT);
                    continue;
                }
                rc = hash_table_add(&table, elem);
                if (rc)
                {
                    printf(MESS_TABLE_OVERFLOW);
                    break;
                }
                if (hash_table_avg_comp(&table) > max_avg_cmp)
                {
                    hash_func_t hash_func = hash_func_mod == table.hash_func ?
                    hash_func_mlt : hash_func_mod;

                    rc = hash_table_restruct(&table, table.len, hash_func);

                    if (rc) {
                        printf(MESS_ALLOCATION_FAILED);
                        break;
                    }
#if false
                    if (hash_table_avg_comp(&table) > max_avg_cmp)
                    {
                        size_t new_len = get_next_prime_num(table.len);
                        rc = hash_table_restruct(&table, new_len, table.hash_func);

                        if (rc) {
                            printf(MESS_ALLOCATION_FAILED);
                            break;
                        }
                    }
#endif

                    LOG_TRACE("%s", "here");
                }
                break;
            case MENU_SECONDARY_FIND:
                printf(MESS_INPUT_NUM);
                if (scan_elem_from_source(stdin, &elem))
                {
                    printf(MESS_INCORRECT_INPUT);
                    continue;
                }
                comparisons = 0;
                if (hash_table_is_elem_found(&table, elem, &comparisons))
                    printf(NUM_FOUND_MASK, elem, comparisons);
                else
                    printf(MESS_NUM_NOT_FOUND);
                break;
            case MENU_SECONDARY_DEL:
                printf(MESS_INPUT_NUM);
                rc = scan_elem_from_source(stdin, &elem);
                if (rc)
                {
                    printf(MESS_INCORRECT_INPUT);
                    continue;
                }
                hash_table_del(&table, elem);
                break;
            case MENU_SECONDARY_PRINT:
                hash_table_print(stdout, table);
                break;
            case MENU_SECONDATY_AVG_CMP:
                printf("Среднее число сравнений: %lf\n", hash_table_avg_comp
                (&table));
                break;
            case MENU_SECONDARY_EXIT:
                printf(MESS_EXIT);
                break;
            default:
                printf(MESS_INCORRECT_INPUT);
        }
    }

    hash_table_free(&table);

    return EXIT_SUCCESS;
}

int work_with_file()
{
    int rc;
    elem_t elem;
    int choice = 10;
    size_t comparisons;

    while (choice)
    {
        printf(MESS_MENU_HEADER_FILE MESS_MENU_FILE MESS_MENU_CHOICE);

        rc = scanf("%d", &choice);
        goto_newline(stdin);
        if (1 != rc)
        {
            printf(MESS_INCORRECT_INPUT);
            continue;
        }

        switch (choice)
        {
            case MENU_SECONDARY_EXIT:
                printf(MESS_EXIT);
                break;
            case MENU_SECONDARY_ADD_FROM_FILE:
                {
                    char *filename = NULL;
                    size_t buffer_len = 0;
                    printf(MESS_INPUT_FILENAME);
                    ssize_t readed = getline(&filename, &buffer_len, stdin);

                    if (EOF == readed)
                    {
                        printf(MESS_INCORRECT_INPUT);
                        continue;
                    }

                    if ('\n' == filename[readed - 1])
                        filename[readed-- - 1] = '\0';

                    FILE *f = fopen(WORK_WITH_FILE_FILENAME, "a");
                    if (NULL == f)
                    {
                        printf("%s %s", WORK_WITH_FILE_FILENAME, MESS_FILE_CANNOT_BE_OPENED);
                        continue;
                    }
                    file_print(f, filename);

                    fclose(f);
                }
                break;
            case MENU_SECONDARY_ADD:
                printf(MESS_INPUT_NUM);
                rc = scan_elem_from_source(stdin, &elem);
                if (rc)
                {
                    printf(MESS_INCORRECT_INPUT);
                    continue;
                }
                rc = file_add(WORK_WITH_FILE_FILENAME, elem);
                assert(!rc);
                break;
            case MENU_SECONDARY_FIND:
                printf(MESS_INPUT_NUM);
                rc = scan_elem_from_source(stdin, &elem);
                if (rc)
                {
                    printf(MESS_INCORRECT_INPUT);
                    continue;
                }
                comparisons = 0;
                int found;
                rc = file_search(WORK_WITH_FILE_FILENAME, elem, &comparisons, &found);
                assert(!rc);
                if (found)
                    printf(NUM_FOUND_MASK, elem, comparisons);
                else
                    printf(MESS_NUM_NOT_FOUND);
                break;
            case MENU_SECONDARY_DEL:
                printf(MESS_INPUT_NUM);
                int rc = scan_elem_from_source(stdin, &elem);
                if (rc)
                {
                    printf(MESS_INCORRECT_INPUT);
                    continue;
                }
                file_del(WORK_WITH_FILE_FILENAME, elem);
                break;
            case MENU_SECONDARY_PRINT:
                rc = file_print(stdout, WORK_WITH_FILE_FILENAME);
                assert(!rc);
                break;
            default:
                printf(MESS_INCORRECT_INPUT);
        }
    }

    return EXIT_SUCCESS;
}

int menu_start(void)
{
    int rc;
    int choice = 10;
    
    while (choice)
    {
        printf(MESS_MENU_MAIN MESS_MENU_CHOICE);

        rc = scanf("%d", &choice);
        goto_newline(stdin);
        if (1 != rc)
        {
            printf(MESS_INCORRECT_INPUT);
            continue;
        }

        switch (choice)
        {
            case MENU_MAIN_TREE:
                work_with_binary_tree();
                break;
            case MENU_MAIN_BTREE:
                work_with_balance_tree();
                break;
            case MENU_MAIN_HASH:
                work_with_hash_table();
                break;
            case MENU_MAIN_FILE:
                work_with_file();
                break;
            case MENU_MAIN_STAT:
                statistics_show();
                break;
            case MENU_MAIN_EXIT:
                break;
            default:
                printf(MESS_INCORRECT_INPUT);
        }
    }

    return EXIT_SUCCESS;
}
