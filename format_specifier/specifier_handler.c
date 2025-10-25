#include "specifier_handler.h"

#include "../my_types.h"

typedef struct {
    bool is_neagtive;
    char sign;
    unsigned long long absolute_value;
} argument_type;

static long long extract_integer_value(format_specifier_type const *specifier, va_list arg_pointer) {
    long long argument_value = 0;

    if (specifier->length == Short) {
        argument_value = (short)va_arg(arg_pointer, int);
    } else if (specifier->length == Long) {
        argument_value = va_arg(arg_pointer, long);
    } else if (specifier->length == LongLong) {
        argument_value = va_arg(arg_pointer, long long);
    } else {
        argument_value = va_arg(arg_pointer, int);
    }
    return argument_value;
}

static argument_type prepare_argument(format_specifier_type const *specifier, va_list arg_pointer) {
    argument_type argument = {0};
    long long argument_value = extract_integer_value(specifier, arg_pointer);

    argument.is_neagtive = (argument_value < 0);
    argument.absolute_value =
        argument.is_neagtive ? (unsigned long long)-argument_value : (unsigned long long)argument_value;
    if (argument.is_neagtive) {
        argument.sign = '-';
    } else if (specifier->flags.sign) {
        argument.sign = '+';
    } else if (specifier->flags.space) {
        argument.sign = ' ';
    } else {
        argument.sign = '\0';
    }
    return argument;
}

static int integer_to_string(char *buffer, argument_type argument, format_specifier_type const *specifier) {
    if (specifier->precision == 0 && argument.absolute_value == 0) {
        return 0;
    }

    char tmp_buffer[32];
    int value_length = 0;

    do {
        tmp_buffer[value_length] = (char)(argument.absolute_value % 10) + '0';
        value_length++;
        argument.absolute_value /= 10;
    } while (argument.absolute_value > 0);
    for (int i = 0; i < value_length; i++) {
        buffer[i] = tmp_buffer[value_length - i - 1];
    }
    return value_length;
}

static int apply_sign(char *buffer, int position, argument_type argumnet) {
    int written_chars = 0;

    if (argumnet.sign != '\0') {
        buffer[position] = argumnet.sign;
        written_chars++;
    }
    return written_chars;
}

static int apply_precision(char *buffer, int position, char *value_string, int digits_count,
                           argument_type argumnet, format_specifier_type const *specifier) {
    int written_chars = 0;
    int leading_zeros = (specifier->precision > digits_count) ? specifier->precision - digits_count : 0;

    for (; leading_zeros > 0; leading_zeros--) {
        buffer[position + written_chars] = '0';
        written_chars++;
    }
    for (int i = 0; i < digits_count; i++) {
        buffer[position + written_chars] = value_string[i];
        written_chars++;
    }
    return written_chars;
}

static int apply_alignment(char *buffer, int position, char padding, int padding_size) {
    int written_chars = 0;

    for (; padding_size > 0; padding_size--) {
        buffer[position + written_chars] = padding;
        written_chars++;
    }
    return written_chars;
}

static int apply_integer_formatting(char *buffer, char *value_string, int digits_count,
                                    argument_type argumnet, format_specifier_type const *specifier) {
    int leading_zeros = (specifier->precision > digits_count) ? specifier->precision - digits_count : 0;
    int value_length = leading_zeros + (argumnet.sign != '\0') + digits_count;
    int padding_size = (specifier->width > value_length) ? specifier->width - value_length : 0;
    char padding = (specifier->flags.zero) ? '0' : ' ';
    int written_chars = 0;

    if (specifier->flags.left) {
        written_chars += apply_sign(buffer, written_chars, argumnet);
        written_chars +=
            apply_precision(buffer, written_chars, value_string, digits_count, argumnet, specifier);
        written_chars += apply_alignment(buffer, written_chars, padding, padding_size);
    } else if (specifier->flags.zero) {
        written_chars += apply_sign(buffer, written_chars, argumnet);
        written_chars += apply_alignment(buffer, written_chars, padding, padding_size);
        written_chars +=
            apply_precision(buffer, written_chars, value_string, digits_count, argumnet, specifier);
    } else {
        written_chars += apply_alignment(buffer, written_chars, padding, padding_size);
        written_chars += apply_sign(buffer, written_chars, argumnet);
        written_chars +=
            apply_precision(buffer, written_chars, value_string, digits_count, argumnet, specifier);
    }
    buffer[written_chars] = '\0';
    return written_chars;
}

typedef int (*specifier_handler)(format_specifier_type const *specifier, va_list arg_pointer, char *buffer);

static int handle_percent(format_specifier_type const *, va_list, char *buffer) {
    *buffer = '%';
    return 1;
}

static int handle_char(format_specifier_type const *specifier, va_list arg_pointer, char *buffer) {
    char symbol = (char)va_arg(arg_pointer, unsigned);
    int written_chars = 0;

    if (specifier->flags.left) {
        buffer[written_chars] = symbol;
        written_chars++;
        if (specifier->width > 1) {
            written_chars += apply_alignment(buffer, written_chars, ' ', specifier->width - 1);
        }
    } else {
        if (specifier->width > 1) {
            written_chars += apply_alignment(buffer, written_chars, ' ', specifier->width - 1);
        }
        buffer[written_chars] = symbol;
        written_chars++;
    }
    buffer[written_chars] = '\0';
    return written_chars;
}

static int handle_integer(format_specifier_type const *specifier, va_list arg_pointer, char *buffer) {
    argument_type argumnet = prepare_argument(specifier, arg_pointer);

    char value_string[32];
    int digits_count = integer_to_string(value_string, argumnet, specifier);

    return apply_integer_formatting(buffer, value_string, digits_count, argumnet, specifier);
}

static int handle_float(format_specifier_type const *specifier, va_list arg_pointer, char *buffer) {}

static int handle_string(format_specifier_type const *specifier, va_list arg_pointer, char *buffer) {}

static int handle_unsigned(format_specifier_type const *specifier, va_list arg_pointer, char *buffer) {}

static specifier_handler get_handler_by_specifier(format_specifier_type const *specifier) {
    specifier_handler handler = NULL;

    if (specifier->converter == Char) {
        handler = handle_char;
    } else if (specifier->converter == Integer) {
        handler = handle_integer;
    } else if (specifier->converter == Float) {
        handler = handle_float;
    } else if (specifier->converter == String) {
        handler = handle_string;
    } else if (specifier->converter == Unsigned) {
        handler = handle_unsigned;
    } else {
        handler = handle_percent;
    }
    return handler;
}

int handle_format_specifier(format_specifier_type const *specifier, va_list arg_pointer, char *buffer) {
    return get_handler_by_specifier(specifier)(specifier, arg_pointer, buffer);
}