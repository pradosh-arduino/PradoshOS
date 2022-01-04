#pragma once
#include "kernelUtil.h"

bool time_init();
long long currentTime();

int getHours();
int getMinutes();
int getSeconds();
uint8_t rtc_get_year();
uint8_t rtc_get_month();
uint8_t rtc_get_day();