#include <stdlib.h>
#include <string.h>

#include "../my_string.h"
#include "test.h"

START_TEST(test_trim_start) {
    const char str[] = "  hello";
    char *res = my_trim(str, " ");
    ck_assert_str_eq(res, "hello");
    free(res);
}
END_TEST

START_TEST(test_trim_end) {
    const char str[] = "world\t\t";
    char *res = my_trim(str, "\t");
    ck_assert_str_eq(res, "world");
    free(res);
}
END_TEST

START_TEST(test_trim_both) {
    const char str[] = "\n\ntrimmed\n\n";
    char *res = my_trim(str, "\n");
    ck_assert_str_eq(res, "trimmed");
    free(res);
}
END_TEST

START_TEST(test_trim_no_chars) {
    const char str[] = "nothing";
    char *res = my_trim(str, " ");
    ck_assert_str_eq(res, "nothing");
    free(res);
}
END_TEST

START_TEST(test_trim_all_chars) {
    const char str[] = "xxx";
    char *res = my_trim(str, "x");
    ck_assert_str_eq(res, "");
    free(res);
}
END_TEST

START_TEST(test_trim_empty_string) {
    const char str[] = "";
    char *res = my_trim(str, " \t\n");
    ck_assert_str_eq(res, "");
    free(res);
}
END_TEST

START_TEST(test_trim_empty_trim_chars) {
    const char str[] = "data";
    char *res = my_trim(str, "");
    ck_assert_str_eq(res, "data");
    free(res);
}
END_TEST

START_TEST(test_trim_default_whitespace) {
    const char str[] = "\t  hello world \n";
    char *res = my_trim(str, "\t\n ");
    ck_assert_str_eq(res, "hello world");
    free(res);
}
END_TEST

START_TEST(test_trim_middle_unchanged) {
    const char str[] = "  middle  space  ";
    char *res = my_trim(str, " ");
    ck_assert_str_eq(res, "middle  space");
    free(res);
}
END_TEST

Suite *suite_trim(void) {
    TCase *tcase_trim = tcase_create("TCase trim");

    tcase_add_test(tcase_trim, test_trim_start);
    tcase_add_test(tcase_trim, test_trim_end);
    tcase_add_test(tcase_trim, test_trim_both);
    tcase_add_test(tcase_trim, test_trim_no_chars);
    tcase_add_test(tcase_trim, test_trim_all_chars);
    tcase_add_test(tcase_trim, test_trim_empty_string);
    tcase_add_test(tcase_trim, test_trim_empty_trim_chars);
    tcase_add_test(tcase_trim, test_trim_default_whitespace);
    tcase_add_test(tcase_trim, test_trim_middle_unchanged);

    Suite *suite_trim = suite_create("MY_TRIM");
    suite_add_tcase(suite_trim, tcase_trim);

    return suite_trim;
}
