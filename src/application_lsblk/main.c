#include <drivers/ide/ide.h>
#include <application_lsblk/main.h>

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <tools.h>

void __application_lsblk_init() {
    puts("NAME      SIZE      TYPE\n");
    int i = 0;

    char *buf = (char *)calloc(1, 128);

    // char *buffers[3] = {
    //     (char *)calloc(1, 128),
    //     (char *)calloc(1, 128),
    //     (char *)calloc(1, 128)
    // };

    while (i < 4) {
        ide_dev_t device = __ide_devices[i];

        if (device.connected) {

            strncpy(buf, "hd", 2);
            
            const char aa[2] = {
                __tools_getDriveLetter(i),
                0
            };

            strncat(buf, aa, 2);

            puts(buf);
            puts("       ");
            printf("%f", (float)device.size / 2.f / 1024.f / 1024.f);
            puts("G disk\n");

            

            memset(buf, 0, 128);
        }

        i++;
    }

    // free(buffers[0]);
    // free(buffers[1]);
    // free(buffers[2]);

    free(buf);
}
