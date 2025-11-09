#include "my_string.h"

char *my_strncpy(char *dest, char const *src, my_size_t n) {
    if (n == 0) {
        return dest;
    }

    my_size_t id = 0;
    for (; id < n && src[id] != '\0'; id++) {
        dest[id] = src[id];
    }
    for (; id < n; id++) {
        dest[id] = '\0';
    }

    return dest;
}