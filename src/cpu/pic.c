#include <pic.h>
#include <io.h>

/**
 * source https://wiki.osdev.org/PIC
*/

/**
 * void __pic_sendEOI(uint8_t irq);
void __pic_remap(int offset1, int offset2);

void __pic_setMask(uint8_t irq);
void __pic_clearMask(uint8_t irq);

uint16_t __pic_getIRQReg(int ocw3);
uint16_t __pic_getIRR();
uint16_t __pic_getISR();
*/

void __pic_sendEOI(uint8_t irq) {
    if (irq >= 8) outb(PIC2_COMMAND, PIC_EOI);
    outb(PIC1_COMMAND, PIC_EOI);
}

void __pic_remap(int offset1, int offset2) {
	uint8_t a1, a2;
 
	a1 = inb(PIC1_DATA);                        // save masks
	a2 = inb(PIC2_DATA);
 
	outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);  // starts the initialization sequence (in cascade mode)
	io_wait();
	outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
	io_wait();
	outb(PIC1_DATA, offset1);                 // ICW2: Master PIC vector offset
	io_wait();
	outb(PIC2_DATA, offset2);                 // ICW2: Slave PIC vector offset
	io_wait();
	outb(PIC1_DATA, 4);                       // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
	io_wait();
	outb(PIC2_DATA, 2);                       // ICW3: tell Slave PIC its cascade identity (0000 0010)
	io_wait();
 
	outb(PIC1_DATA, ICW4_8086);               // ICW4: have the PICs use 8086 mode (and not 8080 mode)
	io_wait();
	outb(PIC2_DATA, ICW4_8086);
	io_wait();
 
	outb(PIC1_DATA, a1);   // restore saved masks.
	outb(PIC2_DATA, a2);
}

void __pic_remapDefault() {
    outb(0x20, 0x11);
    io_wait();
    outb(0xA0, 0x11);
    io_wait();
    outb(0x21, 0x20);
    io_wait();
    outb(0xA1, 0x70);
    io_wait();
    outb(0x21, 0x04);
    io_wait();
    outb(0xA1, 0x02);
    io_wait();
    outb(0x21, 0x01);
    io_wait();
    outb(0xA1, 0x01);
    io_wait();
    outb(0x21, inb(0x21) && 0xFC);
    io_wait();
    outb(0xA1, 0xFF);
}

void __pic_setMask(unsigned char IRQline) {
    uint16_t port = PIC1_DATA;
    uint8_t value;

    if (IRQline > 8) {
        port = PIC2_DATA;
        IRQline -= 8;
    }

    value = inb(port) | (1 << IRQline);
    outb(port, value);        
}
 
void __pic_clearMask(unsigned char IRQline) {
    uint16_t port = PIC1_DATA;
    uint8_t value;
 
    if(IRQline > 8) {
        port = PIC2_DATA;
        IRQline -= 8;
    }

    value = inb(port) & ~(1 << IRQline);
    outb(port, value);        
}

/* Helper func */
uint16_t __pic_getIRQReg(int ocw3) {
    /* OCW3 to PIC CMD to get the register values.  PIC2 is chained, and
     * represents IRQs 8-15.  PIC1 is IRQs 0-7, with 2 being the chain */
    outb(PIC1_COMMAND, ocw3);
    outb(PIC2_COMMAND, ocw3);
    return (inb(PIC2_COMMAND) << 8) | inb(PIC1_COMMAND);
}
 
/* Returns the combined value of the cascaded PICs irq request register */
uint16_t __pic_getIRR(void) {
    return __pic_getIRQReg(PIC_READ_IRR);
}
 
/* Returns the combined value of the cascaded PICs in-service register */
uint16_t __pic_getISR(void) {
    return __pic_getIRQReg(PIC_READ_ISR);
}