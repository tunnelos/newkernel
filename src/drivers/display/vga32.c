#include <vga80x25.h>

uint32_t vga_entry_color32(enum vga_color fg, enum vga_color bg) {
    uint32_t color_set[0xFF] = {
        0xFF000000, 0x00FF0000, 0xFF00FF00, 0xFFFFFF00,
        0xFF0000FF, 0xFFFF00FF, 0xFF2A2AA5, 0xFFD3D3D3, // FF84A4C4
        0xFF999489, 0xFFFF9600, 0xFFBFE29F, 0xFFFFF97D,
        0xFF3344FF, 0xFFFF50FF, 0xFF84A4C4, 0xFFFFFFFF
    };

    return color_set[fg];
}