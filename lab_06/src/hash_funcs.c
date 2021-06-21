#include "../inc/hash_funcs.h"

size_t hash_func_mlt(long value, size_t hash_table_len)
{
    double golden_ratio = (sqrt(5) - 1.0) / 2.0;
    assert(0.0 < golden_ratio && golden_ratio < 1.0);

    double int_part, fraction_part;
    fraction_part = modf(fabs(golden_ratio * (double) value), &int_part);

    size_t res = (size_t) floor((double) hash_table_len * fraction_part);
    LOG_INFO("%zu/%zu", res, hash_table_len);
    assert(res < hash_table_len);

    return res;
}

size_t hash_func_mod(long value, size_t hash_table_len)
{
    return (unsigned  long) labs(value) % hash_table_len;
}
