#include "../include/application_enableints/main.h"
#include "../include/stdio.h"
#include "../include/idt.h"
#include "../include/gdt.h"

void __application_enableints_init() {
    printf("\nEnabling!\n");

    __gdt_init();
    __idt_init();

    printf("Maybe works.\n");
}