#include <stdlib.h>

extern int __stdlib_seed;

int rand() {
    __stdlib_seed = __stdlib_seed * 1103515245 + 12345;
    return (unsigned int) (__stdlib_seed / 65536) % 32768;
}