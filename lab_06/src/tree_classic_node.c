#include "../inc/tree_classic_node.h"

tc_node_t *tc_node_create()
{
    tc_node_t *node = malloc(sizeof(tc_node_t));
    
    if (node)
    {
        node->left = NULL;
        node->right = NULL;
    }

    return node;
}

void tc_node_free(tc_node_t *node)
{
    free(node);
}

void tc_node_to_dot(tc_node_t *node, void *file)
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