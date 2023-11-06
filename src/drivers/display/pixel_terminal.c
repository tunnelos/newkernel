#include <drivers/display/pixel_terminal.h>

#include <external/psf.h>

#include <etc/embeddable/fonts/gui.h>

#include <string.h>

#include <tunnel.h>

#include <vga80x25.h>

#include <serial.h>

void __pixel_terminal_init() {
    __global_currentTextTerminal.buffer = (uint8_t *)0x00400000;
    tunnel_config.terminal.buffer = (uint8_t *)0x00400000;

    // __serial_write_fmt("pixel init\r\n");

    __global_currentTextTerminal.reset();
    __global_currentTextTerminal.clear();

    // __serial_write_fmt("pixel init done\r\n");
}

void __pixel_terminal_reset() {
    // __serial_write_fmt("pixel reset\r\n");

    __global_currentTextTerminal.column = 0;
    __global_currentTextTerminal.row = 0;
    __global_currentTextTerminal.color = VGA_COLOR_WHITE;
    __global_currentTextTerminal.color_bg = VGA_COLOR_BLACK;
    __global_currentTextTerminal.color_fg = VGA_COLOR_WHITE;

    // __serial_write_fmt("pixel reset done\r\n");
}

void __pixel_terminal_swrite(const char *data, int size) {
    for (int i = 0; i < size; i++) __global_currentTextTerminal.putc(data[i]);
}

void __pixel_terminal_put_backspace() {
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

    int old_color = __global_currentTextTerminal.color;

    __pixel_terminal_set_color(VGA_COLOR_BLACK);

    __global_currentTextTerminal.put_byte(0x13, __global_currentTextTerminal.color, pos);

    __pixel_terminal_set_color(old_color);
}

void __pixel_terminal_write(const char *str) {
    __global_currentTextTerminal.swrite(str, strlen(str));
}

void __pixel_terminal_raw_draw_pixel(vector2d_t pos, uint32_t col) {  
    uint32_t offset = (pos.y * (__global_currentTextTerminal.get_size().x * 8) + pos.x);

    ((uint32_t *)__global_currentTextTerminal.buffer)[offset] = col;
}

void __pixel_terminal_clear() {
    // __serial_write_fmt("pixel clear\r\n");

    uint8_t old_color = __global_currentTextTerminal.color;
    __global_currentTextTerminal.set_color(VGA_COLOR_BLACK);

    int w = __global_currentTextTerminal.get_size().x;
    int h = __global_currentTextTerminal.get_size().y;

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            vector2d_t pos;

            pos.x = x;
            pos.y = y;

            // __serial_write_fmt("pixel clear at %d %d\r\n", x, y);

            __global_currentTextTerminal.put_byte(0x13, __global_currentTextTerminal.color, pos);
        }
    }

    __global_currentTextTerminal.set_color(old_color);

    // __serial_write_fmt("pixel clear done\r\n");
}

void __pixel_terminal_slide() {
    // memmove((void *)__global_currentTextTerminal.buffer, (const void *)((uint16_t *)__global_currentTextTerminal.buffer + __global_currentTextTerminal.get_size().x*4), __global_currentTextTerminal.get_size().x*__global_currentTextTerminal.get_size().y*4);
    __pixel_terminal_clear();
    __pixel_terminal_reset();
}

void __pixel_terminal_putc(char c) {
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

vector2d_t __pixel_terminal_get_size() {
    vector2d_t v;

    v.x = 1280 / 8;
    v.y = 720 / 16;

    return v;
}

void __pixel_terminal_set_color(uint8_t color) {
    __global_currentTextTerminal.color_fg = VGA_COLOR_WHITE;
    __global_currentTextTerminal.color = color;
}

void __pixel_terminal_putByte(char c, uint8_t color, vector2d_t pos) {
    // __serial_write_fmt("pixel put byte %c at %d %d with color %d\r\n", c, pos.x, pos.y, color);
    int kx = 0;

    int margin = 1;
 
    uint32_t x, y, line, mask, offs;

    int fb_scanline = 5120;

    psf2_t *font = (psf2_t*)__fonts_gui;
    int bpl = (font->width + 7) / 8;

    int tx = pos.x * font->width;
    int ty = pos.y * font->height;


    uint32_t col = vga_entry_color32(color, VGA_COLOR_BLACK);

    //72
    unsigned char *glyph = (unsigned char*)font + font->headersize + (c > 0 && c < font->numglyph ? c : 0)*font->bytesperglyph;
    offs = (kx * (font->width + margin) * 4);
    if(kx >= 71) {
        ty += font->height;
        kx = 0;
        tx = 0 - font->width;
    } else {
        for(y = 0; y < font->height; y++) {
            line = offs; 
            mask = 1 << (font->width - 1);
            for(x = 0; x < font->width; x++) {
                // uint32_t *address = 
                if (((int)*glyph) & (mask)) {
                    *
                    (
                        (uint32_t*)
                        (
                            (uint32_t)tunnel_config.terminal.buffer + line + 
                                (ty * fb_scanline) 
                            + 
                                (tx * 4)
                        )
                    ) = col;
                }
                mask >>= 1; 
                line += 4;
            } 
            glyph += bpl;
            offs += fb_scanline;
        }
    }
}

uint32_t __pixel_terminal_getPosition(vector2d_t pos) {
    pos.x %= __global_currentTextTerminal.get_size().x;
    pos.y %= __global_currentTextTerminal.get_size().y;
    
    return pos.y * __global_currentTextTerminal.get_size().x + pos.x;
}

terminal_t __pixel_terminal_createTerminal() {
    terminal_t term = {};

    term.clear = __pixel_terminal_clear;
    term.get_1d_position = __pixel_terminal_getPosition;
    term.init = __pixel_terminal_init;
    term.put_backspace = __pixel_terminal_put_backspace;
    term.put_byte = __pixel_terminal_putByte;
    term.putc = __pixel_terminal_putc;
    term.reset = __pixel_terminal_reset;
    term.set_color = __pixel_terminal_set_color;
    term.slide = __pixel_terminal_slide;
    term.swrite = __pixel_terminal_swrite;
    term.write = __pixel_terminal_write;
    term.get_size = __pixel_terminal_get_size;
    term.raw_draw_pixel = __pixel_terminal_raw_draw_pixel;

    return term;
}