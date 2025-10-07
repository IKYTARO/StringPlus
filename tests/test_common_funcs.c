#include "test.h"
#include "../my_string.h"

START_TEST(test_strlen_basic) {
    ck_assert_int_eq(my_strlen(""), 0);
    ck_assert_int_eq(my_strlen("12"), 0);
    ck_assert_int_eq(my_strlen("hello"), 5);
    ck_assert_int_eq(my_strlen("veryVeryVeryLongWord"), 20);
}
END_TEST

START_TEST(test_strlen_with_spaces) {
    ck_assert_int_eq(my_strlen("hello world"), 11);
    ck_assert_int_eq(my_strlen("  "), 2);
    ck_assert_int_eq(my_strlen("a, \t, c, d  "), 12);
}
END_TEST

START_TEST(test_strncmp_equal) {
    ck_assert_int_eq(my_strncmp("hello", "hello", 5), 0);
    ck_assert_int_eq(my_strncmp("abc", "abc", 3), 0);
    ck_assert_int_eq(my_strncmp("first second \t third", "first second \t third", 20), 0);
}
END_TEST

START_TEST(test_strncmp_different) {
    ck_assert_int_lt(my_strncmp("apple", "banana", 5), 0);
    ck_assert_int_gt(my_strncmp("banana", "apple", 5), 0);
}
END_TEST

START_TEST(test_strncpy_basic) {
    char dest[10];
    my_strncpy(dest, "hello", 6);
    ck_assert_str_eq(dest, "hello");
}
END_TEST

START_TEST(test_strncpy_partial) {
    char dest[5] = "xxxxx";
    my_strncpy(dest, "hello world", 4);
    dest[4] = '\0';
    ck_assert_str_eq(dest, "hell");
}
END_TEST

Suite *test_common_functions(void) {
    TCase *tc_strlen = tcase_create("Strlen tests");
    tcase_add_test(tc_strlen, test_strlen_basic);
    tcase_add_test(tc_strlen, test_strlen_with_spaces);

    TCase *tc_strncmp = tcase_create("Strncmp tests");
    tcase_add_test(tc_strncmp, test_strncmp_different);
    tcase_add_test(tc_strncmp, test_strncmp_equal);

    TCase *tc_strncpy = tcase_create("Strncpy tests");
    tcase_add_test(tc_strncpy, test_strncpy_basic);
    tcase_add_test(tc_strncpy, test_strncpy_partial);

    Suite *common_funcs_suite = suite_create("Common Suite");
    suite_add_tcase(common_funcs_suite, tc_strlen);
    suite_add_tcase(common_funcs_suite, tc_strncmp);
    suite_add_tcase(common_funcs_suite, tc_strncpy);

    return common_funcs_suite;
}