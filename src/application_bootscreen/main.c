#include "../include/application_bootscreen/main.h"

#include "../include/terminal80x25.h"
#include "../include/tunnel.h"
#include "../include/vga80x25.h"

void __app_bootscreen_init() {
    __terminal_clear();
    __terminal_reset();

    __terminal_write("Tunnel OS ");
    
    uint8_t colortable[14] = {
        VGA_COLOR_BLUE,
        VGA_COLOR_GREEN,
        VGA_COLOR_CYAN,
        VGA_COLOR_RED,
        VGA_COLOR_MAGENTA,
        VGA_COLOR_BROWN,
        VGA_COLOR_LIGHT_GREY,
        VGA_COLOR_LIGHT_BLUE,
        VGA_COLOR_DARK_GREY,
        VGA_COLOR_LIGHT_GREEN,
        VGA_COLOR_LIGHT_CYAN,
        VGA_COLOR_LIGHT_RED,
        VGA_COLOR_LIGHT_MAGENTA,
        VGA_COLOR_LIGHT_BROWN
    };

    uint8_t i = 0;
    uint8_t offset = 0;

    while(i < 36) {
        __terminal_setColor(vga_entry_color(colortable[(i + offset) % 14], VGA_COLOR_BLACK));
        if((i + 1) != 35) {
            __terminal_putc('.');
            __terminal_putc(' ');
        }
        i++;
    }

    tunnel_config.terminal.column = 0;
    tunnel_config.terminal.row = 1;

    __terminal_setColor(vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK));

    i = 0;
    offset++;
    while(i < 80) {
        __terminal_setColor(vga_entry_color(colortable[(i + offset) % 14], VGA_COLOR_BLACK));
        __terminal_putc(0xDC);
        i++;
    }

    tunnel_config.terminal.row++;
    tunnel_config.terminal.column = 0;

    i = 0;
    while(i < 80) {
        __terminal_setColor(vga_entry_color(colortable[i % 14], VGA_COLOR_BLACK));
        __terminal_putc(0xDF);
        i++;
    }
}