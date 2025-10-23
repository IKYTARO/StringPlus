#include "test.h"
#include "../my_string.h"

#include <string.h>

// TODO: Добавьте достаточное количество тестов для покрытия функции

START_TEST(test_sscanf_basic) {
    // TODO: Реализовать базовый тест
}
END_TEST

Suite *suite_sscanf(void) {
    TCase *tcase_sscanf = tcase_create("TCase sscanf");
    tcase_add_test(tcase_sscanf, test_sscanf_basic);

    Suite *suite_sscanf = suite_create("MY_SSCANF");
    suite_add_tcase(suite_sscanf, tcase_sscanf);

    return suite_sscanf;
}
