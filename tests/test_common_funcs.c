#include "test.h"
#include "../my_string.h"

#include <string.h>

START_TEST(test_strlen_basic) {
    ck_assert_int_eq(my_strlen(""), strlen(""));
    ck_assert_int_eq(my_strlen("12"), strlen("12"));
    ck_assert_int_eq(my_strlen("hello"), strlen("hello"));
    ck_assert_int_eq(my_strlen("veryVeryVeryLongWord"), strlen("veryVeryVeryLongWord"));
}
END_TEST

START_TEST(test_strlen_with_spaces) {
    ck_assert_int_eq(my_strlen("hello world"), strlen("hello world"));
    ck_assert_int_eq(my_strlen("  "), strlen("  "));
    ck_assert_int_eq(my_strlen("a, \t, c, d  "), strlen("a, \t, c, d  "));
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
    char dest_my[20], dest_std[20];
    char src[] = "Hello World";
    
    my_strncpy(dest_my, src, 12);
    strncpy(dest_std, src, 12);
    ck_assert_mem_eq(dest_my, dest_std, 12);
    
    my_strncpy(dest_my, src, 5);
    strncpy(dest_std, src, 5);
    ck_assert_mem_eq(dest_my, dest_std, 5);
    
    my_strncpy(dest_my, "", 5);
    strncpy(dest_std, "", 5);
    ck_assert_mem_eq(dest_my, dest_std, 5);
    
    dest_my[0] = 'X';
    dest_std[0] = 'X';

    my_strncpy(dest_my, src, 0);
    strncpy(dest_std, src, 0);
    ck_assert_int_eq(dest_my[0], dest_std[0]);
    
    my_strncpy(dest_my, "A", 1);
    strncpy(dest_std, "A", 1);
    ck_assert_mem_eq(dest_my, dest_std, 1);
    
    char test_src[] = "Hi";
    char test_dest_my[5], test_dest_std[5];

    my_strncpy(test_dest_my, test_src, 4);
    strncpy(test_dest_std, test_src, 4);
    ck_assert_mem_eq(test_dest_my, test_dest_std, 4);
}
END_TEST

START_TEST(test_strncpy_partial) {
    char dest_my[20], dest_std[20];
    char src[] = "Test";
    
    my_strncpy(dest_my, src, 20);
    strncpy(dest_std, src, 20);
    ck_assert_mem_eq(dest_my, dest_std, 20);
    
    char src_with_null[] = "AB\0CD";
    my_strncpy(dest_my, src_with_null, 5);
    strncpy(dest_std, src_with_null, 5);
    ck_assert_mem_eq(dest_my, dest_std, 5);

    char overlap_my[] = "OverlapTest";
    char overlap_std[] = "OverlapTest";
    my_strncpy(overlap_my + 3, overlap_my, 5);
    strncpy(overlap_std + 3, overlap_std, 5);
    ck_assert_mem_eq(overlap_my, overlap_std, 11);
    
    char buffer_my[] = "XXXXXXXXXX";
    char buffer_std[] = "XXXXXXXXXX";
    my_strncpy(buffer_my + 2, "YY", 2);
    strncpy(buffer_std + 2, "YY", 2);
    ck_assert_mem_eq(buffer_my, buffer_std, 10);

    my_strncpy(dest_my, "\n\t\xFF", 3);
    strncpy(dest_std, "\n\t\xFF", 3);
    ck_assert_mem_eq(dest_my, dest_std, 3);
    
    char *result_my = my_strncpy(dest_my, "Hello", 5);
    char *result_std = strncpy(dest_std, "Hello", 5);
    ck_assert_mem_eq(result_my, result_std, 5);
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

    Suite *common_funcs_suite = suite_create("Common Functions Suite");
    suite_add_tcase(common_funcs_suite, tc_strlen);
    suite_add_tcase(common_funcs_suite, tc_strncmp);
    suite_add_tcase(common_funcs_suite, tc_strncpy);

    return common_funcs_suite;
}