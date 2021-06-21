#ifndef __MENU_H__

#define __MENU_H__

#include <stdio.h>

#include "messages.h"
#include "macrologger.h"

#include "source_interaction.h"
#include "matrix.h"
#include "matrix_methods.h"
#include "sparse_matrix.h"
#include "sparse_matrix_methods.h"

#define OKAY                            0
#define INCORRECT_MENU_INPUT            1
#define INCORRECT_ROW_COL_INPUT         2
#define INCORRECT_COVER_INPUT           3
#define ALLOCATION_FAILED               4
#define INCORRECT_INPUT                 5

#define MATRIX_FREE_IF_NOT_NULL(PTR) \
if (NULL != PTR) \
{ \
    LOG_ERROR("matrix_free for %s", #PTR); \
    matrix_free(PTR); \
    PTR = NULL; \
}

#define SMATRIX_FREE_IF_NOT_NULL(PTR) \
if (NULL != PTR) \
{ \
    LOG_ERROR("matrix_free for %s", #PTR); \
    smatrix_free(PTR); \
    PTR = NULL; \
}

int menu_run();

#endif // __MENU_H__
