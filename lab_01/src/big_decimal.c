#include "../inc/big_decimal.h"
#include "../inc/big_decimal_io.h"

int is_big_decimal_zero(const big_decimal_t num)
{
    for (int i = 0; i < MAX_MANTISSA_LEN; ++i)
        if (0 != num.mantissa[i])
            return FALSE;

    return TRUE;
}

/**
 * @brief Multiple two big_decimal_t number
 *
 * @return OKAY if success;
 * PRODUCT_POWER_LEN_EXCEEDED if permissible power len exceeded
 */
int big_decimal_multiplication(const big_decimal_t num_1,
const big_decimal_t num_2, big_decimal_t *const product)
{
    // Zero check
    if (is_big_decimal_zero(num_1) || is_big_decimal_zero(num_2))
    {
        product->mantissa_sign = 0;
        for (int i = 0; i < MAX_MANTISSA_LEN; ++i)
            product->mantissa[i] = 0;
        product->power = 0;

        return OKAY;
    }

    // Init power value
    int power = num_1.power + num_2.power;

    // Init composition array
    int composition[COMPOSITION_LEN];
    for (int i = 0; i < COMPOSITION_LEN; ++i)
        composition[i] = 0;

    // Calcucate composition
    {
        for (int i = 0; i < MAX_MANTISSA_LEN; ++i)
            for (int j = 0; j < MAX_MANTISSA_LEN; ++j)
                 composition[i + j + 1] += num_1.mantissa[i] * num_2.mantissa[j];

        for (int i = COMPOSITION_LEN - 1; i > 0; --i)
        {
            composition[i - 1] += composition[i] / 10;
            composition[i] %= 10;
        }
    }

    // Left shift
    while (0 == composition[0])
    {
        for (int i = 0; i < COMPOSITION_LEN - 1; ++i)
            composition[i] = composition[i + 1];

        composition[COMPOSITION_LEN - 1] = 0;
        
        --power;
    }

    // Round
    {
        if (composition[MAX_MANTISSA_LEN] >= 5)
        {
            ++composition[MAX_MANTISSA_LEN - 1];

            for (int i = MAX_MANTISSA_LEN - 1; i > 0; --i)
            {
                composition[i - 1] += composition[i] / 10;
                composition[i] %= 10;
            }
        }
    }

    // Check power value
    if (power > MAX_POWER_VALUE || power < MIN_POWER_VALUE)
        return PRODUCT_POWER_LEN_EXCEEDED;

    // Entering data
    product->mantissa_sign = num_1.mantissa_sign * num_2.mantissa_sign;
    for (int i = 0; i < MAX_MANTISSA_LEN; ++i)
        product->mantissa[i] = composition[i];
    product->power = power;

    return OKAY;
}
