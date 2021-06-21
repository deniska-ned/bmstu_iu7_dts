#include "../inc/big_decimal_io.h"

/**
 * @brief Check str to represent bin_decimal_t
 *
 * @return OKAY if string can represent big_decimal_t;
 * INCORRECT_SIGN_POSITION if sign takes incorrect position;
 * DOT_IN_POWER_FOUND if dot in power found;
 * INCORRECT_DOT_COUNT if dot count more than one;
 * INCORRECT_E_COUNT if E count more than one;
 * INCORRECT_SYMBOL if unexpected symbol met in string;
 * ABSENCE_OF_MANTISSA if mantissa absent;
 * MAX_MANTISSA_LEN_EXCEEDED if max mantissa length exceeded;
 * ABSENCE_OF_EXPECTED_POWER if power after E absent;
 * MAX_POWER_LEN_EXCEEDED if power len more than MAX_POWER_LEN;
 */
int check_str(const char *const str)
{
    int mantissa_len = 0;
    int dot_count = 0;
    int e_index = -1;
    int e_count = 0;
    int power_len = 0;

    for (int i = 0; '\0' != str[i]; ++i)
    {
        switch (str[i])
        {
            case ' ':
                break;
            case '+': case '-':
                if (!(0 == i || (e_count > 0 && e_index + 1 == i)))
                    return INCORRECT_SIGN_POSITION;
                break;
            case '.':
                ++dot_count;
                if (0 != e_count)
                    return DOT_IN_POWER_FOUND;
                if (dot_count > 1)
                    return INCORRECT_DOT_COUNT;
                break;
            case 'E':
                ++e_count;
                e_index = i;
                if (e_count > 1)
                    return INCORRECT_E_COUNT;
                break;
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9': 
                if (0 == e_count)
                    ++mantissa_len;
                else
                    ++power_len;
                break;
            default:
                return INCORRECT_SYMBOL;
        }
    }

    if (0 == mantissa_len)
        return ABSENCE_OF_MANTISSA;
    else if (mantissa_len > MAX_MANTISSA_LEN)
        return MAX_MANTISSA_LEN_EXCEEDED;
    
    if (1 == e_count && 0 == power_len)
        return ABSENCE_OF_EXPECTED_POWER;
    else if (power_len > MAX_POWER_LEN)
        return MAX_POWER_LEN_EXCEEDED;

    return OKAY;
}

int str_to_big_decimal(const char *const str, big_decimal_t *const num)
{
    int rc;
    if (OKAY != (rc = check_str(str)))
        return rc;

    big_decimal_t temp;
    // Default values
    {
        temp.mantissa_sign = POSITIVE;
        for (int i = 0; i < MAX_MANTISSA_LEN; ++i)
            temp.mantissa[i] = 0;
        temp.power = 0;
    }

    // Mantissa sign
    temp.mantissa_sign = ('-' == *str) ? NEGATIVE : POSITIVE;


    int first_significant_digit_i = 0;
    {
        int i;
        for (i = 0; NULL == strchr("123456789E", str[i]); ++i)
            ;
    
        if (!isdigit(str[i]))
        {
            *num = temp;
            return OKAY;
        }
        
        first_significant_digit_i = i;
    }

    // Mantissa
    {
        int str_i = first_significant_digit_i, m_i = 0;
        for ( ; 'E' != str[str_i] && str[str_i]; ++str_i)
            if (isdigit(str[str_i]))
                temp.mantissa[m_i++] = str[str_i] - '0';
    }

    // Power
    {
        int power = 0;

        char *dot_p = strchr(str, '.'), *e_p = strchr(str, 'E');
        int dot_i = -1;

        if (NULL == dot_p)
        {
            if (NULL == e_p)
                dot_i = strchr(str, '\0') - str;
            else
                dot_i = e_p - str;
        }
        else
        {
            dot_i = dot_p - str;
        }

        if (first_significant_digit_i < dot_i)
            power += dot_i - first_significant_digit_i;
        else
            power += dot_i - first_significant_digit_i + 1;

        if (NULL != e_p)
        {
            int power_after_e;
            sscanf(e_p + 1, "%d", &power_after_e);

            power += power_after_e;
        }

        // if (power > MAX_POWER_VALUE || power < MIN_POWER_VALUE)
        //     return MAX_POWER_LEN_EXCEEDED;

        temp.power = power;
    }

    *num = temp;

    return OKAY;
}

int input_source_numbers(big_decimal_t *const first_num,
big_decimal_t *const second_num)
{
    printf("┌───────────────────────────────┐\n");
    printf("│  Real numbers multiplication  │\n");
    printf("├───────────────────────────────┤\n");
    printf("│Input number like +/-m.n E +/-K│\n");
    printf("│Length(m + n) <= 30            │\n");
    printf("│Length(power) <= 5             │\n");
    printf("└───────────────────────────────┘\n");

    int rc;
    big_decimal_t nums[2];

    for (int num_i = 0; num_i < 2; ++num_i)
    {
        printf("\nEnter the number %d: \n", num_i + 1);
        printf("1       10        20        30        40\n");
        printf("├────────┼─────────┼─────────┼─────────┤\n");
        char str[MAX_INPUT_STR_LEN + 1];
    
        int c, str_i = 0;
    
        while (('\n' != (c = getchar())) && (EOF != c))
        {
            if (MAX_INPUT_STR_LEN == str_i)
                return CHAR_NUM_EXCEED;
    
            if (' ' == c)
                continue;
    
            str[str_i++] = c;
        }
    
        str[str_i] = '\0';
    
        if (OKAY != (rc = str_to_big_decimal(str, nums + num_i)))
            return rc;
    }

    *first_num = nums[0];
    *second_num = nums[1];

    return OKAY;
}

void big_decimal_to_str(const big_decimal_t  num, char *const str)
{
    int str_i = 0;

    if (NEGATIVE == num.mantissa_sign)
        str[str_i++] = '-';

    str[str_i++] = '0';
    str[str_i++] = '.';

    int last_significant_digit_i = -1;

    for (int i = 0; i < MAX_MANTISSA_LEN; ++i)
        if (0 != num.mantissa[i])
            last_significant_digit_i = i;

    if (-1 == last_significant_digit_i)
    {
        strcpy(str, "0.0E0");
        return;
    }

    for (int i = 0; i <= last_significant_digit_i; ++i)
        str[str_i++] = num.mantissa[i] + '0';

    str[str_i++] = 'E';
    sprintf(str + str_i, "%d", num.power);
}

void print_multiplication_result(const big_decimal_t first_num,
const big_decimal_t second_num, const big_decimal_t result)
{
    char first_num_str[MAX_OUTPUT_STR_LEN + 1];
    big_decimal_to_str(first_num, first_num_str);

    char second_num_str[MAX_OUTPUT_STR_LEN + 1];
    big_decimal_to_str(second_num, second_num_str);

    char result_str[MAX_OUTPUT_STR_LEN + 1];
    big_decimal_to_str(result, result_str);

    printf("\n%s * %s = %s\n", first_num_str, second_num_str, result_str);
}
