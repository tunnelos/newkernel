#pragma once

#include <stddef.h>

size_t strlen(const char *str);

char *tolower(char *data);
char tolowerchar(char data);

int strncmp(const char *s1, const char *s2, size_t n);
int strcmp(const char *s1, const char *s2);

char *strcpy(char *dest, const char *src);
char *strncpy(char *dest, const char *src, size_t n);

char *strchr(const char *s, char c);
char *strrchr(const char *s, char c);
float strtof(const char *nptr, char **endptr);
char *strcat(char *dest, const char *src);
char *strncat(char *dest, const char *src, size_t n);