#include <stdio.h>

#include "../../my_string.h"
#include "sprintf_tests.h"

START_TEST(test_percent_basic) {
    char my_buff[20], std_buff[20];

    int my_res = my_sprintf(my_buff, "Test %% format");
    int std_res = sprintf(std_buff, "Test %% format");
    ck_assert_int_eq(my_res, std_res);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

TCase *tcase_percent(void) {
    TCase *tc_percent = tcase_create("TCase percent");
    tcase_add_test(tc_percent, test_percent_basic);

    return tc_percent;
}