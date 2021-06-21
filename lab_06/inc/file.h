#ifndef __FILE_H__
#define __FILE_H__

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "elem.h"

void print_elem_to_source(FILE *dst, elem_t src);
int scan_elem_from_source(FILE *src, elem_t *dst);
int file_add(char *file_name, elem_t elem);
int file_del(char *file_name, elem_t key);
int file_search(char *file_name, elem_t elem, size_t *comparisons, int *find);
int file_print(FILE *dst, char *file_name);
void file_make_empty(char *filename);

#endif // __FILE_H__
