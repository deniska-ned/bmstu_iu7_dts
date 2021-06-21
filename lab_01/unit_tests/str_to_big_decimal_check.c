#include "str_to_big_decimal_check.h"

// Negative tests

START_TEST(nt_stbd_max_power_len_exceeded)
{
    big_decimal_t num;
    int rc = str_to_big_decimal("123.45E99999", &num);

    ck_assert_int_eq(rc, MAX_POWER_LEN_EXCEEDED);
}
END_TEST

// Positive tests

START_TEST(pt_stbd_num)
{
    big_decimal_t num;
    int rc = str_to_big_decimal("12.34E10", &num);

    ck_assert_int_eq(rc, OKAY);
    ck_assert_int_eq(num.mantissa_sign, POSITIVE);
    for (int i = 0; i < MAX_MANTISSA_LEN; ++i)
    {
        int m_el = num.mantissa[i];
        switch (i)
        {
            case 0:
                ck_assert_int_eq(m_el, 1);
                break;
            case 1:
                ck_assert_int_eq(m_el, 2);
                break;
            case 2:
                ck_assert_int_eq(m_el, 3);
                break;
            case 3:
                ck_assert_int_eq(m_el, 4);
                break;
            default:
                ck_assert_int_eq(m_el, 0);
        }
    }
    ck_assert_int_eq(num.power, 12);
}
END_TEST

START_TEST(pt_stbd_num_with_plus)
{
    big_decimal_t num;
    int rc = str_to_big_decimal("+12.34E10", &num);

    ck_assert_int_eq(rc, OKAY);
    ck_assert_int_eq(num.mantissa_sign, POSITIVE);
    for (int i = 0; i < MAX_MANTISSA_LEN; ++i)
    {
        int m_el = num.mantissa[i];
        switch (i)
        {
            case 0:
                ck_assert_int_eq(m_el, 1);
                break;
            case 1:
                ck_assert_int_eq(m_el, 2);
                break;
            case 2:
                ck_assert_int_eq(m_el, 3);
                break;
            case 3:
                ck_assert_int_eq(m_el, 4);
                break;
            default:
                ck_assert_int_eq(m_el, 0);
        }
    }
    ck_assert_int_eq(num.power, 12);
}
END_TEST

START_TEST(pt_stbd_num_with_minus)
{
    big_decimal_t num;
    int rc = str_to_big_decimal("-12.34E10", &num);

    ck_assert_int_eq(rc, OKAY);
    ck_assert_int_eq(num.mantissa_sign, NEGATIVE);
    for (int i = 0; i < MAX_MANTISSA_LEN; ++i)
    {
        int m_el = num.mantissa[i];
        switch (i)
        {
            case 0:
                ck_assert_int_eq(m_el, 1);
                break;
            case 1:
                ck_assert_int_eq(m_el, 2);
                break;
            case 2:
                ck_assert_int_eq(m_el, 3);
                break;
            case 3:
                ck_assert_int_eq(m_el, 4);
                break;
            default:
                ck_assert_int_eq(m_el, 0);
        }
    }
    ck_assert_int_eq(num.power, 12);
}
END_TEST

START_TEST(pt_stbd_num_without_integer_part)
{
    big_decimal_t num;
    int rc = str_to_big_decimal(".34E10", &num);

    ck_assert_int_eq(rc, OKAY);
    ck_assert_int_eq(num.mantissa_sign, POSITIVE);
    for (int i = 0; i < MAX_MANTISSA_LEN; ++i)
    {
        int m_el = num.mantissa[i];
        switch (i)
        {
            case 0:
                ck_assert_int_eq(m_el, 3);
                break;
            case 1:
                ck_assert_int_eq(m_el, 4);
                break;
            default:
                ck_assert_int_eq(m_el, 0);
        }
    }
    ck_assert_int_eq(num.power, 10);
}
END_TEST

START_TEST(pt_stbd_num_without_integer_part_with_minus)
{
    big_decimal_t num;
    int rc = str_to_big_decimal("-.34E10", &num);

    ck_assert_int_eq(rc, OKAY);
    ck_assert_int_eq(num.mantissa_sign, NEGATIVE);
    for (int i = 0; i < MAX_MANTISSA_LEN; ++i)
    {
        int m_el = num.mantissa[i];
        switch (i)
        {
            case 0:
                ck_assert_int_eq(m_el, 3);
                break;
            case 1:
                ck_assert_int_eq(m_el, 4);
                break;
            default:
                ck_assert_int_eq(m_el, 0);
        }
    }
    ck_assert_int_eq(num.power, 10);
}
END_TEST

START_TEST(pt_stbd_num_without_integral_part)
{
    big_decimal_t num;
    int rc = str_to_big_decimal("12.E10", &num);

    ck_assert_int_eq(rc, OKAY);
    ck_assert_int_eq(num.mantissa_sign, POSITIVE);
    for (int i = 0; i < MAX_MANTISSA_LEN; ++i)
    {
        int m_el = num.mantissa[i];
        switch (i)
        {
            case 0:
                ck_assert_int_eq(m_el, 1);
                break;
            case 1:
                ck_assert_int_eq(m_el, 2);
                break;
            default:
                ck_assert_int_eq(m_el, 0);
        }
    }
    ck_assert_int_eq(num.power, 12);
}
END_TEST

START_TEST(pt_stbd_num_without_integral_part_with_minus)
{
    big_decimal_t num;
    int rc = str_to_big_decimal("-12.E10", &num);

    ck_assert_int_eq(rc, OKAY);
    ck_assert_int_eq(num.mantissa_sign, NEGATIVE);
    for (int i = 0; i < MAX_MANTISSA_LEN; ++i)
    {
        int m_el = num.mantissa[i];
        switch (i)
        {
            case 0:
                ck_assert_int_eq(m_el, 1);
                break;
            case 1:
                ck_assert_int_eq(m_el, 2);
                break;
            default:
                ck_assert_int_eq(m_el, 0);
        }
    }
    ck_assert_int_eq(num.power, 12);
}
END_TEST

START_TEST(pt_stbd_int)
{
    big_decimal_t num;
    int rc = str_to_big_decimal("12", &num);

    ck_assert_int_eq(rc, OKAY);
    ck_assert_int_eq(num.mantissa_sign, POSITIVE);
    for (int i = 0; i < MAX_MANTISSA_LEN; ++i)
    {
        int m_el = num.mantissa[i];
        switch (i)
        {
            case 0:
                ck_assert_int_eq(m_el, 1);
                break;
            case 1:
                ck_assert_int_eq(m_el, 2);
                break;
            default:
                ck_assert_int_eq(m_el, 0);
        }
    }
    ck_assert_int_eq(num.power, 2);
}
END_TEST

START_TEST(pt_stbd_int_with_minus)
{
    big_decimal_t num;
    int rc = str_to_big_decimal("-12", &num);

    ck_assert_int_eq(rc, OKAY);
    ck_assert_int_eq(num.mantissa_sign, NEGATIVE);
    for (int i = 0; i < MAX_MANTISSA_LEN; ++i)
    {
        int m_el = num.mantissa[i];
        switch (i)
        {
            case 0:
                ck_assert_int_eq(m_el, 1);
                break;
            case 1:
                ck_assert_int_eq(m_el, 2);
                break;
            default:
                ck_assert_int_eq(m_el, 0);
        }
    }
    ck_assert_int_eq(num.power, 2);
}
END_TEST

START_TEST(pt_stbd_int_with_power)
{
    big_decimal_t num;
    int rc = str_to_big_decimal("12E10", &num);

    ck_assert_int_eq(rc, OKAY);
    ck_assert_int_eq(num.mantissa_sign, POSITIVE);
    for (int i = 0; i < MAX_MANTISSA_LEN; ++i)
    {
        int m_el = num.mantissa[i];
        switch (i)
        {
            case 0:
                ck_assert_int_eq(m_el, 1);
                break;
            case 1:
                ck_assert_int_eq(m_el, 2);
                break;
            default:
                ck_assert_int_eq(m_el, 0);
        }
    }
    ck_assert_int_eq(num.power, 12);
}
END_TEST

START_TEST(pt_stbd_int_max_mantissa_len)
{
    big_decimal_t num;
    int rc = str_to_big_decimal("121212121212121212121212121212E10", &num);

    ck_assert_int_eq(rc, OKAY);
    ck_assert_int_eq(num.mantissa_sign, POSITIVE);
    for (int i = 0; i < MAX_MANTISSA_LEN; ++i)
    {
        int m_el = num.mantissa[i];
        switch (i % 2)
        {
            case 0:
                ck_assert_int_eq(m_el, 1);
                break;
            case 1:
                ck_assert_int_eq(m_el, 2);
                break;
            default:
                ck_assert(FALSE);
        }
    }
    ck_assert_int_eq(num.power, 40);
}
END_TEST

START_TEST(pt_stbd_int_max_power_len)
{
    big_decimal_t num;
    int rc = str_to_big_decimal("1.2E12121", &num);

    ck_assert_int_eq(rc, OKAY);
    ck_assert_int_eq(num.mantissa_sign, POSITIVE);
    for (int i = 0; i < MAX_MANTISSA_LEN; ++i)
    {
        int m_el = num.mantissa[i];
        switch (i)
        {
            case 0:
                ck_assert_int_eq(m_el, 1);
                break;
            case 1:
                ck_assert_int_eq(m_el, 2);
                break;
            default:
                ck_assert_int_eq(m_el, 0);
        }
    }
    ck_assert_int_eq(num.power, 12122);
}
END_TEST

START_TEST(pt_stbd_power_with_plus)
{
    big_decimal_t num;
    int rc = str_to_big_decimal("1.2E+1", &num);

    ck_assert_int_eq(rc, OKAY);
    ck_assert_int_eq(num.mantissa_sign, POSITIVE);
    for (int i = 0; i < MAX_MANTISSA_LEN; ++i)
    {
        int m_el = num.mantissa[i];
        switch (i)
        {
            case 0:
                ck_assert_int_eq(m_el, 1);
                break;
            case 1:
                ck_assert_int_eq(m_el, 2);
                break;
            default:
                ck_assert_int_eq(m_el, 0);
        }
    }
    ck_assert_int_eq(num.power, 2);
}
END_TEST

START_TEST(pt_stbd_power_with_minus)
{
    big_decimal_t num;
    int rc = str_to_big_decimal("1.2E-1", &num);

    ck_assert_int_eq(rc, OKAY);
    ck_assert_int_eq(num.mantissa_sign, POSITIVE);
    for (int i = 0; i < MAX_MANTISSA_LEN; ++i)
    {
        int m_el = num.mantissa[i];
        switch (i)
        {
            case 0:
                ck_assert_int_eq(m_el, 1);
                break;
            case 1:
                ck_assert_int_eq(m_el, 2);
                break;
            default:
                ck_assert_int_eq(m_el, 0);
        }
    }
    ck_assert_int_eq(num.power, 0);
}
END_TEST

Suite *create_str_to_big_decimal_suite(void)
{
    Suite *suite;
    TCase *tcase_neg;
    TCase *tcase_pos;

    suite = suite_create("str_to_big_decimal");
    // Negative tests
    tcase_neg = tcase_create("negative");

    tcase_add_test(tcase_neg, nt_stbd_max_power_len_exceeded);

    suite_add_tcase(suite, tcase_neg);

    // Positive tests
    tcase_pos = tcase_create("positive");

    tcase_add_test(tcase_pos, pt_stbd_num);
    tcase_add_test(tcase_pos, pt_stbd_num_with_plus);
    tcase_add_test(tcase_pos, pt_stbd_num_with_minus);
    tcase_add_test(tcase_pos, pt_stbd_num_without_integer_part);
    tcase_add_test(tcase_pos, pt_stbd_num_without_integer_part_with_minus);
    tcase_add_test(tcase_pos, pt_stbd_num_without_integral_part);
    tcase_add_test(tcase_pos, pt_stbd_num_without_integral_part_with_minus);
    tcase_add_test(tcase_pos, pt_stbd_int);
    tcase_add_test(tcase_pos, pt_stbd_int_with_minus);
    tcase_add_test(tcase_pos, pt_stbd_int_with_power);
    tcase_add_test(tcase_pos, pt_stbd_int_max_mantissa_len);
    tcase_add_test(tcase_pos, pt_stbd_int_max_power_len);
    tcase_add_test(tcase_pos, pt_stbd_power_with_plus);
    tcase_add_test(tcase_pos, pt_stbd_power_with_minus);

    suite_add_tcase(suite, tcase_pos);

    return suite;
}
