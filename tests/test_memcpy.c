#include <string.h>

#include "../my_string.h"
#include "test.h"

START_TEST(memcpy_test1) {
    char s1[] = "School 21 is awesome!";
    char s2[] = "School 21 is awesome!";
    const char s3[] = "School";
    my_size_t n = 4;
    ck_assert_str_eq(memcpy(s1, s3, n), my_memcpy(s2, s3, n));
}
END_TEST

START_TEST(memcpy_test2) {
    char s1[] = "School 21 is awesome!";
    char s2[] = "School 21 is awesome!";
    const char s3[] = "Hello";
    my_size_t n = 2;
    ck_assert_str_eq(memcpy(s1, s3, n), my_memcpy(s2, s3, n));
}
END_TEST

START_TEST(memcpy_test3) { ck_assert_ptr_eq(my_memcpy(MY_NULL, MY_NULL, 5), MY_NULL); }
END_TEST

Suite *suite_memcpy(void) {
    TCase *tcase_memcpy = tcase_create("TCase memcpy");

    tcase_add_test(tcase_memcpy, memcpy_test1);
    tcase_add_test(tcase_memcpy, memcpy_test2);
    tcase_add_test(tcase_memcpy, memcpy_test3);

    Suite *suite_memcpy = suite_create("MY_MEMCPY");
    suite_add_tcase(suite_memcpy, tcase_memcpy);

    return suite_memcpy;
}
