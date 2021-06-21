#include "../inc/myrandom.h"

long get_random_long()
{
    uint64_t num;

    num = (unsigned) rand();
    num = (num << 32) | (unsigned) rand();

    return (long) num;
}
