#include "kernelUtil.h"
#include "gdt/gdt.h"
#include "IO.h"
#include "rtc.h"
#include "interrupts/IDT.h"
#include "interrupts/interrupts.h"
#include "fade.h"
#include "acpiBoot.c"
#include "fs.h"
#include "pic.h"
#include "ethernet/RTL8139.h"
#include "mtask.h"

KernelInfo kernelInfo; 
PageTableManager pageTableManager = NULL;

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

    kernelInfo.pageTableManager = &g_PageTableManager;
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

    GlobalRenderer->Colour = 0x0000ccff;
    GlobalRenderer->Print("PradoshOS by Pradosh.S");
    GlobalRenderer->Next();
    GlobalRenderer->Print("Source code: https://github.com/pradosh-arduino/PradoshOS");
    GlobalRenderer->Next();
    GlobalRenderer->Print("Font package: https://github.com/pradosh-arduino/Font-Package");
    GlobalRenderer->Colour = 0x00FFFFFF;
    GlobalRenderer->Next();
    GlobalRenderer->Next();
    GlobalRenderer->Seperator();
    GlobalRenderer->Next();

    //InitializeHeap((void*)0x0000100000000000, 0x10);
    PageFrameAllocator* rsvPg;
    rsvPg->ReservePages((void*)0x100000 , 256);

    InitPS2Mouse();

    PrepareACPI(bootInfo);
    AcpiInit();

    cleaner_task();

    //pic_init();

    //AHCIDriver* ahciM;
    //fs_init(ahciM);
    
    rtl8139->Init();

    pic_init();

    GlobalRenderer->Println("Directory of '/' :");
    File* mouse;
    GlobalRenderer->PutChar(' ');
    vFileSystem->NewFile("mouse", "pickle", "32e2qeqeqeqweq", mouse, "/");
    vFileSystem->list();
    File* keyboard;
    GlobalRenderer->PutChar(' ');
    vFileSystem->NewFile("keyboard", "pickle", "test3333", keyboard, "/");
    vFileSystem->list();
    GlobalRenderer->PutChar(' ');
    File* hardwareAL;
    vFileSystem->NewFile("hardwareAL", "out", "test1", hardwareAL, "/");
    vFileSystem->list();

    outb(PIC1_DATA, 0b11111000);
    outb(PIC2_DATA, 0b11101111);

    asm("sti");
    
    return kernelInfo;
}