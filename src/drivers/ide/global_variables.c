#include <drivers/ide/ide.h>

ide_channel_reg_t __ide_channels[2];
uint8_t *__ide_buffer;
volatile uint8_t __ide_irq_trigger;
uint8_t __ide_atapi_packet[12];
ide_dev_t __ide_devices[4];
const char *__ide_error_table[11] = {
    "No address mark found", "No media or media error",
    "Command aborted", "No media or media error",
    "ID mark not found", "No media or media error",
    "Uncorrectable data error", "Bad sectors",
    "Reading nothing", "Read-only data",
    "Device fault"
};
const char *__ide_drive_table1[2] = {
    "Primary", "Secondary"
};
const char *__ide_drive_table2[2] = {
    "Master", "Slave"
};