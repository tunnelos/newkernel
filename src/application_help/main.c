#include <application_help/main.h>
#include <stdio.h>

#include <cJSON.h>

#include <serial.h>

void __application_help_init() {
    //printf("\nCommands:\n - help - help\n - terminal - default terminal\n - bootscreen - small bootscreen\n - exit - exit the terminal");
    puts("\nCommands:\n");
    puts(" - help - help\n");
    puts(" - terminal - default terminal\n");
    puts(" - bootscreen - small bootscreen\n");
    puts(" - exit - exit the terminal\n");
    puts(" - enableints - enable interrupts\n"); 
    puts(" - lsblk - list block devices\n");

    __serial_write_fmt("pre json\r\n");

    cJSON *test = cJSON_Parse("{\"test\":64}");

    __serial_write_fmt("json\r\n");

    printf(" - %d\n", 0);

    __serial_write_fmt("json delete\r\n");

    cJSON_Delete(test);
}