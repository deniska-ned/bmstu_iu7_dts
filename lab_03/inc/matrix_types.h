#ifndef __MATRIX_TYPES_H__

#define __MATRIX_TYPES_H__

#include <stdio.h>

#define MAX_PRINTABLE_ROW_COUNT         10
#define MAX_PRINTABLE_COL_COUNT         10

typedef struct
{
    size_t ticks;
    size_t matrix_size;
    size_t column_size;
    size_t product_size;
} matrix_stat_t;

#endif // __MATRIX_TYPES_H__
