#ifndef SPRINTF_TESTS_H
#define SPRINTF_TESTS_H

#include <check.h>

TCase *tcase_percent(void);
TCase *tcase_integer(void);
TCase *tcase_char(void);
TCase *tcase_unsigned(void);
TCase *tcase_string(void);
TCase *tcase_float(void);
TCase *tcase_hex_octal(void);
TCase *tcase_pointer(void);
TCase *tcase_exponent(void);

#endif