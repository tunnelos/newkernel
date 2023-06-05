#pragma once

#include <stdint.h>

#pragma pack(push, 1)

typedef struct tss_state_t {
    uint16_t link;
    uint16_t rsv0;

    uint32_t esp0;
    
    uint16_t ss0;
    uint16_t rsv1;

    uint32_t esp1;

    uint16_t ss1;
    uint16_t rsv2;

    uint32_t esp2;

    uint16_t ss2;
    uint16_t rsv3;

    uint32_t cr3;

    uint32_t eip;

    uint32_t eflags;

    uint32_t eax;
    uint32_t ecx;
    uint32_t edx;
    uint32_t ebx;
    uint32_t esp;
    uint32_t ebp;
    uint32_t esi;
    uint32_t edi;

    uint16_t es;
    uint16_t rsv4;

    uint16_t cs;
    uint16_t rsv5;

    uint16_t ss;
    uint16_t rsv6;

    uint16_t ds;
    uint16_t rsv7;

    uint16_t fs;
    uint16_t rsv8;

    uint16_t gs;
    uint16_t rsv9;

    uint16_t ldtr;
    uint16_t rsv10;

    uint16_t rsv11;
    uint16_t iopb;

    uint32_t ssp;
} tss_state_t;

extern tss_state_t __tss_global;

#pragma pack(pop)