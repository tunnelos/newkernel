#include <stdlib.h>

void *memcpy(void *dest, const void *src, const size_t size) {
    size_t i = 0;
    char *d = (char *)dest;
    char *s = (char *)src;
    while(i < size) {
        d[i] = s[i];
        i++;
    }

    return dest;
}