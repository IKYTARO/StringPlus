#include "test.h"
#include "../my_string.h"

#include <string.h>

// TODO: Добавьте достаточное количество тестов для покрытия функции

START_TEST(test_trim_basic) {
    // TODO: Реализовать базовый тест
}
END_TEST

Suite *suite_trim(void) {
    TCase *tcase_trim = tcase_create("TCase trim");
    tcase_add_test(tcase_trim, test_trim_basic);

    Suite *suite_trim = suite_create("MY_TRIM");
    suite_add_tcase(suite_trim, tcase_trim);

    return suite_trim;
}
