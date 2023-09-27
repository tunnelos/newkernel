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
    return x < 0.f ? -x : x;
}

float sqrt(float number){
    assert(number >= 0);

    float i = 0;

    while(i <= number){
        if((i * i) >= number) return i;
        i += 0.000001;
    }

    return i;
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
    if( x < 0.0f ) x = -x;
    if (compare_float(x, PI * 2) <= 0) {
        do { x -= PI * 2; }
        while(compare_float(x, PI * 2) <= 0);
    }

    if ((compare_float(x, PI) <= 0) && (compare_float(x, PI * 2) == -1)){
        x -= PI;
        return ((-1) * (1.0f - (x * x / 2.0f) * ( 1.0f - (x * x / 12.0f) * ( 1.0f - (x * x / 30.0f) * (1.0f - (x * x / 56.0f ) * (1.0f - (x * x / 90.0f) * (1.0f - (x * x / 132.0f) * (1.0f - (x * x / 182.0f)))))))));
    } 
    return 1.0f - (x * x/2.0f) * ( 1.0f - (x * x / 12.0f) * ( 1.0f - (x * x / 30.0f) * (1.0f - (x * x / 56.0f ) * (1.0f - (x * x / 90.0f) * (1.0f - (x * x / 132.0f) * (1.0f - (x * x / 182.0f)))))));
}

float fmod(float x, float y){
  return x - truncate(x / y) * y;
}

float sin(float x){
    return cos(x - (PI / 2.f));
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