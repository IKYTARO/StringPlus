#include <string.h>

#include "../my_string.h"
#include "test.h"

START_TEST(test_strpbrk_basic) {
    const char *str1 = "abcdefg";
    const char *str2 = "xdy";
    char *res_std = strpbrk(str1, str2);
    char *res_my = my_strpbrk(str1, str2);
    ck_assert_ptr_eq(res_my, res_std);
}
END_TEST

START_TEST(test_strpbrk_no_match) {
    const char *str1 = "abcdefg";
    const char *str2 = "xyz";
    char *res_std = strpbrk(str1, str2);
    char *res_my = my_strpbrk(str1, str2);
    ck_assert_ptr_eq(res_my, res_std);
}
END_TEST

START_TEST(test_strpbrk_empty_str2) {
    const char *str1 = "abcdefg";
    const char *str2 = "";
    char *res_std = strpbrk(str1, str2);
    char *res_my = my_strpbrk(str1, str2);
    ck_assert_ptr_eq(res_my, res_std);
}
END_TEST

START_TEST(test_strpbrk_empty_str1) {
    const char *str1 = "";
    const char *str2 = "abc";
    char *res_std = strpbrk(str1, str2);
    char *res_my = my_strpbrk(str1, str2);
    ck_assert_ptr_eq(res_my, res_std);
}
END_TEST

START_TEST(test_strpbrk_first_char) {
    const char *str1 = "abcdefg";
    const char *str2 = "a";
    char *res_std = strpbrk(str1, str2);
    char *res_my = my_strpbrk(str1, str2);
    ck_assert_ptr_eq(res_my, res_std);
}
END_TEST

START_TEST(test_strpbrk_last_char) {
    const char *str1 = "abcdefg";
    const char *str2 = "g";
    char *res_std = strpbrk(str1, str2);
    char *res_my = my_strpbrk(str1, str2);
    ck_assert_ptr_eq(res_my, res_std);
}
END_TEST

START_TEST(test_strpbrk_all_match) {
    const char *str1 = "abc";
    const char *str2 = "abc";
    char *res_std = strpbrk(str1, str2);
    char *res_my = my_strpbrk(str1, str2);
    ck_assert_ptr_eq(res_my, res_std);
}
END_TEST

START_TEST(test_strpbrk_repeated_chars) {
    const char *str1 = "aabbcc";
    const char *str2 = "b";
    char *res_std = strpbrk(str1, str2);
    char *res_my = my_strpbrk(str1, str2);
    ck_assert_ptr_eq(res_my, res_std);
}
END_TEST

START_TEST(test_strpbrk_space_and_symbols) {
    const char *str1 = "hello, world!";
    const char *str2 = " !,";
    char *res_std = strpbrk(str1, str2);
    char *res_my = my_strpbrk(str1, str2);
    ck_assert_ptr_eq(res_my, res_std);
}
END_TEST

START_TEST(test_strpbrk_no_common_chars) {
    const char *str1 = "12345";
    const char *str2 = "abc";
    char *res_std = strpbrk(str1, str2);
    char *res_my = my_strpbrk(str1, str2);
    ck_assert_ptr_eq(res_my, res_std);
}
END_TEST

START_TEST(test_strpbrk_unicode) {
    const char *str1 = "héllo";
    const char *str2 = "é";
    char *res_std = strpbrk(str1, str2);
    char *res_my = my_strpbrk(str1, str2);
    ck_assert_ptr_eq(res_my, res_std);
}
END_TEST

Suite *suite_strpbrk(void) {
    TCase *tcase_strpbrk = tcase_create("TCase strpbrk");

    tcase_add_test(tcase_strpbrk, test_strpbrk_basic);
    tcase_add_test(tcase_strpbrk, test_strpbrk_no_match);
    tcase_add_test(tcase_strpbrk, test_strpbrk_empty_str2);
    tcase_add_test(tcase_strpbrk, test_strpbrk_empty_str1);
    tcase_add_test(tcase_strpbrk, test_strpbrk_first_char);
    tcase_add_test(tcase_strpbrk, test_strpbrk_last_char);
    tcase_add_test(tcase_strpbrk, test_strpbrk_all_match);
    tcase_add_test(tcase_strpbrk, test_strpbrk_repeated_chars);
    tcase_add_test(tcase_strpbrk, test_strpbrk_space_and_symbols);
    tcase_add_test(tcase_strpbrk, test_strpbrk_no_common_chars);
    tcase_add_test(tcase_strpbrk, test_strpbrk_unicode);

    Suite *suite_strpbrk = suite_create("MY_STRPBRK");
    suite_add_tcase(suite_strpbrk, tcase_strpbrk);

    return suite_strpbrk;
}
