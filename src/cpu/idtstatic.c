#include <idt.h>

idt_entry_t __idt_table[256] = {};
idt_pointer_t __idt_pointer = {};