#include <drivers/ide/ide.h>

uint8_t __ide_read(uint8_t channel, uint8_t reg) {
    uint8_t res = 0;
    ide_channel_reg_t cc = __ide_channels[channel];
    if(reg > 0x07 && reg < 0x0C) __ide_write(channel, ATA_REG_CONTROL, 0x80 | __ide_channels[channel].no_int);
    if(reg < 0x08) res = inb(cc.base + reg);
    else if (reg < 0x0C) res = inb(cc.base + reg - 6);
    else if (reg < 0x0E) res = inb(cc.ctrl + reg - 0x0A);
    else if (reg < 0x16) res = inb(cc.bmide + reg - 0x0E);
    if (reg > 0x07 && reg < 0x0C) __ide_write(channel, ATA_REG_CONTROL, cc.no_int);
    return res;
}