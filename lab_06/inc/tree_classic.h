#ifndef __TREE_CLASSIC_H__
#define __TREE_CLASSIC_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "elem.h"
#include "file.h"
#include "tree_classic_node.h"
#include "error_codes.h"

void tree_free(tc_node_t *root);
int tree_add_elem(tc_node_t **root, elem_t elem);
int tree_add_from_file(char *file_name, tc_node_t **root);
void tree_del_elem(tc_node_t **root, elem_t elem);
bool tree_is_elem_found(tc_node_t *root, elem_t elem, size_t *comparisons);
int tree_export_to_dot(tc_node_t *root, char *file_dst, char *tree_name);

#endif // __TREE_CLASSIC_H__
