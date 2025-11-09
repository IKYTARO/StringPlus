#include <stdio.h>

#include "../../my_string.h"
#include "sprintf_tests.h"

START_TEST(test_float_basic_cases) {
    char my_buff[100], std_buff[100];

    my_sprintf(my_buff, "Basic: %f %f %f", 3.14159, -2.71828, 0.0);
    sprintf(std_buff, "Basic: %f %f %f", 3.14159, -2.71828, 0.0);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(test_float_precision_control) {
    char my_buff[100], std_buff[100];

    my_sprintf(my_buff, "Precision: %.2f %.0f %.5f %.10f", 3.14159, 2.5, 1.23456, 0.123456789);
    sprintf(std_buff, "Precision: %.2f %.0f %.5f %.10f", 3.14159, 2.5, 1.23456, 0.123456789);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(test_float_width_alignment) {
    char my_buff[100], std_buff[100];

    my_sprintf(my_buff, "Width: %8.2f %-8.2f %10.3f", 3.14, 3.14, -123.456);
    sprintf(std_buff, "Width: %8.2f %-8.2f %10.3f", 3.14, 3.14, -123.456);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(test_float_sign_flags) {
    char my_buff[100], std_buff[100];

    my_sprintf(my_buff, "Sign: %+f % f %+8.2f % 8.2f", 3.14, 3.14, 3.14, 3.14);
    sprintf(std_buff, "Sign: %+f % f %+8.2f % 8.2f", 3.14, 3.14, 3.14, 3.14);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(test_float_zero_hash_flags) {
    char my_buff[100], std_buff[100];

    my_sprintf(my_buff, "Flags: '%08.2f' '%#.0f' '%#.2f' '%08.0f'", 3.14, 3.0, 3.0, 42.7);
    sprintf(std_buff, "Flags: '%08.2f' '%#.0f' '%#.2f' '%08.0f'", 3.14, 3.0, 3.0, 42.7);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(test_float_complex_combinations) {
    char my_buff[100], std_buff[100];

    my_sprintf(my_buff, "Complex: '%-+10.3f' '% 08.2f' '%#.0f'", 123.4567, -45.67, 99.0);
    sprintf(std_buff, "Complex: '%-+10.3f' '% 08.2f' '%#.0f'", 123.4567, -45.67, 99.0);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(test_float_special_values) {
    char my_buff[100], std_buff[100];
    double nan_val = NAN;
    double inf_val = INFINITY;
    double neg_inf_val = -INFINITY;

    my_sprintf(my_buff, "Special: %f %f %f", nan_val, inf_val, neg_inf_val);
    sprintf(std_buff, "Special: %f %f %f", nan_val, inf_val, neg_inf_val);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(test_float_large_numbers) {
    char my_buff[100], std_buff[100];

    my_sprintf(my_buff, "Large: %.2f %.2f", 123456789.123, -987654321.987);
    sprintf(std_buff, "Large: %.2f %.2f", 123456789.123, -987654321.987);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(test_float_long_double) {
    char my_buff[100], std_buff[100];
    long double value = 3.141592653589793238L;

    int my_res = my_sprintf(my_buff, "Long: %.10Lf", value);
    int std_res = sprintf(std_buff, "Long: %.10Lf", value);
    ck_assert_int_eq(my_res, std_res);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(test_float_edge_cases) {
    char my_buff[100], std_buff[100];

    my_sprintf(my_buff, "Edge: '%.0f' '%.1f' '%.0f'", 0.999, 0.999, 0.499999);
    sprintf(std_buff, "Edge: '%.0f' '%.1f' '%.0f'", 0.999, 0.999, 0.499999);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

TCase *tcase_float(void) {
    TCase *tc_float = tcase_create("TCase float");
    tcase_add_test(tc_float, test_float_basic_cases);
    tcase_add_test(tc_float, test_float_precision_control);
    tcase_add_test(tc_float, test_float_width_alignment);
    tcase_add_test(tc_float, test_float_sign_flags);
    tcase_add_test(tc_float, test_float_zero_hash_flags);
    tcase_add_test(tc_float, test_float_complex_combinations);
    tcase_add_test(tc_float, test_float_special_values);
    tcase_add_test(tc_float, test_float_large_numbers);
    tcase_add_test(tc_float, test_float_long_double);
    tcase_add_test(tc_float, test_float_edge_cases);

    return tc_float;
}