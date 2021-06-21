#include "../inc/ptr_vector.h"

ptr_vector_t *ptr_vector_allocate(const size_t init_length)
{
    LOG_INFO(">> initial length = %zu", init_length);

    ptr_vector_t *vector = (ptr_vector_t *) malloc(sizeof(ptr_vector_t));
    
    if (NULL == vector)
    {
        LOG_ERROR("<< Unable to allocate memory for ptr_vector_t [%zu B]",
        sizeof(ptr_vector_t));

        return NULL;
    }

    void *data;

    if (0 == init_length)
    {
        data = NULL;
        LOG_INFO("%s", "vector.data = NULL because length == 0");
    }
    else
    {
        data = calloc(init_length, sizeof(void *));

        if (NULL == data)
        {
            LOG_ERROR("Unable to allocate memory for data [%zu B]",
            init_length * sizeof(void *));

            free(vector);

            return NULL;
        }
    }

    vector->elements = data;
    vector->length = init_length;
    vector->used_length = 0;
    vector->el_size = sizeof(void *);

    return vector;
}

void ptr_vector_free(ptr_vector_t *vector)
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

size_t ptr_vector_get_length(ptr_vector_t *vector)
{
    return vector->length;
}


size_t ptr_vector_get_size(ptr_vector_t *vector)
{
    size_t struct_size = sizeof(ptr_vector_t);

    size_t data_size = vector->length * vector->el_size;

    size_t both = struct_size + data_size;
    LOG_INFO("Vector size: %zu B", both);

    return both;
}

int ptr_vector_realloc(ptr_vector_t *vector, size_t new_length)
{
    vector->length = new_length;

    if (0 == new_length)
    {
        free(vector->elements);
        vector->elements = NULL;

        return OKAY;
    }

    vector->elements = realloc(vector->elements, new_length);

    if (NULL == vector->elements)
    {
        LOG_ERROR("%s", "vector reallocation failed");
        return REALLOC_FAILED;
    }

    return OKAY;
}

int ptr_vector_append(ptr_vector_t *vector, void *new_ptr)
{
    int rc;

    if (vector->used_length == vector->length)
    {
        rc = ptr_vector_realloc(vector, vector->length * 2);
        if (OKAY != rc)
        {
            LOG_ERROR("%s", "Reallocation failed");
            return rc;
        }
    }
    
    int i;
    for (i = 0; NULL != vector->elements[i]; ++i)
        ;

    vector->elements[i] = new_ptr;
    ++vector->used_length;

    return OKAY;
}

void ptr_vector_del(ptr_vector_t *vector, void *ptr)
{
    size_t i;
    for (i = 0; ptr != vector->elements[i] && i < vector->length; ++i)
        ;

    if (ptr == vector->elements[i])
    {
        vector->elements[i] = NULL;
        --vector->used_length;
    }
}

void ptr_vector_print(FILE *f, ptr_vector_t *vector)
{
    fprintf(f, "Массив указателей на элемента списка:\n");

    if (0 == vector->used_length)
    {
        LOG_INFO("%s", "Массив пуст");
        fprintf(f, "Массив пуст\n");
        return;
    }

    size_t count = 0;
    for (size_t i = 0;  i < vector->length; ++i)
        if (NULL != vector->elements[i])
        {
            fprintf(f, "%zu. %p; ", ++count, vector->elements[i]);
        }
    printf("\n");
}
