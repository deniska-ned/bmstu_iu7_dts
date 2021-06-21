#include "../inc/tree_balance_node.h"

tb_node_t *tb_node_create()
{
    tb_node_t *node = malloc(sizeof(tb_node_t));
    
    if (node)
    {
        node->height = 0;
        node->left = NULL;
        node->right = NULL;
    }

    return node;
}

void tb_node_free(tb_node_t *node)
{
    free(node);
}

unsigned int tb_node_height(tb_node_t *node)
{
    return node ? node->height : 0;
}

long bfactor(tb_node_t *node)
{
    long diff = (long) tb_node_height(node->right) - (long) tb_node_height(node->left);

    LOG_DEBUG("right = %u, left = %u", tb_node_height(node->right),
    tb_node_height(node->left));

    LOG_DEBUG("value = %ld; diff = %ld", node->data, diff);
    return diff;
}

void fix_height(tb_node_t *node)
{
    unsigned hl = tb_node_height(node->left);
    unsigned hr = tb_node_height(node->right);
    node->height = (hl > hr ? hl : hr) + 1;

    LOG_DEBUG("value: %ld; height = %u", node->data, node->height);
}

void tb_node_to_dot(tb_node_t *node, void *file)
{
    if (node->left)
        fprintf((FILE *) file, "%ld -> %ld\n", node->data,
                node->left->data);
    if (node->right)
        fprintf((FILE *) file, "%ld -> %ld\n", node->data,
                node->right->data);
    
    if (!node->left && !node->right)
        fprintf((FILE *) file, "%ld\n", node->data);
}
