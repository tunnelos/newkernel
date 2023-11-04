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

vector2d_t __terminal80x25_getSize() {
    vector2d_t vec;

    vec.x = 80;
    vec.y = 25;

    return vec;
}

void __terminal80x25_init() {
    tunnel_config.terminal.buffer = (uint8_t *)0x00400000;
    __global_currentTextTerminal.buffer = (uint8_t *)0x00400000;
    
    __global_currentTextTerminal.reset();
    __global_currentTextTerminal.clear();
}

void __terminal80x25_clear() {
    // uint8_t old_color = __global_currentTextTerminal.color;
    // __global_currentTextTerminal.set_color(vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_BLACK));

    // for (int y = 0; y < 25; y++) {
	// 	for (int x = 0; x < 80; x++) {
	// 		const int index = y * 80 + x;
	// 		__global_currentTextTerminal.buffer[index] = vga_entry(0xDB, __global_currentTextTerminal.color);
	// 	}
	// }

    // __global_currentTextTerminal.set_color(old_color);

    uint8_t old_color = __global_currentTextTerminal.color;
    __global_currentTextTerminal.set_color(vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_BLACK));

    int w = __global_currentTextTerminal.get_size().x;
    int h = __global_currentTextTerminal.get_size().y;

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            vector2d_t pos;

            pos.x = x;
            pos.y = y;

            __global_currentTextTerminal.put_byte(0xDB, __global_currentTextTerminal.color, pos);
        }
    }

    __global_currentTextTerminal.set_color(old_color);
}

void __terminal80x25_slide() {
    // for (int y = 0; y < 25; y++) {
		// for (int x = 0; x < 80; x++) {
			// const int index = y * 80 + x;
			// __global_currentTextTerminal.buffer[index] = __global_currentTextTerminal.buffer[(index == 0) ? 0 : index - 1];
		// }
	// }

    memmove((void *)__global_currentTextTerminal.buffer, (const void *)((uint16_t *)__global_currentTextTerminal.buffer + __global_currentTextTerminal.get_size().x*2), __global_currentTextTerminal.get_size().x*__global_currentTextTerminal.get_size().y*2);

    // uint8_t old_color = __global_currentTextTerminal.color;
    // __terminal80x25_setColor(vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_BLACK));

    // for (int x = 0; x < 80; x++) {
    //     __terminal80x25_putByte(' ', __global_currentTextTerminal.color, (vector2d_t){x, 80});   
    // }

    // __terminal80x25_setColor(old_color);
}

uint32_t __terminal80x25_getPosition(vector2d_t pos) {
    pos.x %= 80;
    pos.y %= 25;
    
    return pos.y * 80 + pos.x;
}

void __terminal80x25_setColor(uint8_t color) {
    __global_currentTextTerminal.color = color;
}

void __terminal80x25_putByte(char c, uint8_t color, vector2d_t pos) {
    const int index = __global_currentTextTerminal.get_1d_position(pos);
    
    uint16_t *b = (uint16_t *)__global_currentTextTerminal.buffer;

    b[index] = vga_entry(c, color);
}

void __terminal80x25_putc(char c) {
    if (c == '\n') {
		__global_currentTextTerminal.row++;
		__global_currentTextTerminal.column = 0;

        if (__global_currentTextTerminal.row == __global_currentTextTerminal.get_size().y) {
            __global_currentTextTerminal.row--;
            __global_currentTextTerminal.slide();
        }
		return;
	}

	if (__global_currentTextTerminal.column == __global_currentTextTerminal.get_size().x) {
		__global_currentTextTerminal.column = 0;
		__global_currentTextTerminal.row++;
		if (__global_currentTextTerminal.row == __global_currentTextTerminal.get_size().y) {
            __global_currentTextTerminal.row--;
            __global_currentTextTerminal.slide();
        }
	}

    vector2d_t pos;
    pos.x = __global_currentTextTerminal.column;
    pos.y = __global_currentTextTerminal.row;

	__global_currentTextTerminal.put_byte(c, __global_currentTextTerminal.color, pos);

	__global_currentTextTerminal.column++;
}

void __terminal80x25_swrite(const char *data, int size) {
    for (int i = 0; i < size; i++) __global_currentTextTerminal.putc(data[i]);
}

void __terminal80x25_write(const char *data) {
    __global_currentTextTerminal.swrite(data, strlen(data));
}

void __terminal80x25_reset() {
    __global_currentTextTerminal.column = 0;
    __global_currentTextTerminal.row = 0;
    __global_currentTextTerminal.color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
}

void __terminal80x25_putBackspace() {
    vector2d_t pos;

    __global_currentTextTerminal.column--;
    if (__global_currentTextTerminal.column < 0) {
        __global_currentTextTerminal.column = 0;
        __global_currentTextTerminal.row--;

        if (__global_currentTextTerminal.row < 0) {
            __global_currentTextTerminal.row = 0;
        }
    }

    pos.x = __global_currentTextTerminal.column;
    pos.y = __global_currentTextTerminal.row;

    __global_currentTextTerminal.put_byte(' ', __global_currentTextTerminal.color, pos);
}

terminal_t __terminal80x25_createTerminal() {
    terminal_t term = {};

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
    term.get_size = __terminal80x25_getSize;
    
    return term;
}