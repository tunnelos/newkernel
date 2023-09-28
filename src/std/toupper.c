#include <ctype.h>

#include <stddef.h>

char toupperchar(char c) {
    if (c >= 'a' && c <= 'z') {
        c = c - 'a' + 'A'; 
    }
    return c;
}

char *toupper(char *data) {
    size_t len = strlen(data);
    size_t i;

    for (i = 0; i < len; i++) {
        data[i] = toupperchar(data[i]);
    }
    return data;
}