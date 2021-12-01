#include "powerMgmt.h"
#include "IO.h"
#include "scheduling/pit/pit.h"
#include "mtask.h"

int failedAttempt = 0;

void restart(){
   terminate_task(4);
   cleanup_terminated_task(task2);
	 uint8_t good = 0x02;
     while (good & 0x02)
        good = inb(0x64);
     outb(0x64, 0xFE);
}

void shutdown(){
   terminate_task(4);
   cleanup_terminated_task(task2);
   __asm__ __volatile__ ("outw %1, %0" : : "dN" ((uint16_t)0xB004), "a" ((uint16_t)0x2000));
}