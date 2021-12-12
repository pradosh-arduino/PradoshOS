#include "tss.h"

struct TSS_X86_64 __user_tss;

void INIT_TSS_X86_64(struct TSS_X86_64* __tss) {
    __memset(__tss, 0, sizeof(struct TSS_X86_64));
}

void* __memset (void *dest, int val, size_t len)
{
  unsigned char *ptr = (unsigned char*)dest;
  while (len-- > 0)
    *ptr++ = val;
  return dest;
}