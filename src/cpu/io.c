#include "../include/io.h"

uint8_t inb(uint16_t port) {
    uint8_t val;
    asm volatile(
        "inb %%dx, %%al"
        : "=a"(val)
        : "d"(port)
    );
    return val;
}
uint16_t inw(uint16_t port) {
    uint16_t val;
    asm volatile(
        "inw %%dx, %%ax"
        : "=a"(val)
        : "d"(port)
        );
    return val;
}
uint32_t inl(uint16_t port) {
    uint32_t val;
    asm volatile(
        "inl %%edx, %%eax"
        : "=a"(val)
        : "d"(port)
    );
    return val;
}

void outb(uint16_t port, uint8_t val){
    asm volatile(
        "outb %%al, %%dx"
        :
        : "d"(port), "a"(val)
    );
    return;
}
void outw(uint16_t port, uint16_t val) {
    asm volatile(
        "outw %%ax, %%dx"
        :
        : "d"(port), "a"(val)
    );
    return;
}
void outl(uint16_t port, uint32_t val) {
    asm volatile(
        "outl %%eax, %%dx"
        :
        : "d"(port), "a"(val)
    );
    return;
}

// waits 1-4 ns
void io_wait() {
    outb(0x81, 0);
    return;
}