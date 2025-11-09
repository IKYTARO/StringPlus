#ifndef SPECIFIER_HANDLER_H
#define SPECIFIER_HANDLER_H

#include <stdarg.h>

#include "specifier_parser.h"

int copy_buff(char *dest, char const *src, int size);

int handle_format_specifier(format_specifier_type const *specifier, va_list arg_pointer, char *buffer);

#endif