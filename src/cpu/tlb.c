#include "../include/tlb.h"

// source: linux kernel
void __tlb_flush(uint32_t address) {
    asm volatile("invlpg (%0)" ::"r" (address) : "memory");
}