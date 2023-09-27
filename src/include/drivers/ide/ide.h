#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "definitions.h"

typedef struct ide_channel_reg_t {
    uint16_t base;
    uint16_t ctrl;
    uint16_t bmide;
    uint8_t no_int;
} ide_channel_reg_t;
typedef struct ide_dev_t {
    bool connected;
    uint8_t channel;
    uint8_t drive;
    uint16_t type;
    uint16_t signature;
    uint16_t capabilities;
    uint32_t cmd_set;
    uint8_t addressing_mode;
    // In kilobits;
    uint32_t size;
    uint8_t model[41];
} ide_dev_t;
typedef struct ide_rw_t {
    //0 - read | 1 - write
    bool rw;
    uint8_t drive;
    uint32_t lba;
    uint8_t sectors;
    uint16_t selector;
    uint32_t buffer;
} ide_rw_t;

extern ide_channel_reg_t __ide_channels[2];
extern uint8_t *__ide_buffer;
extern volatile uint8_t __ide_irq_trigger;
extern uint8_t __ide_atapi_packet[12];
extern ide_dev_t __ide_devices[4];
extern const char *__ide_error_table[11];
extern const char *__ide_drive_table1[2];
extern const char *__ide_drive_table2[2];

void __ide_init(uint32_t *bars);
uint8_t __ide_read(uint8_t channel, uint8_t reg);
void __ide_write(uint8_t channel, uint8_t reg, uint8_t data);
void __ide_read_buffer(uint8_t channel, uint8_t reg, uint32_t *buffer, uint32_t quads);
uint8_t __ide_polling(uint8_t channel, bool advanced);
void __ide_error(uint32_t drive, uint8_t err);

void __ide_get_access(ide_rw_t data);

