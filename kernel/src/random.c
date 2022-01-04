#include "rtc.h"

int randomSeed(int seed, int length);
int random(int length);

int random(int length){
    return randomSeed(getSeconds(), length);
}

int randomSeed(int seed, int length){
    int i = 1;
    for(int j = 0; j < length; j++){
        i = i * 10;
    }

    unsigned long long int a = 2344 + 23434 + 32684845498 + 324234 + 2342 + seed * 48578585;
    a = a / i;

    return a;
}