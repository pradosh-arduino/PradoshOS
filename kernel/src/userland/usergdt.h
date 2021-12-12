#ifndef __USERGDT_H_
#define __USERGDT_H_ 1

#include <stdint.h>

struct GDT_UserDescriptor{
    uint16_t __size;
    uint64_t __addr;
} __attribute__((packed)) ;

struct GDT_UserEntry{
    uint16_t __limit0;
    uint16_t __base0;
    uint8_t __base1;
    uint8_t __access;
    uint8_t __limit1_flags;
    uint8_t __base2;
} __attribute__((packed)) ;

struct GDT_UserSpace {
    struct GDT_UserEntry __kNull;
    struct GDT_UserEntry __kCode;
    struct GDT_UserEntry __kData;
    struct GDT_UserEntry __uNull;
    struct GDT_UserEntry __uCode;
    struct GDT_UserEntry __uData;
    struct GDT_UserEntry __uTSS_low;
    struct GDT_UserEntry __uTSS_high;
} __attribute__((packed)) __attribute__((aligned(0x1000)));

extern struct GDT_UserSpace* __global_userspace_gdt;
void _createUserSpaceGdt(struct GDT_UserSpace* __r);
extern void __loadUserGdt(struct GDT_UserDescriptor* __s);

#endif