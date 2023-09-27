#include <drivers/ide/ide.h>
#include <application_lsblk/main.h>

#include <stdio.h>

#include <stdlib.h>

void __application_lsblk_init() {
    puts("NAME    SIZE    TYPE\n");
    int i = 0;

    char *buf = (char *)calloc(1, 128);

    while (i < 4) {
        ide_dev_t device = __ide_devices[i];

        if (device.connected) {
            memset(buf, 0, 128);
            printf("hd%d", i);
            puts("     ");
            printf("%d", device.size / 1024 / 1024);
            puts("G      disk");
        }

        i++;
    }

    free(buf);
}
