#include <string.h>

#include "../my_string.h"
#include "test.h"

START_TEST(test_strstr_basic) {
    const char *haystack = "Hello, world!";
    const char *needle = "world";
    ck_assert_str_eq(my_strstr(haystack, needle), "world!");
}
END_TEST

START_TEST(test_strstr_start) {
    const char *haystack = "OpenAI creates ChatGPT";
    const char *needle = "OpenAI";
    ck_assert_str_eq(my_strstr(haystack, needle), "OpenAI creates ChatGPT");
}
END_TEST

START_TEST(test_strstr_end) {
    const char *haystack = "OpenAI creates ChatGPT";
    const char *needle = "ChatGPT";
    ck_assert_str_eq(my_strstr(haystack, needle), "ChatGPT");
}
END_TEST

START_TEST(test_strstr_not_found) {
    const char *haystack = "abcdef";
    const char *needle = "xyz";
    ck_assert_ptr_eq(my_strstr(haystack, needle), MY_NULL);
}
END_TEST

START_TEST(test_strstr_empty_needle) {
    const char *haystack = "abcdef";
    const char *needle = "";
    ck_assert_str_eq(my_strstr(haystack, needle), "abcdef");
}
END_TEST

START_TEST(test_strstr_empty_haystack) {
    const char *haystack = "";
    const char *needle = "abc";
    ck_assert_ptr_eq(my_strstr(haystack, needle), MY_NULL);
}
END_TEST

START_TEST(test_strstr_full_match) {
    const char *haystack = "abc";
    const char *needle = "abc";
    ck_assert_str_eq(my_strstr(haystack, needle), "abc");
}
END_TEST

Suite *suite_strstr(void) {
    TCase *tcase_strstr = tcase_create("TCase strstr");

    tcase_add_test(tcase_strstr, test_strstr_basic);
    tcase_add_test(tcase_strstr, test_strstr_start);
    tcase_add_test(tcase_strstr, test_strstr_end);
    tcase_add_test(tcase_strstr, test_strstr_not_found);
    tcase_add_test(tcase_strstr, test_strstr_empty_needle);
    tcase_add_test(tcase_strstr, test_strstr_empty_haystack);
    tcase_add_test(tcase_strstr, test_strstr_full_match);

    Suite *suite_strstr = suite_create("MY_STRSTR");
    suite_add_tcase(suite_strstr, tcase_strstr);

    return suite_strstr;
}
