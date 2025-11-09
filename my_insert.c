#include <stdlib.h>

#include "my_string.h"

void *my_insert(char const *src, char const *str, my_size_t start_index) {
    char *result = MY_NULL;

    if (src != MY_NULL && str != MY_NULL) {
        my_size_t src_len = my_strlen(src);
        my_size_t str_len = my_strlen(str);

        if (start_index > src_len) {
            return MY_NULL;
        }

        my_size_t new_len = src_len + str_len;
        result = (char *)calloc(new_len + 1, sizeof(char));

        if (result != MY_NULL) {
            for (my_size_t i = 0; i < start_index; i++) {
                result[i] = src[i];
            }

            for (my_size_t i = 0; i < str_len; i++) {
                result[start_index + i] = str[i];
            }

            for (my_size_t i = start_index; i < src_len; i++) {
                result[str_len + i] = src[i];
            }

            result[new_len] = '\0';
        }
    }

    return result;
}