#include <stdio.h>
#include "../inc/big_decimal.h"
#include "../inc/big_decimal_io.h"

#define MESS_INCORRECT_SIGN_POSITION     "Incorrect sign position\n"
#define MESS_DOT_IN_POWER_FOUND          "Dot in power found\n"
#define MESS_INCORRECT_DOT_COUNT         "Incorrect dot count\n"
#define MESS_INCORRECT_E_COUNT           "Incorrect e count\n"
#define MESS_INCORRECT_SYMBOL            "Incorrect symbol\n"
#define MESS_ABSENCE_OF_MANTISSA         "Absence of mantissa\n"
#define MESS_MAX_MANTISSA_LEN_EXCEEDED   "Max mantissa len exceeded\n"
#define MESS_ABSENCE_OF_EXPECTED_POWER   "Absence of expected power\n"
#define MESS_MAX_POWER_LEN_EXCEEDED      "Max power len exceeded\n"
#define MESS_CHAR_NUM_EXCEED             "Char num exceeded\n"
#define MESS_PRODUCT_POWER_LEN_EXCEEDED  "Product power length exceeded\n"
#define MESS_UNKNOWN_ERROR               "Unknown error\n"

#define ERR_OKAY                            0
#define ERR_INCORRECT_SIGN_POSITION         1
#define ERR_DOT_IN_POWER_FOUND              2
#define ERR_INCORRECT_DOT_COUNT             3
#define ERR_INCORRECT_E_COUNT               4
#define ERR_INCORRECT_SYMBOL                5
#define ERR_ABSENCE_OF_MANTISSA             6
#define ERR_MAX_MANTISSA_LEN_EXCEEDED       7
#define ERR_ABSENCE_OF_EXPECTED_POWER       8
#define ERR_MAX_POWER_LEN_EXCEEDED          9
#define ERR_CHAR_NUM_EXCEED                 10
#define ERR_PRODUCT_POWER_LEN_EXCEEDED      11
#define ERR_UNKNOWN_ERROR                   127

int process_return_code(const int rc)
{
    switch (rc)
    {
        case OKAY:
            return OKAY;
        case PRODUCT_POWER_LEN_EXCEEDED:
            printf(MESS_PRODUCT_POWER_LEN_EXCEEDED);
            return ERR_PRODUCT_POWER_LEN_EXCEEDED;
        case INCORRECT_SIGN_POSITION:
            printf(MESS_INCORRECT_SIGN_POSITION);
            return ERR_INCORRECT_SIGN_POSITION;
        case DOT_IN_POWER_FOUND:
            printf(MESS_DOT_IN_POWER_FOUND);
            return ERR_DOT_IN_POWER_FOUND;
        case INCORRECT_DOT_COUNT:
            printf(MESS_INCORRECT_DOT_COUNT);
            return ERR_INCORRECT_DOT_COUNT;
        case INCORRECT_E_COUNT:
            printf(MESS_INCORRECT_E_COUNT);
            return ERR_INCORRECT_E_COUNT;
        case INCORRECT_SYMBOL:
            printf(MESS_INCORRECT_SYMBOL);
            return ERR_INCORRECT_SYMBOL;
        case ABSENCE_OF_MANTISSA:
            printf(MESS_ABSENCE_OF_MANTISSA);
            return ERR_ABSENCE_OF_MANTISSA;
        case MAX_MANTISSA_LEN_EXCEEDED:
            printf(MESS_MAX_MANTISSA_LEN_EXCEEDED);
            return ERR_MAX_MANTISSA_LEN_EXCEEDED;
        case ABSENCE_OF_EXPECTED_POWER:
            printf(MESS_ABSENCE_OF_EXPECTED_POWER);
            return ERR_ABSENCE_OF_EXPECTED_POWER;
        case MAX_POWER_LEN_EXCEEDED:
            printf(MESS_MAX_POWER_LEN_EXCEEDED);
            return ERR_MAX_POWER_LEN_EXCEEDED;
        case CHAR_NUM_EXCEED:
            printf(MESS_CHAR_NUM_EXCEED);
            return ERR_CHAR_NUM_EXCEED;
        case UNKNOWN_ERROR: default:
            return ERR_UNKNOWN_ERROR;
    }
}

int main(void)
{
    int rc;

    big_decimal_t num_1, num_2, product;
    if (OKAY != (rc = input_source_numbers(&num_1, &num_2)))
        return process_return_code(rc);

    if (OKAY != (rc = big_decimal_multiplication(num_1, num_2, &product)))
        return process_return_code(rc);

    print_multiplication_result(num_1, num_2, product);

    return process_return_code(OKAY);
}
