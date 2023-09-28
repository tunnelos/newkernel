#pragma once

#include <stdbool.h>
#include <stddef.h>

void putc(const char c);
void puts(const char *str);

void printf(const char *fmt, ...);
void sprintf(char *buffer, const char *fmt, ...);

char *itoa(int num, char *buffer, int base);
int itoa2(int num, char *buffer, int zeros);
char itoh(int num, bool upper);

char *ftoa(float num, char *buffer);
char *ftoa_ex(float num, char *buffer, int afterpoints);

int atoi(const char *str);

char *strrev(char *src);
char *strnrev(char *src, size_t len);