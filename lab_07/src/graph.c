#include "../inc/graph.h"

struct graph *graph_init()
{
    struct graph *graph = malloc(sizeof(struct graph));

    if (NULL != graph)
    {
        INIT_LIST_HEAD(&graph->list);
        graph->graph_node_count = 0;
    }

    return graph;
}

void graph_free(struct graph *graph)
{
    struct graph_edge *current, *next;
    LIST_FOR_EACH_ENTRY_SAFE(current, next, &graph->list, list, struct graph_edge)
    {
        list_del(&current->list);
        free(current);
    }

    free(graph);
}

int graph_add_node(struct graph *graph, unsigned src, unsigned int dst, int weight)
{
    struct graph_edge *node = malloc(sizeof(struct graph_edge));

    if (NULL == node)
    {
        LOG_ERROR("%s", "Allocation failed");
        return ALLOCATION_FAILED;
    }

    node->src = src;
    node->dst = dst;
    node->weight = weight;

    graph->graph_node_count = MAX(graph->graph_node_count, MAX(src, dst));

    list_add_tail(&node->list, &graph->list);

    return OKAY;
}

int graph_add_node_from_file(struct graph *graph, char *filename)
{
    FILE *f = fopen(filename, "r");

    unsigned src, dst;
    int weight;
    int rc;

    while (3 == fscanf(f, "%u %u %d", &src, &dst, &weight))
    {
        if (OKAY != (rc = graph_add_node(graph, src, dst, weight)))
        {
            LOG_ERROR("%s", "Allocation failed");
            return rc;
        }
    }

    return OKAY;
}

void graph_print(struct graph *graph)
{
    struct graph_edge *node;

    LIST_FOR_EACH_ENTRY(node, &graph->list, list, struct graph_edge)
    {
        printf("%d -> %d; weight = %d\n", node->src, node->dst, node->weight);
    }
}

int graph_draw(struct graph *graph)
{
    system("mkdir -p dot_files");
    FILE *f = fopen(GRAPH_INFO_FILE, "w");
    if (NULL == f)
    {
        LOG_ERROR("%s", "File cannot be opened");
        return FILE_CANNOT_BE_OPENED;
    }
    fprintf(f, "digraph my_graph {\n");

    struct graph_edge *node;

    LIST_FOR_EACH_ENTRY(node, &graph->list, list, struct graph_edge)
    {
        fprintf(f, "%u -> %u [label = \"%d\", penwidth = \"1\"]\n", node->src, node->dst, node->weight);
    }
    fprintf(f, "}\n");

    fclose(f);

    system(COMMAND_TO_OUTPUT_PIC);

    return OKAY;
}

int graph_draw_and_select(struct graph *graph, vector_t *vector, int weight, unsigned start_name)
{
    system("mkdir -p dot_files");
    FILE *f = fopen(GRAPH_INFO_FILE, "w");
    if (NULL == f)
    {
        LOG_ERROR("%s", "File cannot be opened");
        return FILE_CANNOT_BE_OPENED;
    }
    fprintf(f, "digraph my_graph {\n");

    struct graph_edge *node;

    for (unsigned name = 1; name <= graph->graph_node_count; ++name)
    {
        struct graph_way_weight node = vector_get_gww_by_name(vector, name);
        if (start_name == node.name)
            fprintf(f, "%u [style=filled, fillcolor = yellow]\n", node.name);
        else if (node.way_weight <= weight)
            fprintf(f, "%u [style=filled, fillcolor = green]\n", node.name);
    }

    LIST_FOR_EACH_ENTRY(node, &graph->list, list, struct graph_edge)
    {
        fprintf(f, "%u -> %u [label = \"%d\", penwidth = \"1\"]\n", node->src, node->dst, node->weight);
    }
    fprintf(f, "}\n");

    fclose(f);

    system(COMMAND_TO_OUTPUT_PIC);

    return OKAY;
}

void graph_way_len_debug_print(FILE *source, vector_t *vector)
{
    for (unsigned name = 1; name <= vector->length; ++name)
    {
        struct graph_way_weight node = vector_get_gww_by_name(vector, name);
        fprintf(source, "value: %d; weight: %d\n", node.name, node.way_weight);
    }
    fprintf(source, "---\n");
}

int graph_bellman_ford(struct graph *graph, vector_t **vector, unsigned start_name)
{
    struct graph_way_weight gww_node;

    LOG_DEBUG("graph->graph_node_count = %d", graph->graph_node_count);

    if (0 == graph->graph_node_count)
    {
        LOG_WARNING("%s", "Empty graph");
        return EMPTY_GRAPH;
    }

    *vector = vector_allocate(graph->graph_node_count,
    sizeof(struct graph_way_weight));

    if (NULL == *vector)
    {
        LOG_ERROR("%s", "Allocation failed");
        return ALLOCATION_FAILED;
    }

    for (unsigned name = 1; name <= graph->graph_node_count; ++name)
    {
        gww_node.name = name;
        gww_node.way_weight = GRAPH_INFINITY_WEIGHT;
        vector_set_gww_by_name(*vector, name, gww_node);
    }

    gww_node.name = start_name;
    gww_node.way_weight = 0;
    vector_set_gww_by_name(*vector, start_name, gww_node);

#if LOG_LEVEL >= DEBUG_LEVEL
    graph_way_len_debug_print(stderr, *vector);
#endif

    struct graph_edge *graph_edge;
    struct graph_way_weight gww_node_dst, gww_node_src;
    for (unsigned i = 0; i < graph->graph_node_count - 1; ++i)
    {
        LIST_FOR_EACH_ENTRY(graph_edge, &graph->list, list, struct graph_edge)
        {
            gww_node_src = vector_get_gww_by_name(*vector, graph_edge->src);
            gww_node_dst = vector_get_gww_by_name(*vector, graph_edge->dst);

            if (gww_node_src.way_weight != GRAPH_INFINITY_WEIGHT &&
            gww_node_src.way_weight + graph_edge->weight < gww_node_dst.way_weight)
            {
                LOG_TRACE("%s", "Changing min way weight");
                gww_node_dst.way_weight = gww_node_src.way_weight + graph_edge->weight;
                vector_set_gww_by_name(*vector, (unsigned) graph_edge->dst, gww_node_dst);
            }
        }

#if LOG_LEVEL >= DEBUG_LEVEL
        graph_way_len_debug_print(stderr, *vector);
#endif
    }

    LIST_FOR_EACH_ENTRY(graph_edge, &graph->list, list, struct graph_edge)
    {
        gww_node_src = vector_get_gww_by_name(*vector, graph_edge->src);
        gww_node_dst = vector_get_gww_by_name(*vector, graph_edge->dst);

        if (gww_node_src.way_weight != GRAPH_INFINITY_WEIGHT &&
        gww_node_src.way_weight + graph_edge->weight < gww_node_dst.way_weight)
        {
            LOG_WARNING("%s", "Negative loop exist");
            // TODO free
            return NEGATIVE_LOOP;
        }
    }

    return OKAY;
}

int graph_bellman_ford_mod(struct graph *graph, vector_t **vector, unsigned start_name)
{
    struct graph_way_weight gww_node;

    LOG_DEBUG("graph->graph_node_count = %d", graph->graph_node_count);

    if (0 == graph->graph_node_count)
    {
        LOG_WARNING("%s", "Empty graph");
        return EMPTY_GRAPH;
    }

    *vector = vector_allocate(graph->graph_node_count,
    sizeof(struct graph_way_weight));

    if (NULL == *vector)
    {
        LOG_ERROR("%s", "Allocation failed");
        return ALLOCATION_FAILED;
    }

    for (unsigned name = 1; name <= graph->graph_node_count; ++name)
    {
        gww_node.name = name;
        gww_node.way_weight = GRAPH_INFINITY_WEIGHT;
        vector_set_gww_by_name(*vector, name, gww_node);
    }

    gww_node.name = start_name;
    gww_node.way_weight = 0;
    vector_set_gww_by_name(*vector, start_name, gww_node);

#if LOG_LEVEL >= DEBUG_LEVEL
    graph_way_len_debug_print(stderr, *vector);
#endif

    struct graph_edge *graph_edge;
    struct graph_way_weight gww_node_dst, gww_node_src;
    for (unsigned i = 0; i < graph->graph_node_count - 1; ++i)
    {
        LIST_FOR_EACH_ENTRY(graph_edge, &graph->list, list, struct graph_edge)
        {
            gww_node_src = vector_get_gww_by_name(*vector, graph_edge->src);
            gww_node_dst = vector_get_gww_by_name(*vector, graph_edge->dst);

            if (gww_node_src.way_weight != GRAPH_INFINITY_WEIGHT &&
            gww_node_src.way_weight + graph_edge->weight < gww_node_dst.way_weight)
            {
                LOG_TRACE("%s", "Changing min way weight");
                gww_node_dst.way_weight = gww_node_src.way_weight + graph_edge->weight;
                vector_set_gww_by_name(*vector, (unsigned) graph_edge->dst, gww_node_dst);
            }
        }

#if LOG_LEVEL >= DEBUG_LEVEL
        graph_way_len_debug_print(stderr, *vector);
#endif
    }

    vector_t *new_vector = vector_copy(*vector);

    if (NULL == new_vector)
    {
        vector_free(*vector);
        return ALLOCATION_FAILED;
    }

    for (unsigned i = 0; i < graph->graph_node_count; ++i)
    {
        LIST_FOR_EACH_ENTRY(graph_edge, &graph->list, list, struct graph_edge)
        {
            gww_node_src = vector_get_gww_by_name(new_vector, graph_edge->src);
            gww_node_dst = vector_get_gww_by_name(new_vector, graph_edge->dst);

            if (gww_node_src.way_weight != GRAPH_INFINITY_WEIGHT &&
            gww_node_src.way_weight + graph_edge->weight < gww_node_dst.way_weight)
            {
                LOG_TRACE("%s", "Changing min way weight");
                gww_node_dst.way_weight = gww_node_src.way_weight + graph_edge->weight;
                vector_set_gww_by_name(new_vector, (unsigned) graph_edge->dst, gww_node_dst);
            }
        }

#if LOG_LEVEL >= DEBUG_LEVEL
        graph_way_len_debug_print(stderr, new_vector);
#endif
    }

    for (unsigned name = 1; name <= graph->graph_node_count; ++name)
    {
        struct graph_way_weight old = vector_get_gww_by_name(*vector, name);
        struct graph_way_weight new = vector_get_gww_by_name(new_vector, name);

        if (old.way_weight != new.way_weight)
        {
            old.way_weight = GRAPH_UNINFINITY_WEIGHT;
            vector_set_gww_by_name(*vector, name, old);
        }
    }

    vector_free(new_vector);

    return OKAY;
}
