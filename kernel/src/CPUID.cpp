#include "CPUID.h"
#include "IO.h"

int cpuData[10];
static inline int cpuid_string(int code, int where[4]) {
  __asm__ volatile ("cpuid":"=a"(*where),"=b"(*(where+0)),
               "=d"(*(where+1)),"=c"(*(where+2)):"a"(code));
  return (int)where[0];
}
 
const char * const cpu_string() {
	static char s[16] = "BogusProces!";//BogusProces!
	cpuid_string(0, (int*)(s));
	return s;
}
inline void cpuid(uint32_t reg, uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t *edx)
{
    __asm__ volatile("cpuid"
        : "=a" (*eax), "=b" (*ebx), "=c" (*ecx), "=d" (*edx)
        : "0" (reg));
}

char vendor[128];
char* getName() {
    cpuid(0x80000002, (uint32_t *)(vendor +  0), (uint32_t *)(vendor +  4), (uint32_t *)(vendor +  8), (uint32_t *)(vendor + 12));
    cpuid(0x80000003, (uint32_t *)(vendor + 16), (uint32_t *)(vendor + 20), (uint32_t *)(vendor + 24), (uint32_t *)(vendor + 28));
    cpuid(0x80000004, (uint32_t *)(vendor + 32), (uint32_t *)(vendor + 36), (uint32_t *)(vendor + 40), (uint32_t *)(vendor + 44));
    vendor[127] = 0;
    return vendor;
}

void fpu_load_control_word(const uint16_t control)
{
  asm volatile("fldcw %0;"::"m"(control)); 
}