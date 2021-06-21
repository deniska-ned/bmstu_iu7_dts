#include "../inc/mymath.h"

double update_avg(double prev_avg, int prev_count, double new_value)
{
    return (prev_avg * prev_count + new_value) / (prev_count + 1);
}
