#ifndef __VECTOR_METHODS__

#define __VECTOR_METHODS__

#include "vector.h"
#include "macrologger.h"

#define OKAY                            0
#define REALLOC_FAILED                  1

int vector_realloc(vector_t *vector, size_t new_length);

#endif // __VECTOR_METHODS__
