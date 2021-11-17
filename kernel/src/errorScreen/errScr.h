#pragma once
#include <stdint.h>

void Panic(const char* msg, const char* location, const char* when, const char* Gate, uint8_t selector);