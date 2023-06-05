#pragma once

#include <stddef.h>

void *memcpy(void *dest, const void *src, const size_t size);
void memset(void *dest, int c, size_t n);

void *malloc(size_t size);
void *calloc(int count, size_t size);
void *realloc(void *address, size_t size);
void free(void *address);