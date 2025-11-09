#include "my_string.h"

my_size_t my_strlen(char const *str) {
    char const *symbol_pointer = str;
    while (*symbol_pointer != '\0') symbol_pointer++;

    return symbol_pointer - str;
}