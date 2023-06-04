#include <stdint.h>
#include "../include/application_terminal/main.h"
#include "../include/stdio.h"
#include "../include/ps2keyboard.h"
#include "../include/terminal80x25.h"
#include "../include/serial.h"
#include "../include/string.h"
#include "../include/tunnel.h"
#include "../include/vga80x25.h"

#include "../include/application_bootscreen/main.h"
#include "../include/application_help/main.h"

bool __applcation_terminal_isCommand(const char *input) {
    if (!strcmp(input, "help")) return true;
    if (!strcmp(input, "bootscreen")) return true;
    if (!strcmp(input, "terminal")) return true;

    return false;
}

void __application_terminal_executeApplication(const char *input) {
    if (!strcmp(input, "help")) {
        __application_help_init();
    }
    if (!strcmp(input, "bootscreen")) {
        __app_bootscreen_init();
    }
    if (!strcmp(input, "terminal")) {
        __application_terminal_init();
    }
}

void __application_terminal_unlightpointer(uint16_t p, char *buffer) {
    char prev_char = buffer[p - ((p == 0) ? 0 : 1)];

    vector2d_t pos;

    pos.x = tunnel_config.terminal.column - ((p == 0) ? 0 : 1);
    pos.y = tunnel_config.terminal.row;

    tunnel_config.terminal.buffer[__terminal_getPosition(pos)] = vga_entry(
        prev_char,
        vga_entry_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK)
    );
}
void __application_terminal_lightpointer(uint16_t p, char *buffer) {
    char prev_char = buffer[p - ((p == 0) ? 0 : 1)];

    vector2d_t pos;

    pos.x = tunnel_config.terminal.column - ((p == 0) ? 0 : 1);
    pos.y = tunnel_config.terminal.row;

    tunnel_config.terminal.buffer[__terminal_getPosition(pos)] = vga_entry(
        prev_char,
        vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_LIGHT_GREEN)
    );
}

void __application_terminal_init() {
    char buffer[256] = {};
    uint16_t buffer_pointer = 0;

    bool inCapsMode = false;
    bool lShift = false;

    puts("\n> ");

    __application_terminal_lightpointer(buffer_pointer, buffer);

    while(1) {
        uint8_t scancode = __keyboard_ps2_getScancode();
        while(scancode == 0) {
            scancode = __keyboard_ps2_getScancode();
        }
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

                    __terminal_putBackspace();

                    __serial_write_fmt("New buffer: %s\r\n", buffer);

                    __application_terminal_lightpointer(buffer_pointer, buffer);

                    break;
                }
                case KP_ENTER: {
                    __application_terminal_unlightpointer(buffer_pointer, buffer);

                    buffer_pointer = 0;
                    if (buffer[0] != 0) putc('\n');

                    if (!__applcation_terminal_isCommand(buffer)) {
                        if (buffer[0] != 0)  puts("   Invalid command! Type 'help' for help.");
                    } else {
                        __application_terminal_executeApplication(buffer);
                    }

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
}