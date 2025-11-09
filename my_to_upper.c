#include <stdlib.h>

#include "my_string.h"

void *my_to_upper(char const *str) {
    char *result = MY_NULL;
    if (str) {
        my_size_t len = my_strlen(str);
        result = (char *)malloc(len + 1);

        if (result != MY_NULL) {
            for (my_size_t i = 0; i < len; ++i) {
                char c = str[i];
                if (c >= 'a' && c <= 'z') c = c - ('a' - 'A');
                result[i] = c;
            }
            result[len] = '\0';
        }
    }
    return result;
}