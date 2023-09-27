#include <ps2keyboard.h>
#include <io.h>

char __keyboard_ps2_lookuptable[256] = {'?',     '?',     '1',     '2',    '3',      '4',      '5',      '6',
                                        '7', '8', '9', '0', '-', '=', '?', '?', 'q', 'w', 'e', 'r', 't', 'y',
                                        'u', 'i', 'o', 'p', '[', ']', '?', '?',  'a',  's',  'd',  'f',  'g',
                                        'h', 'j', 'k', 'l', ';', '\'', '`', '?', '\\', 'z',  'x',  'c',  'v',
                                        'b',   'n',   'm',   ',',   '.',   '/',   '?',    '?',    '?',    ' ' 
};
char *sc_name[256] = {                  "ERROR",    "Esc",    "1",     "2",    "3",     "4",     "5",    "6",
                                        "7", "8", "9", "0", "-", "=",  "Backspace",  "Tab",  "Q",  "W",  "E",
                                        "R", "T", "Y",  "U",  "I",  "O",  "P",  "[", "]",  "Enter",  "Lctrl",
                                        "A", "S",  "D",  "F",  "G",  "H",  "J",  "K",  "L",  ";",  "'",  "`",
                                        "LShift", "\\",  "Z",  "X",  "C",  "V",  "B",  "N",  "M",  ",",  ".",
                                        "/",       "RShift",       "Keypad *",       "LAlt",       "Spacebar" 
};

bool __keyboard_ps2_init() {
    return (inb(KPS2_SR) & KPS2_SF) ? true : false;
}

bool __keyboard_ps2_isTyping() {
    return __keyboard_ps2_getScancode() != 0;
}

uint8_t __keyboard_ps2_getScancode() {
    uint8_t data = inb(0x64) & 1;

    if (data) {
        uint8_t scancode = inb(0x60);
        if(!(scancode & 0x80)) {
            return scancode;
        }
        return 0;
    }
    return 0;
}