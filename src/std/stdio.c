#include <stdio.h>
#include <terminal80x25.h>
#include <string.h>
#include <math.h>

#include <stdarg.h>

#include <tunnel.h>

int sprintf(char *str, const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    int i = 0;
    size_t si = 0;
    int len = strlen(fmt);

    while(i < len) {
        switch(fmt[i]){
            case '%': {
                __serial_write_fmt("Case %c %d %d\n", fmt[i + 1], i, si);
                switch(fmt[i + 1]) {
                    case 'c': {
                        char arg = va_arg(ap, int);
                        str[si] = arg;
                        si++;
                        i++;
                        break;
                    }
                    case 's': {
                        char *arg = va_arg(ap, char *);
                        size_t l = strlen(arg);
                        strncpy(str + si, arg, l);
                        si += strlen(arg);
                        i++;
                        break;
                    }
                    case 'i':
                    case 'd': {
                        int arg = va_arg(ap, int);
                        if(arg == 0) str[si++] = '0';
                        else {
                            char buffer[20];
                            itoa(arg, buffer, 10);
                            strncpy(str + si, buffer, 20);
                            si += strlen(buffer);
                        }
                        i++;
                        break;
                    }
                    case 'x':
                    case 'X': {
                        int arg = va_arg(ap, int);
                        char buffer[20];
                        itoa(arg, buffer, 16);
                        //trncmp(&str[si], buffer, strlen(buffer));
                        strncpy(str + si, buffer, strlen(buffer));
                        i++;
                        si += strlen(buffer);
                        break;
                    }
                    case 'F':
                    case 'f': {
                        float arg = (float)(va_arg(ap, double));
                        char buffer[20];
                        ftoa(arg, buffer);
                        strncpy(str + si, buffer, strlen(buffer));
                        si += strlen(buffer);
                        i++;
                        break;
                    }
                    // default: {
                    //     va_end(ap);
                    //     break;
                    // }
                }
                va_end(ap);
                break;
            }
            case '\n': {
                str[si] = '\n';
                si++;
                va_end(ap);
                break;
            }
            default: {
                str[si] = fmt[i];
                si++;
                va_end(ap);
            }
        }
        i++;
    }

    str[si] = 0;

    return si;
}

void putc(const char c) {
    tunnel_config.terminal.putc(c);
}
void puts(const char *str) {
    tunnel_config.terminal.write(str);
}

int atoi(const char *str) {
    int res = 0;
    for (int i = 0; str[i] != '\0'; ++i) res = res * 10 + str[i] - '0';
    return res;
}

char *strrev(char* src) {
    return strnrev(src, strlen(src));
}

char *strnrev(char* src, size_t len) {
    size_t i = 0;
    size_t j = len - 1;
    char temp = 0;

    while (i < j) {
        temp = src[i];
        src[i] = src[j];
        src[j] = temp;
        i++;
        j--;
    }

    return src;
}

char *ftoa(float num, char* buffer) {
    return ftoa_ex(num, buffer, 6);
}

char *ftoa_ex(float num, char* buffer, int afterpoints) {
    int afterpoint = afterpoints;

    int ipart = (int)num;
    float fpart = num - (float)ipart;
 
    int i = itoa2(ipart, buffer, 1);

    // check for display option after point
    if (afterpoint != 0) {
        buffer[i] = '.';

        fpart = fpart * pow(10, afterpoint);
 
        itoa2((int)fpart, buffer + i + 1, afterpoint);
    }

    return buffer;
}


char itoc(int num) {
    return '0' + num;
}

char itoh(int num, bool upper) {
    if(upper) return num - 10 + 'A';
    return num - 10 + 'a';
}

char *itoa(int num, char *buffer, int base) {
    int buffer_size = 20;
    int counter = 0;
    int digit = 0;
    
    if(num == 0) return "0";

    while(num != 0 && counter < buffer_size){
        digit = (num % base);
        if(digit > 9){
            buffer[counter++] = itoh(digit, true);
        } else {
            buffer[counter++] = itoc(digit);
        }
        num /= base;
    }

    buffer[counter] = '\0';
    return strrev(buffer);
}

int itoa2(int num, char *buffer, int zeros) {
    int i = 0;

    while (num) {
        buffer[i++] = (num % 10) + '0';
        num = num / 10;
    }
 
    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < zeros) buffer[i++] = '0';
 
    strrev(buffer);
    buffer[i] = '\0';

    return i;
}

int printf(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    int i = 0;
    int len = strlen(fmt);
    va_end(ap);

    int si = 0;

    while(i < len) {
        switch(fmt[i]){
            case '%': {
                switch(fmt[i + 1]) {
                    case 'c': {
                        char arg = va_arg(ap, int);
                        putc(arg);
                        i++;
                        si++;
                        break;
                    }
                    case 's': {
                        char *arg = va_arg(ap, char *);
                        puts(arg);
                        i++;
                        si += strlen(arg);
                        break;
                    }
                    case 'i':
                    case 'd': {
                        int arg = va_arg(ap, int);
                        if(arg == 0) {
                            putc('0');
                            si++;
                        } else {
                            char buffer[20];
                            puts(itoa(arg, buffer, 10));
                            si += strlen(buffer);
                        }
                        i++;
                        break;
                    }
                    case 'x':
                    case 'X': {
                        int arg = va_arg(ap, int);
                        char buffer[20];
                        puts(itoa(arg, buffer, 16));
                        si += strlen(buffer);
                        i++;
                        break;
                    }
                    case 'F':
                    case 'f': {
                        float arg = (float)(va_arg(ap, double));
                        char buffer[20];
                        puts(ftoa(arg, buffer));
                        si += strlen(buffer);
                        i++;
                        break;
                    }
                    default: {
                        va_end(ap);
                        si++;
                        break;
                    }
                }
                va_end(ap);
                break;
            }
            default: {
                putc(fmt[i]);
                va_end(ap);
                break;
            }
        }
        i++;
        si++;
    }
    return si;
}