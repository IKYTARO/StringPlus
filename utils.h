#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

bool is_space(char const symbol);

bool is_digit(char const symbol);

bool skip_spaces(char const *string, char const *format);

int write_data_to(char *dst, char const *data);

#endif