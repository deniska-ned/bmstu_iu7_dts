#include "../inc/stack_vector.h"

struct stack_vector
{
    char *left_border;
    void *right_border;
    size_t length;
    char *cur_ptr;

    size_t el_size;
};

stack_vector_t *stack_vector_allocate(const size_t length,
const size_t el_size)
{
    LOG_INFO(">> length = %zu; el_size = %zu", length, el_size);
    assert(0 != el_size);

    stack_vector_t *stack_vector = ((stack_vector_t *)
    malloc(sizeof(struct stack_vector)));
    
    if (NULL == stack_vector)
    {
        LOG_ERROR("<< Unable to allocate memory for stack_vector_t [%zu B]",
        sizeof(stack_vector_t));

        return NULL;
    }

    void *data;

    if (0 == length)
    {
        data = NULL;
        LOG_INFO("%s", "stack_vector.data = NULL because length == 0");
    }
    else
    {
        data = malloc(length * el_size);

        if (NULL == data)
        {
            LOG_ERROR("Unable to allocate memory for data [%zu B]",
            length * el_size);

            free(stack_vector);

            return NULL;
        }
    }

    stack_vector->left_border = data;
    stack_vector->right_border = (char *) data + el_size * length;
    stack_vector->length = length;
    stack_vector->el_size = el_size;
    stack_vector->cur_ptr = (void *) ((char *) data - el_size);

    return stack_vector;
}

void stack_vector_free(stack_vector_t *stack_vector)
{
    if (NULL == stack_vector)
    {
        LOG_WARNING("%s", "NULL == stack_vector");
        return;
    }

    free(stack_vector->left_border);

    free((void *) stack_vector);

    stack_vector = NULL;
}

void stack_vector_push(stack_vector_t *stack_vector, char *str)
{
    stack_vector->cur_ptr += stack_vector->el_size;

    strncpy(stack_vector->cur_ptr, str, MAX_WORD_LEN);
}

char *stack_vector_pop(stack_vector_t *stack_vector, char *str)
{
    if (stack_vector->cur_ptr < stack_vector->left_border)
    {
        LOG_WARNING("%s", "All item removed");
        return NULL;
    }

    strncpy(str, stack_vector->cur_ptr, MAX_WORD_LEN);

    stack_vector->cur_ptr -= stack_vector->el_size;

    return str;
}

size_t stack_vector_get_size(stack_vector_t *stack_vector)
{
    size_t struct_size = sizeof(stack_vector_t);

    size_t data_size = stack_vector->length * stack_vector->el_size;

    size_t both = struct_size + data_size;
    LOG_INFO("Vector size: %zu B", both);

    return both;
}

char *stack_vector_get_cur_ptr(stack_vector_t *stack_vector)
{
    return stack_vector->cur_ptr;
}

char *stack_vector_get_right_border(stack_vector_t *stack_vector)
{
    return stack_vector->right_border;
}

char *stack_vector_get_left_border(stack_vector_t *stack_vector)
{
    return stack_vector->left_border;
}
