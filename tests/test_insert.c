#include "test.h"
#include "../my_string.h"

#include <string.h>

// TODO: Добавьте достаточное количество тестов для покрытия функции

START_TEST(test_insert_basic) {
    // TODO: Реализовать базовый тест
}
END_TEST

Suite *suite_insert(void) {
    TCase *tcase_insert = tcase_create("TCase insert");
    tcase_add_test(tcase_insert, test_insert_basic);

    Suite *suite_insert = suite_create("MY_INSERT");
    suite_add_tcase(suite_insert, tcase_insert);

    return suite_insert;
}
