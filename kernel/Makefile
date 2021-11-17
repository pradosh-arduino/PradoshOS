
OSNAME = CustomOS

GNUEFI = ../gnu-efi
OVMFDIR = ../OVMFbin
LDS = kernel.ld
CC = gcc
ASMC = nasm
LD = ld

CFLAGS = -ffreestanding -fshort-wchar -mno-red-zone -fno-exceptions
ASMFLAGS =
LDFLAGS = -T $(LDS) -static -Bsymbolic -nostdlib

SRCDIR := src
OBJDIR := lib
BUILDDIR = bin
BOOTEFI := $(GNUEFI)/x86_64/bootloader/main.efi
BOOTX64 := $(GNUEFI)/x86_64/bootloader/bootx64.efi
BOOTIA32 := $(BUILDDIR)/bootia32.efi
EXTBIN := .bin
GRUBDIR := grub
rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

SRC = $(call rwildcard,$(SRCDIR),*.cpp)
ASMSRC = $(call rwildcard,$(SRCDIR),*.asm)
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRC))
OBJS += $(patsubst $(SRCDIR)/%.asm, $(OBJDIR)/%_asm.o, $(ASMSRC))
DIRS = $(wildcard $(SRCDIR)/*)

kernel: $(OBJS) link


$(OBJDIR)/interrupts/interrupts.o: $(SRCDIR)/interrupts/interrupts.cpp
	@ echo COMPILING $^
	@ mkdir -p $(@D)
	$(CC) -mno-red-zone -mgeneral-regs-only -ffreestanding -c $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@ echo COMPILING $^
	@ mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@ echo COMPILING $^
	@ mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $^ -o $@

$(OBJDIR)/%_asm.o: $(SRCDIR)/%.asm
	@ echo COMPILING $^
	@ mkdir -p $(@D)
	$(ASMC) $(ASMFLAGS) $^ -f elf64 -o $@

cmplMulitask:
	@ echo COMPILING multitask...
	nasm -f elf32 $(SRCDIR)/mtask.asm -o $(OBJDIR)/mtask_asm.o

link:
	@ echo LINKING
	$(LD) $(LDFLAGS) -o $(BUILDDIR)/kernel.elf $(OBJS)
	readelf -a bin/kernel.elf > ReadELF.txt

setup:
	@mkdir $(BUILDDIR)
	@mkdir $(SRCDIR)
	@mkdir $(OBJDIR)

clean:
	- rm -r lib/*

all: clean kernel buildimg print

verifyAll: verifyKernelFormat verifyMultiBoot

print:
	@ echo
	@ echo [DONE] PradoshOS compiled and builded Successfully!

verifyMultiBoot:
	@ echo
	@ echo Verifying multiboot...
	sh MultiBoot.sh

verifyKernelFormat:
	@ echo
	@ echo Verifying kernel format...
	sh KernelFormat.sh

buildimg:
	dd if=/dev/zero of=$(BUILDDIR)/$(OSNAME).img bs=512 count=93750
	truncate -s 100M $(BUILDDIR)/$(OSNAME).img
	mformat -v PradoshOS -F -c 1 -i $(BUILDDIR)/$(OSNAME).img ::
	mmd -i $(BUILDDIR)/$(OSNAME).img ::/EFI
	mmd -i $(BUILDDIR)/$(OSNAME).img ::/EFI/BOOT
	mcopy -i $(BUILDDIR)/$(OSNAME).img $(BOOTEFI) ::/EFI/BOOT
	mcopy -i $(BUILDDIR)/$(OSNAME).img $(BOOTX64) ::/EFI/BOOT
	mcopy -i $(BUILDDIR)/$(OSNAME).img startup.nsh ::
	mcopy -i $(BUILDDIR)/$(OSNAME).img $(BUILDDIR)/kernel.elf ::
	mcopy -i $(BUILDDIR)/$(OSNAME).img $(BUILDDIR)/zap-light16.psf ::
