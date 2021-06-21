#ifndef __QUERE_VECTOR_H__

#define __QUERE_VECTOR_H__

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "macrologger.h"

#include "request.h"

struct queue_vector_t;

typedef struct queue_vector_t queue_vector_t;

/**
 * @brief Create dynamic array
 *
 * @return pointer to queue_vector if success;
 * NULL if unable to allocate memory;
 */
queue_vector_t *queue_vector_allocate(const size_t length);

/**
 * @brief Frees up memory of queue_vector and assign queue_vector to NULL
 */
void queue_vector_free(queue_vector_t *vector);

#define OKAY                            0
#define VECTOR_IS_FULL                  1
int queue_vector_append(queue_vector_t *vector, request_t *data);

#define OKAY                            0
#define VECTOR_IS_EMPTY                 1
int queue_vector_pop(queue_vector_t *vector, request_t *data);

int queue_vector_get_len(queue_vector_t *vector);

bool is_queue_vector_empty(queue_vector_t *vector);

void print_queue_vector(FILE *source, queue_vector_t *vector);

size_t queue_vector_get_size(queue_vector_t *vector);

#endif // __QUERE_VECTOR_H__
