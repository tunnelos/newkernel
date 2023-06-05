#pragma once

#include <stdint.h>

#pragma pack(push, 1)

typedef struct idt_entry_t {
	uint16_t isr_low;
	uint16_t kernel_cs;
	uint8_t reserved;
	uint8_t attributes;
	uint16_t isr_high;
} idt_entry_t;

typedef struct {
	uint16_t	limit;
	uint32_t	base;
} idt_pointer_t;

extern idt_entry_t __idt_table[256];
extern idt_pointer_t __idt_pointer;
extern void *__idt_stub_table[256];

void __idt_exception_handler(int interrupt_id);
void __idt_interrupt_handler(int interrupt_id);

void __idt_setDescriptor(uint8_t vec, void *isrfunc, uint8_t flags);

void __idt_init();

#pragma pack(pop)