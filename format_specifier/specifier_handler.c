#include "specifier_handler.h"

#include <math.h>

#include "../my_string.h"

/* Копирование буфера */
int copy_buff(char *dest, char const *src, int size) {
    for (int i = 0; i < size; i++) {
        dest[i] = src[i];
    }
    return size;
}

/* numerical_type - тип для представления числовых значений */
typedef struct {
    unsigned long long integer_part;     // целая часть
    unsigned long long fractional_part;  // дробная часть
    int fractional_size;                 // размер дробной части
    bool is_negative;                    // флаг отрицательного числа
    char sign;                           // знак ('+', '-', ' ', '\0')
} numerical_type;

/* exponent_type - тип для представления числа в экспоненциальной нотации */
typedef struct {
    numerical_type mantissa;  // мантисса
    int exponent;             // экспонента
    char symbol;              // символ ('e' или 'E')
} exponent_type;

/* Извлечение аргументов из va_list */
static long long extract_integer_value(format_specifier_type const *specifier, va_list arg_pointer);
static unsigned long long extract_unsigned_value(format_specifier_type const *specifier, va_list arg_pointer);
static long double extract_float_value(format_specifier_type const *specifier, va_list arg_pointer);

/* Разбиение числа на целую и дробную часть с учетом точности */
static void set_float_parts(long double value, format_specifier_type const *specifier,
                            numerical_type *argument);

/* Проверка краевых случаев - nan, inf */
static bool is_special_float(long double value);

/* Определение знака числа */
static void set_sign(format_specifier_type const *specifier, bool is_negative, char *sign);
static void set_argument_sign(format_specifier_type const *specifier, numerical_type *argument);

/* Подготовка числовых аргументов */
static numerical_type prepare_integer_argument(format_specifier_type const *specifier, va_list arg_pointer);
static numerical_type prepare_float_argument(format_specifier_type const *specifier, long double value);
static numerical_type prepare_pointer_argument(unsigned long addr);
static exponent_type prepare_exponent_argument(format_specifier_type const *specifier,
                                               long double argument_value);

/* Преобразование чисел в строки */
static int integer_to_string_base(char *buffer, unsigned long long value,
                                  format_specifier_type const *specifier, int base, bool is_upper);
static int float_to_string(char *buffer, numerical_type argument, format_specifier_type const *specifier);
static int exponent_to_string(char *buffer, exponent_type argument, format_specifier_type const *specifier);

/* Применение элементов форматирования */
static int apply_sign(char *buffer, char sign);
static int apply_comma(char *buffer, numerical_type argument, format_specifier_type const *specifier);
static int apply_prefix(char *buffer, format_specifier_type const *specifier);
static int apply_integer_precision(char *buffer, int position, const char *value_string, int digits_count,
                                   format_specifier_type const *specifier);
static int apply_padding(char *buffer, char padding, int padding_size);

/* Основное форматирование */
static int apply_string_formatting(char *buffer, const char *string, my_size_t string_length,
                                   format_specifier_type const *specifier);
static int apply_integer_base_formatting(char *buffer, const char *value_string, int digits_count,
                                         numerical_type argument, format_specifier_type const *specifier);
static int apply_float_formatting(char *buffer, const char *argument_string, int argument_length,
                                  format_specifier_type const *specifier);

/* Специализированные обработчики для указателей */
static int handle_null_pointer(char *buffer, format_specifier_type const *specifier);
static int handle_valid_pointer(char *buffer, format_specifier_type const *specifier, unsigned long addr);

/* Обработка краевых значений float (nan, inf) */
static int handle_special_float(long double value, format_specifier_type const *specifier, char *buffer);

/* Обработчики для каждого типа спецификатора */
static int handle_percent(format_specifier_type const *specifier, va_list arg_pointer, char *buffer);
static int handle_char_type(format_specifier_type const *specifier, va_list arg_pointer, char *buffer);
static int handle_integer_base_type(format_specifier_type const *specifier, va_list arg_pointer,
                                    char *buffer);
static int handle_float_type(format_specifier_type const *specifier, va_list arg_pointer, char *buffer);
static int handle_string_type(format_specifier_type const *specifier, va_list arg_pointer, char *buffer);
static int handle_pointer_type(format_specifier_type const *specifier, va_list arg_pointer, char *buffer);
static int handle_exponent_type(format_specifier_type const *specifier, va_list arg_pointer, char *buffer);

/* Тип указателя на функцию-обработчик */
typedef int (*specifier_handler)(format_specifier_type const *specifier, va_list arg_pointer, char *buffer);

/* Диспетчер обработчиков */
static specifier_handler get_handler_by_specifier(format_specifier_type const *specifier);

int handle_format_specifier(format_specifier_type const *specifier, va_list arg_pointer, char *buffer) {
    specifier_handler handler = get_handler_by_specifier(specifier);
    if (handler) {
        return handler(specifier, arg_pointer, buffer);
    }

    return ERROR_RETURN;
}

static long long extract_integer_value(format_specifier_type const *specifier, va_list arg_pointer) {
    long long argument_value = 0;

    if (specifier->length == ShortInteger) {
        argument_value = (short)va_arg(arg_pointer, int);
    } else if (specifier->length == LongInteger) {
        argument_value = va_arg(arg_pointer, long);
    } else {
        argument_value = va_arg(arg_pointer, int);
    }
    return argument_value;
}

static unsigned long long extract_unsigned_value(format_specifier_type const *specifier,
                                                 va_list arg_pointer) {
    unsigned long long argument_value = 0;

    if (specifier->length == ShortInteger) {
        argument_value = (unsigned short)va_arg(arg_pointer, unsigned int);
    } else if (specifier->length == LongInteger) {
        argument_value = va_arg(arg_pointer, unsigned long);
    } else {
        argument_value = va_arg(arg_pointer, unsigned int);
    }
    return argument_value;
}

static long double extract_float_value(format_specifier_type const *specifier, va_list arg_pointer) {
    long double argument_value = 0.0;

    if (specifier->length == LongDouble) {
        argument_value = va_arg(arg_pointer, long double);
    } else {
        argument_value = va_arg(arg_pointer, double);
    }
    return argument_value;
}

static void set_float_parts(long double value, format_specifier_type const *specifier,
                            numerical_type *argument) {
    argument->integer_part = (unsigned long long)value;

    long double precision_scaler = powl(10.0, specifier->precision);
    long double scaled_fractional = (value - argument->integer_part) * precision_scaler;
    argument->fractional_part = (unsigned long long)lrint(scaled_fractional);

    if (argument->fractional_part >= (unsigned long long)precision_scaler) {
        argument->integer_part++;
        argument->fractional_part = 0;
    }
    argument->fractional_size = specifier->precision;
}

static void set_sign(format_specifier_type const *specifier, bool is_negative, char *sign) {
    if (is_negative) {
        *sign = '-';
    } else if (specifier->flags.sign) {
        *sign = '+';
    } else if (specifier->flags.space) {
        *sign = ' ';
    } else {
        *sign = '\0';
    }
}

static void set_argument_sign(format_specifier_type const *specifier, numerical_type *argument) {
    if (specifier->converter == Unsigned) {
        argument->sign = '\0';
    } else {
        set_sign(specifier, argument->is_negative, &argument->sign);
    }
}

static numerical_type prepare_integer_argument(format_specifier_type const *specifier, va_list arg_pointer) {
    numerical_type argument = {0};

    if (specifier->converter == Integer) {
        long long argument_value = extract_integer_value(specifier, arg_pointer);
        argument.is_negative = (argument_value < 0);
        argument.integer_part =
            argument.is_negative ? (unsigned long long)-argument_value : (unsigned long long)argument_value;
    }
    if (specifier->converter == Unsigned || specifier->converter == Hexadecimal ||
        specifier->converter == HexadecimalUpper || specifier->converter == Octal) {
        argument.is_negative = false;
        argument.integer_part = extract_unsigned_value(specifier, arg_pointer);
    }
    argument.fractional_part = 0;
    argument.fractional_size = 0;
    set_argument_sign(specifier, &argument);
    return argument;
}

static numerical_type prepare_float_argument(format_specifier_type const *specifier, long double value) {
    numerical_type argument = {0};

    argument.is_negative = (bool)signbit(value);
    long double absolute_value = (argument.is_negative) ? -value : value;
    set_float_parts(absolute_value, specifier, &argument);
    set_argument_sign(specifier, &argument);
    return argument;
}

static numerical_type prepare_pointer_argument(unsigned long addr) {
    numerical_type argument = {0};

    argument.integer_part = addr;
    argument.fractional_part = 0;
    argument.fractional_size = 0;
    argument.is_negative = false;
    argument.sign = '\0';

    return argument;
}

static exponent_type prepare_exponent_argument(format_specifier_type const *specifier,
                                               long double argument_value) {
    exponent_type argument = {0};

    if (argument_value == 0.0) {
        argument.exponent = 0;
    } else {
        argument.exponent = (int)floor(log10(fabsl(argument_value)));
    }

    long double normalized_value = argument_value / powl(10.0, argument.exponent);
    argument.mantissa = prepare_float_argument(specifier, normalized_value);
    if (argument.mantissa.integer_part >= 10) {
        argument.mantissa.integer_part /= 10;
        argument.exponent++;
    }

    if (specifier->converter == Exponent) {
        argument.symbol = 'e';
    } else if (specifier->converter == ExponentUpper) {
        argument.symbol = 'E';
    } else {
        argument.symbol = '\0';
    }

    return argument;
}

static int integer_to_string_base(char *buffer, unsigned long long value,
                                  format_specifier_type const *specifier, int base, bool is_upper) {
    if (specifier->precision == 0 && value == 0 && is_integer_converter(specifier->converter)) {
        return 0;
    }

    const char *digits = is_upper ? "0123456789ABCDEF" : "0123456789abcdef";
    char tmp_buffer[64];
    int value_length = 0;

    do {
        tmp_buffer[value_length] = digits[value % base];
        value_length++;
        value /= base;
    } while (value > 0);

    for (int i = 0; i < value_length; i++) {
        buffer[i] = tmp_buffer[value_length - i - 1];
    }

    return value_length;
}

static int apply_sign(char *buffer, char sign) {
    int written_chars = 0;

    if (sign == '+' || sign == '-' || sign == ' ') {
        *buffer = sign;
        written_chars++;
    }
    return written_chars;
}

static int apply_comma(char *buffer, numerical_type argument, format_specifier_type const *specifier) {
    int written_chars = 0;

    if (argument.fractional_size > 0 || specifier->flags.hash) {
        *buffer = '.';
        written_chars++;
    }
    return written_chars;
}

static int apply_prefix(char *buffer, format_specifier_type const *specifier) {
    int written_chars = 0;

    if (specifier->flags.hash) {
        switch (specifier->converter) {
            case Hexadecimal:
                buffer[written_chars++] = '0';
                buffer[written_chars++] = 'x';
                break;
            case HexadecimalUpper:
                buffer[written_chars++] = '0';
                buffer[written_chars++] = 'X';
                break;
            case Octal:
                buffer[written_chars++] = '0';
                break;
            default:
                break;
        }
    }
    if (specifier->converter == Pointer) {
        buffer[written_chars++] = '0';
        buffer[written_chars++] = 'x';
    }
    return written_chars;
}

static int apply_integer_precision(char *buffer, int position, const char *value_string, int digits_count,
                                   format_specifier_type const *specifier) {
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

static int apply_padding(char *buffer, char padding, int padding_size) {
    int written_chars = 0;

    for (; padding_size > 0; padding_size--) {
        buffer[written_chars] = padding;
        written_chars++;
    }
    return written_chars;
}

static int apply_string_formatting(char *buffer, const char *string, my_size_t string_length,
                                   format_specifier_type const *specifier) {
    int written_chars = 0, padding_size = 0;

    if (specifier->width > (int)string_length) {
        padding_size = specifier->width - (int)string_length;
    }
    if (specifier->flags.left) {
        written_chars += copy_buff(buffer, string, (int)string_length);
        written_chars += apply_padding(buffer + written_chars, ' ', padding_size);
    } else {
        written_chars += apply_padding(buffer + written_chars, ' ', padding_size);
        written_chars += copy_buff(buffer + written_chars, string, (int)string_length);
    }
    return written_chars;
}

static int apply_integer_base_formatting(char *buffer, const char *value_string, int digits_count,
                                         numerical_type argumnet, format_specifier_type const *specifier) {
    int prefix_length = 0;
    if (specifier->flags.hash) {
        if (specifier->converter == Hexadecimal || specifier->converter == HexadecimalUpper) {
            prefix_length = 2;
        } else if (specifier->converter == Octal && argumnet.integer_part != 0) {
            prefix_length = 1;
        }
    }
    if (specifier->converter == Pointer) {
        prefix_length = 2;
    }

    int leading_zeros = (specifier->precision > digits_count) ? specifier->precision - digits_count : 0;
    int value_length = leading_zeros + prefix_length + digits_count;
    if (argumnet.sign != '\0') value_length++;
    int padding_size = (specifier->width > value_length) ? specifier->width - value_length : 0;
    char padding = (specifier->flags.zero) ? '0' : ' ';
    int written_chars = 0;

    if (specifier->flags.left) {
        written_chars += apply_sign(buffer + written_chars, argumnet.sign);
        written_chars += apply_prefix(buffer + written_chars, specifier);
        written_chars +=
            apply_integer_precision(buffer, written_chars, value_string, digits_count, specifier);
        written_chars += apply_padding(buffer + written_chars, padding, padding_size);
    } else if (specifier->flags.zero) {
        written_chars += apply_sign(buffer + written_chars, argumnet.sign);
        written_chars += apply_prefix(buffer + written_chars, specifier);
        written_chars += apply_padding(buffer + written_chars, padding, padding_size);
        written_chars +=
            apply_integer_precision(buffer, written_chars, value_string, digits_count, specifier);
    } else {
        written_chars += apply_padding(buffer + written_chars, padding, padding_size);
        written_chars += apply_sign(buffer + written_chars, argumnet.sign);
        written_chars += apply_prefix(buffer + written_chars, specifier);
        written_chars +=
            apply_integer_precision(buffer, written_chars, value_string, digits_count, specifier);
    }
    buffer[written_chars] = '\0';
    return written_chars;
}

static int float_to_string(char *buffer, numerical_type argument, format_specifier_type const *specifier) {
    int argument_length = 0;

    argument_length += apply_sign(buffer, argument.sign);
    argument_length +=
        integer_to_string_base(buffer + argument_length, argument.integer_part, specifier, 10, false);
    argument_length += apply_comma(buffer + argument_length, argument, specifier);

    if (argument.fractional_size > 0) {
        char fractional_buffer[64] = {0};
        int fractional_length =
            integer_to_string_base(fractional_buffer, argument.fractional_part, specifier, 10, false);

        int leading_zeros = argument.fractional_size - fractional_length;
        argument_length += apply_padding(buffer + argument_length, '0', leading_zeros);

        for (int i = 0; i < fractional_length; i++, argument_length++) {
            buffer[argument_length] = fractional_buffer[i];
        }
    }

    return argument_length;
}

static int apply_float_formatting(char *buffer, const char *argument_string, int argument_lenght,
                                  format_specifier_type const *specifier) {
    int written_chars = 0;
    int padding_size = specifier->width - argument_lenght;

    if (specifier->flags.left) {
        written_chars += copy_buff(buffer, argument_string, argument_lenght);
        written_chars += apply_padding(buffer + written_chars, ' ', padding_size);
    } else if (specifier->flags.zero) {
        int sign_length = apply_sign(buffer, argument_string[0]);
        written_chars += sign_length;

        written_chars += apply_padding(buffer + written_chars, '0', padding_size);
        written_chars +=
            copy_buff(buffer + written_chars, argument_string + sign_length, argument_lenght - sign_length);
    } else {
        written_chars += apply_padding(buffer, ' ', padding_size);
        written_chars += copy_buff(buffer + written_chars, argument_string, argument_lenght);
    }
    return written_chars;
}

static int handle_percent(format_specifier_type const *, va_list, char *buffer) {
    *buffer = '%';
    return 1;
}

static int handle_char_type(format_specifier_type const *specifier, va_list arg_pointer, char *buffer) {
    char symbol = (char)va_arg(arg_pointer, unsigned);
    int written_chars = 0;

    if (specifier->flags.left) {
        buffer[written_chars] = symbol;
        written_chars++;
        if (specifier->width > 1) {
            written_chars += apply_padding(buffer + written_chars, ' ', specifier->width - 1);
        }
    } else {
        if (specifier->width > 1) {
            written_chars += apply_padding(buffer + written_chars, ' ', specifier->width - 1);
        }
        buffer[written_chars] = symbol;
        written_chars++;
    }
    buffer[written_chars] = '\0';
    return written_chars;
}

static int handle_integer_base_type(format_specifier_type const *specifier, va_list arg_pointer,
                                    char *buffer) {
    numerical_type argument = prepare_integer_argument(specifier, arg_pointer);

    char argument_string[64] = {0};
    int digits_count = 0;
    if (specifier->converter == Hexadecimal) {
        digits_count = integer_to_string_base(argument_string, argument.integer_part, specifier, 16, false);
    } else if (specifier->converter == HexadecimalUpper) {
        digits_count = integer_to_string_base(argument_string, argument.integer_part, specifier, 16, true);
    } else if (specifier->converter == Octal) {
        digits_count = integer_to_string_base(argument_string, argument.integer_part, specifier, 8, false);
    } else {
        digits_count = integer_to_string_base(argument_string, argument.integer_part, specifier, 10, false);
    }

    return apply_integer_base_formatting(buffer, argument_string, digits_count, argument, specifier);
}

static bool is_special_float(long double value) {
    return (isnan(value) || value == INFINITY || value == -INFINITY);
}

static int handle_special_float(long double value, format_specifier_type const *specifier, char *buffer) {
    char sign = '\0';
    const char *edge_value = MY_NULL;
    bool is_negative = false, is_upper = (specifier->converter == ExponentUpper);

    if (isnan(value)) {
        edge_value = is_upper ? "NAN" : "nan";
        is_negative = signbit(value);
    } else {
        edge_value = is_upper ? "INF" : "inf";
        is_negative = (value < 0);
    }

    set_sign(specifier, is_negative, &sign);

    char edge_string[4] = {0};
    int sign_length = apply_sign(edge_string, sign);
    copy_buff(edge_string + sign_length, edge_value, 3);

    return apply_string_formatting(buffer, edge_string, (my_size_t)(sign_length + 3), specifier);
}

static int handle_float_type(format_specifier_type const *specifier, va_list arg_pointer, char *buffer) {
    long double argument_value = extract_float_value(specifier, arg_pointer);

    if (is_special_float(argument_value)) {
        return handle_special_float(argument_value, specifier, buffer);
    }

    numerical_type argument = prepare_float_argument(specifier, argument_value);

    char argument_string[512] = {0};
    int argument_length = float_to_string(argument_string, argument, specifier);

    return apply_float_formatting(buffer, argument_string, argument_length, specifier);
}

static int handle_string_type(format_specifier_type const *specifier, va_list arg_pointer, char *buffer) {
    const char *string = va_arg(arg_pointer, char *);
    if (string == MY_NULL) {
        string = "(null)";
    }

    int string_length = (int)my_strlen(string);
    if (specifier->precision >= 0 && specifier->precision < string_length) {
        string_length = specifier->precision;
    }

    return apply_string_formatting(buffer, string, (my_size_t)string_length, specifier);
}
static int handle_null_pointer(char *buffer, format_specifier_type const *specifier) {
    int written_chars = 0;
    char const *nullptr_string = "(nil)";
    int padding_size = (specifier->width > 5) ? specifier->width - 5 : 0;

    if (specifier->flags.left) {
        written_chars += copy_buff(buffer, nullptr_string, 5);
        written_chars += apply_padding(buffer + written_chars, ' ', padding_size);
    } else {
        written_chars += apply_padding(buffer, ' ', padding_size);
        written_chars += copy_buff(buffer + written_chars, nullptr_string, 5);
    }

    return written_chars;
}

static int handle_valid_pointer(char *buffer, format_specifier_type const *specifier, unsigned long addr) {
    numerical_type argument = prepare_pointer_argument(addr);

    char argument_string[64] = {0};
    int argument_length =
        integer_to_string_base(argument_string, argument.integer_part, specifier, 16, false);

    return apply_integer_base_formatting(buffer, argument_string, argument_length, argument, specifier);
}

static int handle_pointer_type(format_specifier_type const *specifier, va_list arg_pointer, char *buffer) {
    void *pointer = va_arg(arg_pointer, void *);
    int written_chars = 0;

    if (pointer == MY_NULL) {
        written_chars = handle_null_pointer(buffer, specifier);
    } else {
        written_chars = handle_valid_pointer(buffer, specifier, (unsigned long)pointer);
    }

    return written_chars;
}

static int exponent_to_string(char *buffer, exponent_type argument, format_specifier_type const *specifier) {
    int argument_length = float_to_string(buffer, argument.mantissa, specifier);

    char exponent_sign;
    unsigned exponent_value;
    if (argument.exponent < 0) {
        exponent_sign = '-';
        exponent_value = (unsigned)-argument.exponent;
    } else {
        exponent_sign = '+';
        exponent_value = (unsigned)argument.exponent;
    }

    buffer[argument_length++] = argument.symbol;
    buffer[argument_length++] = exponent_sign;
    if (exponent_value < 10) {
        buffer[argument_length++] = '0';
    }

    char exponent_value_string[6];
    int digits_count = integer_to_string_base(exponent_value_string, exponent_value, specifier, 10, false);

    argument_length += copy_buff(buffer + argument_length, exponent_value_string, digits_count);

    return argument_length;
}

static int handle_exponent_type(format_specifier_type const *specifier, va_list arg_pointer, char *buffer) {
    long double argument_value = extract_float_value(specifier, arg_pointer);

    if (is_special_float(argument_value)) {
        return handle_special_float(argument_value, specifier, buffer);
    }

    exponent_type argument = prepare_exponent_argument(specifier, argument_value);

    char argument_string[512] = {0};
    int argument_length = exponent_to_string(argument_string, argument, specifier);

    return apply_float_formatting(buffer, argument_string, argument_length, specifier);
}

static specifier_handler get_handler_by_specifier(format_specifier_type const *specifier) {
    specifier_handler handler;

    if (specifier->converter == Char) {
        handler = handle_char_type;
    } else if (specifier->converter == Integer || specifier->converter == Unsigned ||
               specifier->converter == Hexadecimal || specifier->converter == HexadecimalUpper ||
               specifier->converter == Octal) {
        handler = handle_integer_base_type;
    } else if (specifier->converter == Float) {
        handler = handle_float_type;
    } else if (specifier->converter == String) {
        handler = handle_string_type;
    } else if (specifier->converter == Pointer) {
        handler = handle_pointer_type;
    } else if (specifier->converter == Percent) {
        handler = handle_percent;
    } else if (specifier->converter == Exponent || specifier->converter == ExponentUpper) {
        handler = handle_exponent_type;
    } else {
        handler = MY_NULL;
    }

    return handler;
}