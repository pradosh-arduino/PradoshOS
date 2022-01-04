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
#include "sound/sound-blaster16/sb16.h"

struct BootInfo {
	Framebuffer* framebuffer;
	PSF1_FONT* psf1_Font;
	EFI_MEMORY_DESCRIPTOR* mMap;
	void COLD_REBOOT();
	void SHUTDOWN();
	uint64_t mMapSize;
	uint64_t mMapDescSize;
	ACPI::RSDP2* rsdp;
	ACPI::RSDPDescriptor20* rsdp2;
} ;

extern uint64_t _KernelStart;
extern uint64_t _KernelEnd;

extern "C" uint64_t textS;
extern "C" uint64_t dataS;
extern "C" uint64_t rodataS;
extern "C" uint64_t bssS;

struct KernelInfo {
    PageTableManager* pageTableManager;
};

KernelInfo InitializeKernel(BootInfo* BootInfo);