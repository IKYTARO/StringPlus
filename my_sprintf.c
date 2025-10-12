#include <stdlib.h>

#include "my_string.h"
#include "specifier_handler.h"
#include "specifier_parser.h"
#include "utils.h"

int my_sprintf(char *str, char const *format, ...) {
    char *str_begin = str;

    va_list arg_pointer;
    va_start(arg_pointer, format);

    format_specifier_type *specifier = make_format_specifier();

    int position = 0;
    while (format[position] != '\0') {
        if (format[position] == '%') {
            position++;
            if (parse_format_specifier(format, &position, specifier)) {
                char *formatted_string = handle_format_specifier(specifier, arg_pointer);
                str += write_data_to(str, formatted_string);
                free(formatted_string);
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