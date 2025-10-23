#include "test.h"
#include "../my_string.h"

#include <string.h>

// TODO: Добавьте достаточное количество тестов для покрытия функции

START_TEST(test_to_upper_basic) {
    // TODO: Реализовать базовый тест
}
END_TEST

Suite *suite_to_upper(void) {
    TCase *tcase_to_upper = tcase_create("TCase to_upper");
    tcase_add_test(tcase_to_upper, test_to_upper_basic);

    Suite *suite_to_upper = suite_create("MY_TO_UPPER");
    suite_add_tcase(suite_to_upper, tcase_to_upper);

    return suite_to_upper;
}
