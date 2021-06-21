#ifndef __SORT_H__

#define __SORT_H__

#include <stdio.h>
#include <string.h>

#include "macrologger.h"

#include "table_types.h"

#define SWAP(a, b, size)            \
{                                   \
    size_t __size = (size);         \
    char *__a = (a), *__b = (b);    \
    do                              \
        {                           \
            char __tmp = *__a;      \
            *__a++ = *__b;          \
            *__b++ = __tmp;         \
        } while (--__size > 0);     \
}

/**
 * Compare two country table row func for sort func
 *
 * @return A negative integer value if the first argument is less than the
 * second, a positive integer value if the first argument is greater than the
 * second and zero if the arguments are equivalent
 */
int comp_countries(const void *ptr_country_1, const void *ptr_country_2);

/**
 * Compare two keys func for sort func
 *
 * @return A negative integer value if the first argument is less than the
 * second, a positive integer value if the first argument is greater than the
 * second and zero if the arguments are equivalent
 */
int comp_keys(const void *ptr_key_1, const void *ptr_key_2);

/**
 * Selection sort
 */
void selection_sort(void *ptr, size_t count, size_t size,
int (*comp)(const void *, const void *));

#endif // __SORT_H__
