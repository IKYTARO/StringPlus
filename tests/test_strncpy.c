#include <string.h>

#include "../my_string.h"
#include "test.h"

static int is_buffers_equal(char const *buf1, char const *buf2, my_size_t n) {
    for (my_size_t i = 0; i < n; i++) {
        if (buf1[i] != buf2[i]) {
            return 0;
        }
    }
    return 1;
}

START_TEST(test_strncpy_basic) {
    char dest1[20] = {0};
    char dest2[20] = {0};
    const char *src = "hello";

    my_strncpy(dest1, src, 5);
    strncpy(dest2, src, 5);

    ck_assert_str_eq(dest1, dest2);
    ck_assert_ptr_eq(my_strncpy(dest1, src, 5), dest1);
}
END_TEST

START_TEST(test_strncpy_empty_src) {
    char dest1[20] = "initial";
    char dest2[20] = "initial";
    const char *src = "";

    my_strncpy(dest1, src, 5);
    strncpy(dest2, src, 5);

    ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_strncpy_partial_copy) {
    char dest1[20] = "xxxxxxxxxx";
    char dest2[20] = "xxxxxxxxxx";
    const char *src = "hello";

    my_strncpy(dest1, src, 3);
    strncpy(dest2, src, 3);

    ck_assert_int_eq(is_buffers_equal(dest1, dest2, 10), 1);
}
END_TEST

START_TEST(test_strncpy_zero_length) {
    char dest[20] = "initial";
    const char *src = "hello";

    char *result = my_strncpy(dest, src, 0);

    ck_assert_ptr_eq(result, dest);
}
END_TEST

START_TEST(test_strncpy_length_less_than_src) {
    char dest1[20] = {0};
    char dest2[20] = {0};
    const char *src = "hello world";

    my_strncpy(dest1, src, 5);
    strncpy(dest2, src, 5);

    ck_assert_int_eq(is_buffers_equal(dest1, dest2, 10), 1);
}
END_TEST

START_TEST(test_strncpy_length_greater_than_src) {
    char dest1[20];
    char dest2[20];
    const char *src = "hello";

    memset(dest1, 'x', sizeof(dest1));
    memset(dest2, 'x', sizeof(dest2));

    my_strncpy(dest1, src, 10);
    strncpy(dest2, src, 10);

    ck_assert_int_eq(is_buffers_equal(dest1, dest2, 15), 1);
}
END_TEST

START_TEST(test_strncpy_null_padding) {
    char dest1[10];
    char dest2[10];
    const char *src = "hi";

    memset(dest1, 'A', sizeof(dest1));
    memset(dest2, 'A', sizeof(dest2));

    my_strncpy(dest1, src, 5);
    strncpy(dest2, src, 5);

    ck_assert_int_eq(is_buffers_equal(dest1, dest2, 10), 1);
}
END_TEST

START_TEST(test_strncpy_special_chars) {
    char dest1[20] = {0};
    char dest2[20] = {0};
    const char *src = "hello\nworld\t\r";

    my_strncpy(dest1, src, 12);
    strncpy(dest2, src, 12);

    ck_assert_int_eq(is_buffers_equal(dest1, dest2, 15), 1);
}
END_TEST

START_TEST(test_strncpy_numbers) {
    char dest1[20] = {0};
    char dest2[20] = {0};
    const char *src = "1234567890";

    my_strncpy(dest1, src, 10);
    strncpy(dest2, src, 10);

    ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_strncpy_exact_fit) {
    char dest1[6] = {0};
    char dest2[6] = {0};
    const char *src = "hello";

    my_strncpy(dest1, src, 5);
    strncpy(dest2, src, 5);

    ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_strncpy_return_value) {
    char dest1[20] = {0};
    char dest2[20] = {0};
    const char *src = "test";

    my_strncpy(dest1, src, 4);
    strncpy(dest2, src, 4);
    ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_strncpy_utf8) {
    char dest1[20] = {0};
    char dest2[20] = {0};
    const char *src = "café";

    my_strncpy(dest1, src, 5);
    strncpy(dest2, src, 5);

    ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_strncpy_large_buffer) {
    char dest1[1000];
    char dest2[1000];
    char src[1000];

    for (int i = 0; i < 999; i++) {
        src[i] = 'A' + (i % 26);
    }
    src[999] = '\0';

    my_strncpy(dest1, src, 1000);
    strncpy(dest2, src, 1000);

    ck_assert_int_eq(is_buffers_equal(dest1, dest2, 1000), 1);
}
END_TEST

START_TEST(test_strncpy_uninitialized) {
    char dest1[10];
    char dest2[10];
    const char *src = "test";

    my_strncpy(dest1, src, 4);
    strncpy(dest2, src, 4);

    ck_assert_int_eq(is_buffers_equal(dest1, dest2, 4), 1);
}
END_TEST

START_TEST(test_strncpy_after_null) {
    char src[10] = "hello";
    src[5] = 'x';

    char dest1[10] = {0};
    char dest2[10] = {0};

    my_strncpy(dest1, src, 8);
    strncpy(dest2, src, 8);

    ck_assert_int_eq(is_buffers_equal(dest1, dest2, 10), 1);
}
END_TEST

START_TEST(test_strncpy_various_lengths) {
    const char *src = "abcdefghij";

    for (my_size_t n = 0; n <= 12; n++) {
        char dest1[15] = {0};
        char dest2[15] = {0};

        memset(dest1, 'X', sizeof(dest1));
        memset(dest2, 'X', sizeof(dest2));

        my_strncpy(dest1, src, n);
        strncpy(dest2, src, n);

        ck_assert_int_eq(is_buffers_equal(dest1, dest2, 15), 1);
    }
}
END_TEST

Suite *suite_strncpy(void) {
    TCase *tcase_strncpy = tcase_create("TCase strncpy");
    tcase_add_test(tcase_strncpy, test_strncpy_basic);
    tcase_add_test(tcase_strncpy, test_strncpy_empty_src);
    tcase_add_test(tcase_strncpy, test_strncpy_partial_copy);
    tcase_add_test(tcase_strncpy, test_strncpy_zero_length);
    tcase_add_test(tcase_strncpy, test_strncpy_length_less_than_src);
    tcase_add_test(tcase_strncpy, test_strncpy_length_greater_than_src);
    tcase_add_test(tcase_strncpy, test_strncpy_null_padding);
    tcase_add_test(tcase_strncpy, test_strncpy_special_chars);
    tcase_add_test(tcase_strncpy, test_strncpy_numbers);
    tcase_add_test(tcase_strncpy, test_strncpy_exact_fit);
    tcase_add_test(tcase_strncpy, test_strncpy_return_value);
    tcase_add_test(tcase_strncpy, test_strncpy_large_buffer);
    tcase_add_test(tcase_strncpy, test_strncpy_uninitialized);
    tcase_add_test(tcase_strncpy, test_strncpy_after_null);
    tcase_add_test(tcase_strncpy, test_strncpy_various_lengths);
    tcase_add_test(tcase_strncpy, test_strncpy_utf8);

    Suite *suite_strncpy = suite_create("MY_STRNCPY");
    suite_add_tcase(suite_strncpy, tcase_strncpy);

    return suite_strncpy;
}