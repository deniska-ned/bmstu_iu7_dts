#ifndef __STACK_VECTOR_H__

#define __STACK_VECTOR_H__

#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "macrologger.h"
#include "word_info.h"

struct stack_vector;

typedef struct stack_vector stack_vector_t;

stack_vector_t *stack_vector_allocate(const size_t length,
const size_t el_size);

void stack_vector_free(stack_vector_t *stack_vector);

void stack_vector_push(stack_vector_t *stack_vector, char *str);

char *stack_vector_pop(stack_vector_t *stack_vector, char *str);

size_t stack_vector_get_size(stack_vector_t *stack_vector);

char *stack_vector_get_cur_ptr(stack_vector_t *stack_vector);

char *stack_vector_get_right_border(stack_vector_t *stack_vector);

char *stack_vector_get_left_border(stack_vector_t *stack_vector);

#endif // __STACK_VECTOR_H__
