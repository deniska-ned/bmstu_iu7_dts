#include "../inc/tree_balance.h"

void bpost_apply(tb_node_t *root, void (*func)(tb_node_t *, void *), void *param)
{
    if (!root)
        return;
    
    bpost_apply(root->left, func, param);
    bpost_apply(root->right, func, param);

    func(root, param);
}

void bpre_apply(tb_node_t *root, void (*func)(tb_node_t *, void *), void *param)
{
    if (!root)
        return;

    func(root, param);
    
    bpre_apply(root->left, func, param);
    bpre_apply(root->right, func, param);
}

void btree_free(tb_node_t *root)
{
    if (NULL == root)
        return;

    btree_free(root->left);
    btree_free(root->right);

    tb_node_free(root);
}

tb_node_t *rotate_left(tb_node_t *q)
{
    tb_node_t *p = q->right;
    q->right = p->left;
    p->left = q;
    fix_height(q);
    fix_height(p);
    return p;
}

tb_node_t *rotate_right(tb_node_t *p)
{
    tb_node_t *q = p->left;
    p->left = q->right;
    q->right = p;
    fix_height(p);
    fix_height(q);
    return q;
}

tb_node_t *balance(tb_node_t *node)
{
    fix_height(node);
    if (bfactor(node) == 2)
    {
        if (bfactor(node->right) < 0)
            node->right = rotate_right(node->right);
        return rotate_left(node);
    }
    if (bfactor(node) == -2)
    {
        if (bfactor(node->left) > 0)
            node->left = rotate_left(node->left);
        return rotate_right(node);
    }

    return node;
}

int btree_add(tb_node_t **root, elem_t elem)
{
    int rc = EXIT_SUCCESS;
    if (!(*root))
    {
        tb_node_t *node = tb_node_create();
        if (!node)
            return ALLOCATON_ERROR;
        node->data = elem;
        *root = node;
    }
    else if (elem > (*root)->data)
        rc = btree_add(&(*root)->right, elem);
    else if (elem < (*root)->data)
        rc = btree_add(&(*root)->left, elem);
    
    *root = balance(*root);
    
    return rc;
}

elem_t find_btree_min(tb_node_t *root)
{
    if (!root->left)
        return root->data;
    
    return find_btree_min(root->left);
}

elem_t find_btree_max(tb_node_t *root)
{
    if (!root->right)
        return root->data;
    
    return find_btree_min(root->right);
}

void btree_del(tb_node_t **root, elem_t elem)
{
    if (!(*root))
        return;
    else if (elem > (*root)->data)
    {
        btree_del(&(*root)->right, elem);
    }
    else if (elem < (*root)->data)
    {
        btree_del(&(*root)->left, elem);
    }
    else
    {
        if (!(*root)->left && !(*root)->right)
        {
            tb_node_free(*root);
            *root = NULL;
            return;
        }
        else if ((*root)->left && !(*root)->right)
        {
            tb_node_t *node = *root;
            *root = (*root)->left;
            tb_node_free(node);
            return;
        }
        else if (!(*root)->left && (*root)->right)
        {
            tb_node_t *node = *root;
            *root = (*root)->right;
            tb_node_free(node);
            return;
        }
        else
        {
            elem_t min = find_btree_min((*root)->right);
            (*root)->data = min;
            btree_del(&(*root)->right, min);
            return;
        }
    }

    *root = balance(*root);
}

int btree_add_from_file(char *file_name, tb_node_t **root)
{
    FILE *f = fopen(file_name, "r");
    if (!f)
        return OPEN_ERROR;
    
    elem_t elem;
    while (!scan_elem_from_source(f, &elem))
    {
        int rc = btree_add(root, elem);
        if (rc)
        {
            fclose(f);
            return rc;
        }
    }

    fclose(f);
    
    return EXIT_SUCCESS;
}

int btree_export_to_dot(tb_node_t *root, char *file_dst, char *tree_name)
{
    FILE *f = fopen(file_dst, "w");
    if (!f)
        return OPEN_ERROR;

    fprintf(f, "digraph %s {\n", tree_name);

    bpre_apply(root, tb_node_to_dot, f);

    fprintf(f, "}\n");

    fclose(f);

    return EXIT_SUCCESS;
}

bool btree_is_elem_found(tb_node_t *root, elem_t elem, size_t *comparisons)
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
