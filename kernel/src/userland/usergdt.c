#include "usergdt.h"
#include "tss.h"
#include "tss.c"

__attribute__((aligned(0x1000))) struct GDT_UserSpace* __global_userspace_gdt;

void _createUserSpaceGdt(struct GDT_UserSpace* __r) {
    __r->__kNull = { 0, 0, 0, 0x00, 0x00, 0 };
    __r->__kCode = { 0, 0, 0, 0x9a, 0xa0, 0 };
    __r->__kData = { 0, 0, 0, 0x92, 0xa0, 0 };
    __r->__uNull = { 0, 0, 0, 0x00, 0x00, 0 };
    __r->__uCode = { 0, 0, 0, 0x9a, 0xa0, 0 };
    __r->__uData = { 0, 0, 0, 0x92, 0xa0, 0 };
    __r->__uTSS_low = { 0, 0, 0, 0x89, 0xa0, 0 };
    __r->__uTSS_high = { 0, 0, 0, 0x00, 0x00, 0 };

    INIT_TSS_X86_64(&__user_tss);
    uint64_t _tssAddr = ((uint64_t)&__user_tss);

    __r->__uTSS_low.__base0 = (_tssAddr & 0xffff);
    __r->__uTSS_low.__base1 = ( (_tssAddr >> 16) & 0xff );
    __r->__uTSS_low.__base2 = ( (_tssAddr >> 24) & 0xff );
    __r->__uTSS_low.__limit0 = sizeof(struct TSS_X86_64);
    __r->__uTSS_high.__limit0 = ( (_tssAddr >> 32) & 0xffff );
    __r->__uTSS_high.__base0 = ( (_tssAddr >> 48) & 0xffff );
}