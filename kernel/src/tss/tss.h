//#pragma once
//#include <stdint.h>
//#include <stddef.h>
//#include <unistd.h> 
//#include <stdlib.h>
//#include <string.h>
//#include "../gdt/gdt.h"
//
//#define IST_POINTER         0x700000
//#define IST_SIZE            0x100000
//
//
//struct TSS{
//    uint32_t Reserved0;
//
//    //RSP
//    uint64_t RSP[3];
//
//    uint64_t Reserved1;
//
//    //IST
//    uint64_t IST[7];
//
//    uint64_t Reserved2;
//    uint16_t Reserved3;
//
//    uint16_t IOPBOffset;
//}__attribute__((packed));
//
//void TSSInit();
//uint16_t TSSInstall(int numCPU);
//void TSSSetStack(uint64_t numCPU, void* stack);
//void* _memset (void *dest, int val, size_t len);