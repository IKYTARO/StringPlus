#include "test.h"
#include "../my_string.h"

#include <string.h>

// TODO: Добавьте достаточное количество тестов для покрытия функции

START_TEST(test_strerror_basic) {
    // TODO: Реализовать базовый тест
}
END_TEST

Suite *suite_strerror(void) {
    TCase *tcase_strerror = tcase_create("TCase strerror");
    tcase_add_test(tcase_strerror, test_strerror_basic);

    Suite *suite_strerror = suite_create("MY_STRERROR");
    suite_add_tcase(suite_strerror, tcase_strerror);

    return suite_strerror;
}
