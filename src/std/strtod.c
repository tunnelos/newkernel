#include <stdlib.h>

#include <stdbool.h>

double strtod(const char *nptr, char **endptr) {
    if(!nptr || !endptr) return 0.f;

    double res = 0;
    char sr = '\0';
    char se = '\0';
    int decimals = 0;
    bool exponent = false;
    bool hasexponent = false;
    bool result = false;
    double exp = 0;
    char c;
    while('\0' != (c = *nptr)) {
        if((c >= '0') && (c <= '9')) {
            int digit = c - '0';
            if(exponent) {
                exp = (10 * exp) + digit;
                hasexponent = true;
            } else if (!decimals) {
                res = (10 * res) + digit;
                result = true;
            } else {
                res += (double)digit / decimals;
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
                if(se || (exp != 0)) break;
                else se = c;
                continue;
            } else {
                if(sr || (res != 0)) break;
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
        if(se == '-') res /= 10;
        else res *= 10;
        --exp;
    }
    if(se == '-' && res != 0) res = -res;
    return res;
}