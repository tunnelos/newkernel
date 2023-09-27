#include <idt.h>
#include <idt_stubs.h>
#include <serial.h>
#include <io.h>

void *__idt_stub_table[256] = {};

void __idt_exception_handler(int interrupt_id, void *eip, uint32_t cs, uint32_t eflags) {
    __serial_write_fmt("Exception %d", interrupt_id);
    __serial_write_fmt(" at 0x%X!\r\n", eip);

    while (true) {
        __serial_write_fmt("Exception %d", interrupt_id);
        __serial_write_fmt(" at 0x%X!\r\n", eip); 
    }
}
void __idt_interrupt_handler(int interrupt_id, void *eip, uint32_t cs, uint32_t eflags) {
    __serial_write_fmt("Interrupt %d!\r\n", interrupt_id);
}

void __idt_setDescriptor(uint8_t vec, void *isrfunc, uint8_t flags) {
    idt_entry_t *entry = &__idt_table[vec];
    entry->isr_low = (uint32_t)isrfunc & 0xFFFF;
    entry->kernel_cs = 0x01; // change to 0x08 if it gonna crash
    entry->attributes = flags;
    entry->isr_high = (uint32_t)isrfunc >> 16;
    entry->reserved = 0;
}

void __idt_init() {
    __asm__ volatile ("cli"); // unset the interrupt flag

    __idt_pointer.base = (uint32_t)__idt_table;
    __idt_pointer.limit = (uint16_t)sizeof(idt_entry_t) * 256 - 1;

    __idt_stub_table[0] = isr_stub_0;
    __idt_stub_table[1] = isr_stub_1;
    __idt_stub_table[2] = isr_stub_2;
    __idt_stub_table[3] = isr_stub_3;
    __idt_stub_table[4] = isr_stub_4;
    __idt_stub_table[5] = isr_stub_5;
    __idt_stub_table[6] = isr_stub_6;
    __idt_stub_table[7] = isr_stub_7;
    __idt_stub_table[8] = isr_stub_8;
    __idt_stub_table[9] = isr_stub_9;
    __idt_stub_table[10] = isr_stub_10;
    __idt_stub_table[11] = isr_stub_11;
    __idt_stub_table[12] = isr_stub_12;
    __idt_stub_table[13] = isr_stub_13;
    __idt_stub_table[14] = isr_stub_14;
    __idt_stub_table[15] = isr_stub_15;
    __idt_stub_table[16] = isr_stub_16;
    __idt_stub_table[17] = isr_stub_17;
    __idt_stub_table[18] = isr_stub_18;
    __idt_stub_table[19] = isr_stub_19;
    __idt_stub_table[20] = isr_stub_20;
    __idt_stub_table[21] = isr_stub_21;
    __idt_stub_table[22] = isr_stub_22;
    __idt_stub_table[23] = isr_stub_23;
    __idt_stub_table[24] = isr_stub_24;
    __idt_stub_table[25] = isr_stub_25;
    __idt_stub_table[26] = isr_stub_26;
    __idt_stub_table[27] = isr_stub_27;
    __idt_stub_table[28] = isr_stub_28;
    __idt_stub_table[29] = isr_stub_29;
    __idt_stub_table[30] = isr_stub_30;
    __idt_stub_table[31] = isr_stub_31;

    int vec = 0;

    while(vec < (256 - 32)) { 
        __idt_stub_table[vec + 32] = isr_stub_31;

        vec++;
    }
    
    vec = 0;

    while(vec < 256) {
        __idt_setDescriptor(vec, __idt_stub_table[vec], 0x8E);
        vec++;
    }

    outb(0x20, 0x11); io_wait();
    outb(0xA0, 0x11); io_wait();
    outb(0x21, 0x20); io_wait();
    outb(0xA1, 0x28); io_wait();
    outb(0x21, 0x04); io_wait();
    outb(0xA1, 0x02); io_wait();
    outb(0x21, 0x01); io_wait();
    outb(0xa1, 0X91); io_wait();
    outb(0x21, 0x00); io_wait();
    outb(0xA1, 0x00); io_wait();

    __asm__ volatile ("lidt %0" : : "m"(__idt_pointer)); // load the new IDT
    __asm__ volatile ("sti"); // set the interrupt flag
    // __asm__ volatile ("int $9");
    // __asm__ volatile ("int $9");
    // __asm__ volatile ("int $9");
    // __asm__ volatile ("int $9");
    // __asm__ volatile ("ret");
}
