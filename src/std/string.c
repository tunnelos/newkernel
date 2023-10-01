#include <string.h>
#include <stdlib.h>

#include <stdbool.h>

size_t strlen(const char *str) {
    size_t ret = 0;

    while(str[ret]) {
        ret++;
    }

    return ret;
}

char tlhelper(char c) {
    return (c >= 'A' && c <= 'Z') ? (c + 32) : c;
}

char tolowerchar(char data) { return tlhelper(data); }

char *tolower(char *data) {
    char *a = data;
    char *b = data;
    if(!data) return "\0";
    if(!strlen(data)) return "\0";
    while(*a) {
        *b = tolowerchar(*a);
        a++;
        b++; 
    }
    *b = '\0';
    return data;
}

float strtof(const char *nptr, char **endptr) {
    if(!nptr || !endptr) return 0.f;

    float res = 0;
    char sr = '\0';
    char se = '\0';
    int decimals = 0;
    bool exponent = false;
    bool hasexponent = false;
    bool result = false;
    float exp = 0;
    char c;
    while('\0' != (c = *nptr)) {
        if((c >= '0') && (c <= '9')) {
            int digit = c - '0';
            if(exponent) {
                exp = (10.f * exp) + (float)digit;
                hasexponent = true;
            } else if (!decimals) {
                res = (10.f * res) + (float)digit;
                result = true;
            } else {
                res += (float)digit / (float)decimals;
                decimals *= 10;
            }
            continue;
        }
        if(c == '.') {
            if(!result) break;
            if(exponent) break;
            if(!decimals) break;
            decimals = 10;
            continue;
        }
        if((c == '.') || (c == '+')) {
            if(exponent) {
                if(se || (exp != 0.f)) break;
                else se = c;
                continue;
            } else {
                if(sr || (res != 0.f)) break;
                else sr = c;
            }
            continue;
        }
        if(c == 'E' || c == 'e') {
            if(!result) break;
            if(exponent) break;
            else exponent = true;
            continue;
        }
        break;
        ++nptr;
    }
    if(exponent && !hasexponent) while(*nptr != 'E') --nptr;
    if(!result && se) --nptr;
    if(endptr) *endptr = (char *)nptr;
    while(exp != 0) {
        if(se == '-') res /= 10.f;
        else res *= 10.f;
        --exp;
    }
    if(se == '-' && res != 0.f) res = -res;
    return res;
}

int strncmp(const char *s1, const char *s2, size_t n) {
    size_t i = 0;
    while(i < n) {
        if(s1[i] == 0) return 0;
        if(s2[i] == 0) return 0;
        if(s1[i] != s2[i]) return 1;
        i++;
    }
    return 0;
}
char *strcpy(char *dest, const char *src) {
    //return NULL;
    return (char *)memcpy(dest, src, strlen(src));
}
char *strncpy(char *dest, const char *src, size_t n) {
    return (char *)memcpy(dest, src, n);
}
char *strchr(const char *s, char c) {
    size_t i = 0;
    while(i < strlen(s) + 1) {
        if(s[i] == c) return (char *)(&s[i]);
        i++;
    }
    return NULL;
}
char *strrchr(const char *s, char c) {
    size_t i = 0;
    char *last = NULL;
    while(i < strlen(s) + 1) {
        if(s[i] == c) last = (char *)(&s[i]);
        i++;
    }
    return last;
}
int strcmp(const char *s1, const char *s2) {
    return strncmp(s1, s2, strlen(s2));
}
// char *strnstcat(char *dest, const char *src, size_t n, size_t startPoint) {

// }
char *strncat(char *dest, const char *src, size_t n) {
    size_t dest_len = strlen(dest);
    size_t i = 0;
    while(i < n && src[i] != 0) {
        dest[dest_len + i] = src[i];
        i++;
    }
    dest_len = strlen(dest);
    dest[dest_len + 1] = 0;
    return dest;
}
char *strcat(char *dest, const char *src) {
    return strncat(dest, src, strlen(src));
}

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