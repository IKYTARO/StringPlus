#include <stdlib.h>

#include "my_string.h"

void *my_trim(char const *src, char const *trim_chars) {
    char *result = MY_NULL;

    if (src != MY_NULL && trim_chars != MY_NULL) {
        my_size_t start = 0;
        my_size_t end = my_strlen(src);

        while (start < end && my_strchr(trim_chars, src[start]) != MY_NULL) {
            start++;
        }
        while (end > start && my_strchr(trim_chars, src[end - 1]) != MY_NULL) {
            end--;
        }

        if (start == end) {
            result = (char *)calloc(1, sizeof(char));
            if (result) result[0] = '\0';
            return result;
        }

        my_size_t len = end - start;

        result = (char *)calloc(len + 1, sizeof(char));

        if (result) {
            for (my_size_t i = 0; i < len; i++) {
                result[i] = src[start + i];
            }
            result[len] = '\0';
        }
    }

    return (void *)result;
}