#include "test.h"
#include "../my_string.h"

#include <string.h>

// TODO: Добавьте достаточное количество тестов для покрытия функции

START_TEST(test_strncat_basic) {
    // TODO: Реализовать базовый тест
}
END_TEST

Suite *suite_strncat(void) {
    TCase *tcase_strncat = tcase_create("TCase strncat");
    tcase_add_test(tcase_strncat, test_strncat_basic);

    Suite *suite_strncat = suite_create("MY_STRNCAT");
    suite_add_tcase(suite_strncat, tcase_strncat);

    return suite_strncat;
}
