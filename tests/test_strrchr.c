#include <string.h>

#include "../my_string.h"
#include "test.h"

START_TEST(test_strrchr_basic) {
    const char *str = "hello world";
    ck_assert_ptr_eq(my_strrchr(str, 'o'), str + 7);
}
END_TEST

START_TEST(test_strrchr_not_found) {
    const char *str = "hello";
    ck_assert_ptr_eq(my_strrchr(str, 'x'), NULL);
}
END_TEST

START_TEST(test_strrchr_first_char) {
    const char *str = "abcabc";
    ck_assert_ptr_eq(my_strrchr(str, 'a'), str + 3);
}
END_TEST

START_TEST(test_strrchr_last_char) {
    const char *str = "abcdef";
    ck_assert_ptr_eq(my_strrchr(str, 'f'), str + 5);
}
END_TEST

START_TEST(test_strrchr_null_char) {
    const char *str = "abc";
    ck_assert_ptr_eq(my_strrchr(str, '\0'), str + 3);
}
END_TEST

START_TEST(test_strrchr_empty_string) {
    const char *str = "";
    ck_assert_ptr_eq(my_strrchr(str, 'a'), NULL);
    ck_assert_ptr_eq(my_strrchr(str, '\0'), str);
}
END_TEST

Suite *suite_strrchr(void) {
    TCase *tcase_strrchr = tcase_create("TCase strrchr");

    tcase_add_test(tcase_strrchr, test_strrchr_basic);
    tcase_add_test(tcase_strrchr, test_strrchr_not_found);
    tcase_add_test(tcase_strrchr, test_strrchr_first_char);
    tcase_add_test(tcase_strrchr, test_strrchr_last_char);
    tcase_add_test(tcase_strrchr, test_strrchr_null_char);
    tcase_add_test(tcase_strrchr, test_strrchr_empty_string);

    Suite *suite_strrchr = suite_create("MY_STRRCHR");
    suite_add_tcase(suite_strrchr, tcase_strrchr);

    return suite_strrchr;
}
