#pragma once

#include <cpuid.h>
#include "BasicRenderer.h"
#include "cstr.h"


static inline int cpuid_string(int code, int where[4]);
const char * const cpu_string();
char* getName();
void fpu_load_control_word(const uint16_t control);