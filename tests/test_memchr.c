#include <string.h>

#include "../my_string.h"
#include "test.h"

START_TEST(test_memchr_first_char) {
    char str[] = "abcdef";
    ck_assert_ptr_eq(my_memchr(str, 'a', 6), memchr(str, 'a', 6));
}
END_TEST

START_TEST(test_memchr_middle_char) {
    char str[] = "abcdef";
    ck_assert_ptr_eq(my_memchr(str, 'c', 6), memchr(str, 'c', 6));
}
END_TEST

START_TEST(test_memchr_last_char) {
    char str[] = "abcdef";
    ck_assert_ptr_eq(my_memchr(str, 'f', 6), memchr(str, 'f', 6));
}
END_TEST

START_TEST(test_memchr_char_not_found) {
    char str[] = "abcdef";
    ck_assert_ptr_eq(my_memchr(str, 'x', 6), memchr(str, 'x', 6));
}
END_TEST

START_TEST(test_memchr_partial_search) {
    char str[] = "abcdef";
    ck_assert_ptr_eq(my_memchr(str, 'd', 3), memchr(str, 'd', 3));
    ck_assert_ptr_eq(my_memchr(str, 'd', 4), memchr(str, 'd', 4));
}
END_TEST

START_TEST(test_memchr_multiple_same_chars) {
    char str[] = "aaabbbccc";
    ck_assert_ptr_eq(my_memchr(str, 'a', 9), memchr(str, 'a', 9));
    ck_assert_ptr_eq(my_memchr(str, 'b', 9), memchr(str, 'b', 9));
    ck_assert_ptr_eq(my_memchr(str, 'c', 9), memchr(str, 'c', 9));
}
END_TEST

START_TEST(test_memchr_null_inside) {
    char str[] = "abc\0def";
    ck_assert_ptr_eq(my_memchr(str, '\0', 7), memchr(str, '\0', 7));
    ck_assert_ptr_eq(my_memchr(str, 'd', 7), memchr(str, 'd', 7));
    ck_assert_ptr_eq(my_memchr(str, 'f', 7), memchr(str, 'f', 7));
}
END_TEST

START_TEST(test_memchr_all_same_chars) {
    char str[10];
    memset(str, 'x', 10);
    ck_assert_ptr_eq(my_memchr(str, 'x', 10), memchr(str, 'x', 10));
    ck_assert_ptr_eq(my_memchr(str, 'y', 10), memchr(str, 'y', 10));
}
END_TEST

START_TEST(test_memchr_edges_long_string) {
    char str[100];
    memset(str, 'a', 100);
    str[0] = 'b';
    str[99] = 'c';
    ck_assert_ptr_eq(my_memchr(str, 'b', 100), memchr(str, 'b', 100));
    ck_assert_ptr_eq(my_memchr(str, 'c', 100), memchr(str, 'c', 100));
}
END_TEST

START_TEST(test_memchr_out_of_bounds) {
    char str[] = "abcdef";
    ck_assert_ptr_eq(my_memchr(str, 'f', 5), memchr(str, 'f', 5));
}
END_TEST

Suite *suite_memchr(void) {
    TCase *tcase_memchr = tcase_create("TCase memchr");

    tcase_add_test(tcase_memchr, test_memchr_first_char);
    tcase_add_test(tcase_memchr, test_memchr_middle_char);
    tcase_add_test(tcase_memchr, test_memchr_last_char);
    tcase_add_test(tcase_memchr, test_memchr_char_not_found);
    tcase_add_test(tcase_memchr, test_memchr_partial_search);
    tcase_add_test(tcase_memchr, test_memchr_multiple_same_chars);
    tcase_add_test(tcase_memchr, test_memchr_null_inside);
    tcase_add_test(tcase_memchr, test_memchr_all_same_chars);
    tcase_add_test(tcase_memchr, test_memchr_edges_long_string);
    tcase_add_test(tcase_memchr, test_memchr_out_of_bounds);

    Suite *suite_memchr = suite_create("MY_MEMCHR");
    suite_add_tcase(suite_memchr, tcase_memchr);

    return suite_memchr;
}
