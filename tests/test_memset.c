#include "test.h"
#include "../my_string.h"

#include <string.h>

// TODO: Добавьте достаточное количество тестов для покрытия функции

START_TEST(test_memset_basic) {
    // TODO: Реализовать базовый тест
}
END_TEST

Suite *suite_memset(void) {
    TCase *tcase_memset = tcase_create("TCase memset");
    tcase_add_test(tcase_memset, test_memset_basic);

    Suite *suite_memset = suite_create("MY MEMSET");
    suite_add_tcase(suite_memset, tcase_memset);

    return suite_memset;
}
