#ifndef SPECIFIER_PARSER_H
#define SPECIFIER_PARSER_H

#include <stdarg.h>
#include <stdbool.h>

typedef struct {
    bool left;
    bool sign;
    bool space;
    bool zero;
    bool hash;
} flags_type;

typedef enum { NoneLen, ShortInteger, LongInteger, LongDouble } length_type;

typedef enum {
    NoneConv,
    Char,
    Integer,
    Float,
    String,
    Unsigned,
    Percent,
    Hexadecimal,
    HexadecimalUpper,
    Octal,
    Pointer,
    Exponent,
    ExponentUpper
} converter_type;

typedef struct {
    flags_type flags;
    int width;
    int precision;
    length_type length;
    converter_type converter;
} format_specifier_type;

bool is_integer_converter(converter_type converter);

format_specifier_type *make_format_specifier();

void free_format_specifier(format_specifier_type *specifier);

bool parse_format_specifier(char const *format, int *spec_pos, va_list arg_pointer,
                            format_specifier_type *specifier);

#endif