#include "specifier_handler.h"

#include <stdlib.h>

#include "utils.h"
#include "../my_types.h"

typedef struct {
    bool is_neagtive;
    char sign;
    unsigned long long absolute_value;
} number_type;

static long long extract_integer_arg(format_specifier_type const *specifier, va_list arg_pointer) {
    switch (specifier->length) {
        case NoneLen: return va_arg(arg_pointer, int);
        case Short: return (short)va_arg(arg_pointer, int);
        case Long: return va_arg(arg_pointer, long);
        case LongLong: return va_arg(arg_pointer, long long);
        default: return 0;
    }
}

static void prepare_number(format_specifier_type const *specifier, va_list arg_pointer, number_type *number) {
    long long arg_value = extract_integer_arg(specifier, arg_pointer);

    number->is_neagtive = (arg_value < 0);
    number->absolute_value = number->is_neagtive ? -arg_value : arg_value;
    if (number->is_neagtive) {
        number->sign = '-';
    } else if (specifier->flags.sign) {
        number->sign = ' ';
    } else if (specifier->flags.space) {
        number->sign = ' ';
    } else {
        number->sign = '\0';
    }
}

typedef int (*specifier_handler)(format_specifier_type const *specifier, va_list arg_pointer, char *buffer, size_t buff_size);

static int handle_percent(format_specifier_type const *, va_list, char *buffer, size_t) {
    *buffer = '%';
    return 1;
}

static int handle_char(format_specifier_type const *specifier, va_list arg_pointer, char *buffer, size_t buff_size) {}

static int handle_integer(format_specifier_type const *specifier, va_list arg_pointer, char *buffer, size_t buff_size) {
    return integer_to_string(va_arg(arg_pointer, int), buffer);
}

static int handle_float(format_specifier_type const *specifier, va_list arg_pointer, char *buffer, size_t buff_size) {}

static int handle_string(format_specifier_type const *specifier, va_list arg_pointer, char *buffer, size_t buff_size) {}

static int handle_unsigned(format_specifier_type const *specifier, va_list arg_pointer, char *buffer, size_t buff_size) {}

static specifier_handler get_handler_by_specifier(format_specifier_type const *specifier) {
    if (specifier->converter == Char) {
        return handle_char;
    }
    if (specifier->converter == Integer) {
        return handle_integer;
    }
    if (specifier->converter == Float) {
        return handle_float;
    }
    if (specifier->converter == String) {
        return handle_string;
    }
    if (specifier->converter == Unsigned) {
        return handle_unsigned;
    }
    if (specifier->converter == Percent) {
        return handle_percent;
    }
}

int handle_format_specifier(format_specifier_type const *specifier, va_list arg_pointer, char *buffer, size_t buff_size) {
    return get_handler_by_specifier(specifier)(specifier, arg_pointer, buffer, buff_size);
}