#include <etc/appman.h>

#include <string.h>

rsb_array_command_t *__appman_commands = NULL;

command_t __appman_getCommand(const char *name) {
    command_t com = {};

    unsigned int i = 0;
    while (i < __appman_getListLength()) {
        command_t cmd = RSBGetAtIndexcommand_t(__appman_commands, i);

        if (!strcmp(cmd.name, name)) return cmd;

        i++;
    }

    return com;
}

void __appman_pushCommand(const char *name, const char *description, void (*init)()) {
    command_t cmd = __appman_getCommand(name);

    if (cmd.init == NULL) {
        cmd.name = name;
        cmd.init = init;
        cmd.description = description;

        RSBAddElementcommand_t(__appman_commands, cmd);
    }
}

bool __appman_ready() {
    return __appman_commands != NULL;
}

void __appman_init() {
    if (!__appman_ready()) {
        __appman_commands = RSBCreateArraycommand_t();
    }
}

unsigned int __appman_getListLength() {
    return __appman_commands->len;
}
command_t __appman_getCommandByIndex(unsigned int i) {
    command_t cmd = {};

    if (i > __appman_getListLength()) return cmd;

    return RSBGetAtIndexcommand_t(__appman_commands, i);
}