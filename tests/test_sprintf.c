#include "test.h"
#include "../my_string.h"

#include <stdio.h>

START_TEST(test_default) {
    char my_buff[20], std_buff[20];
    my_sprintf(my_buff, "Test %% format");
    sprintf(std_buff, "Test %% format");
    ck_assert_mem_eq(my_buff, std_buff, 13);
}

Suite *suite_sprintf(void) {
    TCase *tc_default = tcase_create("Default TestCase");
    tcase_add_test(tc_default, test_default);

    Suite *suite_default = suite_create("MY_SPRINTF");
    suite_add_tcase(suite_default, tc_default);

    return suite_default;
}