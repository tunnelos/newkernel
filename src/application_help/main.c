#include "../include/application_help/main.h"
#include "../include/stdio.h"

void __application_help_init() {
    //printf("\nCommands:\n - help - help\n - terminal - default terminal\n - bootscreen - small bootscreen\n - exit - exit the terminal");
    puts("\nCommands:\n");
    puts(" - help - help\n");
    puts(" - terminal - default terminal\n");
    puts(" - bootscreen - small bootscreen\n");
    puts(" - exit - exit the terminal\n");
    puts(" - enableints - enable interrupts\n");   
}