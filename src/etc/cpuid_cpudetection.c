#include <stdint.h>

#include <external/cpuid.h>

unsigned int __tools_get_cpu() {
    uint32_t eax, ebx, u1, u2;
    __cpuid(1, eax, ebx, u1, u2);
    return (ebx >> 24) + 1;
}