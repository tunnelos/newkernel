#include <math.h>
#include <stdint.h>
#include <assert.h>

int16_t compare_float(float f1, float f2){
    float precision = 0.000001;
    if ((f1 - precision) < f2)
        return -1;
    else if ((f1 + precision) > f2)
        return 1;
    else
        return 0;
}

int32_t abs(int x){
  return x < 0 ? -x : x;
}

float fabs(float x){
    float result;
    asm("fabs" : "=t"(result) : "0"(x));
    return result;
}

float sqrt(float number){
    assert(number >= 0);

    float result;
    asm("fsqrt" : "=t"(result) : "0"(number));
    return result;
}

float round(float number){
    float r = number;
    if((number - floor(number)) > 0.444444) r++;
    return floor(r);
}

int32_t ceil(float x){
    int32_t y = (int32_t)x;
    if (x == (float)y) return y;
    return y + 1;
}

float cos(float x){
    float result;
    asm("fcos" : "=t"(result) : "0"(x));
    return result;
}

float fmod(float x, float y){
  return x - truncate(x / y) * y;
}

float sin(float x){
    float result;
    asm("fsin" : "=t"(result) : "0"(x));
    return result;
}

int32_t pow(int x, int y){
    int result = x;
    if(y != 0){
        for(int i = 1; i < y; i++){
            result *= x;
        }
    } else {
        result = 1;
    }

    return result;
}

int32_t floor(float x){
    return (int)x;
}

float floorf(float x){
    return (float)floor(x);
}

float truncate(float x){
  return x < 0 ? -floorf(-x) : floorf(x);
}