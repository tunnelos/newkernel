#include <drivers/ide/ide.h>

void __ide_read_buffer(uint8_t channel, uint8_t reg, uint32_t *buffer, uint32_t quads) {
    ide_channel_reg_t cc = __ide_channels[channel];
    if(reg > 0x08 && reg < 0x0C) __ide_write(channel, ATA_REG_CONTROL, 0x80 | cc.no_int);
    if (reg < 0x08) insl(cc.base  + reg - 0x00, buffer, quads);
    else if (reg < 0x0C) insl(cc.base  + reg - 0x06, buffer, quads);
    else if (reg < 0x0E) insl(cc.ctrl  + reg - 0x0A, buffer, quads);
    else if (reg < 0x16) insl(cc.bmide + reg - 0x0E, buffer, quads);
    if (reg > 0x07 && reg < 0x0C) __ide_write(channel, ATA_REG_CONTROL, cc.no_int);
    return;
}