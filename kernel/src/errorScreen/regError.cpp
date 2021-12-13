#include "regError.h"
#include "../BasicRenderer.h"

__REGS__ register64;

void _getReg(void* __r, enum __REGS__ __reg) {
    uint64_t res64 = 0;
    uint32_t res32 = 0;
    uint16_t res16 = 0;
    uint8_t usedValBits = 0;

    switch (__reg) {
        case __REG__RAX:  { asm("movq (%%rax), %0" : "=a"(res64)); usedValBits = 64; break; }
        case __REG__RBX:  { asm("movq (%%rbx), %0" : "=a"(res64)); usedValBits = 64; break; }
        case __REG__RCX:  { asm("movq (%%rcx), %0" : "=a"(res64)); usedValBits = 64; break; }
        case __REG__RDX:  { asm("movq (%%rdx), %0" : "=a"(res64)); usedValBits = 64; break; }
        case __REG__RSP:  { asm("movq (%%rsp), %0" : "=a"(res64)); usedValBits = 64; break; }
        case __REG__RBP:  { asm("movq (%%rbp), %0" : "=a"(res64)); usedValBits = 64; break; }
        case __REG__RIP:  { asm("lea (%%rip), %0"  : "=a"(res64)); usedValBits = 64; break; }
        case __REG__EAX:  { asm("movl (%%eax), %0" : "=a"(res32)); usedValBits = 32; break; }
        case __REG__EBX:  { asm("movl (%%ebx), %0" : "=a"(res32)); usedValBits = 32; break; }
        case __REG__ECX:  { asm("movl (%%ecx), %0" : "=a"(res32)); usedValBits = 32; break; }
        case __REG__EDX:  { asm("movl (%%edx), %0" : "=a"(res32)); usedValBits = 32; break; }
        case __REG__ESP:  { asm("movl (%%esp), %0" : "=a"(res32)); usedValBits = 32; break; }
        case __REG__EBP:  { asm("movl (%%ebp), %0" : "=a"(res32)); usedValBits = 32; break; }
        case __REG__EIP:  { asm("movl (%%eip), %0" : "=a"(res32)); usedValBits = 32; break; }
    }

    if (usedValBits == 16) {
        *(uint16_t*)__r = res16;
    } else if (usedValBits == 32) {
        *(uint32_t*)__r = res32;
    } else if (usedValBits == 64) {
        *(uint64_t*)__r = res64;
    }
}

uint64_t GetRegister64(enum __REGS__ __reg) {
    uint64_t res;
	switch (__reg) {
        case __REG__RAX:  { GlobalRenderer->Print("RAX = "); asm("movq (%%rax), %0" : "=a"(res)); break; }
        case __REG__RBX:  { GlobalRenderer->Print("RBX = "); asm("movq (%%rbx), %0" : "=a"(res)); break; }
        case __REG__RCX:  { GlobalRenderer->Print("RCX = "); asm("movq (%%rcx), %0" : "=a"(res)); break; }
        case __REG__RDX:  { GlobalRenderer->Print("RDX = "); asm("movq (%%rdx), %0" : "=a"(res)); break; }
        case __REG__RSP:  { GlobalRenderer->Print("RSP = "); asm("movq (%%rsp), %0" : "=a"(res)); break; }
        case __REG__RBP:  { GlobalRenderer->Print("RBP = "); asm("movq (%%rbp), %0" : "=a"(res)); break; }
        case __REG__RIP:  { GlobalRenderer->Print("RIP = "); asm("lea (%%rip), %0"  : "=a"(res)); break; }
    }
	return res;
}

uint32_t GetRegister32(enum __REGS__ __reg) {
    uint32_t res;
	switch (__reg) {
        case __REG__EAX:  { GlobalRenderer->Print("EAX = "); asm("movl (%%eax), %0" : "=a"(res)); break; }
        case __REG__EBX:  { GlobalRenderer->Print("EBX = "); asm("movl (%%ebx), %0" : "=a"(res)); break; }
        case __REG__ECX:  { GlobalRenderer->Print("ECX = "); asm("movl (%%ecx), %0" : "=a"(res)); break; }
        case __REG__EDX:  { GlobalRenderer->Print("EDX = "); asm("movl (%%edx), %0" : "=a"(res)); break; }
        case __REG__ESP:  { GlobalRenderer->Print("ESP = "); asm("movl (%%esp), %0" : "=a"(res)); break; }
        case __REG__EBP:  { GlobalRenderer->Print("EBP = "); asm("movl (%%ebp), %0" : "=a"(res)); break; }
        case __REG__EIP:  { GlobalRenderer->Print("EIP = "); asm("movl (%%eip), %0"  : "=a"(res)); break; }
    }
	return res;
}