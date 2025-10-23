#include <stdlib.h>

#include "my_string.h"
#include "format_specifier/specifier_handler.h"

#define BUFF_MAX_SIZE 1024

int my_sprintf(char *str, char const *format, ...) {
    char *str_begin = str;
    int position = 0;
    format_specifier_type *specifier = make_format_specifier();

    va_list arg_pointer;
    va_start(arg_pointer, format);

    while (format[position] != '\0') {
        if (format[position] == '%') {
            position++;
            if (parse_format_specifier(format, &position, arg_pointer, specifier)) {
                char formatted_string[BUFF_MAX_SIZE];
                int written_chars = handle_format_specifier(specifier, arg_pointer, formatted_string);
                my_strncpy(str, formatted_string, written_chars);
                str += written_chars;
            }
        } else {
            *str = format[position];
            str++;
            position++;
        }
    }

    *str = '\0';
    va_end(arg_pointer);
    free_format_specifier(specifier);

    return str - str_begin;
}