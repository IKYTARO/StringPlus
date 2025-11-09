#include "my_string.h"

char *my_strstr(char const *haystack, char const *needle) {
    const char *result = MY_NULL;

    if (haystack && needle) {
        if (!*needle) {
            result = haystack;
        } else {
            const char *h = haystack;
            while (*h && !result) {
                const char *h_sub = h;
                const char *n = needle;

                while (*h_sub && *n && (*h_sub == *n)) {
                    h_sub++;
                    n++;
                }

                if (!*n)
                    result = h;
                else
                    h++;
            }
        }
    }

    return (char *)result;
}