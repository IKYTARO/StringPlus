#include "my_string.h"

char *my_strpbrk(char const *str1, char const *str2) {
    if (!str1 || !str2) return MY_NULL;

    for (const char *p = str1; *p != '\0'; p++) {
        for (const char *q = str2; *q != '\0'; q++) {
            if (*p == *q) {
                return (char *)p;
            }
        }
    }
    return MY_NULL;
}