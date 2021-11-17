#pragma once

#include <cpuid.h>
#include "BasicRenderer.h"
#include "cstr.h"


static inline int cpuid_string(int code, int where[4]);
const char * const cpu_string();
char* getName();