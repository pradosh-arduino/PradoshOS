//applist
#include "userspace.h"
//#include <stdio.h>
#include <cstdio>
//#include <glibc.h>
//applist
#include "kernelUtil.h"
#include "paging/PageFrameAllocator.h"
#include "scheduling/pit/pit.h"
//error controller
#include "memPanic.h"
#include "filePanic.h"
#include "hpanic.h"
#include "userPanic.h"
//error contoller
//userinput
#include "userinput/mouse.h"
#include "userinput/keyboard.h"
//userinput
//interupts
#include "ahci/ahci.h"
//interupts
#include "Screen.h"
#include "bootscr.h"
#include "Sound.h"
//user
#include "GUI.h"
//efimemory
#include "efiMemory.h"
#include "Framebuffer.h"
#include "CPUID.h"
#include "pci/pci.h"
#include "LoadBMP.h"
//memory
#include "memory/heap.h"
//memory
#include "PradX.h"
#include "colours.h"
//limine
#include <stdint.h>
#include <stddef.h>
//#include <stivale.h>
//limine
//#include "memory/heap.h"
//
#include <stdio.h>
#include <stdlib.h>
//#include <iostream>
//#include <string>
#include "apps/testapp.h"
//file reading
#include <stdio.h>
#include <stdlib.h>
#include "COM.h"
//file reading
#include "Log/syscalls2.h"
#include "progLang/code.h"
#include "errorScreen/errScr.h"

#include "malloc.h"
#include "acpi.h"
#include "pci.h"
#include "rtc.h"
#include "mtask.h"
#include "shell.h"
#include "fs.h"
#include "fade.h"

using namespace blaster;
using namespace OSDatas;
using namespace AHCI;

extern "C" void _start(BootInfo* bootInfo){
    KernelInfo kernelInfo = InitializeKernel(bootInfo);
    PageTableManager* pageTableManager = kernelInfo.pageTableManager;
    cleanup_terminated_task(task2);
    //PIT::TimeSinceBoot = 1;
    PIT::SetDivisor(65535);
    int HardDriveAvaStorageMB = 276447231;
    int HardDriveAvaStorageKB = 276447231;
    int AppUsedStorageKB = 7;
    int AppUsedStorageMB = 7128;
    bool IsOSBooted = true;
    bool IsKernelLoaded = true;
    int FpsCalculator = 0;
    float Version = 0.1;
    bool stable = false;
    int yPos = 0;
    //
    bool verboseMode = false;
    //
    int RamCursorPos = 0;
    Syscalls* LogRenderer;

    //fade();

    //memset(bootInfo->framebuffer->BaseAddress, 0, bootInfo->framebuffer->BufferSize);
    BasicRenderer newRenderer = BasicRenderer(bootInfo->framebuffer, bootInfo->psf1_Font); 
    uint64_t kernelSize = (uint64_t)&_KernelEnd - (uint64_t)&_KernelStart;
    uint64_t kernelPages = (uint64_t)kernelSize / 4096 + 1;
    int tests;
    LogRenderer->Done("RAM:");
    
    uint64_t mMapEntries = bootInfo->mMapSize / bootInfo->mMapDescSize;

    PageFrameAllocator newAllocator;
    newAllocator.ReadEFIMemoryMap(bootInfo->mMap, bootInfo->mMapSize, bootInfo->mMapDescSize);

    newAllocator.LockPages(&_KernelStart, kernelPages); //lock
    uint64_t fbBase = (uint64_t)bootInfo->framebuffer->BaseAddress;
    uint64_t fbSize = (uint64_t)bootInfo->framebuffer->BufferSize + 0x1000;
    uint64_t ScreenWidth = (uint64_t)bootInfo->framebuffer->Width;
    uint64_t ScreenHeight = (uint64_t)bootInfo->framebuffer->Height;
    uint64_t ScreenPixelsPerScanLine = (uint64_t)bootInfo->framebuffer->PixelsPerScanLine;
    GlobalAllocator.LockPages((void*)fbBase, fbSize / 0x1000 + 1);
    for(uint64_t t = fbBase; t < fbBase + fbSize; t += 4096){
      pageTableManager->MapMemory((void*)t, (void*)t);
    }
    int memoryData = newAllocator.GetUsedRAM() / 1024 + newAllocator.GetFreeRAM() / 1024;
    GlobalRenderer->Print("Total RAM: ");
    GlobalRenderer->Colour = 0x0000ccff;
    GlobalRenderer->Print(" ");
    GlobalRenderer->Print(" ");
    GlobalRenderer->Print(" ");
    GlobalRenderer->Print(to_string(newAllocator.GetUsedRAM() / 1024 + newAllocator.GetFreeRAM() / 1024));
    GlobalRenderer->Print(" KB");
    GlobalRenderer->Print(" ");
    GlobalRenderer->Print(to_string(newAllocator.GetUsedRAM() / 1000000 + newAllocator.GetFreeRAM() / 1000000));
    GlobalRenderer->Print(" MB ");
    GlobalRenderer->Colour = 0xffffffff;
    GlobalRenderer->Next();
    GlobalRenderer->Print("Free RAM: ");
    GlobalRenderer->Colour = 0x0000ccff;
    GlobalRenderer->Print(" ");
    GlobalRenderer->Print(" ");
    GlobalRenderer->Print(" ");
    GlobalRenderer->Print(" ");
    GlobalRenderer->Print(to_string(newAllocator.GetFreeRAM() / 1024 - newAllocator.GetReservedRAM() / 1024));
    GlobalRenderer->Print(" KB");
    GlobalRenderer->Print(" ");
    GlobalRenderer->Print(to_string(newAllocator.GetFreeRAM() / 1000000 - newAllocator.GetReservedRAM() / 1000000));
    GlobalRenderer->Print(" MB ");
    GlobalRenderer->Colour = 0xffffffff;
    GlobalRenderer->Next();
    GlobalRenderer->Print("Used RAM: ");
    GlobalRenderer->Colour = 0x0000ccff;
    GlobalRenderer->Print(" ");
    GlobalRenderer->Print(" ");
    GlobalRenderer->Print(" ");
    GlobalRenderer->Print(" ");
    GlobalRenderer->Print(to_string((newAllocator.GetUsedRAM() / 1024)));
    GlobalRenderer->Print(" KB ");
    GlobalRenderer->Print(" ");
    GlobalRenderer->Print(" ");
    GlobalRenderer->Print(to_string((newAllocator.GetUsedRAM() / 1000000)));
    GlobalRenderer->Print(" MB ");
    GlobalRenderer->Colour = 0xffffffff;
    GlobalRenderer->Next();
    GlobalRenderer->Print("Reserved RAM: ");
    GlobalRenderer->Colour = 0x0000ccff;
    GlobalRenderer->Print(to_string(newAllocator.GetReservedRAM() / 1024));
    GlobalRenderer->Print(" KB ");
    GlobalRenderer->Print(" ");
    GlobalRenderer->Print(to_string(newAllocator.GetReservedRAM()/ 1000000));
    GlobalRenderer->Print(" MB ");
    GlobalRenderer->Colour = 0xffffffff;
    GlobalRenderer->Next();
    GlobalRenderer->Colour = 0xffffffff; //text colour
    GlobalRenderer->Print("[");
    GlobalRenderer->Colour = 0x0000ff00;
    GlobalRenderer->Print("***");
    GlobalRenderer->Colour = 0xffffffff;
    GlobalRenderer->Print("]");
    GlobalRenderer->Colour = 0xffffffff;
    GlobalRenderer->Print("CPU:");
    GlobalRenderer->Next();
    GlobalRenderer->Colour = 0x0000ccff;
    GlobalRenderer->Print("CPU type:");
    GlobalRenderer->Print(getName());
    GlobalRenderer->Next();
    GlobalRenderer->Print("CPU Vendor ID:");
    GlobalRenderer->Print(cpu_string());
    GlobalRenderer->Colour = 0x0000ccff;
    GlobalRenderer->Next();
    GlobalRenderer->Print("CPU Architecture:");
    GlobalRenderer->Print("x86_64");
    GlobalRenderer->Next();
    /*
        EFI_MEMORY_DESCRIPTOR* desc = (EFI_MEMORY_DESCRIPTOR*)((uint64_t)bootInfo->mMap + (i * bootInfo->mMapDescSize));
        //newRenderer.CursorPosition = {1650, yPos};
        GlobalRenderer->Colour = 0x0000ccff;
        GlobalRenderer->Print(EFI_MEMORY_TYPE_STRINGS[desc->type]);
        GlobalRenderer->Colour = 0x0000ccff;
        GlobalRenderer->Print(" ");
        GlobalRenderer->Print(to_string(desc->numPages * 4096 / 1024));
        GlobalRenderer->Print(" KB");
        GlobalRenderer->Next();
        //GlobalRenderer->Next();*/
    //GlobalRenderer->Next();
    GlobalRenderer->Colour = 0xffffffff; //text colour
    GlobalRenderer->Print("[");
    GlobalRenderer->Colour = 0x0000ff00;
    GlobalRenderer->Print("***");
    GlobalRenderer->Colour = 0xffffffff;
    GlobalRenderer->Print("]");
    GlobalRenderer->Colour = 0xffffffff;
    GlobalRenderer->Print("Display Settings:");
    GlobalRenderer->Next();
    GlobalRenderer->Colour = 0x0000ccff;
    GlobalRenderer->Print("BaseAddress:");
    GlobalRenderer->Print("0x");
    GlobalRenderer->Print(to_hstring(fbBase));
    GlobalRenderer->Next();
    GlobalRenderer->Print("Buffer Size:");
    GlobalRenderer->Print("0x");
    GlobalRenderer->Print(to_hstring(fbSize));
    GlobalRenderer->Next();
    GlobalRenderer->Print("Resolution:");
    GlobalRenderer->Print(to_string(ScreenWidth));
    GlobalRenderer->Print("x");
    GlobalRenderer->Print(to_string(ScreenHeight));
    GlobalRenderer->Next();
    GlobalRenderer->Print("Pixels Per Scale line:");
    GlobalRenderer->Print(to_string(ScreenPixelsPerScanLine));
    GlobalRenderer->Next();
    GlobalRenderer->Print("[");
    GlobalRenderer->Colour = 0x0000ff00;
    GlobalRenderer->Print("***");
    GlobalRenderer->Colour = 0xffffffff;
    GlobalRenderer->Print("]");
    GlobalRenderer->Print("Serial COM:");
    GlobalRenderer->Next();
    //setRect(0, 1050, 30, 1920, 0x00ffffff, 5);
    if(GlobalSerial->serial_configure_baud_rate(PORT, 65535) == true){
      GlobalRenderer->Print("Found COM port:");
      GlobalRenderer->Print(to_hstring((uint16_t)PORT));
    }else{
      GlobalRenderer->Print("no serial found.");
    }
    GlobalRenderer->Next();
    int* foo;
    foo = (int*)_malloc(0xffffff);
    foo = (int*)_realloc(foo, 10 * sizeof(int));
    foo = (int*)_calloc(5, sizeof(int));
    if(foo == NULL){
      LogRenderer->Failed("Unable to allocate memory!");
    }else{
      LogRenderer->Done("Done allocating!");
      LogRenderer->Done(to_hstring((uint64_t)foo));
      //delete foo;
      LogRenderer->Done(to_string((uint64_t)foo));
    }    
    GlobalRenderer->Colour = 0xffffffff;
    float v2 = (float)PIT::TimeSinceBoot / 10;
    GlobalRenderer->Print("Time Since boot:");
    GlobalRenderer->Print(to_string(v2));
    GlobalRenderer->Print(" sec ");
    GlobalRenderer->Next();
    printFill("i can print filed text hahaha");
    GlobalRenderer->Next();
    GlobalRenderer->Print("TIME: ");
    GlobalRenderer->Print(to_string((float)getHours()));
    GlobalRenderer->ClearChar();
    GlobalRenderer->ClearChar();
    GlobalRenderer->ClearChar();
    GlobalRenderer->PutChar('.');
    GlobalRenderer->Print(to_string((float)getMinutes()));
    GlobalRenderer->ClearChar();
    GlobalRenderer->ClearChar();
    GlobalRenderer->ClearChar();
    GlobalRenderer->PutChar('.');
    GlobalRenderer->Print(to_string((float)getSeconds()));
    GlobalRenderer->ClearChar();
    GlobalRenderer->ClearChar();
    GlobalRenderer->ClearChar();
    GlobalRenderer->Next();
    //GlobalShell->Init(); //SHELL MODE
    MousePosition.X = ScreenWidth / 2;
    MousePosition.Y = ScreenHeight / 2;
    GlobalRenderer->PutChar(*(uint8_t*)bootInfo->rsdp);
    GlobalRenderer->PutChar(*((uint8_t*)bootInfo->rsdp + 1));
    GlobalRenderer->PutChar(*((uint8_t*)bootInfo->rsdp + 2));
    GlobalRenderer->PutChar(*((uint8_t*)bootInfo->rsdp + 3));
    GlobalRenderer->PutChar(*((uint8_t*)bootInfo->rsdp + 4));
    GlobalRenderer->PutChar(*((uint8_t*)bootInfo->rsdp + 5));
    GlobalRenderer->PutChar(*((uint8_t*)bootInfo->rsdp + 6));
    GlobalRenderer->PutChar(*((uint8_t*)bootInfo->rsdp + 7));
    GlobalRenderer->Next();
    GlobalRenderer->Print(to_hstring((uint32_t)bootInfo->rsdp->RSDTAddress));
    ACPI::FACPHeader* fadt;
    outb(fadt->SMI_CMD, fadt->ACPI_ENABLE);
    while (inw(fadt->PM1a_CNT_BLK) & 1 == 0);
    GlobalRenderer->Print(to_hstring((uint32_t)fadt->PM1a_CNT_BLK));
    GlobalRenderer->Next();
    lock_scheduler();
    schedule();
    unlock_scheduler();
    terminate_task(5);
    cleanup_terminated_task(task2);

    GlobalRenderer->PutPix(0, tga_parse((unsigned char*)"img.tga", (int)50.823), NULL);

    for(;;){
      asm("hlt"); // imp cpu eff
      ProcessMousePacket();
    }
while(true);
}