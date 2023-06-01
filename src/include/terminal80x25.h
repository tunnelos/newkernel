#pragma once

#include <stdint.h>
#include "vector2d.h"

typedef struct terminal_t {
    uint32_t row;
    uint32_t column;
    uint8_t color;
    uint16_t *buffer;
} terminal_t;

void __terminal_init();
void __terminal_setColor(uint8_t color);
void __terminal_putByte(char c, uint8_t color, vector2d_t pos);
void __terminal_putc(char c);
void __terminal_swrite(const char *data, int size);
void __terminal_write(const char *str);