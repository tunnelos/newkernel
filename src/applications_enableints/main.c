#include <application_enableints/main.h>
#include <stdio.h>
#include <idt.h>
#include <pic.h>

#include <service_load.h>

void __application_enableints_fun1() {
    __pic_remap(0, 8);
    __pic_setMask(8);
}


void __application_enableints_init() {
    // printf("Enabling!\n * PIC...");

    // // __pic_remapDefault();
    // __pic_remap(0, 8);
    // __pic_setMask(8);
    // printf(" done\n * IDT...");

    // __idt_init();
    // printf(" done\n");
    __service_startInitService(__application_enableints_fun1, "PIC", false);
    __service_startInitService(__idt_init, "IDT", false);
}