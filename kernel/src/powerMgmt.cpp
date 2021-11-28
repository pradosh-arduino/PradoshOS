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
   outw(0xB004, 0x2000);  //bochs
   outw(0x604, 0x2000);   //qemu
   outw(0x4004, 0x3400);  //vbox
} 