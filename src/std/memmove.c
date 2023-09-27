#include <string.h>

void *memmove(void *dest, const void *src, size_t n) {
    char *d = (char *)dest;
    char const *s = (char const *)(src);

    if (s < d) {
        s += n;
        d += n;
        while (n--) *--d = *--s;
    } else {
        while (n--) *d++ = *s++;
    }

    return dest;
}