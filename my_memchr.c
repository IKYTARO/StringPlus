#include "my_string.h"

void *my_memchr(void const *str, int c, my_size_t n) {
    const unsigned char *str_str = (const unsigned char *)str;
    const unsigned char *result = MY_NULL;

    for (int i = 0; i < (int)n; i++) {
        if (str_str[i] == (unsigned char)c) {
            result = str_str + i;
            break;
        }
    }
    return (void *)result;
}