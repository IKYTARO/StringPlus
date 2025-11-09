#include <stdlib.h>
#include <string.h>

#include "../my_string.h"
#include "test.h"

START_TEST(test_to_upper_basic) {
    char *res = (char *)my_to_upper("Hello World");
    ck_assert_ptr_nonnull(res);
    ck_assert_str_eq(res, "HELLO WORLD");
    free(res);
}
END_TEST

START_TEST(test_to_upper_all_lowercase) {
    char *res = (char *)my_to_upper("abcdef");
    ck_assert_ptr_nonnull(res);
    ck_assert_str_eq(res, "ABCDEF");
    free(res);
}
END_TEST

START_TEST(test_to_upper_mixed_chars) {
    char *res = (char *)my_to_upper("123abc!@#");
    ck_assert_ptr_nonnull(res);
    ck_assert_str_eq(res, "123ABC!@#");
    free(res);
}
END_TEST

START_TEST(test_to_upper_empty_string) {
    char *res = (char *)my_to_upper("");
    ck_assert_ptr_nonnull(res);
    ck_assert_str_eq(res, "");
    free(res);
}
END_TEST

START_TEST(test_to_upper_null_input) {
    char *res = (char *)my_to_upper(NULL);
    ck_assert_ptr_null(res);
    free(res);
}
END_TEST

START_TEST(test_to_upper_no_letters) {
    char *res = (char *)my_to_upper("123!@#");
    ck_assert_ptr_nonnull(res);
    ck_assert_str_eq(res, "123!@#");
    free(res);
}
END_TEST

START_TEST(test_to_upper_ascii_limits) {
    char *res = (char *)my_to_upper("z{y|x}");
    ck_assert_ptr_nonnull(res);
    ck_assert_str_eq(res, "Z{Y|X}");
    free(res);
}
END_TEST

Suite *suite_to_upper(void) {
    TCase *tcase_to_upper = tcase_create("TCase to_upper");

    tcase_add_test(tcase_to_upper, test_to_upper_basic);
    tcase_add_test(tcase_to_upper, test_to_upper_all_lowercase);
    tcase_add_test(tcase_to_upper, test_to_upper_mixed_chars);
    tcase_add_test(tcase_to_upper, test_to_upper_empty_string);
    tcase_add_test(tcase_to_upper, test_to_upper_null_input);
    tcase_add_test(tcase_to_upper, test_to_upper_no_letters);
    tcase_add_test(tcase_to_upper, test_to_upper_ascii_limits);

    Suite *suite_to_upper = suite_create("MY_TO_UPPER");
    suite_add_tcase(suite_to_upper, tcase_to_upper);

    return suite_to_upper;
}
