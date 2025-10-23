#include "test.h"
#include "../my_string.h"

#include <string.h>

// TODO: Добавьте достаточное количество тестов для покрытия функции

START_TEST(test_to_lower_basic) {
    // TODO: Реализовать базовый тест
}
END_TEST

Suite *suite_to_lower(void) {
    TCase *tcase_to_lower = tcase_create("TCase to_lower");
    tcase_add_test(tcase_to_lower, test_to_lower_basic);

    Suite *suite_to_lower = suite_create("MY_TO_LOWER");
    suite_add_tcase(suite_to_lower, tcase_to_lower);

    return suite_to_lower;
}
