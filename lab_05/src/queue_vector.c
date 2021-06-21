#include "../inc/queue_vector.h"

struct queue_vector_t
{
    request_t *right_border;
    request_t *left_border;

    request_t *pin;
    request_t *pout;

    size_t length;
    size_t used_len;
    size_t el_size;

    bool is_full;
};

queue_vector_t *queue_vector_allocate(const size_t length)
{
    size_t el_size = sizeof(request_t);
    LOG_INFO(">> length = %zu; el_size = %zu", length, el_size);
    assert(0 != el_size);

    queue_vector_t *vector = (queue_vector_t *) malloc(sizeof(struct queue_vector_t));

    if (NULL == vector)
    {
        LOG_ERROR("<< Unable to allocate memory for queue_vector_t [%zu B]",
        sizeof(queue_vector_t));

        return NULL;
    }

    request_t *data;

    if (0 == length)
    {
        data = NULL;
        LOG_INFO("%s", "queue_vector.data = NULL because length == 0");
    }
    else
    {
        data = malloc(length * el_size);

        if (NULL == data)
        {
            LOG_ERROR("Unable to allocate memory for data [%zu B]",
            length * el_size);

            free(vector);

            return NULL;
        }
    }

    vector->left_border = data;
    vector->right_border = data + length;

    vector->pin = data;
    vector->pout = data;

    vector->length = length;
    vector->used_len = 0;
    vector->el_size = el_size;

    vector->is_full = false;

    return vector;
}

void queue_vector_free(queue_vector_t *vector)
{
    if (NULL == vector)
    {
        LOG_WARNING("%s", "NULL == queue_vector");
        return;
    }

    free(vector->left_border);

    free((void *) vector);

    vector = NULL;
}

int queue_vector_append(queue_vector_t *vector, request_t *data)
{
    LOG_DEBUG(">> vector->pin = %p; vector->pout = %p",
    (void *) vector->pin, (void *) vector->pout);
    LOG_TRACE("Value = %d", data->value);

    if (vector->is_full)
    {
        LOG_ERROR("%s", "Impossible to append new item. Vector is full");
        return VECTOR_IS_FULL;
    }

    *(vector->pin) = *data;
    LOG_DEBUG("vector->pin->value = %d", vector->pin->value);

    if (vector->pin + 1 >= vector->right_border)
    {
        vector->pin = vector->left_border;
    }
    else
    {
        ++vector->pin;
    }

    if (vector->pin == vector->pout)
    {
        vector->is_full = true;
    }

    LOG_DEBUG("<< vector->pin = %p; vector->pout = %p",
    (void *) vector->pin, (void *) vector->pout);

    ++vector->used_len;

    return OKAY;
}

int queue_vector_pop(queue_vector_t *vector, request_t *data)
{
    LOG_DEBUG(">> vector->pin = %p; vector->pout = %p",
    (void *) vector->pin, (void *) vector->pout);

    if (vector->is_full && vector->pin == vector->pout)
    {
        vector->is_full = false;
    }
    else if (vector->pin == vector->pout)
    {
        LOG_ERROR("%s", "Vector is empty");
        return VECTOR_IS_EMPTY;
    }

    *data = *(vector->pout);

    if (vector->pout + 1 >= vector->right_border)
    {
        vector->pout = vector->left_border;
    }
    else
    {
        ++vector->pout;
    }

    LOG_DEBUG("<< vector->pin = %p; vector->pout = %p",
    (void *) vector->pin, (void *) vector->pout);

    --vector->used_len;

    return OKAY;
}

int queue_vector_get_len(queue_vector_t *vector)
{
    return (int) vector->used_len;
}

bool is_queue_vector_empty(queue_vector_t *vector)
{
    return 0 == queue_vector_get_len(vector);
}

void print_queue_vector(FILE *source, queue_vector_t *vector)
{
    int len = queue_vector_get_len(vector);

    if (0 == len)
    {
        // LOG_WARNING("%s", "Vector is empty");
        fprintf(source, "Vector is empty\n");

        return;
    }

    request_t *request = vector->pout;

    fprintf(source, "Vector: ");

    for (int i = 0; i < len; ++i)
    {
        printf("%d (%d)->", request->value, request->processing_count);

        if (request + 1 >= vector->right_border)
        {
            request = vector->left_border;
        }
        else
        {
            ++request;
        }
    }
    printf("End\n");
}

size_t queue_vector_get_size(queue_vector_t *vector)
{
    return vector->el_size * vector->length;
}
