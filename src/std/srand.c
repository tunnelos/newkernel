#include <stdlib.h>

int __stdlib_seed = 0;

void srand(int seed) {
    __stdlib_seed = seed;
    return;
}