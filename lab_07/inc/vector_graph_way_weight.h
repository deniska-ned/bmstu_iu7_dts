#ifndef __VECTOR_GRAPH_WAY_H__
#define __VECTOR_GRAPH_WAY_H__

#include "vector.h"

struct graph_way_weight
{
    unsigned name;
    int way_weight;
};

struct graph_way_weight vector_get_gww(const vector_t *vector,
const size_t index);

void vector_set_gww(const vector_t *vector, const size_t index,
const struct graph_way_weight value);

struct graph_way_weight vector_get_gww_by_name(const vector_t *vector,
const unsigned int name);

void vector_set_gww_by_name(const vector_t *vector, const unsigned int name,
const struct graph_way_weight value);

#endif // __VECTOR_GRAPH_WAY_H__
