#include "../inc/first_alloc.h"

int first_allocation(stack_vector_t **stack_vector,
list_item_t **stack_list_head,  vector_t **adress_vector)
{
    *stack_vector = stack_vector_allocate(MAX_WORD_COUNT, MAX_WORD_LEN + 1);
    *stack_list_head = NULL;

    *adress_vector = vector_allocate(MAX_WORD_COUNT, sizeof(list_item_t *));

    if (NULL == stack_vector || NULL == adress_vector)
    {
        LOG_ERROR("Init failed: stack_vector = %p; adress_vector = %p",
        (void *) *stack_vector, (void *) *adress_vector);

        stack_vector_free(*stack_vector);
        vector_free(*adress_vector);

        return ALLOCATION_FAILED;
    }

    return OKAY;
}

void end_free(stack_vector_t **stack_vector,
list_item_t **stack_list_head, vector_t **adress_vector)
{
    vector_free(*adress_vector);
    stack_vector_free(*stack_vector);

    char buffer[MAX_WORD_LEN + 1];
    while (NULL != *stack_list_head)
        list_pop(stack_list_head, buffer);

    *stack_vector = NULL;
    *stack_list_head = NULL;
    *adress_vector = NULL;
}
