#include <string.h>

#include "../my_string.h"
#include "test.h"

START_TEST(strchr_test1) {
    const char str[] = "Hello, world!";
    ck_assert_ptr_eq(my_strchr(str, 'H'), strchr(str, 'H'));
    ck_assert_ptr_eq(my_strchr(str, 'o'), strchr(str, 'o'));
    ck_assert_ptr_eq(my_strchr(str, '!'), strchr(str, '!'));
}
END_TEST

START_TEST(strchr_test2) {
    const char str[] = "Test string";
    ck_assert_ptr_eq(my_strchr(str, 'x'), strchr(str, 'x'));    // символ отсутствует
    ck_assert_ptr_eq(my_strchr(str, '\0'), strchr(str, '\0'));  // поиск нулевого символа
}
END_TEST

START_TEST(strchr_test3) {
    const char str[] = "";
    ck_assert_ptr_eq(my_strchr(str, 'a'), strchr(str, 'a'));    // пустая строка
    ck_assert_ptr_eq(my_strchr(str, '\0'), strchr(str, '\0'));  // поиск нулевого символа
}
END_TEST

START_TEST(strchr_test4) {
    const char str[] = "abcabcabc";
    ck_assert_ptr_eq(my_strchr(str, 'a'), strchr(str, 'a'));  // первый вхождение
    ck_assert_ptr_eq(my_strchr(str, 'b'), strchr(str, 'b'));
    ck_assert_ptr_eq(my_strchr(str, 'c'), strchr(str, 'c'));
}
END_TEST

Suite *suite_strchr(void) {
    TCase *tcase_strchr = tcase_create("TCase strchr");

    tcase_add_test(tcase_strchr, strchr_test1);
    tcase_add_test(tcase_strchr, strchr_test2);
    tcase_add_test(tcase_strchr, strchr_test3);
    tcase_add_test(tcase_strchr, strchr_test4);

    Suite *suite_strchr = suite_create("MY_STRCHR");
    suite_add_tcase(suite_strchr, tcase_strchr);

    return suite_strchr;
}
