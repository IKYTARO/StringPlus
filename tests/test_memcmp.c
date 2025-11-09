#include <string.h>

#include "../my_string.h"
#include "test.h"

START_TEST(test_memcmp_equal_strings) {
    const char str1[] = "abcdef";
    const char str2[] = "abcdef";
    ck_assert_int_eq(my_memcmp(str1, str2, 6), memcmp(str1, str2, 6));
}
END_TEST

START_TEST(test_memcmp_first_greater) {
    const char str1[] = "abcdz";
    const char str2[] = "abcdy";
    ck_assert_int_eq((my_memcmp(str1, str2, 5) > 0), (memcmp(str1, str2, 5) > 0));
}
END_TEST

START_TEST(test_memcmp_second_greater) {
    const char str1[] = "abcdy";
    const char str2[] = "abcdz";
    ck_assert_int_eq((my_memcmp(str1, str2, 5) < 0), (memcmp(str1, str2, 5) < 0));
}
END_TEST

START_TEST(test_memcmp_partial) {
    const char str1[] = "abcdef";
    const char str2[] = "abcxyz";
    ck_assert_int_eq(my_memcmp(str1, str2, 3), memcmp(str1, str2, 3));  // первые 3 символа равны
    ck_assert_int_eq((my_memcmp(str1, str2, 6) < 0), (memcmp(str1, str2, 6) < 0));
}
END_TEST

START_TEST(test_memcmp_with_null) {
    const char str1[] = "abc\0def";
    char str2[] = "abc\0xyz";
    ck_assert_int_eq(my_memcmp(str1, str2, 7), memcmp(str1, str2, 7));
}
END_TEST

START_TEST(test_memcmp_same_chars) {
    char str1[10];
    char str2[10];
    memset(str1, 'x', 10);
    memset(str2, 'x', 10);
    ck_assert_int_eq(my_memcmp(str1, str2, 10), memcmp(str1, str2, 10));
}
END_TEST

START_TEST(test_memcmp_all_bytes) {
    unsigned char arr1[256];
    unsigned char arr2[256];

    for (int i = 0; i < 256; i++) {
        arr1[i] = (unsigned char)i;
        arr2[i] = (unsigned char)i;
    }

    for (int n = 0; n <= 256; n++) {
        ck_assert_int_eq(my_memcmp(arr1, arr2, n), memcmp(arr1, arr2, n));
    }

    for (int i = 0; i < 256; i++) {
        arr2[i] = arr1[i] + 1;
        ck_assert_int_eq((my_memcmp(arr1, arr2, 256) < 0), (memcmp(arr1, arr2, 256) < 0));
    }
}
END_TEST

START_TEST(test_memcmp_null_inside) {
    const char str1[] = "abc\0def";
    const char str2[] = "abc\0xyz";

    ck_assert_int_eq(my_memcmp(str1, str2, 4), memcmp(str1, str2, 4));
    ck_assert_int_eq((my_memcmp(str1, str2, 7) < 0), (memcmp(str1, str2, 7) < 0));
}
END_TEST

START_TEST(test_memcmp_repeated_chars) {
    char str1[100];
    char str2[100];
    memset(str1, 'x', 100);
    memset(str2, 'x', 100);

    ck_assert_int_eq(my_memcmp(str1, str2, 100), memcmp(str1, str2, 100));

    str2[50] = 'y';
    ck_assert_int_eq((my_memcmp(str1, str2, 100) < 0), (memcmp(str1, str2, 100) < 0));
}
END_TEST

Suite *suite_memcmp(void) {
    TCase *tcase_memcmp = tcase_create("TCase memcmp");

    tcase_add_test(tcase_memcmp, test_memcmp_equal_strings);
    tcase_add_test(tcase_memcmp, test_memcmp_first_greater);
    tcase_add_test(tcase_memcmp, test_memcmp_second_greater);
    tcase_add_test(tcase_memcmp, test_memcmp_partial);
    tcase_add_test(tcase_memcmp, test_memcmp_with_null);
    tcase_add_test(tcase_memcmp, test_memcmp_same_chars);
    tcase_add_test(tcase_memcmp, test_memcmp_all_bytes);
    tcase_add_test(tcase_memcmp, test_memcmp_null_inside);
    tcase_add_test(tcase_memcmp, test_memcmp_repeated_chars);

    Suite *suite_memcmp = suite_create("MY_MEMCMP");
    suite_add_tcase(suite_memcmp, tcase_memcmp);

    return suite_memcmp;
}
