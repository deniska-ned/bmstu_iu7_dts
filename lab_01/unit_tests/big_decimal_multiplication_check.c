#include "big_decimal_multiplication_check.h"

// Negative tests

START_TEST(nt_bdm_product_power_len_exceeded)
{
    int rc;
    big_decimal_t num_1, num_2, product;

    rc = str_to_big_decimal("0.12E99999", &num_1);
    ck_assert_int_eq(rc, OKAY);

    rc = str_to_big_decimal("2E99998", &num_2);
    ck_assert_int_eq(rc, OKAY);
    
    rc = big_decimal_multiplication(num_1, num_2, &product);

    ck_assert_int_eq(rc, PRODUCT_POWER_LEN_EXCEEDED);
}
END_TEST

START_TEST(nt_bdm_product_power_len_exceeded_2)
{
    int rc;
    big_decimal_t num_1, num_2, product;

    rc = str_to_big_decimal("0.12E-99999", &num_1);
    ck_assert_int_eq(rc, OKAY);

    rc = str_to_big_decimal("2E-99999", &num_2);
    ck_assert_int_eq(rc, OKAY);
    
    rc = big_decimal_multiplication(num_1, num_2, &product);

    ck_assert_int_eq(rc, PRODUCT_POWER_LEN_EXCEEDED);
}
END_TEST


// Positive tests

START_TEST(pt_bdm_default)
{
    int rc;
    big_decimal_t num_1, num_2, product;

    rc = str_to_big_decimal("0.12", &num_1);
    ck_assert_int_eq(rc, OKAY);

    rc = str_to_big_decimal("2", &num_2);
    ck_assert_int_eq(rc, OKAY);
    
    rc = big_decimal_multiplication(num_1, num_2, &product);

    ck_assert_int_eq(rc, OKAY);

    ck_assert_int_eq(product.mantissa_sign, POSITIVE);

    
    ck_assert_int_eq(product.mantissa[0], 2);
    ck_assert_int_eq(product.mantissa[1], 4);

    for (int i = 2; i < MAX_MANTISSA_LEN; ++i)
        ck_assert_int_eq(product.mantissa[i], 0);

    ck_assert_int_eq(product.power, 0);
}
END_TEST

START_TEST(pt_bdm_zero)
{
    int rc;
    big_decimal_t num_1, num_2, product;

    rc = str_to_big_decimal("0", &num_1);
    ck_assert_int_eq(rc, OKAY);

    rc = str_to_big_decimal("123E10", &num_2);
    ck_assert_int_eq(rc, OKAY);
    
    rc = big_decimal_multiplication(num_1, num_2, &product);

    ck_assert_int_eq(rc, OKAY);
    ck_assert(is_big_decimal_zero(product));
}
END_TEST

Suite *create_big_decimal_multiplication_suite(void)
{
    Suite *s;
    TCase *tcase_pos;
    TCase *tcase_neg;

    s = suite_create("big_decimal_multiplication");

    tcase_neg = tcase_create("negative");

    tcase_add_test(tcase_neg, nt_bdm_product_power_len_exceeded);
    tcase_add_test(tcase_neg, nt_bdm_product_power_len_exceeded_2);

    suite_add_tcase(s, tcase_neg);
    
    tcase_pos = tcase_create("positive");

    tcase_add_test(tcase_pos, pt_bdm_default);
    tcase_add_test(tcase_pos, pt_bdm_zero);

    suite_add_tcase(s, tcase_pos);

    return s;
}
