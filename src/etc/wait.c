#include <tools.h>

#include <io.h>

void wait(uint32_t ms) {
    uint32_t i = 0;

    int cpu = __tools_get_cpu() - 1;

    uint16_t port = 0x80 - cpu;

    while(i < ms * 10000) {
        outb(port, 0);
        i++;
    }
    return;
}