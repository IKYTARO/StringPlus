#include "utils.h"

#include "../my_string.h"

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

static void reverse(char *string) {
    int symbol;
    size_t i, j;

    for (i = 0, j = my_strlen(string) - 1; i < j; i++, j--) {
        symbol = string[i];
        string[i] = string[j];
        string[j] = symbol;
    }
}

int integer_to_string(int number, char *string) {
    int position = 0, sign = number;

    if (sign < 0) number = -number;
    while (number > 0) {
        string[position] = number % 10 + '0';
        position++;
        number /= 10;
    }
    if (sign < 0) {
        string[position] = '-';
        position++;
    }
    string[position] = '\0';
    reverse(string);
    return (position - 1);
}