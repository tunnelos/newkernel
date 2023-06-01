#include "../include/terminal80x25.h"
#include "../include/tunnel.h"
#include "../include/vga80x25.h"
#include "../include/string.h"

void __terminal_init() {
    tunnel_config.terminal.row = 0;
    tunnel_config.terminal.column = 0;
    tunnel_config.terminal.color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    tunnel_config.terminal.buffer = (uint16_t *)0xB8000;

    for (int y = 0; y < 25; y++) {
		for (int x = 0; x < 80; x++) {
			const int index = y * 80 + x;
			tunnel_config.terminal.buffer[index] = vga_entry(' ', tunnel_config.terminal.color);
		}
	}
}

void __terminal_setColor(uint8_t color) {
    tunnel_config.terminal.color = color;
}

void __terminal_putByte(char c, uint8_t color, vector2d_t pos) {
    pos.x %= 80;
    pos.y %= 25;

    const int index = pos.y * 80 + pos.x;
    tunnel_config.terminal.buffer[index] = vga_entry(c, color);
}

void __terminal_putc(char c) {
    if (c == '\n') {
		tunnel_config.terminal.row++;
		tunnel_config.terminal.column = 0;
		return;
	}

	if (tunnel_config.terminal.column == 80) {
		tunnel_config.terminal.column = 0;
		tunnel_config.terminal.row++;
		if (tunnel_config.terminal.row == 25) tunnel_config.terminal.row = 0;
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