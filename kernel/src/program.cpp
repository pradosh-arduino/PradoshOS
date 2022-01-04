#include "mtask.h"

extern "C" void programASM();

void program(){
    lock_scheduler();
    schedule();
    unlock_scheduler();
    programASM();
}