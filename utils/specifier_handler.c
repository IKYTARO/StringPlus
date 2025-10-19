#include "specifier_handler.h"

#include <stdlib.h>

#include "utils.h"
#include "../my_types.h"

static char *handle_percent() {
    char *result = (char *)calloc(1, sizeof(char));
    *result = '%';
    return result;
}

static char *handle_char(format_specifier_type const *specifier, va_list arg_pointer) {}

static char *handle_integer(format_specifier_type const *specifier, va_list arg_pointer) {
    char *result = (char *)calloc(10, sizeof(char));
    integer_to_string(va_arg(arg_pointer, int), result);
    return result;
}

static char *handle_float(format_specifier_type const *specifier, va_list arg_pointer) {}

static char *handle_string(format_specifier_type const *specifier, va_list arg_pointer) {}

static char *handle_unsigned(format_specifier_type const *specifier, va_list arg_pointer) {}

char *handle_format_specifier(format_specifier_type const *specifier, va_list arg_pointer) {
    char *formatted_string = NULL;
    switch (specifier->converter) {
        case Char:
            formatted_string = handle_char(specifier, arg_pointer);
            break;
        case Integer:
            formatted_string = handle_integer(specifier, arg_pointer);
            break;
        case Float:
            formatted_string = handle_float(specifier, arg_pointer);
            break;
        case String:
            formatted_string = handle_string(specifier, arg_pointer);
            break;
        case Unsigned:
            formatted_string = handle_unsigned(specifier, arg_pointer);
            break;
        case Percent:
            formatted_string = handle_percent();
            break;
        default:
            break;
    }

    return formatted_string;
}