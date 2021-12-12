#include "usergdt.h"
#include "tss.h"
#include "../BasicRenderer.h"

uint64_t UserStack[0x400];

void userFunction() {
    while(1){}
}