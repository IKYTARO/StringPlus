#include "my_string.h"

void *my_memchr(void const *str, int c, size_t n) {}

int my_memcmp(void const *str1, void const *str2, size_t n) {}

void *my_memcpy(void *dest, void const *src, size_t n) {}

void *my_memset(void *str, int c, size_t n) {}

char *my_strncat(char *dest, char const *src, size_t n) {}

char *my_strchr(char const *str, int c) {}

int my_strncmp(char const *str1, char const *str2, size_t n) {
    int result = 0;
    if (n > 0) {
        while (*str1 && *str2 && n > 0 && *str1 == *str2) {
            str1++;
            str2++;
            n--;
        }
        result = *str1 - *str2;
    }
    return result;
}

char *my_strncpy(char *dest, char const *src, size_t n) {
    if (n > 0) {
        while (n > 0) {
            if (*src)
                *dest = *src;
            else
                *dest = '\0';
            dest++;
            src++;
            n--;
        }
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