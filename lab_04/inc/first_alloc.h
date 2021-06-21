#ifndef __FIRST_ALLOC_H__

#define __FIRST_ALLOC_H__

#include "list.h"
#include "vector.h"
#include "stack_vector.h"

#define OKAY                            0
#define ALLOCATION_FAILED               128
int first_allocation(stack_vector_t **stack_vector,
list_item_t **stack_list_head, vector_t **adress_vector);

void end_free(stack_vector_t **stack_vector,
list_item_t **stack_list_head, vector_t **adress_vector);

#endif // __FIRST_ALLOC_H__
