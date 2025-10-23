#include "test.h"
#include "../my_string.h"

#include <string.h>

// TODO: Добавьте достаточное количество тестов для покрытия функции

START_TEST(test_strchr_basic) {
    // TODO: Реализовать базовый тест
}
END_TEST

Suite *suite_strchr(void) {
    TCase *tcase_strchr = tcase_create("TCase strchr");
    tcase_add_test(tcase_strchr, test_strchr_basic);

    Suite *suite_strchr = suite_create("MY_STRCHR");
    suite_add_tcase(suite_strchr, tcase_strchr);

    return suite_strchr;
}
