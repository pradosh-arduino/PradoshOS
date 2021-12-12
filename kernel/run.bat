@echo off
set BUILDDIR=%0/../bin
set OVMFDIR=%0/../../OVMFbin
set KERNELDIR=%0/../

set BUILDDIR=%BUILDDIR:"=%
set OVMFDIR=%OVMFDIR:"=%
set OSNAME=PradoshOS
copy \\wsl$\Ubuntu-20.04\home\pradosh\PradoshOS-0.1.0-indev-uint8_t-error\PradoshOS-0.1.0-indev-uint8_t-error\PureBin\ \\wsl$\Ubuntu-20.04\home\pradosh\PradoshOS-0.1.0-indev-uint8_t-error\PradoshOS-0.1.0-indev-uint8_t-error\OVMFbin\
cls

cd C:\Program Files\
cd qemu
qemu-system-x86_64 -drive file=%BUILDDIR%/%OSNAME%.img -drive file=%BUILDDIR%/floppy.img -rtc base=localtime,clock=host -device nvme,serial=PradoshOS -m 256M -cpu qemu64 -drive if=pflash,format=raw,unit=0,file=%OVMFDIR%/OVMF_CODE-pure-efi.fd,readonly=on -drive if=pflash,format=raw,unit=1,file=%OVMFDIR%/OVMF_VARS-pure-efi.fd -net none
timeout 30