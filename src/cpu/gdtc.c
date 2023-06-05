#include "../include/gdt.h"
#include "../include/tss.h"
#include "../include/paging.h"

#include <assert.h>

void __gdt_setEntry(uint8_t *target, gdt_big_entry_t source) {
    // Check the limit to make sure that it can be encoded
    
    //if (source.limit > 0xFFFFF) {kerror("GDT cannot encode limits larger than 0xFFFFF");}
    //assert(source.limit <= 0xFFFFF);
    // Encode the limit
    target[0] = source.limit & 0xFF;
    target[1] = (source.limit >> 8) & 0xFF;
    target[6] = (source.limit >> 16) & 0x0F;
 
    // Encode the base
    target[2] = source.base & 0xFF;
    target[3] = (source.base >> 8) & 0xFF;
    target[4] = (source.base >> 16) & 0xFF;
    target[7] = (source.base >> 24) & 0xFF;
 
    // Encode the access byte
    target[5] = source.access;
 
    // Encode the flags
    target[6] |= (source.flags << 4);
}

void __gdt_init() {
    gdt_pointer_t ptr;
    gdt_big_entry_t b;

    __gdt_setEntry((uint8_t *)&__gdt_entries[NULENT], b);
    
    b.base = 0xC0000000;
    b.limit = 0x3FFFFF;
    b.access = 0x9A;
    b.flags = 0x0C;
    __gdt_setEntry((uint8_t *)&__gdt_entries[CS_KRN], b);

    b.access = 0x9A;
    __gdt_setEntry((uint8_t *)&__gdt_entries[DS_KRN], b);

    b.access = 0x89;
    b.flags = 0x00;
    b.base = (uint32_t)&__tss_global;
    b.limit = sizeof(tss_state_t);
    __gdt_setEntry((uint8_t *)&__gdt_entries[TS_STT], b);

    // __gdt_setEntry(NULENT, 0,    0   );
    // __gdt_setEntry(CS_KRN, 0x20, 0x9A);
    // __gdt_setEntry(DS_KRN, 0x20, 0x92);
    // __gdt_setEntry(CS_USR, 0x20, 0xFA);
    // __gdt_setEntry(DS_USR, 0x20, 0xF2);
    //__gdt_setEntry(TS_STT, 0x20, 0xF2);

    ptr.limit = sizeof(gdt_entry_t) * 5 - 1;
    ptr.base = (uint32_t)__gdt_entries;

    __gdt_load((uint32_t)&ptr);
}