#include "../include/terminal80x25.h"
#include "../include/tunnel.h"
#include "../include/vga80x25.h"
#include "../include/string.h"

void __terminal_init() {
    tunnel_config.terminal.buffer = (uint16_t *)0x00400000;

    __terminal_reset();
    __terminal_clear();
}

void __terminal_clear() {
    uint8_t old_color = tunnel_config.terminal.color;
    __terminal_setColor(vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_BLACK));

    for (int y = 0; y < 25; y++) {
		for (int x = 0; x < 80; x++) {
			const int index = y * 80 + x;
			tunnel_config.terminal.buffer[index] = vga_entry(0xDB, tunnel_config.terminal.color);
		}
	}

    __terminal_setColor(old_color);
}

uint32_t __terminal_getPosition(vector2d_t pos) {
    pos.x %= 80;
    pos.y %= 25;
    
    return pos.y * 80 + pos.x;
}

void __terminal_setColor(uint8_t color) {
    tunnel_config.terminal.color = color;
}

void __terminal_putByte(char c, uint8_t color, vector2d_t pos) {
    const int index = __terminal_getPosition(pos);
    tunnel_config.terminal.buffer[index] = vga_entry(c, color);
}

void __terminal_putc(char c) {
    if (c == '\n') {
		tunnel_config.terminal.row++;
		tunnel_config.terminal.column = 0;

        if (tunnel_config.terminal.row == 25) {
            tunnel_config.terminal.row = 0;
            __terminal_clear();
        }
		return;
	}

	if (tunnel_config.terminal.column == 80) {
		tunnel_config.terminal.column = 0;
		tunnel_config.terminal.row++;
		if (tunnel_config.terminal.row == 25) {
            tunnel_config.terminal.row = 0;
            __terminal_clear();
        }
	}

    vector2d_t pos;
    pos.x = tunnel_config.terminal.column;
    pos.y = tunnel_config.terminal.row;

	__terminal_putByte(c, tunnel_config.terminal.color, pos);

	tunnel_config.terminal.column++;
}

void __terminal_swrite(const char *data, int size) {
    for (int i = 0; i < size; i++) __terminal_putc(data[i]);
}

void __terminal_write(const char *data) {
    __terminal_swrite(data, strlen(data));
}

void __terminal_reset() {
    tunnel_config.terminal.column = 0;
    tunnel_config.terminal.row = 0;
    tunnel_config.terminal.color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
}

void __terminal_putBackspace() {
    vector2d_t pos;

    tunnel_config.terminal.column--;
    if (tunnel_config.terminal.column < 0) {
        tunnel_config.terminal.column = 0;
        tunnel_config.terminal.row--;

        if (tunnel_config.terminal.row < 0) {
            tunnel_config.terminal.row = 0;
        }
    }

    pos.x = tunnel_config.terminal.column;
    pos.y = tunnel_config.terminal.row;

    __terminal_putByte(' ', tunnel_config.terminal.color, pos);
}