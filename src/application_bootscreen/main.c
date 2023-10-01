#include <application_bootscreen/main.h>

#include <terminal80x25.h>
#include <tunnel.h>
#include <vga80x25.h>

#include <string.h>

#include <stdlib.h>
#include <stdio.h>

void __app_bootscreen_init() {
    vector2d_t old_pos;
    uint8_t old_color;

    old_pos.x = tunnel_config.terminal.column;
    old_pos.y = tunnel_config.terminal.row;
    old_color = tunnel_config.terminal.color;

    tunnel_config.terminal.column = 0;
    tunnel_config.terminal.row = 0;
    tunnel_config.terminal.color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    char *buffer = calloc(1, 128);

    

    sprintf(buffer, "Tunnel OS Loader (%s) %s", "dev", "1.0");

    tunnel_config.terminal.write(buffer);
    
    free(buffer);
    
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

    while(i < ((tunnel_config.terminal.get_size().x - strlen(buffer)) / 2)) {
        tunnel_config.terminal.set_color(vga_entry_color(colortable[(i + offset) % 14], VGA_COLOR_BLACK));
        if((i + 1) != tunnel_config.terminal.get_size().y) {
            tunnel_config.terminal.putc('.');
            tunnel_config.terminal.putc(' ');
        }
        i++;
    }

    tunnel_config.terminal.column = 0;
    tunnel_config.terminal.row = 1;

    tunnel_config.terminal.set_color(vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK));

    i = 0;
    offset++;
    while(i < 80) {
        tunnel_config.terminal.set_color(vga_entry_color(colortable[(i + offset) % 14], VGA_COLOR_BLACK));
        tunnel_config.terminal.putc(0xDC);
        i++;
    }

    tunnel_config.terminal.row++;
    tunnel_config.terminal.column = 0;

    i = 0;
    while(i < 80) {
        tunnel_config.terminal.set_color(vga_entry_color(colortable[i % 14], VGA_COLOR_BLACK));
        tunnel_config.terminal.putc(0xDF);
        i++;
    }

    tunnel_config.terminal.column = old_pos.x;
    tunnel_config.terminal.row = old_pos.y;
    tunnel_config.terminal.color = old_color;
}