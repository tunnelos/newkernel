#pragma once

#include <stdint.h>

#pragma pack(push, 1)

typedef struct gdt_entry_t {
    uint16_t limitLow;
    
    uint16_t baseLow;
    uint8_t  baseMiddle;

    uint8_t  access;
    uint8_t  granularity;

    uint8_t  baseHigh;
} gdt_entry_t;
typedef struct gdt_pointer_t {
    uint16_t limit;
    uint32_t base;
} gdt_pointer_t;

extern gdt_entry_t __gdt_entries[6];
extern gdt_pointer_t __gdt_pointer;

#pragma pack(pop)