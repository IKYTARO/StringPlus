#include <stdlib.h>

#include "my_string.h"

char *my_strncpy(char *dest, char const *src, size_t n) {
    if (n == 0) return dest;

    size_t src_len = my_strlen(src);
    char *src_copy = (char *)calloc(src_len + 1, sizeof(char));
    for (int i = 0; i < src_len; i++) {
        src_copy[i] = src[i];
    }
    src_copy[src_len] = '\0';

    size_t id = 0;
    for (; id < n && src[id] != '\0'; id++) {
        dest[id] = src_copy[id];
    }
    for (; id < n; id++) {
        dest[id] = '\0';
    }

    free(src_copy);

    return dest;
}