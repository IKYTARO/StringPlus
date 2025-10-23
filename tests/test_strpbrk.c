#include "test.h"
#include "../my_string.h"

#include <string.h>

// TODO: Добавьте достаточное количество тестов для покрытия функции

START_TEST(test_strpbrk_basic) {
    // TODO: Реализовать базовый тест
}
END_TEST

Suite *suite_strpbrk(void) {
    TCase *tcase_strpbrk = tcase_create("TCase strpbrk");
    tcase_add_test(tcase_strpbrk, test_strpbrk_basic);

    Suite *suite_strpbrk = suite_create("MY_STRPBRK");
    suite_add_tcase(suite_strpbrk, tcase_strpbrk);

    return suite_strpbrk;
}
