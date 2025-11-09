#include <stdlib.h>
#include <string.h>

#include "../my_string.h"
#include "test.h"

START_TEST(insert_test1) {
    const char src[] = "hello world";
    const char str[] = "beautiful ";
    my_size_t start_index = 6;
    char sample[] = "hello beautiful world";
    char *up_str = my_insert(src, str, start_index);
    ck_assert_str_eq(sample, up_str);
    free(up_str);
}
END_TEST

START_TEST(insert_test2) {
    const char *str = MY_NULL;
    const char src[] = "hello world";
    my_size_t start_index = 6;
    char *up_str = my_insert(src, str, start_index);
    ck_assert_ptr_null(up_str);
}
END_TEST

START_TEST(insert_test3) {
    const char str[] = "beautiful ";
    const char src[] = "hello world";
    my_size_t start_index = 40;
    char *up_str = my_insert(src, str, start_index);
    ck_assert_ptr_null(up_str);
    free(up_str);
}
END_TEST

START_TEST(insert_test4) {
    const char *src = MY_NULL;
    const char str[] = "hello world";
    my_size_t start_index = 6;
    char *up_str = my_insert(src, str, start_index);
    ck_assert_ptr_null(up_str);
}
END_TEST

Suite *suite_insert(void) {
    TCase *tcase_insert = tcase_create("TCase insert");

    tcase_add_test(tcase_insert, insert_test1);
    tcase_add_test(tcase_insert, insert_test2);
    tcase_add_test(tcase_insert, insert_test3);
    tcase_add_test(tcase_insert, insert_test4);

    Suite *suite_insert = suite_create("MY_INSERT");
    suite_add_tcase(suite_insert, tcase_insert);

    return suite_insert;
}
