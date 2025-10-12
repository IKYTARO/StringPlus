#ifndef SPECIFIER_HANDLER_H
#define SPECIFIER_HANDLER_H

#include <stdarg.h>

#include "specifier_parser.h"

char *handle_format_specifier(format_specifier_type const *specifier, va_list arg_pointer);

#endif