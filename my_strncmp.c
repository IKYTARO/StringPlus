#include "my_string.h"

int my_strncmp(char const *str1, char const *str2, my_size_t n) {
    int result = 0;
    for (my_size_t id = 0; id < n; id++) {
        if (str1[id] != str2[id]) {
            result = (unsigned char)str1[id] - (unsigned char)str2[id];
            break;
        } else if (str1[id] == '\0') {
            result = 0;
            break;
        }
    }
    return result;
}