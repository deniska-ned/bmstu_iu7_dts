#ifndef __DEFINES_H__

#define __DEFINES_H__

#include <math.h>
#include <stdbool.h>

#define BOOL_TO_STR(VALUE) VALUE ? "true" : "false"

#define DOUBLE_TOL                      1e-4

#define IS_DOUBLE_EQ(VALUE_1, VALUE_2) (fabs(VALUE_1 - VALUE_2) < DOUBLE_TOL ? true : false)

#define IS_DOUBLE_ZERO(VALUE) IS_DOUBLE_EQ(VALUE, 0.0)

#define DOUBLE_CMP()

#endif // __DEFINES_H__
