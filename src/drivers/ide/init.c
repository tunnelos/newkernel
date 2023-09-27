#include <drivers/ide/ide.h>

#include <stdlib.h>

#include <serial.h>
#include <tools.h>

void __ide_init(uint32_t *bars) {
    __ide_buffer = (uint8_t *)calloc(1, 2048);

    __serial_write_fmt("CPU %d -> tos > Searching for IDE devices...\r\n", __tools_get_cpu() - 1);

    int j = 0, k = 0, count = 0;

    __ide_channels[ATA_PRIMARY].base = (bars[0] & 0xFFFFFFFC) + 0x1F0 * (!bars[0]);
    __ide_channels[ATA_PRIMARY].ctrl = (bars[1] & 0xFFFFFFFC) + 0x3F6 * (!bars[1]);
    __ide_channels[ATA_SECONDARY].base = (bars[2] & 0xFFFFFFFC) + 0x170 * (!bars[2]);
    __ide_channels[ATA_SECONDARY].ctrl = (bars[3] & 0xFFFFFFFC) + 0x376 * (!bars[3]);
    __ide_channels[ATA_PRIMARY].bmide = (bars[4] & 0xFFFFFFFC) + 0;
    __ide_channels[ATA_SECONDARY].bmide = (bars[4] & 0xFFFFFFFC) + 8;

    __ide_write(ATA_PRIMARY, ATA_REG_CONTROL, 2);
    __ide_write(ATA_SECONDARY, ATA_REG_CONTROL, 2);

    while(k < 2) {
        while(j < 2) {
            uint8_t err = 0, type = IDE_ATA, status = 0;
            __ide_devices[count].connected = false;

            __ide_write(k, ATA_REG_HDDEVSEL, 0xA0 | (j << 4));
            wait(1);
            __ide_write(k, ATA_REG_COMMAND, ATA_CMD_IDENTIFY);
            wait(1);
            if(__ide_read(k, ATA_REG_STATUS) != 0) {
                __serial_write_fmt("CPU %d -> tos > Found evidence of IDE device.\r\n", __tools_get_cpu() - 1);
            } else {
                __serial_write_fmt("CPU %d -> tos > IDE device not found. Skipping.\r\n", __tools_get_cpu() - 1);
                break;
            }
            bool ssksk = false;
            while(!ssksk) {
                status = __ide_read(k, ATA_REG_STATUS);
                if ((status & ATA_SR_ERR)) {
                    err = 1; 
                    __ide_error(j, err);
                    __serial_write_fmt("CPU %d -> tos > Invalid device. Skipping drive.\r\n", __tools_get_cpu() - 1);
                    break;
                } else {
                    ssksk = true;
                    break;
                }
                if (!(status & ATA_SR_BSY) && (status & ATA_SR_DRQ)) ssksk = true;
                
            }
            if (err != 0) {
                uint8_t cl = __ide_read(k, ATA_REG_LBA1);
                uint8_t ch = __ide_read(k, ATA_REG_LBA2);

                if(cl == 0x14 && ch == 0xEB) {
                    __serial_write_fmt("CPU %d -> tos > ATAPI device found\r\n", __tools_get_cpu() - 1);
                    type = IDE_ATAPI;
                }
                else if (cl == 0x69 && ch == 0x96) {
                    __serial_write_fmt("CPU %d -> tos > ATAPI device found\r\n", __tools_get_cpu() - 1);
                    type = IDE_ATAPI;
                }
                else {
                    __serial_write_fmt("CPU %d -> tos > Unknown device found. Skipping it.\r\n", __tools_get_cpu() - 1);
                    break;
                }

                __ide_write(k, ATA_REG_COMMAND, ATA_CMD_IDENTIFY_PACKET);
                wait(1);
            }

            __ide_read_buffer(k, ATA_REG_DATA, (uint32_t *)__ide_buffer, 128);
            
            __ide_devices[count].connected = true;
            __ide_devices[count].type = type;
            __ide_devices[count].channel = k;
            __ide_devices[count].drive = j;
            __ide_devices[count].signature = *((uint16_t *)(__ide_buffer + ATA_IDENT_DEVICETYPE));
            __ide_devices[count].capabilities = *((uint16_t *)(__ide_buffer + ATA_IDENT_CAPABILITIES));
            __ide_devices[count].cmd_set = *((uint32_t *)(__ide_buffer + ATA_IDENT_COMMANDSETS));
            if (__ide_devices[count].cmd_set & (1 << 26)) {
                __ide_devices[count].addressing_mode = 48;
                __ide_devices[count].size = *((uint32_t *)(__ide_buffer + ATA_IDENT_MAX_LBA_EXT));
            } else {
                __ide_devices[count].addressing_mode = 28;
                __ide_devices[count].size = *((uint32_t *)(__ide_buffer + ATA_IDENT_MAX_LBA));
            }
            if(__ide_devices[count].size == 0) {
                __serial_write_fmt("CPU %d -> tos > Found garbade data. Skipping it.\r\n", __tools_get_cpu() - 1);
                __ide_devices[count].connected = false;
                break;
            } else {
                __serial_write_fmt("CPU %d -> tos > Found connected IDE device (%s %s)\r\n", __tools_get_cpu() - 1, __ide_drive_table1[__ide_devices[count].channel], __ide_drive_table2[__ide_devices[count].drive]);
                __serial_write_fmt("CPU %d -> tos > Connected IDE size: %dMb with %d-bit addressing\r\n", __tools_get_cpu() - 1, __ide_devices[count].size / 1024 / 2, __ide_devices[count].addressing_mode);
            }

            for (uint8_t i = 0; i < 40; i++) __ide_devices[count].model[i] = __ide_buffer[ATA_IDENT_MODEL + i];
            __ide_devices[count].model[40] = 0;
            __serial_write_fmt("CPU %d -> tos > Connected IDE model: %d\r\n", __tools_get_cpu() - 1, __ide_devices[count].model);

            j++;
            count++;
        }
        j = 0;
        k++;
    }
}