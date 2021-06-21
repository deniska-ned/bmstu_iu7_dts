#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "hash_funcs.h"
#include "elem.h"
#include "file.h"
#include "error_codes.h"

typedef size_t (*hash_func_t) (elem_t, size_t);

typedef enum HASH_TABLE_ITEM_STATUS
{
    DELETED = -1,
    EMPTY   =  0,
    USE     =  1
} hash_item_status_t;

#define HASH_TABLE_ITEM_TYPE_TO_STR(VAL) \
DELETED == (VAL) ? "Удалено  " : \
EMPTY   == (VAL) ? "Пусто    " : \
USE     == (VAL) ? "Занято   " : "Unknown"

typedef struct
{
    elem_t elem;
    hash_item_status_t item_status;
} hash_table_item_t;

typedef struct
{
    hash_table_item_t *data;
    size_t len;
    hash_func_t hash_func;
} hash_table_t;

int hash_table_create(hash_table_t *table, size_t table_len,
hash_func_t hash_func);
void hash_table_free(hash_table_t *table);
int hash_table_add(hash_table_t *table, elem_t elem);
int hash_table_add_from_file(char *file_name, hash_table_t *table);
void hash_table_del(hash_table_t *table, elem_t elem);
double hash_table_avg_comp(hash_table_t *table);
int
hash_table_restruct(hash_table_t *table, size_t new_len, hash_func_t hash_func);

bool
hash_table_is_elem_found(hash_table_t *table, elem_t elem, size_t *comparisons);
void hash_table_print(FILE *dst, hash_table_t table);

#endif //HASH_TABLE_H
