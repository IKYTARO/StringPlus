#include "test.h"
#include "../my_string.h"

#include <string.h>

// TODO: Добавьте достаточное количество тестов для покрытия функции

START_TEST(test_memcmp_basic) {
    // TODO: Реализовать базовый тест
}
END_TEST

Suite *suite_memcmp(void) {
    TCase *tcase_memcmp = tcase_create("TCase memcmp");
    tcase_add_test(tcase_memcmp, test_memcmp_basic);

    Suite *suite_memcmp = suite_create("MY_MEMCMP");
    suite_add_tcase(suite_memcmp, tcase_memcmp);

    return suite_memcmp;
}
