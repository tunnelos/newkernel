#include <drivers/ide/ide.h>

void __ide_write(uint8_t channel, uint8_t reg, uint8_t data) {
    ide_channel_reg_t cc = __ide_channels[channel];
    if(reg > 0x07 && reg < 0x0C) __ide_write(channel, ATA_REG_CONTROL, 0x80 | cc.no_int);
    if(reg < 0x08) outb(cc.base + reg, data);
    else if (reg < 0x0C) outb(cc.base + reg - 0x06, data);
    else if (reg < 0x0E) outb(cc.ctrl + reg - 0x0A, data);
    else if (reg < 0x16) outb(cc.bmide + reg - 0x0E, data);
    if (reg > 0x07 && reg < 0x0C) __ide_write(channel, ATA_REG_CONTROL, cc.no_int);
}