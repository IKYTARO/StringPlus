#include <stdio.h>

#include "../my_string.h"
#include "sprintf_tests/sprintf_tests.h"
#include "test.h"

START_TEST(test_base_complex_combination_1) {
    char my_buff[200], std_buff[200];

    my_sprintf(my_buff, "Format: %+-10.3ld | %#.0f | %10.5s | %c", (long)12345, 3.14159, "HelloWorld", 'X');
    sprintf(std_buff, "Format: %+-10.3ld | %#.0f | %10.5s | %c", (long)12345, 3.14159, "HelloWorld", 'X');
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(test_base_complex_combination_2) {
    char my_buff[200], std_buff[200];

    my_sprintf(my_buff, "Numbers: % lf | %-8.2hu | %015.3f %%", -45.678, (unsigned short)123, 7.891);
    sprintf(std_buff, "Numbers: % lf | %-8.2hu | %015.3f %%", -45.678, (unsigned short)123, 7.891);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(test_base_complex_combination_3) {
    char my_buff[200], std_buff[200];

    my_sprintf(my_buff, "Mixed: %#10.4Lf | %.3s | %+08d | %c%c", 3.141592653589793238L, "Testing", -42, 'A',
               'B');
    sprintf(std_buff, "Mixed: %#10.4Lf | %.3s | %+08d | %c%c", 3.141592653589793238L, "Testing", -42, 'A',
            'B');
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(test_base_complex_combination_4) {
    char my_buff[200], std_buff[200];

    my_sprintf(my_buff, "All flags: %-+15.6ld | % 020.2f | %#.1f | %.0s end", (long)-987654, 123.456789, 5.0,
               "");
    sprintf(std_buff, "All flags: %-+15.6ld | % 020.2f | %#.1f | %.0s end", (long)-987654, 123.456789, 5.0,
            "");
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(test_base_complex_combination_5) {
    char my_buff[200], std_buff[200];

    my_sprintf(my_buff, "Final: %c | %-10.3s | %+08.2f | %lu | %%", '\n', "Short", -0.007, 4294967295UL);
    sprintf(std_buff, "Final: %c | %-10.3s | %+08.2f | %lu | %%", '\n', "Short", -0.007, 4294967295UL);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(test_addition_complex_1) {
    char my_buff[100] = {0};
    char std_buff[100] = {0};
    int width = 0;
    int precision = 5;
    int value = -123;
    unsigned hex_value = 0xABC;
    char const *format = "%+*d, %#*.*x, %0*o";

    my_sprintf(my_buff, format, width, value, width, precision, hex_value, width, 0777);
    sprintf(std_buff, format, width, value, width, precision, hex_value, width, 0777);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(test_addition_complex_2) {
    char my_buff[100] = {0};
    char std_buff[100] = {0};
    int width = 12;
    int precision = 3;
    double value1 = 1234.56789;
    double value2 = -0.0009876;
    char const *format = "% *.*e, %+*.*E, %.*f";

    my_sprintf(my_buff, format, width, precision, value1, width, precision, value2, precision, value1);
    sprintf(std_buff, format, width, precision, value1, width, precision, value2, precision, value1);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(test_addition_complex_3) {
    char my_buff[100] = {0};
    char std_buff[100] = {0};
    int width = 8;
    int precision = 3;
    int arr[5] = {1, 2, 3, 4, 5};
    char *str = "test_string";
    void *ptr = (void *)&arr[0];
    char const *format = "%p, %*.*s, %#x";

    my_sprintf(my_buff, format, ptr, width, precision, str, 255);
    sprintf(std_buff, format, ptr, width, precision, str, 255);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(test_addition_complex_4) {
    char my_buff[100] = {0};
    char std_buff[100] = {0};
    int width = 6;
    int precision = 2;
    short short_val = (short)-123;
    long long_val = 123456789L;
    unsigned long ulong_val = 0xDEADBEEF;
    char const *format = "%*hd, %+*ld, %#*.*lx";

    my_sprintf(my_buff, format, width, short_val, width, long_val, width, precision, ulong_val);
    sprintf(std_buff, format, width, short_val, width, long_val, width, precision, ulong_val);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

Suite *suite_sprintf(void) {
    TCase *tc_base = tcase_create("TCase base part");
    tcase_add_test(tc_base, test_base_complex_combination_1);
    tcase_add_test(tc_base, test_base_complex_combination_2);
    tcase_add_test(tc_base, test_base_complex_combination_3);
    tcase_add_test(tc_base, test_base_complex_combination_4);
    tcase_add_test(tc_base, test_base_complex_combination_5);

    TCase *tc_addition = tcase_create("TCase additional part");
    tcase_add_test(tc_addition, test_addition_complex_1);
    tcase_add_test(tc_addition, test_addition_complex_2);
    tcase_add_test(tc_addition, test_addition_complex_3);
    tcase_add_test(tc_addition, test_addition_complex_4);

    Suite *suite_sprintf = suite_create("MY_SPRINTF");
    suite_add_tcase(suite_sprintf, tcase_percent());
    suite_add_tcase(suite_sprintf, tcase_integer());
    suite_add_tcase(suite_sprintf, tcase_char());
    suite_add_tcase(suite_sprintf, tcase_unsigned());
    suite_add_tcase(suite_sprintf, tcase_string());
    suite_add_tcase(suite_sprintf, tcase_float());
    suite_add_tcase(suite_sprintf, tcase_hex_octal());
    suite_add_tcase(suite_sprintf, tcase_pointer());
    suite_add_tcase(suite_sprintf, tcase_exponent());

    suite_add_tcase(suite_sprintf, tc_base);
    suite_add_tcase(suite_sprintf, tc_addition);

    return suite_sprintf;
}