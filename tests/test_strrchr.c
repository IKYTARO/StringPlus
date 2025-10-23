#include "test.h"
#include "../my_string.h"

#include <string.h>

// TODO: Добавьте достаточное количество тестов для покрытия функции

START_TEST(test_strrchr_basic) {
    // TODO: Реализовать базовый тест
}
END_TEST

Suite *suite_strrchr(void) {
    TCase *tcase_strrchr = tcase_create("TCase strrchr");
    tcase_add_test(tcase_strrchr, test_strrchr_basic);

    Suite *suite_strrchr = suite_create("MY_STRRCHR");
    suite_add_tcase(suite_strrchr, tcase_strrchr);

    return suite_strrchr;
}
