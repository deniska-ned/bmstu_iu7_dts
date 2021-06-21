#include "../inc/tree_classic.h"

void post_apply(tc_node_t *root, void (*func)(tc_node_t *, void *), void *param)
{
    if (!root)
        return;
    
    post_apply(root->left, func, param);
    post_apply(root->right, func, param);

    func(root, param);
}

void pre_apply(tc_node_t *root, void (*func)(tc_node_t *, void *), void *param)
{
    if (!root)
        return;

    func(root, param);
    
    pre_apply(root->left, func, param);
    pre_apply(root->right, func, param);
}

void tree_free(tc_node_t *root)
{
    if (NULL == root)
        return;

    tree_free(root->left);
    tree_free(root->right);
    tc_node_free(root);
}

int tree_add_elem(tc_node_t **root, elem_t elem)
{
    if (!(*root))
    {
        tc_node_t *node = tc_node_create();
        if (!node)
            return ALLOCATON_ERROR;
        node->data = elem;
        *root = node;
    }
    else if (elem > (*root)->data)
        return tree_add_elem(&(*root)->right, elem);
    else if (elem < (*root)->data)
        return tree_add_elem(&(*root)->left, elem);
    
    return EXIT_SUCCESS;
}

elem_t find_tree_min(tc_node_t *root)
{
    if (!root->left)
        return root->data;
    
    return find_tree_min(root->left);
}

elem_t find_tree_max(tc_node_t *root)
{
    if (!root->right)
        return root->data;
    
    return find_tree_min(root->right);
}

int tree_add_from_file(char *file_name, tc_node_t **root)
{
    FILE *f = fopen(file_name, "r");
    if (!f)
        return OPEN_ERROR;
    
    elem_t elem;
    while (!scan_elem_from_source(f, &elem))
    {
        int rc = tree_add_elem(root, elem);
        if (rc)
        {
            fclose(f);
            return rc;
        }
    }

    fclose(f);
    
    return EXIT_SUCCESS;
}

void tree_del_elem(tc_node_t **root, elem_t elem)
{
    if (!(*root))
        return;
    else if (elem > (*root)->data)
    {
        tree_del_elem(&(*root)->right, elem);
        return;
    }
    else if (elem < (*root)->data)
    {
        tree_del_elem(&(*root)->left, elem);
        return;
    }
    else
    {
        if (!(*root)->left && !(*root)->right)
        {
            tc_node_free(*root);
            *root = NULL;
            return;
        }
        else if ((*root)->left && !(*root)->right)
        {
            tc_node_t *node = *root;
            *root = (*root)->left;
            tc_node_free(node);
        }
        else if (!(*root)->left && (*root)->right)
        {
            tc_node_t *node = *root;
            *root = (*root)->right;
            tc_node_free(node);
        }
        else
        {
            elem_t min = find_tree_min((*root)->right);
            (*root)->data = min;
            tree_del_elem(&(*root)->right, min);
        }
    }
}

bool tree_is_elem_found(tc_node_t *root, elem_t elem, size_t *comparisons)
{
    *comparisons = 0;

    while (root)
    {
        *comparisons += 1;
        if (root->data == elem)
            return true;
        else if (root->data > elem)
            root = root->left;
        else
            root = root->right;
    }

    return false;
}

int tree_export_to_dot(tc_node_t *root, char *file_dst, char *tree_name)
{
    FILE *f = fopen(file_dst, "w");
    if (!f)
        return OPEN_ERROR;

    fprintf(f, "digraph %s {\n", tree_name);

    pre_apply(root, tc_node_to_dot, f);

    fprintf(f, "}\n");

    fclose(f);

    return EXIT_SUCCESS;
}
