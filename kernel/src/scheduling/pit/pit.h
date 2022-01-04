#pragma once
#include <stdint.h>

namespace PIT {
    extern double TimeSinceBoot;
    extern double BootTime;
    const uint64_t BaseFrequency = 1193182;
    
    void Sleepd(double second);
    void Sleep(uint64_t milliseconds);
    void Sleeps(uint64_t microseconds);

    void SetDivisor(uint16_t divisor);
    uint64_t GetFrequency();
    void SetFrequency(uint64_t frequency);
    void Tick();

}