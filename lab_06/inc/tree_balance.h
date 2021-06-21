#ifndef __TREE_BALANCE_H__
#define __TREE_BALANCE_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "elem.h"
#include "file.h"
#include "tree_balance_node.h"
#include "error_codes.h"

void btree_free(tb_node_t *root);
int btree_add(tb_node_t **root, elem_t elem);
int btree_add_from_file(char *file_name, tb_node_t **root);
void btree_del(tb_node_t **root, elem_t elem);
bool btree_is_elem_found(tb_node_t *root, elem_t elem, size_t *comparisons);
int btree_export_to_dot(tb_node_t *root, char *file_dst, char *tree_name);

#endif // __TREE_BALANCE_H__