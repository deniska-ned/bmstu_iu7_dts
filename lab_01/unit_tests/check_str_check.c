#include "check_str_check.h"

// Negative tests

START_TEST(ng_cs_incorrect_sign_position_mantissa)
{
    int rc = check_str("12+3.34E10");

    ck_assert_int_eq(rc, INCORRECT_SIGN_POSITION);
}
END_TEST

START_TEST(ng_cs_incorrect_sign_position_power)
{
    int rc = check_str("123.34E1-0");

    ck_assert_int_eq(rc, INCORRECT_SIGN_POSITION);
}
END_TEST

START_TEST(ng_cs_dot_in_power_found)
{
    int rc = check_str("123E1.0");

    ck_assert_int_eq(rc, DOT_IN_POWER_FOUND);
}
END_TEST

START_TEST(ng_cs_incorrect_dot_count)
{
    int rc = check_str("1.23.34E10");

    ck_assert_int_eq(rc, INCORRECT_DOT_COUNT);
}
END_TEST

START_TEST(ng_cs_incorrect_e_count)
{
    int rc = check_str("123.E34E10");

    ck_assert_int_eq(rc, INCORRECT_E_COUNT);
}
END_TEST

START_TEST(ng_cs_incorrect_symbol)
{
    int rc = check_str("123i.34E10");

    ck_assert_int_eq(rc, INCORRECT_SYMBOL);
}
END_TEST

START_TEST(ng_cs_absence_of_mantissa)
{
    int rc = check_str(".E10");

    ck_assert_int_eq(rc, ABSENCE_OF_MANTISSA);
}
END_TEST

START_TEST(ng_cs_max_mantissa_len_exceeded)
{
    int rc = check_str("12345678901234567890123.45678901E10");

    ck_assert_int_eq(rc, MAX_MANTISSA_LEN_EXCEEDED);
}
END_TEST

START_TEST(ng_cs_absence_of_expected_power)
{
    int rc = check_str("123.34E");

    ck_assert_int_eq(rc, ABSENCE_OF_EXPECTED_POWER);
}
END_TEST

START_TEST(ng_cs_max_power_len_exceeded)
{
    int rc = check_str("123.34E123456");

    ck_assert_int_eq(rc, MAX_POWER_LEN_EXCEEDED);
}
END_TEST

// Positive tests

START_TEST(pt_cs_num_record)
{
    int rc = check_str("123.45E10");

    ck_assert_int_eq(rc, OKAY);
}
END_TEST

START_TEST(pt_cs_num_record_with_plus)
{
    int rc = check_str("+123.45E10");

    ck_assert_int_eq(rc, OKAY);
}
END_TEST

START_TEST(pt_cs_num_record_with_minus)
{
    int rc = check_str("-123.45E10");

    ck_assert_int_eq(rc, OKAY);
}
END_TEST

START_TEST(pt_cs_num_record_without_integer_part)
{
    int rc = check_str(".45E10");

    ck_assert_int_eq(rc, OKAY);
}
END_TEST

START_TEST(pt_cs_num_record_without_integer_part_with_minus)
{
    int rc = check_str("-.45E10");

    ck_assert_int_eq(rc, OKAY);
}
END_TEST

START_TEST(pt_cs_num_record_without_integral_part)
{
    int rc = check_str("123.E10");

    ck_assert_int_eq(rc, OKAY);
}
END_TEST

START_TEST(pt_cs_num_record_without_integral_part_with_minus)
{
    int rc = check_str("-123.E10");

    ck_assert_int_eq(rc, OKAY);
}
END_TEST

START_TEST(pt_cs_int_num_with_power)
{
    int rc = check_str("123E10");

    ck_assert_int_eq(rc, OKAY);
}
END_TEST

START_TEST(pt_cs_int_num)
{
    int rc = check_str("123");

    ck_assert_int_eq(rc, OKAY);
}
END_TEST

START_TEST(pt_cs_int_num_with_minus)
{
    int rc = check_str("+123");

    ck_assert_int_eq(rc, OKAY);
}
END_TEST

START_TEST(pt_cs_max_mantissa_len)
{
    int rc = check_str("123456789012345678901234567890E10");

    ck_assert_int_eq(rc, OKAY);
}
END_TEST

START_TEST(pt_cs_max_power_len)
{
    int rc = check_str("123.45E12345");

    ck_assert_int_eq(rc, OKAY);
}
END_TEST

START_TEST(pt_cs_power_with_plus)
{
    int rc = check_str("123.45E+10");

    ck_assert_int_eq(rc, OKAY);
}
END_TEST

START_TEST(pt_cs_power_with_minus)
{
    int rc = check_str("123.45E-10");

    ck_assert_int_eq(rc, OKAY);
}
END_TEST


Suite *create_check_str_suite(void)
{
    Suite* suite;
    TCase *tcase_neg;
    TCase *tcase_pos;

    suite = suite_create("check_str");

    // Negative tests
    tcase_neg = tcase_create("negative");

    tcase_add_test(tcase_neg, ng_cs_incorrect_sign_position_mantissa);
    tcase_add_test(tcase_neg, ng_cs_incorrect_sign_position_power);
    tcase_add_test(tcase_neg, ng_cs_dot_in_power_found);
    tcase_add_test(tcase_neg, ng_cs_incorrect_dot_count);
    tcase_add_test(tcase_neg, ng_cs_incorrect_e_count);
    tcase_add_test(tcase_neg, ng_cs_incorrect_symbol);
    tcase_add_test(tcase_neg, ng_cs_absence_of_mantissa);
    tcase_add_test(tcase_neg, ng_cs_max_mantissa_len_exceeded);
    tcase_add_test(tcase_neg, ng_cs_absence_of_expected_power);
    tcase_add_test(tcase_neg, ng_cs_max_power_len_exceeded);

    suite_add_tcase(suite, tcase_neg);

    // Positive tests
    tcase_pos = tcase_create("positive");

    tcase_add_test(tcase_pos, pt_cs_num_record);
    tcase_add_test(tcase_pos, pt_cs_num_record_with_plus);
    tcase_add_test(tcase_pos, pt_cs_num_record_with_minus);
    tcase_add_test(tcase_pos, pt_cs_num_record_without_integer_part);
    tcase_add_test(tcase_pos, pt_cs_num_record_without_integer_part_with_minus);
    tcase_add_test(tcase_pos, pt_cs_num_record_without_integral_part);
    tcase_add_test(tcase_pos, pt_cs_num_record_without_integral_part_with_minus);
    tcase_add_test(tcase_pos, pt_cs_int_num_with_power);
    tcase_add_test(tcase_pos, pt_cs_int_num);
    tcase_add_test(tcase_pos, pt_cs_int_num_with_minus);
    tcase_add_test(tcase_pos, pt_cs_max_mantissa_len);
    tcase_add_test(tcase_pos, pt_cs_max_power_len);
    tcase_add_test(tcase_pos, pt_cs_power_with_plus);
    tcase_add_test(tcase_pos, pt_cs_power_with_minus);

    suite_add_tcase(suite, tcase_pos);

    return suite;
}
