#include "../include/paging.h"

#include <stdint.h>

void *__paging_getPhysical(void *virt) {
    uint32_t pdindex = (uint32_t)virt >> 22;
    uint32_t ptindex = (uint32_t)virt >> 12 & 0x03FF;
 
    uint32_t *pd = (uint32_t *)0xFFFFF000;
    // Here you need to check whether the PD entry is present.
 
    uint32_t *pt = ((uint32_t *)0xFFC00000) + (0x400 * pdindex);
    // Here you need to check whether the PT entry is present.
 
    return (void *)((pt[ptindex] & ~0xFFF) + ((uint32_t)virt & 0xFFF));
}