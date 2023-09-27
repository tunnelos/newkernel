#include <drivers/ide/ide.h>

void __ide_get_access(ide_rw_t data) {
    uint8_t lba_mode, dma, cmd;
    uint8_t lba_io[6];
    uint32_t channel = __ide_devices[data.drive].channel;
    uint32_t slavebit = __ide_devices[data.drive].drive;
    uint32_t bus = __ide_channels[channel].base;
    uint32_t words = 256;
    uint16_t cyl, i = 0;
    uint8_t head, sect, err;

    __ide_write(channel, ATA_REG_CONTROL, __ide_channels[channel].no_int = (__ide_irq_trigger = 0) + 2);

    if(data.lba >= 0x10000000) {
        lba_mode = IDE_LBA48;
        lba_io[0] = (data.lba & 0x000000FF) >> 0;
        lba_io[1] = (data.lba & 0x0000FF00) >> 8;
        lba_io[2] = (data.lba & 0x00FF0000) >> 16;
        lba_io[3] = (data.lba & 0xFF000000) >> 24;
        lba_io[4] = 0;
        lba_io[5] = 0;
        head = 0;
    } else if (__ide_devices[data.drive].capabilities & IDE_HAS_LBA) {
        lba_mode = IDE_LBA28;
        lba_io[0] = (data.lba & 0x000000FF) >> 0;
        lba_io[1] = (data.lba & 0x0000FF00) >> 8;
        lba_io[2] = (data.lba & 0x00FF0000) >> 16;
        head = (data.lba & 0xF000000) >> 24;
    } else {
        lba_mode = IDE_CHS;
        sect = (data.lba % 63) + 1;
        cyl = (data.lba + 1 - sect) / (16 * 63);
        lba_io[0] = sect;
        lba_io[1] = (cyl >> 0) & 0xFF;
        lba_io[2] = (cyl >> 8) & 0xFF;
        lba_io[3] = 0;
        lba_io[4] = 0;
        lba_io[5] = 0;
        head = (data.lba + 1 - sect) % (16 * 63) / (63);
    }
    dma = 0;
    while(__ide_read(channel, ATA_REG_STATUS) & ATA_SR_BSY);
    if(!lba_mode) __ide_write(channel, ATA_REG_HDDEVSEL, 0xA0 | (slavebit << 4) | head);
    else __ide_write(channel, ATA_REG_HDDEVSEL, 0xE0 | (slavebit << 4) | head);

    if(lba_mode == IDE_LBA48) {
        __ide_write(channel, ATA_REG_SECCOUNT1, 0);
        __ide_write(channel, ATA_REG_LBA3, lba_io[3]);
        __ide_write(channel, ATA_REG_LBA4, lba_io[4]);
        __ide_write(channel, ATA_REG_LBA5, lba_io[5]);
    }
    __ide_write(channel, ATA_REG_SECCOUNT0, data.sectors);
    __ide_write(channel, ATA_REG_LBA0, lba_io[0]);
    __ide_write(channel, ATA_REG_LBA1, lba_io[1]);
    __ide_write(channel, ATA_REG_LBA2, lba_io[2]);

         if (lba_mode == IDE_CHS && dma == ATA_DMA_UNSUPPORTED && data.rw == ATA_READ) cmd = ATA_CMD_READ_PIO;
    else if (lba_mode == IDE_LBA28 && dma == ATA_DMA_UNSUPPORTED && data.rw == ATA_READ) cmd = ATA_CMD_READ_PIO;   
    else if (lba_mode == IDE_LBA48 && dma == ATA_DMA_UNSUPPORTED && data.rw == ATA_READ) cmd = ATA_CMD_READ_PIO_EXT;   
    else if (lba_mode == IDE_CHS && dma == ATA_DMA_SUPPORTED && data.rw == ATA_READ) cmd = ATA_CMD_READ_DMA;
    else if (lba_mode == IDE_LBA28 && dma == ATA_DMA_SUPPORTED && data.rw == ATA_READ) cmd = ATA_CMD_READ_DMA;
    else if (lba_mode == IDE_LBA48 && dma == ATA_DMA_SUPPORTED && data.rw == ATA_READ) cmd = ATA_CMD_READ_DMA_EXT;
    else if (lba_mode == IDE_CHS && dma == ATA_DMA_UNSUPPORTED && data.rw == ATA_WRITE) cmd = ATA_CMD_WRITE_PIO;
    else if (lba_mode == IDE_LBA28 && dma == ATA_DMA_UNSUPPORTED && data.rw == ATA_WRITE) cmd = ATA_CMD_WRITE_PIO;
    else if (lba_mode == IDE_LBA48 && dma == ATA_DMA_UNSUPPORTED && data.rw == ATA_WRITE) cmd = ATA_CMD_WRITE_PIO_EXT;
    else if (lba_mode == IDE_CHS && dma == ATA_DMA_SUPPORTED && data.rw == ATA_WRITE) cmd = ATA_CMD_WRITE_DMA;
    else if (lba_mode == IDE_LBA28 && dma == ATA_DMA_SUPPORTED && data.rw == ATA_WRITE) cmd = ATA_CMD_WRITE_DMA;
    else if (lba_mode == IDE_LBA48 && dma == ATA_DMA_SUPPORTED && data.rw == ATA_WRITE) cmd = ATA_CMD_WRITE_DMA_EXT;
    __ide_write(channel, ATA_REG_COMMAND, cmd);

    if (dma) {
        if(data.rw == ATA_READ) {
            //read
        } else {
            //write
        }
    } else {
        if(data.rw == ATA_READ) {
            //read
            while(i < data.sectors) {
                err = __ide_polling(channel, true);
                if(err) return;
                asm volatile("mov %%ax, %%es" : : "a"(data.selector));
                asm volatile("rep insw" : : "c"(words), "d"(bus), "D"(data.buffer));
                data.buffer += (words * 2);
                i++;
            }
        } else {
            //write
            while(i < data.sectors) {
                __ide_polling(channel, 0);
                asm volatile("mov %%ax, %%ds" : : "a"(data.selector));
                asm volatile("rep outsw" : : "c"(words), "d"(bus), "S"(data.buffer));
                data.buffer += (words * 2);
                i++;
            }
            __ide_write(channel, ATA_REG_COMMAND, (char []) { ATA_CMD_CACHE_FLUSH, ATA_CMD_CACHE_FLUSH, ATA_CMD_CACHE_FLUSH_EXT }[lba_mode]);
            __ide_polling(channel, 0);
        }
    }
    return;
}