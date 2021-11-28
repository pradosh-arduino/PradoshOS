
OSNAME = CustomOS

GNUEFI = ../gnu-efi
OVMFDIR = ../OVMFbin
LDS = kernel.ld
CC = gcc
ASMC = nasm
LD = ld

CFLAGS = -ffreestanding -fshort-wchar -mno-red-zone -fno-exceptions  --verbose
ASMFLAGS =
LDFLAGS = -T $(LDS) -static -Bsymbolic -nostdlib  --verbose

SRCDIR := src
OBJDIR := lib
BUILDDIR = bin
USRDIR := userland
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
	@ echo "\e[1;34mCOMPILING $^\e[0m"
	@ mkdir -p $(@D)
	$(CC) -mno-red-zone -mgeneral-regs-only -ffreestanding -c $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@ echo "\e[1;34mCOMPILING $^\e[0m"
	@ mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@ echo "\e[1;34mCOMPILING $^\e[0m"
	@ mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $^ -o $@

$(OBJDIR)/%_asm.o: $(SRCDIR)/%.asm
	@ echo "\e[1;34mCOMPILING $^\e[0m"
	@ mkdir -p $(@D)
	$(ASMC) $(ASMFLAGS) $^ -f elf64 -o $@

cmplMulitask:
	@ echo COMPILING multitask...
	nasm -f elf32 $(SRCDIR)/mtask.asm -o $(OBJDIR)/mtask_asm.o

link:
	@ echo "\e[1;34mLINKING $^\e[0m"
	$(LD) $(LDFLAGS) -o $(BUILDDIR)/kernel.elf $(OBJS)
	readelf -a bin/kernel.elf > ReadELF.txt

setup:
	@mkdir $(BUILDDIR)
	@mkdir $(SRCDIR)
	@mkdir $(OBJDIR)

clean:
	- rm -r lib/*

all: clean kernel buildimg read print

userland:
	copy $(USRDIR)/userentry.o $(OBJDIR)/

print:
	@ echo
	@ echo "\e[1;32m [DONE] PradoshOS compiled and builded Successfully! \e[0m"

read:
	hexdump -C bin/kernel.elf
	readelf -a bin/kernel.elf

version:
	objcopy res/version.txt -O version.o
	copy res/version.o lib/

buildimg:
	dd if=/dev/zero of=$(BUILDDIR)/$(OSNAME).img bs=512 count=93750
	mformat -v PradoshOS -i $(BUILDDIR)/$(OSNAME).img -f 1440 ::
	mmd -i $(BUILDDIR)/$(OSNAME).img ::/EFI
	mmd -i $(BUILDDIR)/$(OSNAME).img ::/EFI/BOOT
	mmd -i $(BUILDDIR)/$(OSNAME).img ::/StartupApps
	mmd -i $(BUILDDIR)/$(OSNAME).img ::/StartupApps/b64
	mcopy -i $(BUILDDIR)/$(OSNAME).img $(BOOTEFI) ::/EFI/BOOT
	mcopy -i $(BUILDDIR)/$(OSNAME).img startup.nsh ::
	mcopy -i $(BUILDDIR)/$(OSNAME).img $(BUILDDIR)/kernel.elf ::
	mcopy -i $(BUILDDIR)/$(OSNAME).img $(USRDIR)/userland.elf ::
	mcopy -i $(BUILDDIR)/$(OSNAME).img $(BUILDDIR)/zap-light16.psf ::
	mcopy -i $(BUILDDIR)/$(OSNAME).img img.tga ::
