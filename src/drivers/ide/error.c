#include <drivers/ide/ide.h>

#include <tools.h>
#include <serial.h>

void __ide_error(uint32_t drive, uint8_t err) {
    if(!err) return;
    
    __serial_write_fmt("CPU %d -> tos > IDE error report.\r\n", __tools_get_cpu() - 1);
    uint8_t jj = 0;
    if(err == 1) {
        jj = 10;
    } else if (err == 2) {
        uint8_t st = __ide_read(__ide_devices[drive].channel, ATA_REG_ERROR);
        if(st & ATA_ER_TK0NF) jj = 1;
        if(st & ATA_ER_ABRT) jj = 2;
        if(st & ATA_ER_MCR) jj = 3;
        if(st & ATA_ER_IDNF) jj = 4;
        if(st & ATA_ER_MC) jj = 5;
        if(st & ATA_ER_UNC) jj = 6;
        if(st & ATA_ER_BBK) jj = 7;
    } else if (err == 3) {
        jj = 8;
    } else if (err == 4) {
        jj = 9;
    }
    __serial_write_fmt("CPU %d -> tos > * Reported Error: %s\r\n", __tools_get_cpu() - 1, __ide_error_table[jj]);
    ide_dev_t id = __ide_devices[drive];
    __serial_write_fmt("CPU %d -> tos > * Reported Device: %s %s [%s]\r\n", __tools_get_cpu() - 1, __ide_drive_table1[id.channel], __ide_drive_table2[id.drive], id.model);

    return;
}