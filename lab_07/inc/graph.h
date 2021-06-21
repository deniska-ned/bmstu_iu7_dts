#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

#include "macrologger.h"
#include "list.h"
#include "rc.h"
#include "vector_graph_way_weight.h"
#include "defmath.h"

#define GRAPH_INFINITY_WEIGHT           INT_MAX
#define GRAPH_UNINFINITY_WEIGHT         INT_MIN

#define GRAPH_INFO_FILE                 "dot_files/graph.gv"
#define GRAPH_PICTURE_FILE              "dot_files/graph.png"
#define COMMAND_TO_OUTPUT_PIC \
"dot -Tpng " GRAPH_INFO_FILE " -o " GRAPH_PICTURE_FILE " && kde-open5 " GRAPH_PICTURE_FILE

struct graph_edge
{
    unsigned src;
    unsigned dst;
    int weight;

    struct list_head list;
};

struct graph
{
    struct list_head list;
    unsigned graph_node_count;
};

#define EMPTY_GRAPH                     1
#define NEGATIVE_LOOP                   2

struct graph *graph_init();

void graph_free(struct graph *graph);

int graph_add_node(struct graph *graph, unsigned src, unsigned int dst, int weight);

int graph_add_node_from_file(struct graph *graph, char *filename);

void graph_print(struct graph *graph);

int graph_draw(struct graph *graph);

void graph_way_len_debug_print(FILE *source, vector_t *vector);

int graph_bellman_ford(struct graph *graph, vector_t **vector, unsigned start_name);

int graph_bellman_ford_mod(struct graph *graph, vector_t **vector, unsigned start_name);

int graph_draw_and_select(struct graph *graph, vector_t *vector, int weight, unsigned start_name);

#endif // __GRAPH_H__
