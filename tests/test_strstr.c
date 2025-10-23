#include "test.h"
#include "../my_string.h"

#include <string.h>

// TODO: Добавьте достаточное количество тестов для покрытия функции

START_TEST(test_strstr_basic) {
    // TODO: Реализовать базовый тест
}
END_TEST

Suite *suite_strstr(void) {
    TCase *tcase_strstr = tcase_create("TCase strstr");
    tcase_add_test(tcase_strstr, test_strstr_basic);

    Suite *suite_strstr = suite_create("MY_STRSTR");
    suite_add_tcase(suite_strstr, tcase_strstr);

    return suite_strstr;
}
