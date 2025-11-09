#include <string.h>

#include "../my_string.h"
#include "test.h"

START_TEST(test_strtok_basic) {
    char str1[] = "Hello world test";
    char str2[] = "Hello world test";
    const char *delim = " ";
    char *t1 = my_strtok(str1, delim);
    char *t2 = strtok(str2, delim);
    while (t1 || t2) {
        ck_assert_str_eq(t1, t2);
        t1 = my_strtok(MY_NULL, delim);
        t2 = strtok(MY_NULL, delim);
    }
}
END_TEST

START_TEST(test_strtok_no_delim) {
    char str1[] = "apple";
    char str2[] = "apple";
    const char *delim = ",";
    char *t1 = my_strtok(str1, delim);
    char *t2 = strtok(str2, delim);
    ck_assert_str_eq(t1, t2);
    ck_assert_ptr_eq(my_strtok(MY_NULL, delim), strtok(MY_NULL, delim));
}
END_TEST

START_TEST(test_strtok_empty_string) {
    char str1[] = "";
    char str2[] = "";
    const char *delim = ",";
    ck_assert_ptr_eq(my_strtok(str1, delim), strtok(str2, delim));
}
END_TEST

START_TEST(test_strtok_all_delims) {
    char str1[] = ",,,";
    char str2[] = ",,,";
    const char *delim = ",";
    ck_assert_ptr_eq(my_strtok(str1, delim), strtok(str2, delim));
}
END_TEST

START_TEST(test_strtok_multiple_delims) {
    char str1[] = "one,,two,,,three";
    char str2[] = "one,,two,,,three";
    const char *delim = ",";
    char *t1 = my_strtok(str1, delim);
    char *t2 = strtok(str2, delim);
    while (t1 || t2) {
        ck_assert_str_eq(t1, t2);
        t1 = my_strtok(MY_NULL, delim);
        t2 = strtok(MY_NULL, delim);
    }
}
END_TEST

START_TEST(test_strtok_leading_trailing) {
    char str1[] = ",,apple,banana,";
    char str2[] = ",,apple,banana,";
    const char *delim = ",";
    char *t1 = my_strtok(str1, delim);
    char *t2 = strtok(str2, delim);
    while (t1 || t2) {
        ck_assert_str_eq(t1, t2);
        t1 = my_strtok(MY_NULL, delim);
        t2 = strtok(MY_NULL, delim);
    }
}
END_TEST

START_TEST(test_strtok_spaces_tabs) {
    char str1[] = "  one\t two   three\t";
    char str2[] = "  one\t two   three\t";
    const char *delim = " \t";
    char *t1 = my_strtok(str1, delim);
    char *t2 = strtok(str2, delim);
    while (t1 || t2) {
        ck_assert_str_eq(t1, t2);
        t1 = my_strtok(MY_NULL, delim);
        t2 = strtok(MY_NULL, delim);
    }
}
END_TEST

START_TEST(test_strtok_mixed_delims) {
    char str1[] = "cat;dog,bird fish";
    char str2[] = "cat;dog,bird fish";
    const char *delim = ";, ";
    char *t1 = my_strtok(str1, delim);
    char *t2 = strtok(str2, delim);
    while (t1 || t2) {
        ck_assert_str_eq(t1, t2);
        t1 = my_strtok(MY_NULL, delim);
        t2 = strtok(MY_NULL, delim);
    }
}
END_TEST

START_TEST(test_strtok_numbers) {
    char str1[] = "123,456,789";
    char str2[] = "123,456,789";
    const char *delim = ",";
    char *t1 = my_strtok(str1, delim);
    char *t2 = strtok(str2, delim);
    while (t1 || t2) {
        ck_assert_str_eq(t1, t2);
        t1 = my_strtok(MY_NULL, delim);
        t2 = strtok(MY_NULL, delim);
    }
}
END_TEST

START_TEST(test_strtok_special_chars) {
    char str1[] = "word1@word2#word3$word4";
    char str2[] = "word1@word2#word3$word4";
    const char *delim = "@#$";
    char *t1 = my_strtok(str1, delim);
    char *t2 = strtok(str2, delim);
    while (t1 || t2) {
        ck_assert_str_eq(t1, t2);
        t1 = my_strtok(MY_NULL, delim);
        t2 = strtok(MY_NULL, delim);
    }
}
END_TEST

START_TEST(test_strtok_long_string) {
    char str1[256] = "a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p";
    char str2[256];
    strcpy(str2, str1);
    const char *delim = ",";
    char *t1 = my_strtok(str1, delim);
    char *t2 = strtok(str2, delim);
    while (t1 || t2) {
        ck_assert_str_eq(t1, t2);
        t1 = my_strtok(MY_NULL, delim);
        t2 = strtok(MY_NULL, delim);
    }
}
END_TEST

START_TEST(test_strtok_unicode) {
    char str1[] = "кошка,собака,птица";
    char str2[] = "кошка,собака,птица";
    const char *delim = ",";
    char *t1 = my_strtok(str1, delim);
    char *t2 = strtok(str2, delim);
    while (t1 || t2) {
        ck_assert_str_eq(t1, t2);
        t1 = my_strtok(MY_NULL, delim);
        t2 = strtok(MY_NULL, delim);
    }
}
END_TEST

START_TEST(test_strtok_delim_in_middle_only) {
    char str1[] = "token1,token2";
    char str2[] = "token1,token2";
    const char *delim = ",";
    char *t1 = my_strtok(str1, delim);
    char *t2 = strtok(str2, delim);
    while (t1 || t2) {
        ck_assert_str_eq(t1, t2);
        t1 = my_strtok(MY_NULL, delim);
        t2 = strtok(MY_NULL, delim);
    }
}
END_TEST

START_TEST(test_strtok_mixed_spaces_and_commas) {
    char str1[] = "a, b ,c , d";
    char str2[] = "a, b ,c , d";
    const char *delim = " ,";
    char *t1 = my_strtok(str1, delim);
    char *t2 = strtok(str2, delim);
    while (t1 || t2) {
        ck_assert_str_eq(t1, t2);
        t1 = my_strtok(MY_NULL, delim);
        t2 = strtok(MY_NULL, delim);
    }
}
END_TEST

START_TEST(test_strtok_empty_delim) {
    char str1[] = "abc";
    const char *delim = "";
    my_strtok(str1, delim);
    ck_assert_ptr_nonnull(str1);
}
END_TEST

Suite *suite_strtok(void) {
    TCase *tcase_strtok = tcase_create("TCase strtok");
    tcase_add_test(tcase_strtok, test_strtok_basic);
    tcase_add_test(tcase_strtok, test_strtok_no_delim);
    tcase_add_test(tcase_strtok, test_strtok_empty_string);
    tcase_add_test(tcase_strtok, test_strtok_all_delims);
    tcase_add_test(tcase_strtok, test_strtok_multiple_delims);
    tcase_add_test(tcase_strtok, test_strtok_leading_trailing);
    tcase_add_test(tcase_strtok, test_strtok_spaces_tabs);
    tcase_add_test(tcase_strtok, test_strtok_mixed_delims);
    tcase_add_test(tcase_strtok, test_strtok_numbers);
    tcase_add_test(tcase_strtok, test_strtok_special_chars);
    tcase_add_test(tcase_strtok, test_strtok_long_string);
    tcase_add_test(tcase_strtok, test_strtok_unicode);
    tcase_add_test(tcase_strtok, test_strtok_delim_in_middle_only);
    tcase_add_test(tcase_strtok, test_strtok_mixed_spaces_and_commas);
    tcase_add_test(tcase_strtok, test_strtok_empty_delim);

    Suite *suite_strtok = suite_create("MY_STRTOK");
    suite_add_tcase(suite_strtok, tcase_strtok);

    return suite_strtok;
}
