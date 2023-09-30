#pragma once

#include <external/rsb_array_gen.h>

typedef struct command_t {
    const char *name;
    const char *description;
    void (*init)();
} command_t;

RSB_ARRAY_DEF_GEN(command_t, command_t);

command_t __appman_getCommand(const char *name);
void __appman_pushCommand(const char *name, const char *description, void (*init)());

unsigned int __appman_getListLength();
command_t __appman_getCommandByIndex(unsigned int i);

#include <stdbool.h>

bool __appman_ready();

void __appman_init();