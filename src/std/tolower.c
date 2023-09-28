#include <ctype.h>

#include <string.h>

char tolowerchar(char data) { return (data >= 'A' && data <= 'Z') ? (data + 32) : data; }

char *tolower(char *data) {
    char *a = data;
    char *b = data;

    if(!data) return "\0";
    if(!strlen(data)) return "\0";

    while(*a) {
        *b = (*a >= 'A' && *a <= 'Z') ? (*a + 32) : *a;
        a++;
        b++; 
    }
    *b = '\0';
    return data;
}