#include <string.h>

#include "../my_string.h"
#include "test.h"

START_TEST(strncat_test1) {
    char str1[50] = "Hello";
    char str2[50] = "Hello";

    ck_assert_str_eq(my_strncat(str1, " World", 4), strncat(str2, " World", 4));
}
END_TEST

START_TEST(strncat_test2) {
    char str1[50] = "Test";
    char str2[50] = "Test";

    ck_assert_str_eq(my_strncat(str1, "ing123", 3), strncat(str2, "ing123", 3));
}
END_TEST

START_TEST(strncat_test3) {
    char str1[50] = "";
    char str2[50] = "";

    ck_assert_str_eq(my_strncat(str1, "Empty", 4), strncat(str2, "Empty", 4));
}
END_TEST

START_TEST(strncat_test4) {
    char str1[50] = "Start ";
    char str2[50] = "Start ";

    ck_assert_str_eq(my_strncat(str1, "Finish", 0), strncat(str2, "Finish", 0));
}
END_TEST

START_TEST(strncat_test5) {
    char str1[50] = "Line1\n";
    char str2[50] = "Line1\n";

    ck_assert_str_eq(my_strncat(str1, "Line2\nEnd", 10), strncat(str2, "Line2\nEnd", 10));
}
END_TEST

Suite *suite_strncat(void) {
    TCase *tcase_strncat = tcase_create("TCase strncat");

    tcase_add_test(tcase_strncat, strncat_test1);
    tcase_add_test(tcase_strncat, strncat_test2);
    tcase_add_test(tcase_strncat, strncat_test3);
    tcase_add_test(tcase_strncat, strncat_test4);
    tcase_add_test(tcase_strncat, strncat_test5);

    Suite *suite_strncat = suite_create("MY_STRNCAT");
    suite_add_tcase(suite_strncat, tcase_strncat);

    return suite_strncat;
}
