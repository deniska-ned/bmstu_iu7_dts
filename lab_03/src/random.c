#include "../inc/random.h"

size_t rand_uint64_slow(void) {
    size_t r = 0;

    for (int i = 0; i < 64; i++)
        r = r * 2 + (size_t) rand() % 2;

    return r;
}
