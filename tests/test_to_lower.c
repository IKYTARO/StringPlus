#include <stdlib.h>
#include <string.h>

#include "../my_string.h"
#include "test.h"

START_TEST(test_to_lower_basic) {
    char *res = (char *)my_to_lower("HELLO WORLD");
    ck_assert_ptr_nonnull(res);
    ck_assert_str_eq(res, "hello world");
    free(res);
}
END_TEST

START_TEST(test_to_lower_all_uppercase) {
    char *res = (char *)my_to_lower("ABCDEF");
    ck_assert_ptr_nonnull(res);
    ck_assert_str_eq(res, "abcdef");
    free(res);
}
END_TEST

START_TEST(test_to_lower_mixed_chars) {
    char *res = (char *)my_to_lower("123ABC!@#");
    ck_assert_ptr_nonnull(res);
    ck_assert_str_eq(res, "123abc!@#");
    free(res);
}
END_TEST

START_TEST(test_to_lower_empty_string) {
    char *res = (char *)my_to_lower("");
    ck_assert_ptr_nonnull(res);
    ck_assert_str_eq(res, "");
    free(res);
}
END_TEST

START_TEST(test_to_lower_null_input) {
    char *res = (char *)my_to_lower(NULL);
    ck_assert_ptr_null(res);
}
END_TEST

START_TEST(test_to_lower_no_letters) {
    char *res = (char *)my_to_lower("123!@#");
    ck_assert_ptr_nonnull(res);
    ck_assert_str_eq(res, "123!@#");
    free(res);
}
END_TEST

START_TEST(test_to_lower_ascii_limits) {
    char *res = (char *)my_to_lower("A[Z\\a]");
    ck_assert_ptr_nonnull(res);
    ck_assert_str_eq(res, "a[z\\a]");
    free(res);
}
END_TEST

Suite *suite_to_lower(void) {
    TCase *tcase_to_lower = tcase_create("TCase to_lower");

    tcase_add_test(tcase_to_lower, test_to_lower_basic);
    tcase_add_test(tcase_to_lower, test_to_lower_all_uppercase);
    tcase_add_test(tcase_to_lower, test_to_lower_mixed_chars);
    tcase_add_test(tcase_to_lower, test_to_lower_empty_string);
    tcase_add_test(tcase_to_lower, test_to_lower_null_input);
    tcase_add_test(tcase_to_lower, test_to_lower_no_letters);
    tcase_add_test(tcase_to_lower, test_to_lower_ascii_limits);

    Suite *suite_to_lower = suite_create("MY_TO_LOWER");
    suite_add_tcase(suite_to_lower, tcase_to_lower);

    return suite_to_lower;
}
