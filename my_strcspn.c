#include "my_string.h"

my_size_t my_strcspn(char const *str1, char const *str2) {
    unsigned char tmp[256] = {0};
    const unsigned char *p1 = (const unsigned char *)str1;
    const unsigned char *p2 = (const unsigned char *)str2;
    my_size_t result = 0;
    int found = 0;

    while (*p2) tmp[*p2++] = 1;

    while (*p1 && !found) {
        if (tmp[*p1])
            found = 1;
        else {
            result++;
            p1++;
        }
    }

    return result;
}