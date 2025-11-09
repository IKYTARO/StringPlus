#include <stdio.h>

#include "../../my_string.h"
#include "sprintf_tests.h"

START_TEST(test_exponent_basic_cases) {
    char my_buff[100], std_buff[100];

    my_sprintf(my_buff, "Basic: %e %E", 123.456, 123.456);
    sprintf(std_buff, "Basic: %e %E", 123.456, 123.456);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(test_exponent_precision_control) {
    char my_buff[100], std_buff[100];

    my_sprintf(my_buff, "Precision: %.2e %.4E %.0e", 123.456, 0.00123, 99.999);
    sprintf(std_buff, "Precision: %.2e %.4E %.0e", 123.456, 0.00123, 99.999);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(test_exponent_width_alignment) {
    char my_buff[100], std_buff[100];

    my_sprintf(my_buff, "Width: %12e %-12E %10e", 123.456, 123.456, -0.000789);
    sprintf(std_buff, "Width: %12e %-12E %10e", 123.456, 123.456, -0.000789);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(test_exponent_sign_flags) {
    char my_buff[100], std_buff[100];

    my_sprintf(my_buff, "Sign: %+e % E %+E", 123.456, 123.456, -123.456);
    sprintf(std_buff, "Sign: %+e % E %+E", 123.456, 123.456, -123.456);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(test_exponent_zero_hash_flags) {
    char my_buff[100], std_buff[100];

    my_sprintf(my_buff, "Flags: %015e %#.0e %#.0E", 123.456, 123.456, 100.0);
    sprintf(std_buff, "Flags: %015e %#.0e %#.0E", 123.456, 123.456, 100.0);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(test_exponent_small_large_numbers) {
    char my_buff[100], std_buff[100];

    my_sprintf(my_buff, "Range: %.2e %.2e %.2E", 0.0000123, 1234567.89, 0.0000001);
    sprintf(std_buff, "Range: %.2e %.2e %.2E", 0.0000123, 1234567.89, 0.0000001);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(test_exponent_complex_combinations) {
    char my_buff[100], std_buff[100];

    my_sprintf(my_buff, "Complex: %-+12.3e % 010.2E", 123.4567, -45.678);
    sprintf(std_buff, "Complex: %-+12.3e % 010.2E", 123.4567, -45.678);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(test_exponent_special_values) {
    char my_buff[100], std_buff[100];
    double nan_val = NAN;
    double inf_val = INFINITY;
    double neg_inf_val = -INFINITY;

    my_sprintf(my_buff, "Special: %e %E %e", nan_val, inf_val, neg_inf_val);
    sprintf(std_buff, "Special: %e %E %e", nan_val, inf_val, neg_inf_val);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(test_exponent_zero) {
    char my_buff[100], std_buff[100];

    my_sprintf(my_buff, "Zero: %e %E %.0e", 0.0, -0.0, 0.0);
    sprintf(std_buff, "Zero: %e %E %.0e", 0.0, -0.0, 0.0);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(test_exponent_edge_rounding) {
    char my_buff[100], std_buff[100];

    my_sprintf(my_buff, "Round: %.2e %.2e %.1e", 9.999, 0.0999, 9.95);
    sprintf(std_buff, "Round: %.2e %.2e %.1e", 9.999, 0.0999, 9.95);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

TCase *tcase_exponent(void) {
    TCase *tc_exponent = tcase_create("TCase exponent");
    tcase_add_test(tc_exponent, test_exponent_basic_cases);
    tcase_add_test(tc_exponent, test_exponent_precision_control);
    tcase_add_test(tc_exponent, test_exponent_width_alignment);
    tcase_add_test(tc_exponent, test_exponent_sign_flags);
    tcase_add_test(tc_exponent, test_exponent_zero_hash_flags);
    tcase_add_test(tc_exponent, test_exponent_small_large_numbers);
    tcase_add_test(tc_exponent, test_exponent_complex_combinations);
    tcase_add_test(tc_exponent, test_exponent_special_values);
    tcase_add_test(tc_exponent, test_exponent_zero);
    tcase_add_test(tc_exponent, test_exponent_edge_rounding);

    return tc_exponent;
}