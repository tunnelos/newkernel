#include <terminal80x25.h>
#include <tunnel.h>
#include <vga80x25.h>
#include <string.h>

void __terminal80x25_init();
void __terminal80x25_setColor(uint8_t color);
void __terminal80x25_putByte(char c, uint8_t color, vector2d_t pos);
void __terminal80x25_putc(char c);
void __terminal80x25_putBackspace();
uint32_t __terminal80x25_getPosition(vector2d_t pos);

void __terminal80x25_swrite(const char *data, int size);
void __terminal80x25_write(const char *str);

void __terminal80x25_clear();
void __terminal80x25_reset();
void __terminal80x25_slide();

void __terminal80x25_init() {
    tunnel_config.terminal.buffer = (uint16_t *)0x00400000;

    __global_currentTextTerminal.reset();
    __global_currentTextTerminal.clear();
}

void __terminal80x25_clear() {
    uint8_t old_color = tunnel_config.terminal.color;
    __global_currentTextTerminal.set_color(vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_BLACK));

    for (int y = 0; y < 25; y++) {
		for (int x = 0; x < 80; x++) {
			const int index = y * 80 + x;
			tunnel_config.terminal.buffer[index] = vga_entry(0xDB, tunnel_config.terminal.color);
		}
	}

    __global_currentTextTerminal.set_color(old_color);
}

void __terminal80x25_slide() {
    // for (int y = 0; y < 25; y++) {
		// for (int x = 0; x < 80; x++) {
			// const int index = y * 80 + x;
			// tunnel_config.terminal.buffer[index] = tunnel_config.terminal.buffer[(index == 0) ? 0 : index - 1];
		// }
	// }

    memmove((void *)tunnel_config.terminal.buffer, (const void *)(tunnel_config.terminal.buffer + 80*2), 80*25*2);

    // uint8_t old_color = tunnel_config.terminal.color;
    // __terminal80x25_setColor(vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_BLACK));

    // for (int x = 0; x < 80; x++) {
    //     __terminal80x25_putByte(' ', tunnel_config.terminal.color, (vector2d_t){x, 80});   
    // }

    // __terminal80x25_setColor(old_color);
}

uint32_t __terminal80x25_getPosition(vector2d_t pos) {
    pos.x %= 80;
    pos.y %= 25;
    
    return pos.y * 80 + pos.x;
}

void __terminal80x25_setColor(uint8_t color) {
    tunnel_config.terminal.color = color;
}

void __terminal80x25_putByte(char c, uint8_t color, vector2d_t pos) {
    const int index = __global_currentTextTerminal.get_1d_position(pos);
    tunnel_config.terminal.buffer[index] = vga_entry(c, color);
}

void __terminal80x25_putc(char c) {
    if (c == '\n') {
		tunnel_config.terminal.row++;
		tunnel_config.terminal.column = 0;

        if (tunnel_config.terminal.row == 25) {
            tunnel_config.terminal.row--;
            __global_currentTextTerminal.slide();
        }
		return;
	}

	if (tunnel_config.terminal.column == 80) {
		tunnel_config.terminal.column = 0;
		tunnel_config.terminal.row++;
		if (tunnel_config.terminal.row == 25) {
            tunnel_config.terminal.row--;
            __global_currentTextTerminal.slide();
        }
	}

    vector2d_t pos;
    pos.x = tunnel_config.terminal.column;
    pos.y = tunnel_config.terminal.row;

	__global_currentTextTerminal.put_byte(c, tunnel_config.terminal.color, pos);

	tunnel_config.terminal.column++;
}

void __terminal80x25_swrite(const char *data, int size) {
    for (int i = 0; i < size; i++) __global_currentTextTerminal.putc(data[i]);
}

void __terminal80x25_write(const char *data) {
    __global_currentTextTerminal.swrite(data, strlen(data));
}

void __terminal80x25_reset() {
    tunnel_config.terminal.column = 0;
    tunnel_config.terminal.row = 0;
    tunnel_config.terminal.color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
}

void __terminal80x25_putBackspace() {
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

    __global_currentTextTerminal.put_byte(' ', tunnel_config.terminal.color, pos);
}

terminal_t __terminal80x25_createTerminal() {
    terminal_t term;

    term.clear = __terminal80x25_clear;
    term.get_1d_position = __terminal80x25_getPosition;
    term.init = __terminal80x25_init;
    term.put_backspace = __terminal80x25_putBackspace;
    term.put_byte = __terminal80x25_putByte;
    term.putc = __terminal80x25_putc;
    term.reset = __terminal80x25_reset;
    term.set_color = __terminal80x25_setColor;
    term.slide = __terminal80x25_slide;
    term.swrite = __terminal80x25_swrite;
    term.write = __terminal80x25_write;
    
    return term;
}