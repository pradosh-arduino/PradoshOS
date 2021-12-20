@echo off
set BUILDDIR=%0/../bin
set OVMFDIR=%0/../../OVMFbin
set KERNELDIR=%0/../

set BUILDDIR=%BUILDDIR:"=%
set OVMFDIR=%OVMFDIR:"=%
set OSNAME=PradoshOS

qemu-system-x86_64 -m 256M -cpu qemu64 -drive file=%BUILDDIR%/%OSNAME%.img -drive file=%BUILDDIR%/floppy.img -rtc base=localtime,clock=host -device nvme,serial=PradoshOS -drive if=pflash,format=raw,unit=0,file=%OVMFDIR%/OVMF_CODE-pure-efi.fd,readonly=on -drive if=pflash,format=raw,unit=1,file=%OVMFDIR%/OVMF_VARS-pure-efi.fd -net none
pause