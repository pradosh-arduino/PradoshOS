#pragma once

#include <stdint.h>
#include "BasicRenderer.h"
#include "cstr.h"
#include "efiMemory.h"
#include "memory.h"
#include "Bitmap.h"
#include "paging/PageFrameAllocator.h"
#include "paging/PageMapIndexer.h"
#include "paging/paging.h"
#include "paging/PageTableManager.h"
#include "userinput/mouse.h"
#include "acpi.h"
#include "pci.h"
#include "interrupts/IDT.h"
#include "interrupts/interrupts.h"

struct BootInfo {
	Framebuffer* framebuffer;
	PSF1_FONT* psf1_Font;
	EFI_MEMORY_DESCRIPTOR* mMap;
	void COLD_REBOOT();
	void SHUTDOWN();
	uint64_t mMapSize;
	uint64_t mMapDescSize;
	ACPI::RSDP2* rsdp;
} ;

extern uint64_t _KernelStart;
extern uint64_t _KernelEnd;

extern "C" void flush_tss(void);
extern "C" void jump_usermode();

struct KernelInfo {
    PageTableManager* pageTableManager;
};

KernelInfo InitializeKernel(BootInfo* BootInfo);