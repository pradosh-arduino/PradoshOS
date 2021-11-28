@echo off
set BUILDDIR=%0/../bin
set OVMFDIR=%0/../../OVMFbin
set KERNELDIR=%0/../

set BUILDDIR=%BUILDDIR:"=%
set OVMFDIR=%OVMFDIR:"=%
set OSNAME=CustomOS
clear
type %KERNELDIR%/cpu-print.txt
set /p processor=Enter Processor to boot:
set /p mem=Enter memory:

cd C:\Program Files\
cd qemu
qemu-system-x86_64 -drive file=%BUILDDIR%/%OSNAME%.img -drive file=%BUILDDIR%/floppy.img -device nvme,serial=PradoshOS -m %mem% -cpu %processor% -drive if=pflash,format=raw,unit=0,file=%OVMFDIR%/OVMF_CODE-pure-efi.fd,readonly=on -drive if=pflash,format=raw,unit=1,file=%OVMFDIR%/OVMF_VARS-pure-efi.fd -net none
timeout 30