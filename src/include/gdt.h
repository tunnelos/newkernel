#pragma once

#include <stdint.h>

#pragma pack(push, 1)

#define NULENT 0
#define CS_KRN 1
#define DS_KRN 2
#define CS_USR 3
#define DS_USR 4
#define TS_STT 5

typedef struct gdt_entry_t {
    uint16_t limitLow;
    
    uint16_t baseLow;
    uint8_t  baseMiddle;

    uint8_t  access;
    uint8_t  flags;

    uint8_t  baseHigh;
} gdt_entry_t;
typedef struct gdt_big_entry_t {
    uint32_t limit;
    uint32_t base;
    uint8_t access;
    uint8_t flags;
} gdt_big_entry_t;
typedef struct gdt_pointer_t {
    uint16_t limit;
    uint32_t base;
} gdt_pointer_t;

extern gdt_entry_t __gdt_entries[6];
extern gdt_pointer_t __gdt_pointer;

void __gdt_setEntry(uint8_t *target, gdt_big_entry_t source);
void __gdt_init();
void __gdt_load(uint32_t gdt_ptr);

#pragma pack(pop)