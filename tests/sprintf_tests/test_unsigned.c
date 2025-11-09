#include <limits.h>
#include <stdio.h>

#include "../../my_string.h"
#include "sprintf_tests.h"

START_TEST(test_unsigned_basic_cases) {
    char my_buff[100], std_buff[100];

    int my_res = my_sprintf(my_buff, "Basic: %u %u %u", 123, 0, UINT_MAX);
    int std_res =
        sprintf(std_buff, "Basic: %u %u %u", (unsigned int)123, (unsigned int)0, (unsigned int)UINT_MAX);
    ck_assert_int_eq(my_res, std_res);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(test_unsigned_width_precision) {
    char my_buff[100], std_buff[100];

    int my_res = my_sprintf(my_buff, "WP: %5u %-5u %.3u %8.5u", 42, 42, 42, 42);
    int std_res = sprintf(std_buff, "WP: %5u %-5u %.3u %8.5u", (unsigned int)42, (unsigned int)42,
                          (unsigned int)42, (unsigned int)42);
    ck_assert_int_eq(my_res, std_res);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(test_unsigned_multiple_specifiers) {
    char my_buff[100], std_buff[100];

    int my_res = my_sprintf(my_buff, "Multi: %u %05u %-8.3u %u", 1, 2, 3, 999);
    int std_res = sprintf(std_buff, "Multi: %u %05u %-8.3u %u", (unsigned int)1, (unsigned int)2,
                          (unsigned int)3, (unsigned int)999);
    ck_assert_int_eq(my_res, std_res);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(test_unsigned_edge_cases) {
    char my_buff[100], std_buff[100];

    int my_res = my_sprintf(my_buff, "Edge: %.0u %u %.5u", 0, UINT_MAX - 1, 7);
    int std_res = sprintf(std_buff, "Edge: %.0u %u %.5u", (unsigned int)0, (unsigned int)(UINT_MAX - 1),
                          (unsigned int)7);
    ck_assert_int_eq(my_res, std_res);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(test_unsigned_large_values) {
    char my_buff[100], std_buff[100];
    unsigned large_val = 4294967290u;

    int my_res = my_sprintf(my_buff, "Large: %15u %-15u %.10u", large_val, large_val, large_val);
    int std_res = sprintf(std_buff, "Large: %15u %-15u %.10u", large_val, large_val, large_val);
    ck_assert_int_eq(my_res, std_res);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(test_unsigned_short) {
    char my_buff[100], std_buff[100];
    int value = 2345;

    int my_res = my_sprintf(my_buff, "%hu", (unsigned short)value);
    int std_res = sprintf(std_buff, "%hu", (unsigned short)value);
    ck_assert_int_eq(my_res, std_res);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(test_unsigned_long) {
    char my_buff[100], std_buff[100];
    int value = 2345;

    int my_res = my_sprintf(my_buff, "%lu", (unsigned long)value);
    int std_res = sprintf(std_buff, "%lu", (unsigned long)value);
    ck_assert_int_eq(my_res, std_res);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

TCase *tcase_unsigned(void) {
    TCase *tc_unsigned = tcase_create("TCase unsigned");
    tcase_add_test(tc_unsigned, test_unsigned_basic_cases);
    tcase_add_test(tc_unsigned, test_unsigned_width_precision);
    tcase_add_test(tc_unsigned, test_unsigned_multiple_specifiers);
    tcase_add_test(tc_unsigned, test_unsigned_edge_cases);
    tcase_add_test(tc_unsigned, test_unsigned_large_values);
    tcase_add_test(tc_unsigned, test_unsigned_short);
    tcase_add_test(tc_unsigned, test_unsigned_long);

    return tc_unsigned;
}