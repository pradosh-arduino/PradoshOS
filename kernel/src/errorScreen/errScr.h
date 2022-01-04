#pragma once
#include <stdint.h>
//#include "../userspace/tss.h"

void Panic(const char* msg, const char* location, const char* when, uint64_t offset, uint8_t type_attr, uint16_t selector);
void LinuxPanic(const char* msg, const char* location, const char* when, uint64_t offset, uint8_t type_attr, uint16_t selector);