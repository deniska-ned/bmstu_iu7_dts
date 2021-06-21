#ifndef __HASH_FUNCS_H__
#define __HASH_FUNCS_H__

#include <assert.h>
#include <math.h>
#include <stdlib.h>

#include "macrologger.h"

size_t hash_func_mlt(long value, size_t hash_table_len);

size_t hash_func_mod(long value, size_t hash_table_len);

#endif // __HASH_FUNCS_H__
