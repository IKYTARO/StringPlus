#include <stdio.h>

#include "../../my_string.h"
#include "sprintf_tests.h"

START_TEST(test_pointer_basic) {
    char my_buff[100], std_buff[100];
    int x = 42;
    void *ptr = &x;

    my_sprintf(my_buff, "Pointer: %p", ptr);
    sprintf(std_buff, "Pointer: %p", ptr);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(test_pointer_null) {
    char my_buff[100], std_buff[100];

    my_sprintf(my_buff, "Null: '%5p' '%-7p'", (void *)NULL, (void *)NULL);
    sprintf(std_buff, "Null: '%5p' '%-7p'", NULL, NULL);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(test_pointer_formatting) {
    char my_buff[100], std_buff[100];
    int y = 100;
    void *ptr = &y;

    my_sprintf(my_buff, "Format: %10p %-10p", ptr, ptr);
    sprintf(std_buff, "Format: %10p %-10p", ptr, ptr);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(test_pointer_multiple) {
    char my_buff[100], std_buff[100];
    int a = 1, b = 2;
    void *ptr1 = &a, *ptr2 = &b;

    my_sprintf(my_buff, "Multiple: %p %p", ptr1, ptr2);
    sprintf(std_buff, "Multiple: %p %p", ptr1, ptr2);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(test_pointer_with_other_specifiers) {
    char my_buff[100], std_buff[100];
    int value = 42;
    void *ptr = &value;

    my_sprintf(my_buff, "Mixed: %d %p %s", value, ptr, "test");
    sprintf(std_buff, "Mixed: %d %p %s", value, ptr, "test");
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

TCase *tcase_pointer(void) {
    TCase *tc_pointer = tcase_create("TCase Pointer");

    tcase_add_test(tc_pointer, test_pointer_basic);
    tcase_add_test(tc_pointer, test_pointer_null);
    tcase_add_test(tc_pointer, test_pointer_formatting);
    tcase_add_test(tc_pointer, test_pointer_multiple);
    tcase_add_test(tc_pointer, test_pointer_with_other_specifiers);

    return tc_pointer;
}