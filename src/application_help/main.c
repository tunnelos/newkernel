#include <application_help/main.h>
#include <stdio.h>

#include <cJSON.h>

#include <serial.h>

#include <etc/appman.h>

void __application_help_init() {
    //printf("\nCommands:\n - help - help\n - terminal - default terminal\n - bootscreen - small bootscreen\n - exit - exit the terminal");
    
    puts("Commands:\n");
    // puts(" - help - help\n");
    // puts(" - terminal - default terminal\n");
    // puts(" - bootscreen - small bootscreen\n");
    // puts(" - exit - exit the terminal\n");
    // puts(" - enableints - enable interrupts\n"); 
    // puts(" - lsblk - list block devices\n");
    // puts(" - clear - clear the terminal\n");
    if (__appman_ready()) {
        unsigned int i = 0;
        
        while (i < __appman_getListLength()) {
            command_t cmd = __appman_getCommandByIndex(i);

            printf(" * %s - %s\n", cmd.name, cmd.description);

            i++;
        }
    }
    // unsigned int i = 0;
    // while (i < __appman)

    // while ()

    // __serial_write_fmt("pre json\r\n");

    // cJSON *test = cJSON_Parse("{\"test\":64}");

    // __serial_write_fmt("json\r\n");

    // printf(" - %d\n", 0);

    // __serial_write_fmt("json delete\r\n");

    // cJSON_Delete(test);
}