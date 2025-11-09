#include <string.h>

#include "../my_string.h"
#include "test.h"

START_TEST(memset_test1) {
    char str1[15] = "1234567890";
    char str2[15] = "1234567890";
    int c = '1';
    int n = 10;
    ck_assert_str_eq(memset(str1, c, n), my_memset(str2, c, n));
}
END_TEST

START_TEST(memset_test2) {
    char str1[15] = "1234567890";
    char str2[15] = "5432167890";
    int c = 'q';
    int n = 10;
    ck_assert_str_eq(memset(str1, c, n), my_memset(str2, c, n));
}
END_TEST

Suite *suite_memset(void) {
    TCase *tcase_memset = tcase_create("TCase memset");

    tcase_add_test(tcase_memset, memset_test1);
    tcase_add_test(tcase_memset, memset_test2);

    Suite *suite_memset = suite_create("MY_MEMSET");
    suite_add_tcase(suite_memset, tcase_memset);

    return suite_memset;
}
