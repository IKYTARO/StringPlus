#include "my_string.h"

char *my_strrchr(char const *str, int c) {
    char *last = MY_NULL;

    do {
        if (*str == (char)c) {
            last = (char *)str;
        }
    } while (*str++);

    return last;
}