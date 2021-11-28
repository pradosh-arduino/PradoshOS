#pragma once

#include "BasicRenderer.h"

typedef const char* HGROUP;
typedef const char* HKEY;

class Registry{
    public:
    void Init();
    void PrintKey(HKEY a);
    void PrintGroup(HGROUP a, bool expaned, int subClass, int minus);
};

void putSpace(int f);

extern Registry* registry;