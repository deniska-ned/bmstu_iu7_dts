#include "../inc/random.h"

void random_init()
{
    srand((unsigned) time(0));
}

double random01()
{
    return rand() / (double) RAND_MAX;
}

double random_double_in_range(double left_border, double right_border)
{
    return left_border + (right_border - left_border) * random01();
}
