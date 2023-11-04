#include <vga80x25.h>

uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
    return fg | bg << 4;
}
uint16_t vga_entry(unsigned char uc, uint8_t color) {
    return (uint16_t) uc | (uint16_t) color << 8;
}

uint32_t vga_entry_color32(enum vga_color fg, enum vga_color bg) {
    uint32_t color_set[0xFF] = {
        0x000000FF, 0x0000FF00, 0x00FF00FF, 0x00FFFFFF,
        0xFF0000FF, 0xFF00FFFF, 0xA52A2AFF, 0xD3D3D3FF,
        0x899499FF, 0x0096FFFF, 0x9FE2BFFF, 0x7DF9FFFF,
        0xFF4433FF, 0xFF50FFFF, 0xC4A484FF, 0xFFFFFFFF
    };

    return color_set[fg];
}