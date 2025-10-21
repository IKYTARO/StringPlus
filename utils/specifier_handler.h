#ifndef SPECIFIER_HANDLER_H
#define SPECIFIER_HANDLER_H

#include <stdarg.h>

#include "specifier_parser.h"
#include "../my_types.h"

int handle_format_specifier(format_specifier_type const *specifier, va_list arg_pointer, char *buffer, size_t buff_size);

#endif