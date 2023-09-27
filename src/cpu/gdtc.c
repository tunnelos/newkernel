#include <gdt.h>
#include <tss.h>

#include <assert.h>

void __gdt_setEntry(uint8_t *target, gdt_big_entry_t source) {
    // Check the limit to make sure that it can be encoded
    
    //if (source.limit > 0xFFFFF) {kerror("GDT cannot encode limits larger than 0xFFFFF");}
    // printf("%X %X\n", source.limit, source.base);
    // assert(source.limit < 0xFFFFF || source.limit == 0xFFFFF);
    // if (source.limit > 0xFFFFF) {
    //     source.limit = 0xFFFFF;
    // }
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

gdt_pointer_t __gdt_ptr = {};

extern uint32_t _kernel_text_start;
extern uint32_t _kernel_data_start;

void __gdt_init() {
    gdt_big_entry_t b = {};

    __gdt_setEntry((uint8_t *)&__gdt_entries[NULENT], b);
    
    b.base = 0xC0000000;
    b.limit = 0x000FFFFF;
    b.access = 0b10011010;
    b.flags = 0x20;
    __gdt_setEntry((uint8_t *)&__gdt_entries[CS_KRN], b);    

    b.base = 0xC0000000;
    b.limit = 0x000FFFFF;
    b.flags = 0x20;
    b.access = 0b10011010;
    __gdt_setEntry((uint8_t *)&__gdt_entries[DS_KRN], b);

    b.access = 0x89;
    b.flags = 0x00;
    b.base = (uint32_t)&__tss_global;
    b.limit = sizeof(tss_state_t);
    __gdt_setEntry((uint8_t *)&__gdt_entries[TS_STT], b);

    __gdt_ptr.limit = sizeof(gdt_entry_t) * 6 - 1;
    __gdt_ptr.base = (uint32_t)__gdt_entries;

    __gdt_load((uint32_t)&__gdt_ptr);
}