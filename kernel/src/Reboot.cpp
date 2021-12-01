#include <stdint.h>
#include "IO.h"
#include "Reboot.h"
#include "BasicRenderer.h"

#define KBRD_INTRFC 0x64

#define KBRD_BIT_KDATA 0
#define KBRD_BIT_UDATA 1
 
#define KBRD_IO 0x60
#define KBRD_RESET 0xFE
 
#define bit(n) (1<<(n))

#define check_flag(flags, n) ((flags) & bit(n))
 
void RebootSystem()
{
    
    uint8_t temp;
 
    asm volatile ("cli");

    do
    {
        temp = inb(KBRD_INTRFC);
        if (check_flag(temp, KBRD_BIT_KDATA) != 0)
            inb(KBRD_IO);
    } while (check_flag(temp, KBRD_BIT_UDATA) != 0);
 
    outb(KBRD_INTRFC, KBRD_RESET);
    GlobalRenderer->Print("Unable to reboot system press and hold power button to shutdown.");
    Fail();
}

void Fail(){
    asm("hlt");
    Fail();
}