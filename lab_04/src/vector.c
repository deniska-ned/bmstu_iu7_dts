#include "../inc/vector.h"

struct vector_t
{
    void *elements;
    size_t availible_length;
    size_t used_length;

    size_t el_size;
};

vector_t *vector_allocate(const size_t length, const size_t el_size)
{
    LOG_INFO(">> length = %zu; el_size = %zu", length, el_size);
    assert(0 != el_size);

    vector_t *vector = (vector_t *) malloc(sizeof(struct vector_t));
    
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
    vector->availible_length = length;
    vector->el_size = el_size;
    vector->used_length = 0;

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
    LOG_DEBUG(">> Index: %zu", index);
    assert(index < vector->availible_length);

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
    return vector->availible_length;
}

size_t vector_get_used_length(vector_t *vector)
{
    return vector->used_length;
}

size_t vector_get_size(vector_t *vector)
{
    size_t struct_size = sizeof(vector_t);

    size_t data_size = vector->used_length * vector->el_size;

    size_t both = struct_size + data_size;
    LOG_INFO("Vector size: %zu B", both);

    return both;
}

void vector_add_ptr(vector_t *vector, void *new_ptr)
{
    LOG_DEBUG("used_length before: %zu", vector->used_length);
    vector->used_length++;
    void *item_ptr = vector_get_ptr_to(vector, vector->used_length - 1);
    *((void **) item_ptr) = new_ptr;
}

void *vector_get_ptr_to_ptr_to(vector_t *vector, size_t i)
{
    return *(void **) vector_get_ptr_to(vector, i);
}

void vector_del_ptr(vector_t *vector, void *ptr)
{
    size_t i = vector->used_length;
    LOG_INFO("Used len is %zu", i);

    if (0 == i)
        return;

    do
    {
        --i;

        void *value_ptr = vector_get_ptr_to(vector, i);
        if (*(void **) value_ptr == ptr && vector->used_length - 1 == i)
        {
            LOG_INFO("%s", "This value found is array at the last position");
            vector->used_length--;
            return;
        }
        if (*(void **) value_ptr == ptr)
        {
            LOG_INFO("This value found is array at index %zu", i);
            void *last_value_ptr = vector_get_ptr_to(vector, vector->used_length - 1);
            void *last_value = *(void **) last_value_ptr;
            *(void **) value_ptr = last_value;

            vector->used_length--;
            return;
        }

    }
    while (0 != i);
}
