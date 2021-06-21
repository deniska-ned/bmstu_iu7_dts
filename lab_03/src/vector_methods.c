#include "../inc/vector_methods.h"

int vector_realloc(vector_t *vector, size_t new_length)
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
        LOG_ERROR("%s", "vector realloc failed");
        return REALLOC_FAILED;
    }

    return OKAY;
}
