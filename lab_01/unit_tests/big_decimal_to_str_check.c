#include "big_decimal_to_str_check.h"

START_TEST(pt_bdts_default_num)
{
    big_decimal_t num;
    int rc = str_to_big_decimal("123.45E10", &num);
    ck_assert_int_eq(rc, OKAY);

    char res_str[MAX_OUTPUT_STR_LEN + 1];
    big_decimal_to_str(num, res_str);

    ck_assert_str_eq(res_str, "0.12345E13");
}
END_TEST

START_TEST(pt_bdts_default_negative_num)
{
    big_decimal_t num;
    int rc = str_to_big_decimal("-123.45E10", &num);
    ck_assert_int_eq(rc, OKAY);

    char res_str[MAX_OUTPUT_STR_LEN + 1];
    big_decimal_to_str(num, res_str);

    ck_assert_str_eq(res_str, "-0.12345E13");
}
END_TEST

START_TEST(pt_bdts_zero)
{
    big_decimal_t num;
    int rc = str_to_big_decimal("0.E10", &num);
    ck_assert_int_eq(rc, OKAY);

    char res_str[MAX_OUTPUT_STR_LEN + 1];
    big_decimal_to_str(num, res_str);

    ck_assert_str_eq(res_str, "0.0E0");
}
END_TEST

START_TEST(pt_bdts_minus_zero)
{
    big_decimal_t num;
    int rc = str_to_big_decimal("-0.E10", &num);
    ck_assert_int_eq(rc, OKAY);

    char res_str[MAX_OUTPUT_STR_LEN + 1];
    big_decimal_to_str(num, res_str);

    ck_assert_str_eq(res_str, "0.0E0");
}
END_TEST



Suite *create_big_decimal_to_str_suite(void)
{
    Suite *s;
    TCase *tcase_pos;

    s = suite_create("big_decimal_to_str");
    
    tcase_pos = tcase_create("positive");

    tcase_add_test(tcase_pos, pt_bdts_default_num);
    tcase_add_test(tcase_pos, pt_bdts_default_negative_num);
    tcase_add_test(tcase_pos, pt_bdts_zero);
    tcase_add_test(tcase_pos, pt_bdts_minus_zero);
    
    suite_add_tcase(s, tcase_pos);

    return s;
}

