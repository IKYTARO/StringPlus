#include <string.h>

#include "../my_string.h"
#include "test.h"

START_TEST(test_strlen_empty) { ck_assert_int_eq(my_strlen(""), strlen("")); }
END_TEST

START_TEST(test_strlen_single_char) {
    ck_assert_int_eq(my_strlen("a"), strlen("a"));
    ck_assert_int_eq(my_strlen(" "), strlen(" "));
    ck_assert_int_eq(my_strlen("\0"), strlen("\0"));
}
END_TEST

START_TEST(test_strlen_short_strings) {
    ck_assert_int_eq(my_strlen("12"), strlen("12"));
    ck_assert_int_eq(my_strlen("ab"), strlen("ab"));
    ck_assert_int_eq(my_strlen("!@"), strlen("!@"));
}
END_TEST

START_TEST(test_strlen_common_words) {
    ck_assert_int_eq(my_strlen("hello"), strlen("hello"));
    ck_assert_int_eq(my_strlen("world"), strlen("world"));
    ck_assert_int_eq(my_strlen("test"), strlen("test"));
}
END_TEST

START_TEST(test_strlen_long_strings) {
    ck_assert_int_eq(my_strlen("veryVeryVeryLongWord"), strlen("veryVeryVeryLongWord"));
    ck_assert_int_eq(my_strlen("ThisIsAVeryLongStringForTestingPurposes"),
                     strlen("ThisIsAVeryLongStringForTestingPurposes"));
}
END_TEST

START_TEST(test_strlen_special_chars) {
    ck_assert_int_eq(my_strlen("hello\nworld"), strlen("hello\nworld"));
    ck_assert_int_eq(my_strlen("tab\tcharacter"), strlen("tab\tcharacter"));
    ck_assert_int_eq(my_strlen("null\0in_middle"), strlen("null\0in_middle"));
}
END_TEST

START_TEST(test_strlen_numbers) {
    ck_assert_int_eq(my_strlen("1234567890"), strlen("1234567890"));
    ck_assert_int_eq(my_strlen("1a2b3c4d"), strlen("1a2b3c4d"));
}
END_TEST

START_TEST(test_strlen_punctuation) {
    ck_assert_int_eq(my_strlen("Hello, World!"), strlen("Hello, World!"));
    ck_assert_int_eq(my_strlen("test@email.com"), strlen("test@email.com"));
    ck_assert_int_eq(my_strlen("path/to/file"), strlen("path/to/file"));
}
END_TEST

START_TEST(test_strlen_utf8) {
    ck_assert_int_eq(my_strlen("привет"), strlen("привет"));
    ck_assert_int_eq(my_strlen("🎉"), strlen("🎉"));
    ck_assert_int_eq(my_strlen("café"), strlen("café"));
}
END_TEST

START_TEST(test_strlen_repeated_chars) {
    ck_assert_int_eq(my_strlen("aaaaa"), strlen("aaaaa"));
    ck_assert_int_eq(my_strlen("ababab"), strlen("ababab"));
}
END_TEST

START_TEST(test_strlen_max_length) {
    char long_str[1024];
    memset(long_str, 'a', sizeof(long_str) - 1);
    long_str[sizeof(long_str) - 1] = '\0';

    ck_assert_int_eq(my_strlen(long_str), strlen(long_str));
}
END_TEST

Suite *suite_strlen(void) {
    TCase *tcase_strlen = tcase_create("TCase strlen");
    tcase_add_test(tcase_strlen, test_strlen_empty);
    tcase_add_test(tcase_strlen, test_strlen_single_char);
    tcase_add_test(tcase_strlen, test_strlen_short_strings);
    tcase_add_test(tcase_strlen, test_strlen_common_words);
    tcase_add_test(tcase_strlen, test_strlen_long_strings);
    tcase_add_test(tcase_strlen, test_strlen_special_chars);
    tcase_add_test(tcase_strlen, test_strlen_numbers);
    tcase_add_test(tcase_strlen, test_strlen_punctuation);
    tcase_add_test(tcase_strlen, test_strlen_repeated_chars);
    tcase_add_test(tcase_strlen, test_strlen_max_length);
    tcase_add_test(tcase_strlen, test_strlen_utf8);

    Suite *suite_strlen = suite_create("MY_STRLEN");
    suite_add_tcase(suite_strlen, tcase_strlen);

    return suite_strlen;
}