#ifndef __RANDOM_H__

#define __RANDOM_H__

#include <stdlib.h>
#include <time.h>

void random_init();

double random01();

double random_double_in_range(double left_border, double right_border);

#endif // __RANDOM_H__
