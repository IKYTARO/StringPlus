#include <stdio.h>

#include "../../my_string.h"
#include "sprintf_tests.h"

START_TEST(test_string_basic_cases) {
    char my_buff[100], std_buff[100];

    my_sprintf(my_buff, "Basic: %s %s %s", "hello", "world", "test");
    sprintf(std_buff, "Basic: %s %s %s", "hello", "world", "test");
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(test_string_width_precision) {
    char my_buff[100], std_buff[100];

    my_sprintf(my_buff, "WP: '%8s' '%-8s' '%.3s' '%10.5s'", "hello", "world", "testing", "longstring");
    sprintf(std_buff, "WP: '%8s' '%-8s' '%.3s' '%10.5s'", "hello", "world", "testing", "longstring");
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(test_string_null_and_empty) {
    char my_buff[100], std_buff[100];
    char *null_str = NULL;

    my_sprintf(my_buff, "Null: '%s' '%5s'", null_str, "");
    sprintf(std_buff, "Null: '%s' '%5s'", "(null)", "");
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(test_string_complex_format) {
    char my_buff[100], std_buff[100];

    my_sprintf(my_buff, "Complex: '%-10.3s' '%5.2s' '%-5.10s'", "hello", "world", "test");
    sprintf(std_buff, "Complex: '%-10.3s' '%5.2s' '%-5.10s'", "hello", "world", "test");
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(test_string_special_chars) {
    char my_buff[100], std_buff[100];

    my_sprintf(my_buff, "Special: %s %s", "line1\nline2", "tab\tspace");
    sprintf(std_buff, "Special: %s %s", "line1\nline2", "tab\tspace");
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(test_string_long_strings) {
    char my_buff[200], std_buff[200];
    char long_str[] = "This is a very long string that should be handled correctly";

    my_sprintf(my_buff, "Long: '%.20s' '%-30.10s'", long_str, long_str);
    sprintf(std_buff, "Long: '%.20s' '%-30.10s'", long_str, long_str);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

TCase *tcase_string(void) {
    TCase *tc_string = tcase_create("TCase string");
    tcase_add_test(tc_string, test_string_basic_cases);
    tcase_add_test(tc_string, test_string_width_precision);
    tcase_add_test(tc_string, test_string_null_and_empty);
    tcase_add_test(tc_string, test_string_complex_format);
    tcase_add_test(tc_string, test_string_special_chars);
    tcase_add_test(tc_string, test_string_long_strings);

    return tc_string;
}