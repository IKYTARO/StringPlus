#include <stdio.h>

#include "../../my_string.h"
#include "sprintf_tests.h"

START_TEST(test_hex_basic) {
    char my_buff[100], std_buff[100];

    my_sprintf(my_buff, "Hex: %x %X", 255, 255);
    sprintf(std_buff, "Hex: %x %X", 255, 255);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(test_hex_alternate) {
    char my_buff[100], std_buff[100];

    my_sprintf(my_buff, "Alt: %#x %#X", 255, 255);
    sprintf(std_buff, "Alt: %#x %#X", 255, 255);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(test_octal_basic) {
    char my_buff[100], std_buff[100];

    my_sprintf(my_buff, "Oct: %o %#o", 64, 64);
    sprintf(std_buff, "Oct: %o %#o", 64, 64);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(test_hex_octal_formatting) {
    char my_buff[100], std_buff[100];

    my_sprintf(my_buff, "Format: %08x %-8o %#10X", 42, 42, 42);
    sprintf(std_buff, "Format: %08x %-8o %#10X", 42, 42, 42);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(test_hex_octal_precision) {
    char my_buff[100], std_buff[100];

    my_sprintf(my_buff, "Prec: %.4x %.4o %#.4x", 15, 15, 15);
    sprintf(std_buff, "Prec: %.4x %.4o %#.4x", 15, 15, 15);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

TCase *tcase_hex_octal(void) {
    TCase *tc_hex_oct = tcase_create("TCase Hex Octal");

    tcase_add_test(tc_hex_oct, test_hex_basic);
    tcase_add_test(tc_hex_oct, test_hex_alternate);
    tcase_add_test(tc_hex_oct, test_octal_basic);
    tcase_add_test(tc_hex_oct, test_hex_octal_formatting);
    tcase_add_test(tc_hex_oct, test_hex_octal_precision);

    return tc_hex_oct;
}