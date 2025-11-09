#include "my_string.h"

static int is_delim(char c, const char *delim) {
    int result = 0;
    for (my_size_t i = 0; delim[i]; i++) {
        if (c == delim[i]) {
            result = 1;
            break;
        }
    }
    return result;
}

char *my_strtok(char *str, char const *delim) {
    static char *last = MY_NULL;
    char *token = MY_NULL;

    if (str != MY_NULL) last = str;

    if (last != MY_NULL) {
        while (*last && is_delim(*last, delim)) last++;

        if (*last == '\0')
            last = MY_NULL;
        else {
            token = last;
            while (*last && !is_delim(*last, delim)) last++;

            if (*last) {
                *last = '\0';
                last++;
            } else
                last = MY_NULL;
        }
    }
    return token;
}