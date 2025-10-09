#include "test.h"
#include "../my_string.h"

#include <string.h>

START_TEST(test_strlen_basic) {
    ck_assert_int_eq(my_strlen(""), 0);
    ck_assert_int_eq(my_strlen("12"), 2);
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
    ck_assert_int_eq(my_strncmp("hello", "hello", 5), strncmp("hello", "hello", 5));
    ck_assert_int_eq(my_strncmp("test", "test", 4), strncmp("test", "test", 4));
    ck_assert_int_eq(my_strncmp("", "", 1), strncmp("", "", 1));
    ck_assert_int_eq(my_strncmp("hello", "hello", 3), strncmp("hello", "hello", 3));
    ck_assert_int_eq(my_strncmp("abcdef", "abcdef", 0), strncmp("abcdef", "abcdef", 0));
}
END_TEST

START_TEST(test_strncmp_different) {
    ck_assert_int_eq(my_strncmp("apple", "banana", 5), strncmp("apple", "banana", 5));
    ck_assert_int_eq(my_strncmp("banana", "apple", 5), strncmp("banana", "apple", 5));
    ck_assert_int_eq(my_strncmp("hello", "world", 3), strncmp("hello", "world", 3));
    ck_assert_int_eq(my_strncmp("hello", "world", 0), strncmp("hello", "world", 0));
    ck_assert_int_eq(my_strncmp("abc", "def", 0), strncmp("abc", "def", 0));
    ck_assert_int_eq(my_strncmp("", "", 0), strncmp("", "", 0));
    ck_assert_int_eq(my_strncmp("abcdef", "abcxyz", 3), strncmp("abcdef", "abcxyz", 3));
    ck_assert_int_eq(my_strncmp("abcdef", "abcxyz", 4), strncmp("abcdef", "abcxyz", 4));
    ck_assert_int_eq(my_strncmp("hello", "help", 4), strncmp("hello", "help", 4));
    ck_assert_int_eq(my_strncmp("test1", "test2", 5), strncmp("test1", "test2", 5));
}
END_TEST

START_TEST(test_strncmp_lengths) {
    ck_assert_int_eq(my_strncmp("hi", "hello", 5), strncmp("hi", "hello", 5));
    ck_assert_int_eq(my_strncmp("hello", "hi", 5), strncmp("hello", "hi", 5));
    ck_assert_int_eq(my_strncmp("abc", "abcd", 4), strncmp("abc", "abcd", 4));
    ck_assert_int_eq(my_strncmp("abcd", "abc", 4), strncmp("abcd", "abc", 4));
    ck_assert_int_eq(my_strncmp("a\0b", "a\0c", 3), strncmp("a\0b", "a\0c", 3));
    ck_assert_int_eq(my_strncmp("\xFF\xFE", "\xFF\xFE", 2), strncmp("\xFF\xFE", "\xFF\xFE", 2));
    ck_assert_int_eq(my_strncmp("\x00\x01", "\x00\x02", 2), strncmp("\x00\x01", "\x00\x02", 2));
    ck_assert_int_eq(my_strncmp("café", "cafe", 4), strncmp("café", "cafe", 4));
    ck_assert_int_eq(my_strncmp("привет", "пока", 2), strncmp("привет", "пока", 2));
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
    tcase_add_test(tc_strncmp, test_strncmp_lengths);

    TCase *tc_strncpy = tcase_create("Strncpy tests");
    tcase_add_test(tc_strncpy, test_strncpy_basic);
    tcase_add_test(tc_strncpy, test_strncpy_partial);

    Suite *common_funcs_suite = suite_create("Common Suite");
    suite_add_tcase(common_funcs_suite, tc_strlen);
    suite_add_tcase(common_funcs_suite, tc_strncmp);
    suite_add_tcase(common_funcs_suite, tc_strncpy);

    return common_funcs_suite;
}