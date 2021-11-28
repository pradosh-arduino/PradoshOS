#pragma once

#include <stdint.h>
#include <stddef.h>

struct AppValues{
    char AppStart;
    bool test;
    char AppEnd;
};

struct AppDatas{
    int AppSize = 1; //KB
    const char* AppName = "testapp.h";
    float version = 0.1;
    size_t TotalAppValues = sizeof(AppValues);
    size_t appCodeSize = sizeof(TotalAppValues) - 2;
};