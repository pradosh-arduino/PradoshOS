# PradoshOS
 This is a Minimum OS with a lot of codes that execute things like PCI, AHCI, RTC. PIT etc This is a UEFI-based OS
# Setup

 if your building any OS for first time, you have a lot to install
 
 Step 1: Install WSL
 
         - WSL emulates Linux System in windows without any virtual machine (skip the step if your using Linux)
 
 Step 2: Update WSL/Linux Enviroinment (Optional but recommended)
 
         - Run `sudo apt update` (in terminal) to Update your WSL/Linux

 Step 3: Get Some Build tools
 
         - Run the following commands:
         - `sudo apt-get install build-essential mtools`
         - (Optional)
         - `sudo apt install perl`

 Step 4: Get Qemu Emulator
 
         - If your in linux type this in terminal `sudo apt install qemu`
         - If your in WSL goto https://www.qemu.org/ and download from there
# Compilation of Bootloader

 now open WSL/Linux terminal and goto your directory by typing `cd <path/to/os/dir>`
 then type `cd gnu-efi` to get in to bootloader's directory
 then type `make bootloader`
 DONE You compiled the bootloader but that's not enough that leads to compilation of kernel
 
# Compilation of Kernel

 now type `cd ../kernel` to exit bootloader's Directory and enter Kernel Directory
 now type `make all`
 
 Done You compiled the Kernel and builded a bootable floppy disk file (.img)
# Running the OS

 Now the OS cannot run in VirtualBox or VMware, it only run on qemu and real hardware
 so here are the steps to run in qemu
 if your in linux you need to add some attributes to makefile to run (not inplemented by my self yet)
 if your in Windows run `run.bat`
 
# Pictures
 Main Screen:
 
 ![Capture](https://user-images.githubusercontent.com/69463173/142187242-f170b502-a119-4a2c-9b4f-b99a2650fe78.PNG)
 
 Error Screen:
 ![error_scr](https://user-images.githubusercontent.com/69463173/142187283-0f9dbdd4-7bd0-4471-880c-0242dca4db6c.PNG)

# Problems
 Q: Qemu stuck while booting (Tiano Core)
 A: That means UEFI binaries had corrupted which is a normal thing goto
    https://github.com/pradosh-arduino/UEFI-Firmware and download the files
    then paste it in OVMFbin
    
 Q: I'm Getting General Protection Fault!
 A: That's because you tried to change run.bat's qemu arguments if the arguments are bad that will cause a GPF

 Q: I'm Getting Page Fault!!!
 A: That's occured because if you run the OS in very little amount of resolution

 General protection fault and Page fault will occur various reasons the above is the errors that will occur most likely it's recommended to Contact me
 
# Contact
 E-Mail: pradoshnathan@gmail.com or pradoshgame@gmail.com
 Discord: helloImPR#6776
