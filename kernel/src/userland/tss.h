#ifndef __TSS_H_
#define __TSS_H_ 1

#include <stdint.h>

struct TSS_X86 {
    uint8_t LINK;
    uint8_t Reserved0;
    uint16_t ESP0;
    uint8_t SS0;
    uint8_t Reserved1;
    uint16_t ESP1;
    uint8_t SS1;
    uint8_t Reserved2;
    uint16_t ESP2;
    uint8_t SS2;
    uint8_t Reserved3;
    uint16_t CR3;
    uint16_t EIP;
    uint16_t EFLAGS;
    uint16_t EAX;
    uint16_t ECX;
    uint16_t EDX;
    uint16_t EBX;
    uint16_t ESP;
    uint16_t EBP;
    uint16_t ESI;
    uint16_t EDI;
    uint8_t ES;
    uint8_t Reserved4;
    uint8_t CS;
    uint8_t Reserved5;
    uint8_t SS;
    uint8_t Reserved6;
    uint8_t DS;
    uint8_t Reserved7;
    uint8_t FS;
    uint8_t Reserved8;
    uint8_t GS;
    uint8_t Reserved9;
    uint8_t LDTR;
    uint8_t Reserved10;
    uint8_t Reserved11;
    uint8_t IOPB_Offset;
};

struct TSS_X86_64 {
    uint32_t Reserved0;
    uint64_t RSP0;
    uint64_t RSP1;
    uint64_t RSP2;
    uint64_t Reserved1;
    uint64_t IST1;
    uint64_t IST2;
    uint64_t IST3;
    uint64_t IST4;
    uint64_t IST5;
    uint64_t IST6;
    uint64_t IST7;
    uint64_t Reserved2;
    uint16_t Reserved5;
    uint16_t IOPB_Offset;
};

extern struct TSS_X86_64 __user_tss;

void INIT_TSS_X86_64(struct TSS_X86_64* __tss);
void* __memset (void *dest, int val, size_t len);

#endif