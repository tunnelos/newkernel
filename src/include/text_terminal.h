#pragma once

#include <stdint.h>

#include <vector2d.h>

typedef struct terminal_t {
    int row;
    int column;
    uint8_t color;
    uint8_t color_fg;
    uint8_t color_bg;
    uint8_t *buffer;

    // functions

    void (*init)();

    void (*set_color)(uint8_t color);

    void (*put_byte)(char c, uint8_t color, vector2d_t pos);
    void (*putc)(char c);
    void (*put_backspace)();

    uint32_t (*get_1d_position)(vector2d_t pos);

    void (*swrite)(const char *data, int size);
    void (*write)(const char *str);

    void (*clear)();
    void (*reset)();
    void (*slide)();

    vector2d_t (*get_size)();

    void *(*get_static_buffer_address)();

    // draws pixel, not character on mapped character table for this terminal
    void (*raw_draw_pixel)(vector2d_t pos, uint32_t color);
} terminal_t;

extern terminal_t __global_currentTextTerminal;

terminal_t __text_terminal_createBasicTerminal();