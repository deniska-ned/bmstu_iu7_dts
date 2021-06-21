#ifndef _BIG_DECIMAL_IO_H_
#define _BIG_DECIMAL_IO_H_

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "big_decimal.h"

#define TRUE 1
#define FALSE 0

#define MAX_INPUT_STR_LEN 38
#define MAX_OUTPUT_STR_LEN 38

#ifndef OKAY
#define OKAY                            0
#endif // OKAY

#define INCORRECT_SIGN_POSITION         1
#define DOT_IN_POWER_FOUND              2
#define INCORRECT_DOT_COUNT             3
#define INCORRECT_E_COUNT               4
#define INCORRECT_SYMBOL                5
#define ABSENCE_OF_MANTISSA             6
#define MAX_MANTISSA_LEN_EXCEEDED       7
#define ABSENCE_OF_EXPECTED_POWER       8
#define MAX_POWER_LEN_EXCEEDED          9
#define CHAR_NUM_EXCEED                 10
#define UNKNOWN_ERROR                   127

int check_str(const char *const str);

int str_to_big_decimal(const char *const str, big_decimal_t *const num);

int input_source_numbers(big_decimal_t *const first_num,
big_decimal_t *const second_num);

void big_decimal_to_str(const big_decimal_t  num, char *const str);

void print_multiplication_result(const big_decimal_t first_num,
const big_decimal_t second_num, const big_decimal_t result);

#endif // _BIG_DECIMAL_IO_H_
