#ifndef MY_STRING_H
#define MY_STRING_H

#include <stdlib.h>

#define size_t long unsigned int
#define NULL ((void *)0)

void *memchr(void const *str, int c, size_t n);

int memcmp(void const *str1, void const *str2, size_t n);

void *memcpy(void *dest, void const *src, size_t n);

void *memset(void *str, int c, size_t n);

char *strncat(char *dest, char const *src, size_t n);

char *strchr(char const *str, int c);

int strncmp(char const *str1, char const *str2, size_t n);

char *strncpy(char *dest, char const *src, size_t n);

size_t strcspn(char const *str1, char const *str2);

char *strerror(int errnum);

size_t strlen(char const *str);

char *strpbrk(char const *str1, char const *str2);

char *strrchr(char const *str, int c);

char *strstr(char const *haystack, char const *needle);

char *strtok(char *str, char const *delim);

void *to_upper(char const *str);

void *to_lower(char const *str);

void *insert(char const *src, char const *str, size_t start_index);

void *trim(char const *src, char const *trim_chars);

int sprintf(char *str, char const *format, ...);

int sscanf(char const *str, char const *format, ...);

#endif