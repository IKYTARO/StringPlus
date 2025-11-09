#include <limits.h>
#include <stdio.h>

#include "../../my_string.h"
#include "sprintf_tests.h"

START_TEST(test_integer_basic) {
    char my_buff[50], std_buff[50];

    int my_res = my_sprintf(my_buff, "Basic: %d", 42);
    int std_res = sprintf(std_buff, "Basic: %d", 42);
    ck_assert_str_eq(my_buff, std_buff);
    ck_assert_int_eq(my_res, std_res);
}
END_TEST

START_TEST(test_integer_negative) {
    char my_buff[50], std_buff[50];

    int my_res = my_sprintf(my_buff, "Negative: %d", -42);
    int std_res = sprintf(std_buff, "Negative: %d", -42);
    ck_assert_str_eq(my_buff, std_buff);
    ck_assert_int_eq(my_res, std_res);
}
END_TEST

START_TEST(test_integer_zero) {
    char my_buff[50], std_buff[50];

    int my_res = my_sprintf(my_buff, "Zero: %d", 0);
    int std_res = sprintf(std_buff, "Zero: %d", 0);
    ck_assert_str_eq(my_buff, std_buff);
    ck_assert_int_eq(my_res, std_res);
}
END_TEST

START_TEST(test_integer_left_align) {
    char my_buff[50], std_buff[50];

    int my_res = my_sprintf(my_buff, "Left: %-6d end", 42);
    int std_res = sprintf(std_buff, "Left: %-6d end", 42);
    ck_assert_str_eq(my_buff, std_buff);
    ck_assert_int_eq(my_res, std_res);
}
END_TEST

START_TEST(test_integer_zero_padding) {
    char my_buff[50], std_buff[50];

    int my_res = my_sprintf(my_buff, "Zero pad: %05d", 42);
    int std_res = sprintf(std_buff, "Zero pad: %05d", 42);
    ck_assert_str_eq(my_buff, std_buff);
    ck_assert_int_eq(my_res, std_res);
}
END_TEST

START_TEST(test_integer_zero_with_negative) {
    char my_buff[50], std_buff[50];

    int my_res = my_sprintf(my_buff, "Zero neg: %05d", -42);
    int std_res = sprintf(std_buff, "Zero neg: %05d", -42);
    ck_assert_str_eq(my_buff, std_buff);
    ck_assert_int_eq(my_res, std_res);
}
END_TEST

START_TEST(test_integer_plus_flag) {
    char my_buff[50], std_buff[50];

    int my_res = my_sprintf(my_buff, "Plus: %+d and %+d", 42, -42);
    int std_res = sprintf(std_buff, "Plus: %+d and %+d", 42, -42);
    ck_assert_str_eq(my_buff, std_buff);
    ck_assert_int_eq(my_res, std_res);
}
END_TEST

START_TEST(test_integer_space_flag) {
    char my_buff[50], std_buff[50];

    int my_res = my_sprintf(my_buff, "Space: % d and % d", 42, -42);
    int std_res = sprintf(std_buff, "Space: % d and % d", 42, -42);
    ck_assert_str_eq(my_buff, std_buff);
    ck_assert_int_eq(my_res, std_res);
}
END_TEST

START_TEST(test_integer_width_basic) {
    char my_buff[50], std_buff[50];

    int my_res = my_sprintf(my_buff, "Width: %5d", 42);
    int std_res = sprintf(std_buff, "Width: %5d", 42);
    ck_assert_str_eq(my_buff, std_buff);
    ck_assert_int_eq(my_res, std_res);
}
END_TEST

START_TEST(test_integer_width_large_number) {
    char my_buff[50], std_buff[50];

    int my_res = my_sprintf(my_buff, "Large: %10d", 123456789);
    int std_res = sprintf(std_buff, "Large: %10d", 123456789);
    ck_assert_str_eq(my_buff, std_buff);
    ck_assert_int_eq(my_res, std_res);
}
END_TEST

START_TEST(test_integer_width_negative) {
    char my_buff[50], std_buff[50];

    int my_res = my_sprintf(my_buff, "Width neg: %6d", -42);
    int std_res = sprintf(std_buff, "Width neg: %6d", -42);
    ck_assert_str_eq(my_buff, std_buff);
    ck_assert_int_eq(my_res, std_res);
}
END_TEST

START_TEST(test_integer_precision_basic) {
    char my_buff[50], std_buff[50];

    int my_res = my_sprintf(my_buff, "Prec: %.4d", 42);
    int std_res = sprintf(std_buff, "Prec: %.4d", 42);
    ck_assert_str_eq(my_buff, std_buff);
    ck_assert_int_eq(my_res, std_res);
}
END_TEST

START_TEST(test_integer_precision_zero) {
    char my_buff[50], std_buff[50];

    int my_res = my_sprintf(my_buff, "Prec zero: %.0d", 0);
    int std_res = sprintf(std_buff, "Prec zero: %.0d", 0);
    ck_assert_str_eq(my_buff, std_buff);
    ck_assert_int_eq(my_res, std_res);
}
END_TEST

START_TEST(test_integer_precision_negative) {
    char my_buff[50], std_buff[50];

    int my_res = my_sprintf(my_buff, "Prec neg: %.4d", -42);
    int std_res = sprintf(std_buff, "Prec neg: %.4d", -42);
    ck_assert_str_eq(my_buff, std_buff);
    ck_assert_int_eq(my_res, std_res);
}
END_TEST

START_TEST(test_integer_width_precision) {
    char my_buff[50], std_buff[50];

    int my_res = my_sprintf(my_buff, "Combo: %8.5d", 42);
    int std_res = sprintf(std_buff, "Combo: %8.5d", 42);
    ck_assert_str_eq(my_buff, std_buff);
    ck_assert_int_eq(my_res, std_res);
}
END_TEST

START_TEST(test_integer_width_precision_negative) {
    char my_buff[50], std_buff[50];

    int my_res = my_sprintf(my_buff, "Combo neg: %8.5d", -42);
    int std_res = sprintf(std_buff, "Combo neg: %8.5d", -42);
    ck_assert_str_eq(my_buff, std_buff);
    ck_assert_int_eq(my_res, std_res);
}
END_TEST

START_TEST(test_integer_precision_over_width) {
    char my_buff[50], std_buff[50];

    int my_res = my_sprintf(my_buff, "Over: %3.5d", 42);
    int std_res = sprintf(std_buff, "Over: %3.5d", 42);
    ck_assert_str_eq(my_buff, std_buff);
    ck_assert_int_eq(my_res, std_res);
}
END_TEST

START_TEST(test_integer_complex_flags) {
    char my_buff[50], std_buff[50];

    int my_res = my_sprintf(my_buff, "Complex: %-+8.5d", 42);
    int std_res = sprintf(std_buff, "Complex: %-+8.5d", 42);
    ck_assert_str_eq(my_buff, std_buff);
    ck_assert_int_eq(my_res, std_res);
}
END_TEST

START_TEST(test_integer_multiple_specifiers) {
    char my_buff[100], std_buff[100];

    int my_res = my_sprintf(my_buff, "Multi: %+-8.5d and % 3d cases %05d", 42, -7, 123);
    int std_res = sprintf(std_buff, "Multi: %+-8.5d and % 3d cases %05d", 42, -7, 123);
    ck_assert_str_eq(my_buff, std_buff);
    ck_assert_int_eq(my_res, std_res);
}
END_TEST

START_TEST(test_integer_mixed_flags) {
    char my_buff[100], std_buff[100];

    int my_res = my_sprintf(my_buff, "Mixed: %d %+d %-5d %.3d %5d", 1, 2, 3, 4, 5);
    int std_res = sprintf(std_buff, "Mixed: %d %+d %-5d %.3d %5d", 1, 2, 3, 4, 5);
    ck_assert_str_eq(my_buff, std_buff);
    ck_assert_int_eq(my_res, std_res);
}
END_TEST

START_TEST(test_integer_int_max) {
    char my_buff[50], std_buff[50];

    int my_res = my_sprintf(my_buff, "Max: %d", INT_MAX);
    int std_res = sprintf(std_buff, "Max: %d", INT_MAX);
    ck_assert_str_eq(my_buff, std_buff);
    ck_assert_int_eq(my_res, std_res);
}
END_TEST

START_TEST(test_integer_int_min) {
    char my_buff[50], std_buff[50];
    int min_value = INT_MIN;

    int my_res = my_sprintf(my_buff, "Min: %d", min_value);
    int std_res = sprintf(std_buff, "Min: %d", min_value);
    ck_assert_str_eq(my_buff, std_buff);
    ck_assert_int_eq(my_res, std_res);
}
END_TEST

START_TEST(test_integer_large_precision) {
    char my_buff[50], std_buff[50];

    int my_res = my_sprintf(my_buff, "Large prec: %.10d", 42);
    int std_res = sprintf(std_buff, "Large prec: %.10d", 42);
    ck_assert_str_eq(my_buff, std_buff);
    ck_assert_int_eq(my_res, std_res);
}
END_TEST

START_TEST(test_integer_empty_precision) {
    char my_buff[50], std_buff[50];

    int my_res = my_sprintf(my_buff, "Empty prec: %.d", 42);
    int std_res = sprintf(std_buff, "Empty prec: %.d", 42);
    ck_assert_str_eq(my_buff, std_buff);
    ck_assert_int_eq(my_res, std_res);
}
END_TEST

START_TEST(test_integer_only_percent) {
    char my_buff[50], std_buff[50];

    int my_res = my_sprintf(my_buff, "%d", 42);
    int std_res = sprintf(std_buff, "%d", 42);
    ck_assert_str_eq(my_buff, std_buff);
    ck_assert_int_eq(my_res, std_res);
}
END_TEST

START_TEST(test_integer_multiple_same) {
    char my_buff[100], std_buff[100];

    int my_res = my_sprintf(my_buff, "%d%d%d", 1, 2, 3);
    int std_res = sprintf(std_buff, "%d%d%d", 1, 2, 3);
    ck_assert_str_eq(my_buff, std_buff);
    ck_assert_int_eq(my_res, std_res);
}
END_TEST

START_TEST(test_integer_short) {
    char my_buff[100], std_buff[100];
    int value = 2345;

    int my_res = my_sprintf(my_buff, "%hd", (short)value);
    int std_res = sprintf(std_buff, "%hd", (short)value);
    ck_assert_int_eq(my_res, std_res);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(test_integer_long) {
    char my_buff[100], std_buff[100];
    int value = 2345;

    int my_res = my_sprintf(my_buff, "%ld", (long)value);
    int std_res = sprintf(std_buff, "%ld", (long)value);
    ck_assert_int_eq(my_res, std_res);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

TCase *tcase_integer(void) {
    TCase *tc_integer = tcase_create("TCase integer");
    tcase_add_test(tc_integer, test_integer_basic);
    tcase_add_test(tc_integer, test_integer_negative);
    tcase_add_test(tc_integer, test_integer_zero);
    tcase_add_test(tc_integer, test_integer_left_align);
    tcase_add_test(tc_integer, test_integer_zero_padding);
    tcase_add_test(tc_integer, test_integer_zero_with_negative);
    tcase_add_test(tc_integer, test_integer_plus_flag);
    tcase_add_test(tc_integer, test_integer_space_flag);
    tcase_add_test(tc_integer, test_integer_width_basic);
    tcase_add_test(tc_integer, test_integer_width_large_number);
    tcase_add_test(tc_integer, test_integer_width_negative);
    tcase_add_test(tc_integer, test_integer_precision_basic);
    tcase_add_test(tc_integer, test_integer_precision_zero);
    tcase_add_test(tc_integer, test_integer_precision_negative);
    tcase_add_test(tc_integer, test_integer_width_precision);
    tcase_add_test(tc_integer, test_integer_width_precision_negative);
    tcase_add_test(tc_integer, test_integer_precision_over_width);
    tcase_add_test(tc_integer, test_integer_complex_flags);
    tcase_add_test(tc_integer, test_integer_multiple_specifiers);
    tcase_add_test(tc_integer, test_integer_mixed_flags);
    tcase_add_test(tc_integer, test_integer_int_max);
    tcase_add_test(tc_integer, test_integer_int_min);
    tcase_add_test(tc_integer, test_integer_large_precision);
    tcase_add_test(tc_integer, test_integer_empty_precision);
    tcase_add_test(tc_integer, test_integer_only_percent);
    tcase_add_test(tc_integer, test_integer_multiple_same);
    tcase_add_test(tc_integer, test_integer_short);
    tcase_add_test(tc_integer, test_integer_long);

    return tc_integer;
}