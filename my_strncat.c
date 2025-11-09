#include "my_string.h"

char *my_strncat(char *dest, char const *src, my_size_t n) {
    char *ptr = dest;
    while (*ptr) ptr++;

    my_size_t i;
    for (i = 0; i < n && src[i] != '\0'; i++) {
        ptr[i] = src[i];
    }
    ptr[i] = '\0';

    return dest;
}