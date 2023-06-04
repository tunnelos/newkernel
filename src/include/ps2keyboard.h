#pragma once

#define KPS2_OB 0b00000001
#define KPS2_IB 0b00000010
#define KPS2_SF 0b00000100
#define KPS2_CD 0b00001000
#define KPS2_UL 0b00010000
#define KPS2_UT 0b00100000
#define KPS2_TE 0b01000000
#define KPS2_PE 0b10000000
#define KPS2_DP 0x60
#define KPS2_SR 0x64

#include <stdbool.h>
#include <stdint.h>

extern char __keyboard_ps2_lookuptable[256];
extern char __keyboard_ps2_buffer[256];
extern char *sc_name[256];

enum KeyboardPS2 {
    KP_ERROR = 0,
    KP_ESC = 1,
    KP_BACKSPACE = 14,
    KP_TAB = 15,
    KP_ENTER = 28,
    KP_LCTRL = 29,
    KP_LSHIFT = 42,
    KP_RSHIFT = 54,
    KP_LALT = 56,
    KP_CAPSLOCK = 0x3A
};

bool __keyboard_ps2_init();
bool __keyboard_ps2_isTyping();
uint8_t __keyboard_ps2_getScancode();