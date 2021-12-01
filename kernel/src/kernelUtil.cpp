#include "kernelUtil.h"
#include "gdt/gdt.h"
#include "IO.h"
#include "rtc.h"
#include "interrupts/IDT.h"
#include "interrupts/interrupts.h"
#include "fade.h"
#include "acpiBoot.c"
#include "fat_fs/filesystems/fat.h"
#include "fat_fs/filesystems/fs.h"
#include "fs.h"

KernelInfo kernelInfo; 
PageTableManager pageTableManager = NULL;

using namespace AHCI;

void PrepareMemory(BootInfo* bootInfo){
    uint64_t mMapEntries = bootInfo->mMapSize / bootInfo->mMapDescSize;

    GlobalAllocator = PageFrameAllocator();
    GlobalAllocator.ReadEFIMemoryMap(bootInfo->mMap, bootInfo->mMapSize, bootInfo->mMapDescSize);

    uint64_t kernelSize = (uint64_t)&_KernelEnd - (uint64_t)&_KernelStart;
    uint64_t kernelPages = (uint64_t)kernelSize / 4096 + 1;

    GlobalAllocator.LockPages(&_KernelStart, kernelPages);

    PageTable* PML4 = (PageTable*)GlobalAllocator.RequestPage();
    memset(PML4, 0, 0x1000);

    g_PageTableManager = PageTableManager(PML4);

    for (uint64_t t = 0; t < GetMemorySize(bootInfo->mMap, mMapEntries, bootInfo->mMapDescSize); t+= 0x1000){
        g_PageTableManager.MapMemory((void*)t, (void*)t);
    }

    uint64_t fbBase = (uint64_t)bootInfo->framebuffer->BaseAddress;
    uint64_t fbSize = (uint64_t)bootInfo->framebuffer->BufferSize + 0x1000;
    GlobalAllocator.LockPages((void*)fbBase, fbSize/ 0x1000 + 1);
    for (uint64_t t = fbBase; t < fbBase + fbSize; t += 4096){
        g_PageTableManager.MapMemory((void*)t, (void*)t);
    }

    asm ("mov %0, %%cr3" : : "r" (PML4));
    kernelInfo.pageTableManager = &pageTableManager;
}

void PrepareACPI(BootInfo* bootInfo){
    ACPI::SDTHeader* xsdt = (ACPI::SDTHeader*)(bootInfo->rsdp->XSDTAddress);

    ACPI::MCFGHeader* mcfg = (ACPI::MCFGHeader*)ACPI::FindTable(xsdt, (char*)"MCFG");

    PCI::EnumeratePCI(mcfg);
}

BasicRenderer r = BasicRenderer(NULL, NULL);
KernelInfo InitializeKernel(BootInfo* bootInfo){
    r = BasicRenderer(bootInfo->framebuffer, bootInfo->psf1_Font);
    GlobalRenderer = &r;

    GDTDescriptor gdtDescriptor;
    gdtDescriptor.Size = sizeof(GDT) - 1;
    gdtDescriptor.Offset = (uint64_t)&DefaultGDT;
    LoadGDT(&gdtDescriptor);

    PrepareMemory(bootInfo);

    memset(bootInfo->framebuffer->BaseAddress, 0, bootInfo->framebuffer->BufferSize);

    PrepareInterrupts();

    //InitializeHeap((void*)0x0000100000000000, 0x10);
    PageFrameAllocator* rsvPg;
    rsvPg->ReservePages((void*)0x100000 , 256);

    InitPS2Mouse();

    AHCIDriver* add;
    AHCIDriver(add->PCIBaseAdderess);


    PrepareACPI(bootInfo);
    AcpiInit();

    Directory* ffs;
    File* files;
    FileSystem(NULL);
    init_fs();
    const char* content = "ggggrwegwwgewwgewggwe";
    create_file("log.txt", (char*)content);
    ls();

    outb(PIC1_DATA, 0b11111000);
    outb(PIC2_DATA, 0b11101111);

    asm ("sti");
    
    return kernelInfo;
}