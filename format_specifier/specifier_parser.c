#include "specifier_parser.h"

#include <limits.h>
#include <stdlib.h>

static bool is_digit(char const symbol) { return (symbol >= '0' && symbol <= '9'); }

static bool is_flag(char const symbol) {
    return (symbol == '-' || symbol == '+' || symbol == ' ' || symbol == '0' || symbol == '#');
}

static void reset_flags(flags_type *flags) {
    flags->left = false;
    flags->sign = false;
    flags->space = false;
    flags->zero = false;
    flags->hash = false;
}

static bool is_converter(char const symbol) {
    return (symbol == 'c' || symbol == 'd' || symbol == 'f' || symbol == 's' || symbol == 'u' ||
            symbol == '%' || symbol == 'x' || symbol == 'X' || symbol == 'o' || symbol == 'p' ||
            symbol == 'e' || symbol == 'E');
}

bool is_integer_converter(converter_type converter) {
    return (converter == Integer || converter == Unsigned);
}

static bool is_float_converter(converter_type converter) {
    return (converter == Float || converter == Exponent || converter == ExponentUpper);
}

static void read_flags(char const *string, int *position, flags_type *flags) {
    while (is_flag(string[*position])) {
        switch (string[*position]) {
            case '-':
                flags->left = true;
                break;
            case '+':
                flags->sign = true;
                break;
            case ' ':
                flags->space = true;
                break;
            case '0':
                flags->zero = true;
                break;
            case '#':
                flags->hash = true;
                break;
            default:
                break;
        }
        (*position)++;
    }
}

static bool read_number(char const *string, int *position, va_list arg_pointer, int *value) {
    bool value_overflow = false;

    if (string[*position] == '*') {
        *value = va_arg(arg_pointer, int);
        (*position)++;
    } else {
        while (is_digit(string[*position])) {
            char digit = string[*position];
            if (*value > INT_MAX / 10 || (*value == INT_MAX / 10 && digit > INT_MAX % 10)) {
                value_overflow = true;
                (*position)++;
                continue;
            }
            *value = (*value) * 10 + (digit - '0');
            (*position)++;
        }
    }

    return !value_overflow;
}

static bool read_length(char const *string, int *position, length_type *length) {
    bool valid_symbol = true;
    switch (string[*position]) {
        case 'h':
            *length = ShortInteger;
            (*position)++;
            break;
        case 'l':
            *length = LongInteger;
            (*position)++;
            break;
        case 'L':
            *length = LongDouble;
            (*position)++;
            break;
        default:
            valid_symbol = is_converter(string[*position]);
            break;
    }

    return valid_symbol;
}

static bool read_converter(char const *string, int *position, converter_type *converter) {
    bool valid_symbol = true;

    if (string[*position] == 'c') {
        *converter = Char;
    } else if (string[*position] == 'd') {
        *converter = Integer;
    } else if (string[*position] == 'f') {
        *converter = Float;
    } else if (string[*position] == 's') {
        *converter = String;
    } else if (string[*position] == 'u') {
        *converter = Unsigned;
    } else if (string[*position] == '%') {
        *converter = Percent;
    } else if (string[*position] == 'x') {
        *converter = Hexadecimal;
    } else if (string[*position] == 'X') {
        *converter = HexadecimalUpper;
    } else if (string[*position] == 'o') {
        *converter = Octal;
    } else if (string[*position] == 'p') {
        *converter = Pointer;
    } else if (string[*position] == 'e') {
        *converter = Exponent;
    } else if (string[*position] == 'E') {
        *converter = ExponentUpper;
    } else {
        valid_symbol = false;
    }
    if (valid_symbol) (*position)++;

    return valid_symbol;
}

static void reset_format_specifier(format_specifier_type *specifier) {
    if (specifier) {
        reset_flags(&specifier->flags);
        specifier->width = 0;
        specifier->precision = -1;
        specifier->length = NoneLen;
        specifier->converter = NoneConv;
    }
}

static void normalize_format_specifier(format_specifier_type *specifier) {
    if (specifier->flags.left) specifier->flags.zero = false;
    if (specifier->precision >= 0) {
        if (is_integer_converter(specifier->converter)) {
            specifier->flags.zero = false;
        }
    }
    if (specifier->flags.sign) {
        specifier->flags.space = false;
    }
    if (is_float_converter(specifier->converter) && specifier->precision == -1) {
        specifier->precision = 6;
    }
}

format_specifier_type *make_format_specifier() {
    format_specifier_type *specifier = (format_specifier_type *)calloc(1, sizeof(format_specifier_type));
    return specifier;
}

void free_format_specifier(format_specifier_type *specifier) { free(specifier); }

bool parse_format_specifier(char const *format, int *spec_pos, va_list arg_pointer,
                            format_specifier_type *specifier) {
    int initial_specifier_pos = *spec_pos;
    bool parsing_success = true;

    reset_format_specifier(specifier);
    read_flags(format, spec_pos, &specifier->flags);
    parsing_success = read_number(format, spec_pos, arg_pointer, &specifier->width);
    if (parsing_success && format[*spec_pos] == '.') {
        (*spec_pos)++;
        specifier->precision = 0;
        parsing_success = read_number(format, spec_pos, arg_pointer, &specifier->precision);
    }
    if (parsing_success) {
        parsing_success = read_length(format, spec_pos, &specifier->length);
    }
    if (parsing_success) {
        parsing_success = read_converter(format, spec_pos, &specifier->converter);
    }
    normalize_format_specifier(specifier);
    if (!parsing_success) {
        *spec_pos = initial_specifier_pos;
    }

    return parsing_success;
}