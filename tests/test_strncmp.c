#include <string.h>

#include "../my_string.h"
#include "test.h"

static int check_equal_results(int my_res, int std_res) {
    int is_equal = 0;

    if ((my_res < 0 && std_res < 0) || (my_res == 0 && std_res == 0) || (my_res > 0 && std_res > 0)) {
        is_equal = 1;
    }
    return is_equal;
}

START_TEST(test_strncmp_equal_strings) {
    const char *str1 = "hello";
    const char *str2 = "hello";

    ck_assert_int_eq(check_equal_results(my_strncmp(str1, str2, 5), strncmp(str1, str2, 5)), 1);
    ck_assert_int_eq(check_equal_results(my_strncmp(str1, str2, 10), strncmp(str1, str2, 10)), 1);
}
END_TEST

START_TEST(test_strncmp_different_strings) {
    const char *str1 = "hello";
    const char *str2 = "world";

    ck_assert_int_eq(check_equal_results(my_strncmp(str1, str2, 5), strncmp(str1, str2, 5)), 1);
}
END_TEST

START_TEST(test_strncmp_empty_strings) {
    const char *str1 = "";
    const char *str2 = "";

    ck_assert_int_eq(check_equal_results(my_strncmp(str1, str2, 0), strncmp(str1, str2, 0)), 1);
    ck_assert_int_eq(check_equal_results(my_strncmp(str1, str2, 1), strncmp(str1, str2, 1)), 1);
}
END_TEST

START_TEST(test_strncmp_partial_comparison) {
    const char *str1 = "hello world";
    const char *str2 = "hello there";

    ck_assert_int_eq(check_equal_results(my_strncmp(str1, str2, 5), strncmp(str1, str2, 5)), 1);
    ck_assert_int_eq(check_equal_results(my_strncmp(str1, str2, 6), strncmp(str1, str2, 6)), 1);
}
END_TEST

START_TEST(test_strncmp_zero_length) {
    const char *str1 = "hello";
    const char *str2 = "world";

    ck_assert_int_eq(check_equal_results(my_strncmp(str1, str2, 0), strncmp(str1, str2, 0)), 1);
}
END_TEST

START_TEST(test_strncmp_length_exceeds_strings) {
    const char *str1 = "hello";
    const char *str2 = "hello";

    ck_assert_int_eq(check_equal_results(my_strncmp(str1, str2, 10), strncmp(str1, str2, 10)), 1);

    const char *str3 = "hello";
    const char *str4 = "hell";

    ck_assert_int_eq(check_equal_results(my_strncmp(str3, str4, 10), strncmp(str3, str4, 10)), 1);
}
END_TEST

START_TEST(test_strncmp_case_sensitive) {
    const char *str1 = "Hello";
    const char *str2 = "hello";

    ck_assert_int_eq(check_equal_results(my_strncmp(str1, str2, 5), strncmp(str1, str2, 5)), 1);
}
END_TEST

START_TEST(test_strncmp_numbers) {
    const char *str1 = "12345";
    const char *str2 = "12346";

    ck_assert_int_eq(check_equal_results(my_strncmp(str1, str2, 4), strncmp(str1, str2, 4)), 1);
    ck_assert_int_eq(check_equal_results(my_strncmp(str1, str2, 5), strncmp(str1, str2, 5)), 1);
}
END_TEST

START_TEST(test_strncmp_special_chars) {
    const char *str1 = "hello\nworld";
    const char *str2 = "hello\tworld";

    ck_assert_int_eq(check_equal_results(my_strncmp(str1, str2, 5), strncmp(str1, str2, 5)), 1);
    ck_assert_int_eq(check_equal_results(my_strncmp(str1, str2, 6), strncmp(str1, str2, 6)), 1);
}
END_TEST

START_TEST(test_strncmp_one_empty) {
    const char *str1 = "";
    const char *str2 = "hello";

    ck_assert_int_eq(check_equal_results(my_strncmp(str1, str2, 3), strncmp(str1, str2, 3)), 1);
    ck_assert_int_eq(check_equal_results(my_strncmp(str2, str1, 3), strncmp(str2, str1, 3)), 1);
}
END_TEST

START_TEST(test_strncmp_same_prefix) {
    const char *str1 = "apple";
    const char *str2 = "apples";

    ck_assert_int_eq(check_equal_results(my_strncmp(str1, str2, 5), strncmp(str1, str2, 5)), 1);
    ck_assert_int_eq(check_equal_results(my_strncmp(str1, str2, 6), strncmp(str1, str2, 6)), 1);
}
END_TEST

START_TEST(test_strncmp_negative_result) {
    const char *str1 = "apple";
    const char *str2 = "banana";

    ck_assert_int_eq(check_equal_results(my_strncmp(str1, str2, 5), strncmp(str1, str2, 5)), 1);
}
END_TEST

START_TEST(test_strncmp_positive_result) {
    const char *str1 = "zebra";
    const char *str2 = "apple";

    ck_assert_int_eq(check_equal_results(my_strncmp(str1, str2, 5), strncmp(str1, str2, 5)), 1);
}
END_TEST

START_TEST(test_strncmp_after_null) {
    char str1[10] = "hello";
    char str2[10] = "hello";
    str1[5] = 'x';
    str2[5] = 'y';

    ck_assert_int_eq(check_equal_results(my_strncmp(str1, str2, 10), strncmp(str1, str2, 10)), 1);
}
END_TEST

START_TEST(test_strncmp_utf8) {
    const char *str1 = "café";
    const char *str2 = "cafe";

    ck_assert_int_eq(check_equal_results(my_strncmp(str1, str2, 4), strncmp(str1, str2, 4)), 1);
}
END_TEST

START_TEST(test_strncmp_edge_cases) {
    const char *str1 = "a";
    const char *str2 = "b";

    ck_assert_int_eq(check_equal_results(my_strncmp(str1, str2, 1), strncmp(str1, str2, 1)), 1);

    const char *str3 = "a";
    const char *str4 = "a";

    ck_assert_int_eq(check_equal_results(my_strncmp(str3, str4, 1), strncmp(str3, str4, 1)), 1);
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