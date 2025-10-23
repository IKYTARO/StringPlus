#include "test.h"
#include "../my_string.h"

#include <string.h>

// TODO: Добавьте достаточное количество тестов для покрытия функции

START_TEST(test_strtok_basic) {
    // TODO: Реализовать базовый тест
}
END_TEST

Suite *suite_strtok(void) {
    TCase *tcase_strtok = tcase_create("TCase strtok");
    tcase_add_test(tcase_strtok, test_strtok_basic);

    Suite *suite_strtok = suite_create("MY_STRTOK");
    suite_add_tcase(suite_strtok, tcase_strtok);

    return suite_strtok;
}
