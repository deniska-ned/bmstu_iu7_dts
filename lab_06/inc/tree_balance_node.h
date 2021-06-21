#ifndef __TREE_BALANCE_NODE_H__
#define __TREE_BALANCE_NODE_H__

#include <stdio.h>
#include <stdlib.h>

#include "elem.h"
#include "macrologger.h"

typedef struct tree_balance_node tb_node_t;

struct tree_balance_node
{
    elem_t data;
    unsigned height;
    tb_node_t *right;
    tb_node_t *left;
};

tb_node_t *tb_node_create();
void tb_node_free(tb_node_t *node);
void tb_node_to_dot(tb_node_t *node, void *file);

unsigned int tb_node_height(tb_node_t *node);
long bfactor(tb_node_t *node);
void fix_height(tb_node_t *node);

#endif // __TREE_BALANCE_NODE_H__
