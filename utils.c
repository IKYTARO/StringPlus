#include "utils.h"

bool is_space(char symbol) { return (symbol == ' ' || symbol == '\t'); }

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