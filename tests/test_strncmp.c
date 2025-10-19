#include "test.h"
#include "../my_string.h"

#include <string.h>

START_TEST(test_strncmp_equal_strings) {
    char *str1 = "hello";
    char *str2 = "hello";
    ck_assert_int_eq(my_strncmp(str1, str2, 5), strncmp(str1, str2, 5));
    ck_assert_int_eq(my_strncmp(str1, str2, 10), strncmp(str1, str2, 10));
}
END_TEST

START_TEST(test_strncmp_different_strings) {
    char *str1 = "hello";
    char *str2 = "world";
    ck_assert_int_eq(my_strncmp(str1, str2, 5), strncmp(str1, str2, 5));
}
END_TEST

START_TEST(test_strncmp_empty_strings) {
    char *str1 = "";
    char *str2 = "";
    ck_assert_int_eq(my_strncmp(str1, str2, 0), strncmp(str1, str2, 0));
    ck_assert_int_eq(my_strncmp(str1, str2, 1), strncmp(str1, str2, 1));
}
END_TEST

START_TEST(test_strncmp_partial_comparison) {
    char *str1 = "hello world";
    char *str2 = "hello there";
    ck_assert_int_eq(my_strncmp(str1, str2, 5), strncmp(str1, str2, 5));
    ck_assert_int_eq(my_strncmp(str1, str2, 6), strncmp(str1, str2, 6));
}
END_TEST

START_TEST(test_strncmp_zero_length) {
    char *str1 = "hello";
    char *str2 = "world";
    ck_assert_int_eq(my_strncmp(str1, str2, 0), strncmp(str1, str2, 0));
}
END_TEST

START_TEST(test_strncmp_length_exceeds_strings) {
    char *str1 = "hello";
    char *str2 = "hello";
    ck_assert_int_eq(my_strncmp(str1, str2, 10), strncmp(str1, str2, 10));
    
    char *str3 = "hello";
    char *str4 = "hell";
    ck_assert_int_eq(my_strncmp(str3, str4, 10), strncmp(str3, str4, 10));
}
END_TEST

START_TEST(test_strncmp_case_sensitive) {
    char *str1 = "Hello";
    char *str2 = "hello";
    ck_assert_int_eq(my_strncmp(str1, str2, 5), strncmp(str1, str2, 5));
}
END_TEST

START_TEST(test_strncmp_numbers) {
    char *str1 = "12345";
    char *str2 = "12346";
    ck_assert_int_eq(my_strncmp(str1, str2, 4), strncmp(str1, str2, 4));
    ck_assert_int_eq(my_strncmp(str1, str2, 5), strncmp(str1, str2, 5));
}
END_TEST

START_TEST(test_strncmp_special_chars) {
    char *str1 = "hello\nworld";
    char *str2 = "hello\tworld";
    ck_assert_int_eq(my_strncmp(str1, str2, 5), strncmp(str1, str2, 5));
    ck_assert_int_eq(my_strncmp(str1, str2, 6), strncmp(str1, str2, 6));
}
END_TEST

START_TEST(test_strncmp_one_empty) {
    char *str1 = "";
    char *str2 = "hello";
    ck_assert_int_eq(my_strncmp(str1, str2, 3), strncmp(str1, str2, 3));
    ck_assert_int_eq(my_strncmp(str2, str1, 3), strncmp(str2, str1, 3));
}
END_TEST

START_TEST(test_strncmp_same_prefix) {
    char *str1 = "apple";
    char *str2 = "apples";
    ck_assert_int_eq(my_strncmp(str1, str2, 5), strncmp(str1, str2, 5));
    ck_assert_int_eq(my_strncmp(str1, str2, 6), strncmp(str1, str2, 6));
}
END_TEST

START_TEST(test_strncmp_negative_result) {
    char *str1 = "apple";
    char *str2 = "banana";
    
    int my_result = my_strncmp(str1, str2, 5);
    int std_result = strncmp(str1, str2, 5);
    
    if (std_result < 0) {
        ck_assert_int_lt(my_result, 0);
    } else if (std_result > 0) {
        ck_assert_int_gt(my_result, 0);
    } else {
        ck_assert_int_eq(my_result, 0);
    }
}
END_TEST

START_TEST(test_strncmp_positive_result) {
    char *str1 = "zebra";
    char *str2 = "apple";
    
    int my_result = my_strncmp(str1, str2, 5);
    int std_result = strncmp(str1, str2, 5);
    
    if (std_result < 0) {
        ck_assert_int_lt(my_result, 0);
    } else if (std_result > 0) {
        ck_assert_int_gt(my_result, 0);
    } else {
        ck_assert_int_eq(my_result, 0);
    }
}
END_TEST

START_TEST(test_strncmp_after_null) {
    char str1[10] = "hello";
    char str2[10] = "hello";
    str1[5] = 'x';
    str2[5] = 'y';
    
    ck_assert_int_eq(my_strncmp(str1, str2, 10), strncmp(str1, str2, 10));
}
END_TEST

START_TEST(test_strncmp_utf8) {
    char *str1 = "café";
    char *str2 = "cafe";
    ck_assert_int_eq(my_strncmp(str1, str2, 4), strncmp(str1, str2, 4));
}
END_TEST

START_TEST(test_strncmp_edge_cases) {
    char *str1 = "a";
    char *str2 = "b";
    ck_assert_int_eq(my_strncmp(str1, str2, 1), strncmp(str1, str2, 1));
    
    char *str3 = "a";
    char *str4 = "a";
    ck_assert_int_eq(my_strncmp(str3, str4, 1), strncmp(str3, str4, 1));
}
END_TEST


Suite *suite_strncmp(void) {
    TCase *tcase_strncmp = tcase_create("TCase strncmp");
    tcase_add_test(tcase_strncmp, test_strncmp_equal_strings);
    tcase_add_test(tcase_strncmp, test_strncmp_different_strings);
    tcase_add_test(tcase_strncmp, test_strncmp_empty_strings);
    tcase_add_test(tcase_strncmp, test_strncmp_partial_comparison);
    tcase_add_test(tcase_strncmp, test_strncmp_zero_length);
    tcase_add_test(tcase_strncmp, test_strncmp_length_exceeds_strings);
    tcase_add_test(tcase_strncmp, test_strncmp_case_sensitive);
    tcase_add_test(tcase_strncmp, test_strncmp_numbers);
    tcase_add_test(tcase_strncmp, test_strncmp_special_chars);
    tcase_add_test(tcase_strncmp, test_strncmp_one_empty);
    tcase_add_test(tcase_strncmp, test_strncmp_same_prefix);
    tcase_add_test(tcase_strncmp, test_strncmp_negative_result);
    tcase_add_test(tcase_strncmp, test_strncmp_positive_result);
    tcase_add_test(tcase_strncmp, test_strncmp_after_null);
    tcase_add_test(tcase_strncmp, test_strncmp_edge_cases);
    tcase_add_test(tcase_strncmp, test_strncmp_utf8);

    Suite *suite_strncmp = suite_create("MY_STRNCMP");
    suite_add_tcase(suite_strncmp, tcase_strncmp);

    return suite_strncmp;
}