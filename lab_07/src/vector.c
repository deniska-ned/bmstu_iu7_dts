#include "../inc/vector.h"

vector_t *vector_allocate(const size_t length, const size_t el_size)
{
    LOG_INFO(">> length = %zu; el_size = %zu", length, el_size);
    assert(0 != el_size);

    vector_t *vector = (vector_t *) malloc(sizeof(vector_t));
    
    if (NULL == vector)
    {
        LOG_ERROR("<< Unable to allocate memory for vector_t [%zu B]",
        sizeof(vector_t));

        return NULL;
    }

    void *data;

    if (0 == length)
    {
        data = NULL;
        LOG_INFO("%s", "vector.data = NULL because length == 0");
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

    vector->elements = data;
    vector->length = length;
    vector->el_size = el_size;

    return vector;
}

void vector_free(vector_t *vector)
{
    if (NULL == vector)
    {
        LOG_WARNING("%s", "NULL == vector");
        return;
    }

    free(vector->elements);

    free((void *) vector);

    vector = NULL;
}

void *vector_get_ptr_to(const vector_t *vector, const size_t index)
{
    assert(index < vector->length);

    return (void *) ((char *) vector->elements + index * vector->el_size);
}

int vector_get_int_at(const vector_t *vector, const size_t index)
{
    assert(sizeof(int) == vector->el_size);

    return *((int *) vector_get_ptr_to(vector, index));
}

size_t vector_get_size_t_at(const vector_t *vector, const size_t index)
{
    assert(sizeof(size_t) == vector->el_size);

    return *((size_t *) vector_get_ptr_to(vector, index));
}

void vector_set_int_at(const vector_t *vector, const size_t index,
const int value)
{
    assert(sizeof(int) == vector->el_size);

    *((int *) vector_get_ptr_to(vector, index)) = value;
}

void vector_set_size_t_at(const vector_t *vector, const size_t index,
const size_t value)
{
    assert(sizeof(size_t) == vector->el_size);

    *((size_t *) vector_get_ptr_to(vector, index)) = value;
}

size_t vector_get_length(vector_t *vector)
{
    return vector->length;
}

size_t vector_get_size(vector_t *vector)
{
    size_t struct_size = sizeof(vector_t);

    size_t data_size = vector->length * vector->el_size;

    size_t both = struct_size + data_size;
    LOG_INFO("Vector size: %zu B", both);

    return both;
}

vector_t *vector_copy(vector_t *vector)
{
    vector_t *new_vector = vector_allocate(vector->length, vector->el_size);
    if (NULL != new_vector)
    {
        size_t byte_count = vector->el_size * vector->length;
        memcpy(new_vector->elements, vector->elements, byte_count);
    }

    return new_vector;
}
