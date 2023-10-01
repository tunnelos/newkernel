#include <application_enableints/main.h>
#include <stdio.h>
#include <idt.h>
#include <pic.h>

#include <service_load.h>

void __application_enableints_fun1() {
    __pic_remap(0, 8);
    int i = 0;
    while (i < 9) {
        __pic_clearMask(i);
        i++;
    }
    // __pic_remapDefault();
}

void __application_enableints_init() {
    __service_startInitService(__application_enableints_fun1, "PIC", false);
    __service_startInitService(__idt_init, "IDT", false);
}