#ifndef __TREE_CLASSIC_NODE_H__
#define __TREE_CLASSIC_NODE_H__

#include <stdio.h>
#include <stdlib.h>

#include "elem.h"

typedef struct tree_classic_node tc_node_t;

struct tree_classic_node
{
    elem_t data;
    tc_node_t *left;
    tc_node_t *right;
};

tc_node_t *tc_node_create();
void tc_node_free(tc_node_t *node);
void tc_node_to_dot(tc_node_t *node, void *file);

#endif // __TREE_CLASSIC_NODE_H__