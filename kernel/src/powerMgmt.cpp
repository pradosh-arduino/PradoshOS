#include "powerMgmt.h"
#include "IO.h"

int failedAttempt = 0;

void restart(){
	 uint8_t good = 0x02;
     while (good & 0x02)
        good = inb(0x64);
     outb(0x64, 0xFE);
}

void shutdown(){
   asm("cli");
   outw(0xB004, 0x2000);  //bochs
   outw(0x604, 0x2000);   //qemu
   outw(0x4004, 0x3400);  //vbox
   failedAttempt++;
   shutdown();
} 