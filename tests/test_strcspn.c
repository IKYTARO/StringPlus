#include "test.h"
#include "../my_string.h"

#include <string.h>

// TODO: Добавьте достаточное количество тестов для покрытия функции

START_TEST(test_strcspn_basic) {
    // TODO: Реализовать базовый тест
}
END_TEST

Suite *suite_strcspn(void) {
    TCase *tcase_strcspn = tcase_create("TCase strcspn");
    tcase_add_test(tcase_strcspn, test_strcspn_basic);

    Suite *suite_strcspn = suite_create("MY_STRCSPN");
    suite_add_tcase(suite_strcspn, tcase_strcspn);

    return suite_strcspn;
}
