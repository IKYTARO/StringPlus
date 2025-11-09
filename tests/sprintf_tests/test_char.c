#include <stdio.h>

#include "../../my_string.h"
#include "sprintf_tests.h"

START_TEST(test_char_basic) {
    char my_buff[50], std_buff[50];

    my_sprintf(my_buff, "Char: %c", 'A');
    sprintf(std_buff, "Char: %c", 'A');
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(test_char_special_chars) {
    char my_buff[50], std_buff[50];

    my_sprintf(my_buff, "Special: %c %c %c", '\n', '\t', '\0');
    sprintf(std_buff, "Special: %c %c %c", '\n', '\t', '\0');
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(test_char_width) {
    char my_buff[50], std_buff[50];

    my_sprintf(my_buff, "Width: %5c", 'X');
    sprintf(std_buff, "Width: %5c", 'X');
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(test_char_left_align) {
    char my_buff[50], std_buff[50];

    my_sprintf(my_buff, "Left: %-5c", 'X');
    sprintf(std_buff, "Left: %-5c", 'X');
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(test_char_multiple) {
    char my_buff[50], std_buff[50];

    my_sprintf(my_buff, "Multi: %c%c%c", 'a', 'b', 'c');
    sprintf(std_buff, "Multi: %c%c%c", 'a', 'b', 'c');
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(test_char_mixed_format) {
    char my_buff[50], std_buff[50];

    my_sprintf(my_buff, "Mixed: %c and %-3c end", 'A', 'B');
    sprintf(std_buff, "Mixed: %c and %-3c end", 'A', 'B');
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

TCase *tcase_char(void) {
    TCase *tc_char = tcase_create("TCase char");
    tcase_add_test(tc_char, test_char_basic);
    tcase_add_test(tc_char, test_char_special_chars);
    tcase_add_test(tc_char, test_char_width);
    tcase_add_test(tc_char, test_char_left_align);
    tcase_add_test(tc_char, test_char_multiple);
    tcase_add_test(tc_char, test_char_mixed_format);

    return tc_char;
}