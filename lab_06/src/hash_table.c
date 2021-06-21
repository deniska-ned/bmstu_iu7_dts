#include <stdbool.h>
#include "../inc/hash_table.h"

int hash_table_create(hash_table_t *table, size_t table_len, hash_func_t
hash_func)
{
    table->data = calloc(table_len, sizeof(hash_table_item_t));
    if (!table->data)
        return ALLOCATON_ERROR;
    
    table->len = table_len;
    table->hash_func = hash_func;

    return EXIT_SUCCESS;
}

void hash_table_free(hash_table_t *table)
{
    free(table->data);
}

int hash_table_add(hash_table_t *table, elem_t elem)
{
    size_t elem_index = table->hash_func(elem, table->len);
    size_t looked = 0;

    while (USE == table->data[elem_index].item_status && looked < table->len)
    {
        if (elem == table->data[elem_index].elem)
        {
            LOG_WARNING("%s", "This value exist in table");
            return EXIT_SUCCESS;
        }

        ++looked;
        elem_index = (elem_index + 1) % table->len;
    }

    if (looked == table->len)
        return TABEL_OVERFLOW;
    
    table->data[elem_index].elem = elem;
    table->data[elem_index].item_status = USE;

    return EXIT_SUCCESS;
}

int hash_table_add_from_file(char *file_name, hash_table_t *table)
{
    FILE *f = fopen(file_name, "r");
    if (!f)
        return OPEN_ERROR;
    
    elem_t elem;
    while (!scan_elem_from_source(f, &elem))
    {
        int rc = hash_table_add(table, elem);
        if (rc)
        {
            fclose(f);
            return rc;
        }
    }

    fclose(f);
    
    return EXIT_SUCCESS;
}

void hash_table_del(hash_table_t *table, elem_t elem)
{
    size_t elem_index = table->hash_func(elem, table->len);
    size_t looked = 0;
    while (EMPTY != table->data[elem_index].item_status && looked < table->len)
    {
        if (USE == table->data[elem_index].item_status &&
        elem == table->data[elem_index].elem)
        {
            table->data[elem_index].item_status = DELETED;
            break;
        }
        ++looked;
        elem_index = (elem_index + 1) % table->len;
    }
}

double hash_table_avg_comp(hash_table_t *table)
{
    size_t cmp_count = 0, elems = 0;
    for (size_t i = 0; i < table->len; ++i)
        if (table->data[i].item_status == USE)
        {
            size_t cur_cmp;
            hash_table_is_elem_found(table, table->data[i].elem, &cur_cmp);
            cmp_count += cur_cmp;
            ++elems;
        }
    
    return elems > 0 ? (double) cmp_count / (double) elems : 0.0;
}

int hash_table_restruct(hash_table_t *table, size_t new_len, hash_func_t hash_func)
{
    hash_table_t temp;
    int rc = hash_table_create(&temp, new_len, hash_func);
    if (rc)
        return rc;
    
    for (size_t i = 0; i < table->len; i++)
        if (USE == table->data[i].item_status)
            hash_table_add(&temp, table->data[i].elem);

    hash_table_free(table);

    *table = temp;

    return EXIT_SUCCESS;
}

bool hash_table_is_elem_found(hash_table_t *table, elem_t elem, size_t *comparisons)
{
    size_t elem_index = table->hash_func(elem, table->len);

    *comparisons = 0;

    size_t looked = 0;
    while (EMPTY != table->data[elem_index].item_status &&
    looked < table->len)
    {
        if (USE == table->data[elem_index].item_status)
        {
            ++*comparisons;
            if (elem == table->data[elem_index].elem)
            {
                // LOG_INFO("FOUND: Comparison of %ld = %zu", elem, *comparisons);
                return true;
            }
        }

        ++looked;
        elem_index = (elem_index + 1) % table->len;
    }

    *comparisons = 0;
    LOG_DEBUG("NOT_FOUND: Comparison of %ld = %zu", elem, *comparisons);
    return false;
}

void hash_table_print(FILE *dst, hash_table_t table)
{
    fprintf(dst, "| Индекс | Значение | Состояние |\n");
    fprintf(dst, "|--------|----------|-----------|\n");
    for (size_t i = 0; i < table.len; i++)
        fprintf(dst, "| %6zu | %8ld | %9s |\n", i, table.data[i].elem,
                HASH_TABLE_ITEM_TYPE_TO_STR(table.data[i].item_status));
}
