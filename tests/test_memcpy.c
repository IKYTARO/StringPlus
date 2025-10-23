#include "test.h"
#include "../my_string.h"

#include <string.h>

// TODO: Добавьте достаточное количество тестов для покрытия функции

START_TEST(test_memcpy_basic) {
    // TODO: Реализовать базовый тест
}
END_TEST

Suite *suite_memcpy(void) {
    TCase *tcase_memcpy = tcase_create("TCase memcpy");
    tcase_add_test(tcase_memcpy, test_memcpy_basic);

    Suite *suite_memcpy = suite_create("MY_MEMCPY");
    suite_add_tcase(suite_memcpy, tcase_memcpy);

    return suite_memcpy;
}
