#include <stdlib.h>

#include "my_string.h"
#include "utils/utils.h"

char *my_strncpy(char *dest, char const *src, size_t n) {
    if (n == 0) return dest;

    size_t src_len = my_strlen(src);
    char *src_copy = (char *)calloc(src_len + 1, sizeof(char));
    write_data_to(src_copy, src);
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