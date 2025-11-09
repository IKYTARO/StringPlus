#include "my_string.h"

int my_memcmp(void const *str1, void const *str2, my_size_t n) {
    const unsigned char *s1 = (unsigned char *)str1;
    const unsigned char *s2 = (unsigned char *)str2;

    int result = 0;

    for (my_size_t i = 0; i < n && result == 0; i++) {
        if (s1[i] != s2[i]) {
            result = s1[i] - s2[i];
        }
    }

    return result;
}