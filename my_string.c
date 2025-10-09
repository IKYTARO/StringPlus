#include "my_string.h"

#include <stdio.h>

void *my_memchr(void const *str, int c, size_t n) {}

int my_memcmp(void const *str1, void const *str2, size_t n) {}

void *my_memcpy(void *dest, void const *src, size_t n) {}

void *my_memset(void *str, int c, size_t n) {}

char *my_strncat(char *dest, char const *src, size_t n) {}

char *my_strchr(char const *str, int c) {}

int my_strncmp(char const *str1, char const *str2, size_t n) {
    int result = 0;
    for (size_t id = 0; id < n; id++) {
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

char *my_strncpy(char *dest, char const *src, size_t n) {
    size_t id = 0;
    for (; id < n && src[id] != '\0'; id++) {
        dest[id] = src[id];
    }
    for (; id < n; id++) {
        dest[id] = '\0';
    }
    return dest;
}

size_t my_strcspn(char const *str1, char const *str2) {}

char *my_strerror(int errnum) {}

size_t my_strlen(char const *str) {
    char const *symbol_pointer = str;
    while (*symbol_pointer != '\0') symbol_pointer++;

    return symbol_pointer - str;
}

char *my_strpbrk(char const *str1, char const *str2) {}

char *my_strrchr(char const *str, int c) {}

char *my_strstr(char const *haystack, char const *needle) {}

char *my_strtok(char *str, char const *delim) {}

void *my_to_upper(char const *str) {}

void *my_to_lower(char const *str) {}

void *my_insert(char const *src, char const *str, size_t start_index) {}

void *my_trim(char const *src, char const *trim_chars) {}