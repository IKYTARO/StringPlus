#include "my_string.h"

void *my_memcpy(void *dest, void const *src, my_size_t n) {
    void *result = dest;

    if (dest != MY_NULL && src != MY_NULL) {
        unsigned char *d = (unsigned char *)dest;
        const unsigned char *s = (const unsigned char *)src;

        for (my_size_t i = 0; i < n; i++) d[i] = s[i];
    } else
        result = MY_NULL;

    return result;
}