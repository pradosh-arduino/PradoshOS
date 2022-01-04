#include "pit.h"
#include "../../IO.h"
#include "../../userinput/mouse.h"

namespace PIT{
    double TimeSinceBoot = 0;
    uint16_t Divisor = 65535;
    double BootTime = 0;
    void Sleepd(double seconds){
        double startTime = TimeSinceBoot;
        while (TimeSinceBoot < startTime + seconds){
            asm("hlt");
            ProcessMousePacket();
        }
    }
    void Sleep(uint64_t milliseconds){
        Sleepd((double)milliseconds / 1000);
    }
    void Sleeps(uint64_t microseconds){
        Sleepd((double)microseconds / 10000);
    }
    void SetDivisor(uint16_t divisor)
    {
        if (divisor < 100) divisor = 100;
        Divisor = divisor;   
        outb(0x40, (uint8_t)(divisor & 0x00ff));
        io_wait();   
        outb(0x40, (uint8_t)((divisor & 0xff00) >> 8));

    }
    uint64_t GetFrequency(){
        return BaseFrequency / Divisor;
    }
    void SetFrequency(uint64_t frequency){
        SetDivisor(BaseFrequency / frequency);
    }
    void Tick(){
        float lastTime = 1;
        double startTime = TimeSinceBoot;
        while(TimeSinceBoot < startTime + lastTime){
          TimeSinceBoot += 1;
        }
    }
}