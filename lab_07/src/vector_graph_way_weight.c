#include "../inc/vector_graph_way_weight.h"

struct graph_way_weight vector_get_gww(const vector_t *vector,
const size_t index)
{
    assert(sizeof(struct graph_way_weight) == vector->el_size);

    return *((struct graph_way_weight *) vector_get_ptr_to(vector, index));
}

struct graph_way_weight vector_get_gww_by_name(const vector_t *vector,
const unsigned int name)
{
    assert(sizeof(struct graph_way_weight) == vector->el_size);
    assert(name >= 1);

    size_t index = name - 1;
    return *((struct graph_way_weight *) vector_get_ptr_to(vector, index));
}

void vector_set_gww(const vector_t *vector, const size_t index,
                    const struct graph_way_weight value)
{
    assert(sizeof(struct graph_way_weight) == vector->el_size);

    *((struct graph_way_weight *) vector_get_ptr_to(vector, index)) = value;
}

void vector_set_gww_by_name(const vector_t *vector, const unsigned int name,
                            const struct graph_way_weight value)
{
    assert(sizeof(struct graph_way_weight) == vector->el_size);
    assert(name >= 1);

    *((struct graph_way_weight *) vector_get_ptr_to(vector, (size_t) name - 1)) = value;
}
