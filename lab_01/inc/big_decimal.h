#ifndef _BIG_DECIMAL_H_
#define _BIG_DECIMAL_H_

#include <inttypes.h>

#define MAX_MANTISSA_LEN 30
#define MAX_POWER_LEN 5
#define COMPOSITION_LEN MAX_MANTISSA_LEN * 2 + 1

#define MAX_POWER_VALUE 99999
#define MIN_POWER_VALUE -99999

#ifndef OKAY
#define OKAY 0
#endif // OKAY

#define PRODUCT_POWER_LEN_EXCEEDED 11

enum num_sign {
    POSITIVE = 1,
    NEGATIVE = -1
};

struct big_decimal {
    int8_t mantissa_sign;               // num_sign
    int8_t mantissa[MAX_MANTISSA_LEN];
    int32_t power;
};

typedef struct big_decimal big_decimal_t;

int is_big_decimal_zero(const big_decimal_t num);

int big_decimal_multiplication(const big_decimal_t num_1,
const big_decimal_t num_2, big_decimal_t *const product);

#endif // _BIG_DECIMAL_H_
