#include <drivers/display/pixel_terminal.h>

#include <external/psf.h>

#include <etc/embeddable/fonts/gui.h>

#include <string.h>

void __pixel_terminal_init() {
    __global_currentTextTerminal.buffer = (uint16_t *)0x00400000;

    __global_currentTextTerminal.reset();
    __global_currentTextTerminal.clear();
}

void __pixel_terminal_reset() {
    __global_currentTextTerminal.column = 0;
    __global_currentTextTerminal.row = 0;
    // __global_currentTextTerminal.color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
}

void __pixel_terminal_write(const char *str) {
    __global_currentTextTerminal.swrite(str, strlen(str));
}

void __pixel_terminal_putByte(char c, uint8_t color, vector2d_t pos) {
    psf2_t *font = (psf2_t *)__fonts_gui;

    int x = pos.x, y = pos.y, kx = 0, line, mask, offs;
    int bpl = (font->width + 7) / 8;
    int char_index = 0;

    char s1[] = {c, 0};

    char *s = s1;

    int fb_scanline = 1;

    while(*s) {
        unsigned char *glyph = __fonts_gui + font->headersize + (*s>0&&*s<font->numglyph?*s:0)*font->bytesperglyph;
        offs = (kx * (font->width+1) * 4);
        for(y = 0; y < font->height; y++) {
            line= offs; mask = 1 << (font->width - 1);
            for(x = 0; x < font->width; x++) {
                *((uint32_t*)((uint32_t)__global_currentTextTerminal.buffer + line)) = ((int)*glyph) & (mask) ? 0xFFFFFF : 0;
                mask >>= 1; line += 4;
            }
            *((uint32_t*)((uint32_t)__global_currentTextTerminal.buffer + line)) = 0; glyph += bpl; offs += fb_scanline;
        }
        s++; 
        kx++;
        char_index++;
    }

}

terminal_t __pixel_terminal_createTerminal() {
    terminal_t term = {};

    return term;
}