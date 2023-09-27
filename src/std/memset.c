#include <stdlib.h>

void memset(void *dest, int c, size_t n) {
    size_t i = 0;
    char *d = (char *)dest;
    while(i < n) {
        d[i] = c % 256;
        i++;
    }
    return;
}