#include "utils.h"

bool is_space(char const symbol) { return (symbol == ' ' || symbol == '\t'); }

bool is_digit(char const symbol) { return (symbol >= '0' && symbol <= '9'); }

bool skip_spaces(char const *string, char const *format) {
    bool processing_status = true;
    while (is_space(*string)) {
        if (*string == *format) {
            string++;
            format++;
        } else {
            processing_status = false;
        }
    }

    return processing_status;
}

int write_data_to(char *dst, char const *data) {
    int char_written = 0;
    while (*data) {
        *dst = *data;
        data++;
        dst++;
        char_written++;
    }
    return char_written;
}