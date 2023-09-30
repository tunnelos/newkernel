#include <text_terminal.h>

void *__text_terminal_getStaticBufferAddress() {
    return (void *)0x00400000;
}

terminal_t __text_terminal_createBasicTerminal() {
    terminal_t t;
}