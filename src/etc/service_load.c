#include <service_load.h>

#include <stdio.h>

#include "serial.h"

void __service_startInitService(void (*init_function)(), const char *name, bool transparent) {
    __serial_write_fmt("* Starting %s... ", name);
    if (!transparent) {
        puts("* Starting ");
        puts(name);
        puts("... ");
    }
    
    if (!init_function) goto fail;

    init_function();
    goto success;

    fail:

    __serial_write_fmt("fail!\r\n");
    if (!transparent) puts("fail!\n");

    return;

    success:

    __serial_write_fmt("success!\r\n");
    if (!transparent) puts("success!\n");

    return;
}