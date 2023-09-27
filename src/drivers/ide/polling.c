#include <drivers/ide/ide.h>

uint8_t __ide_polling(uint8_t channel, bool advanced) {
    for(uint8_t i = 0; i < 4; i++) __ide_read(channel, ATA_REG_ALTSTATUS);
    while(__ide_read(channel, ATA_REG_STATUS) & ATA_SR_BSY);
    if(advanced) {
        uint8_t state = __ide_read(channel, ATA_REG_STATUS);
        if (state & ATA_SR_ERR) return 2;
        if (state & ATA_SR_DF) return 1;
        if (!(state & ATA_SR_DRQ)) return 3;
    }
    return 0;
}