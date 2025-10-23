#include "test.h"
#include "../my_string.h"

#include <string.h>

// TODO: Добавьте достаточное количество тестов для покрытия функции

START_TEST(test_memchr_basic) {
    // TODO: Реализовать базовый тест
}
END_TEST

Suite *suite_memchr(void) {
    TCase *tcase_memchr = tcase_create("TCase memchr");
    tcase_add_test(tcase_memchr, test_memchr_basic);

    Suite *suite_memchr = suite_create("MY_MEMCHR");
    suite_add_tcase(suite_memchr, tcase_memchr);

    return suite_memchr;
}
