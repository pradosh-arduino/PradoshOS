#ifndef __REGS_H_
#define __REGS_H_ 1

#include <stdint.h>

enum __REGS__{
    __REG_UNUSED,

    __REG__RAX,
    __REG__RBX,
    __REG__RCX,
    __REG__RDX,
    __REG__RSP,
    __REG__RBP,
    __REG__RIP,

    __REG__EAX,
    __REG__EBX,
    __REG__ECX,
    __REG__EDX,
    __REG__ESP,
    __REG__EBP,
    __REG__EIP,

    __REG__AX,
    __REG__BX,
    __REG__CX,
    __REG__DX,
    __REG__SP,
    __REG__BP,


    __REG_FIRST = __REG__RAX,
    __REG_LAST = __REG__DX,
    
    __REG_FIRST64 = __REG__RAX,
    __REG_LAST64 = __REG__RIP+1,
    
    __REG_FIRST32 = __REG__EAX,
    __REG_LAST32 = __REG__EIP+1,
    
    __REG_FIRST16 = __REG__AX,
    __REG_LAST16 = __REG__BP+1,
};
extern __REGS__ register64;

void _getReg(void* __r, enum __REGS__ __reg);
uint64_t GetRegister64(enum __REGS__ __reg);
uint32_t GetRegister32(enum __REGS__ __reg);
void PrintReg64();

#endif