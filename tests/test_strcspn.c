#include <string.h>

#include "../my_string.h"
#include "test.h"

START_TEST(test_strcspn_middle) {
    const char *s1 = "abcdef";
    const char *s2 = "xdy";
    ck_assert_int_eq(my_strcspn(s1, s2), strcspn(s1, s2));
}
END_TEST

START_TEST(test_strcspn_start) {
    const char *s1 = "abcdef";
    const char *s2 = "a";
    ck_assert_int_eq(my_strcspn(s1, s2), strcspn(s1, s2));
}
END_TEST

START_TEST(test_strcspn_end) {
    const char *s1 = "abcdef";
    const char *s2 = "f";
    ck_assert_int_eq(my_strcspn(s1, s2), strcspn(s1, s2));
}
END_TEST

START_TEST(test_strcspn_no_match) {
    const char *s1 = "abcdef";
    const char *s2 = "xyz";
    ck_assert_int_eq(my_strcspn(s1, s2), strcspn(s1, s2));
}
END_TEST

START_TEST(test_strcspn_empty_str1) {
    const char *s1 = "";
    const char *s2 = "abc";
    ck_assert_int_eq(my_strcspn(s1, s2), strcspn(s1, s2));
}
END_TEST

START_TEST(test_strcspn_empty_str2) {
    const char *s1 = "abcdef";
    const char *s2 = "";
    ck_assert_int_eq(my_strcspn(s1, s2), strcspn(s1, s2));
}
END_TEST

START_TEST(test_strcspn_multiple_chars) {
    const char *s1 = "hello world";
    const char *s2 = "ow";
    ck_assert_int_eq(my_strcspn(s1, s2), strcspn(s1, s2));
}
END_TEST

START_TEST(test_strcspn_repeated_chars) {
    const char *s1 = "aaabbbccc";
    const char *s2 = "b";
    ck_assert_int_eq(my_strcspn(s1, s2), strcspn(s1, s2));
}
END_TEST

Suite *suite_strcspn(void) {
    TCase *tcase_strcspn = tcase_create("TCase strcspn");

    tcase_add_test(tcase_strcspn, test_strcspn_middle);
    tcase_add_test(tcase_strcspn, test_strcspn_start);
    tcase_add_test(tcase_strcspn, test_strcspn_end);
    tcase_add_test(tcase_strcspn, test_strcspn_no_match);
    tcase_add_test(tcase_strcspn, test_strcspn_empty_str1);
    tcase_add_test(tcase_strcspn, test_strcspn_empty_str2);
    tcase_add_test(tcase_strcspn, test_strcspn_multiple_chars);
    tcase_add_test(tcase_strcspn, test_strcspn_repeated_chars);

    Suite *suite_strcspn = suite_create("MY_STRCSPN");
    suite_add_tcase(suite_strcspn, tcase_strcspn);

    return suite_strcspn;
}
