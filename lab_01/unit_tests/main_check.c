#include <check.h>

#include "check_str_check.h"
#include "str_to_big_decimal_check.h"
#include "big_decimal_to_str_check.h"
#include "big_decimal_multiplication_check.h"

int main(void)
{
    int num_failed = 0;
    Suite *s;
    SRunner *runner;

    s = create_check_str_suite();

    runner = srunner_create(s);
    srunner_run_all(runner, CK_VERBOSE);
    num_failed += srunner_ntests_failed(runner);
    srunner_free(runner);

    printf("\n");
    s = create_str_to_big_decimal_suite();

    runner = srunner_create(s);
    srunner_run_all(runner, CK_VERBOSE);
    num_failed += srunner_ntests_failed(runner);
    srunner_free(runner);

    printf("\n");
    s = create_big_decimal_to_str_suite();

    runner = srunner_create(s);
    srunner_run_all(runner, CK_VERBOSE);
    num_failed += srunner_ntests_failed(runner);
    srunner_free(runner);

    printf("\n");
    s = create_big_decimal_multiplication_suite();

    runner = srunner_create(s);
    srunner_run_all(runner, CK_VERBOSE);
    num_failed += srunner_ntests_failed(runner);
    srunner_free(runner);

    return (0 == num_failed) ? 0 : -1;
}
