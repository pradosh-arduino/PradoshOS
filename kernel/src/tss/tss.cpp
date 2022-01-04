//#include "tss.h"
//
//static TSS TSSdescriptors[10];
//
//void TSSInit(){
//    _memset(TSSdescriptors, 0, sizeof(TSS) * 10);
//}
//
//void TSSSetStack(uint64_t numCPU, void* stack){
//    TSSdescriptors[numCPU].RSP[0] = (uint64_t)stack;
//}
//
//uint16_t TSSInstall(int numCPU){
//    uint64_t tss_base = (uint64_t)&TSSdescriptors[numCPU];
//    _memset((void *)tss_base, 0, sizeof(TSS));
//
//    uint16_t location = gdtInstallTSS(tss_base, sizeof(TSS));
//    TSSdescriptors[numCPU].IOPBOffset = sizeof(TSS);
//    return location;
//}
//
//
//void* _memset (void *dest, int val, size_t len)
//{
//  unsigned char *ptr = (unsigned char*)dest;
//  while (len-- > 0)
//    *ptr++ = val;
//  return dest;
//}