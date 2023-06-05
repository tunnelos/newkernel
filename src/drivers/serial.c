#include "../include/serial.h"
#include "../include/io.h"
#include <stdarg.h>
#include "../include/stdio.h"
#include "../include/string.h"

int __serial_got_signal() {
    return inb(PORT + 5) & 1;
}
char __serial_read() {
    while(__serial_got_signal() == 0);
    return inb(PORT);
}
int __serial_transmit_check(){
    return inb(PORT + 5) & 0x20;
}
void __serial_write_char(char a){
    while(__serial_transmit_check() == 0);
    outb(PORT, a);
}
void __serial_write_raw(const char *data, uint32_t size) {
    for (uint32_t i = 0; i < size; i++) __serial_write_char(data[i]);
    return;
}
void __serial_write_fmt(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    int i = 0;
    int len = strlen(fmt);
    
    for(; i < len; i++) {
        switch(fmt[i]) {
            case '%': {
                switch(fmt[i + 1]) {
                    case 'c': {
                        char arg = va_arg(ap, int);
                        __serial_write_char(arg);
                        i++;
                        break;
                    }
                    case 's': {
                        char *arg = va_arg(ap, char *);
                        __serial_write_raw(arg, strlen(arg));
                        i++;
                        break;
                    }
                    case 'i':
                    case 'd': {
                        uint32_t arg = va_arg(ap, uint32_t);
                        if(!arg) __serial_write_char('0');
                        else {
                            char buffer[20];
                            __serial_write_raw(itoa(arg, buffer, 10), strlen(itoa(arg, buffer, 10)));
                        }
                        i++;
                        break;
                    }
                    case 'x':
                    case 'X': {
                        uint32_t arg = va_arg(ap, uint32_t);
                        char buffer[20];
                        __serial_write_raw(itoa(arg, buffer, 16), strlen(itoa(arg, buffer, 16)));
                        i++;
                        break;
                    }
                    case 'o': {
                        uint32_t arg = va_arg(ap, uint32_t);
                        char buffer[20];
                        __serial_write_raw(itoa(arg, buffer, 8), strlen(itoa(arg, buffer, 8)));
                        i++;
                        break;
                    }
                    default: {
                        va_end(ap);
                        i++;
                        break;
                    }
                }
                va_end(ap);
                break;
            }
            default: {
                __serial_write_char(fmt[i]);
                va_end(ap);
                break;
            }
        }
    }

    return;
}