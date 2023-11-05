#include <stdint.h>
#include <application_terminal/main.h>
#include <stdio.h>
#include <ps2keyboard.h>
#include <terminal80x25.h>
#include <serial.h>
#include <string.h>
#include <tunnel.h>
#include <vga80x25.h>
#include <stdlib.h>

#include <ctype.h>

#include <application_bootscreen/main.h>
#include <application_help/main.h>
#include <application_enableints/main.h>
#include <application_lsblk/main.h>
#include <application_memusage/main.h>

#include <vector_constcharp/def.h>

#include <drivers/ide/ide.h>

#include <etc/appman.h>

bool __applcation_terminal_isCommand(const char *input) {
    command_t cmd = __appman_getCommand(input);

    return cmd.init != NULL;
}

void __application_terminal_executeApplication(const char *input) {
    if (!__applcation_terminal_isCommand(input)) return;
    command_t cmd = __appman_getCommand(input);
    if (cmd.init != NULL) {
        cmd.init();
    }
}

void __application_terminal_unlightpointer(uint16_t p, char *buffer) {
    char prev_char = buffer[p - ((p == 0) ? 0 : 1)];

    vector2d_t pos;

    pos.x = tunnel_config.terminal.column - ((p == 0) ? 0 : 1);
    pos.y = tunnel_config.terminal.row;

    tunnel_config.terminal.buffer[tunnel_config.terminal.get_1d_position(pos)] = vga_entry(
        prev_char,
        vga_entry_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK)
    );
}
void __application_terminal_lightpointer(uint16_t p, char *buffer) {
    char prev_char = buffer[p - ((p == 0) ? 0 : 1)];

    vector2d_t pos;

    pos.x = tunnel_config.terminal.column - ((p == 0) ? 0 : 1);
    pos.y = tunnel_config.terminal.row;

    tunnel_config.terminal.buffer[tunnel_config.terminal.get_1d_position(pos)] = vga_entry(
        prev_char,
        vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_LIGHT_GREEN)
    );
}

void __application_terminal_test() {
    ide_dev_t device = __ide_devices[0];

    if (!device.connected) {
        puts("IDE device 0 is not connected or is corrupted.\n");
    } else {
        puts("Dumping Multiboot structure to the IDE 0\n");
        
        char *address = (char *)tunnel_config.multiboot;

        ide_rw_t action;
        action.buffer = (uint32_t)address;
        action.drive = 0;
        action.lba = 0;
        action.rw = 1;
        action.selector = 0;
        action.sectors = 1;
        __ide_get_access(action);

        puts("Done.\n");
    }
}

void __application_terminal_init() {
    if (__appman_ready()) {
        __appman_pushCommand("help", "command info", __application_help_init);
        __appman_pushCommand("bootscreen", "simple bootscreen", __app_bootscreen_init);
        __appman_pushCommand("terminal", "embedded terminal", __application_terminal_init);
        __appman_pushCommand("enableints", "enable interrupts", __application_enableints_init);
        __appman_pushCommand("lsblk", "list block devices", __application_lsblk_init);
        __appman_pushCommand("exit", "exit the terminal", NULL);
        __appman_pushCommand("mount", "mount drive 0 as fat32", NULL);
        __appman_pushCommand("test", "just a test", __application_terminal_test);
        __appman_pushCommand("memusage", "memory usage", __application_memusage_init);
    }
    rsb_array_constcharp *autostart = RSBCreateArrayconstcharp();

    // RSBAddElementconstcharp(autostart, "bootscreen");
    RSBAddElementconstcharp(autostart, "lsblk");

    tunnel_config.terminal.set_color(VGA_COLOR_WHITE);

    char *buffer = (char *)calloc(256, 1);
    uint16_t buffer_pointer = 0;

    bool inCapsMode = false;
    bool lShift = false;

    unsigned int m = 0 ;
    while (m < autostart->len) {
        const char *command = RSBGetAtIndexconstcharp(autostart, m);
        if (command != NULL) {
            __application_terminal_executeApplication(command);
        }
        m++;
    }
    RSBDestroyconstcharp(autostart);

    puts("\n> ");

    __application_terminal_lightpointer(buffer_pointer, buffer);

    while(1) {
        uint8_t scancode = __keyboard_ps2_getScancode();
        // while(scancode == 0) {
        //     scancode = __keyboard_ps2_getScancode();
        // }
        if (scancode != 0) {
            //__serial_write_fmt("Scancode: %d\r\n", scancode);
            switch(scancode) {
                case KP_LSHIFT: {
                    lShift = true;
                    break;
                }
                case KP_CAPSLOCK: {
                    inCapsMode = !inCapsMode;
                    break;
                }
                case KP_BACKSPACE: {
                    if (buffer_pointer == 0) break;

                    __application_terminal_unlightpointer(buffer_pointer, buffer);

                    buffer_pointer--;
                    buffer[buffer_pointer] = 0;

                    tunnel_config.terminal.put_backspace();

                    __serial_write_fmt("New buffer: %s\r\n", buffer);

                    __application_terminal_lightpointer(buffer_pointer, buffer);

                    break;
                }
                case KP_ENTER: {
                    __application_terminal_unlightpointer(buffer_pointer, buffer);

                    buffer_pointer = 0;
                    if (buffer[0] != 0) putc('\n');

                    if (!__applcation_terminal_isCommand(buffer)) {
                        if (!strcmp(buffer, "exit")) goto exit;
                        if (buffer[0] != 0)  puts("   Invalid command! Type 'help' for help.");
                    } else {
                        __application_terminal_executeApplication(buffer);
                    }

                    int testlol = 2048;
                    testlol *= 2048;

                    puts("\n> ");

                    buffer_pointer = 0;
                    while(buffer_pointer < 256) {
                        if (buffer[buffer_pointer] == 0) break;
                        buffer[buffer_pointer] = 0;
                        //buffer2[buffer_pointer] = false;
                        buffer_pointer++;
                    }

                    buffer_pointer = 0;

                    __application_terminal_lightpointer(buffer_pointer, buffer);

                    break;
                }
                default: {
                    if (__keyboard_ps2_lookuptable[scancode] != '?' && buffer_pointer != 256) {
                        __application_terminal_unlightpointer(buffer_pointer, buffer);

                        buffer[buffer_pointer] = __keyboard_ps2_lookuptable[scancode];
                        if (inCapsMode) {
                            buffer[buffer_pointer] = toupperchar(buffer[buffer_pointer]);
                        }
                        putc(buffer[buffer_pointer]);
                        buffer_pointer++;

                        __application_terminal_lightpointer(buffer_pointer, buffer);

                        if(lShift) {
                            lShift = false;
                        }
                    }

                    break;
                }
            }
        }
    }

    exit:
    free(buffer);
    return;
}