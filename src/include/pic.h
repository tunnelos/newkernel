#pragma once

#define PIC1		0x20		/* IO base address for master PIC */
#define PIC2		0xA0		/* IO base address for slave PIC */
#define PIC1_COMMAND	PIC1
#define PIC1_DATA	(PIC1+1)
#define PIC2_COMMAND	PIC2
#define PIC2_DATA	(PIC2+1)
#define PIC_READ_IRR 0x0A    /* OCW3 irq ready next CMD read */
#define PIC_READ_ISR 0x0B    /* OCW3 irq service next CMD read */
#define PIC_EOI		 0x20	 /* End-of-interrupt command code */

#include "pic_icw.h"

#include <stdint.h>

void __pic_sendEOI(uint8_t irq);

void __pic_remap(int offset1, int offset2);
void __pic_remapDefault();

void __pic_setMask(uint8_t irq);
void __pic_clearMask(uint8_t irq);

uint16_t __pic_getIRQReg(int ocw3);
uint16_t __pic_getIRR();
uint16_t __pic_getISR();