#ifndef __VECTOR_H__

#define __VECTOR_H__

#include <stdlib.h>
#include <assert.h>

#include "macrologger.h"

typedef struct
{
    void **elements;
    size_t used_length;
    size_t length;

    size_t el_size;
} ptr_vector_t;

/**
 * @brief Create dynamic array
 *
 * @return pointer to vector if success;
 * NULL if unable to allocate memory;
 */
ptr_vector_t *ptr_vector_allocate(const size_t init_length);

/**
 * @brief Frees up memory of vector and assign vector to NULL
 */
void ptr_vector_free(ptr_vector_t *vector);

/**
 * @brief Return length of dynamic array
 *
 * @return Length of dynamic array
 */
size_t ptr_vector_get_length(ptr_vector_t *vector);

size_t ptr_vector_get_size(ptr_vector_t *vector);

#define OKAY                            0
#define REALLOC_FAILED                  1
int ptr_vector_realloc(ptr_vector_t *vector, size_t new_length);

int ptr_vector_append(ptr_vector_t *vector, void *new_ptr);

void ptr_vector_del(ptr_vector_t *vector, void *ptr);

void ptr_vector_print(FILE *f, ptr_vector_t *vector);

#endif // __VECTOR_H__
