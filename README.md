### Welcome To PradoshOS Github!

![Untitled-1](https://user-images.githubusercontent.com/69463173/144822865-e740934e-7358-4b68-9e23-b0591941c65d.png)

![GitHub stats](https://github-readme-stats.vercel.app/api?username=pradosh-arduino&show_icons=true)

<a href="https://www.buymeacoffee.com/pradoshArduino"><img src="https://img.buymeacoffee.com/button-api/?text=Buy me a coffee&emoji=&slug=pradoshArduino&button_colour=FFDD00&font_colour=000000&font_family=Comic&outline_colour=000000&coffee_colour=ffffff"></a>
![Dev](https://img.shields.io/badge/Current%20Status-Halted-red)

# Index

+ [Main heading](https://github.com/pradosh-arduino/PradoshOS#welcome-to-pradoshos-github)
+ [Setup](https://github.com/pradosh-arduino/PradoshOS#setup)
+ [Compilation of Bootloader](https://github.com/pradosh-arduino/PradoshOS#compilation-of-bootloader)
+ [Compilation of Kernel](https://github.com/pradosh-arduino/PradoshOS#compilation-of-kernel)
+ [Setup of compile-all.sh](https://github.com/pradosh-arduino/PradoshOS#setup-of-compile-allsh)
+ [Setup of limine](https://github.com/pradosh-arduino/PradoshOS/blob/main/README.md#setup-of-limine)
+ [Steps](https://github.com/pradosh-arduino/PradoshOS#steps)
+ [Running the OS](https://github.com/pradosh-arduino/PradoshOS#running-the-os)
+ [Pictures](https://github.com/pradosh-arduino/PradoshOS#pictures)
+ [Font Package](https://github.com/pradosh-arduino/PradoshOS#font-package)
+ [Tables](https://github.com/pradosh-arduino/PradoshOS/blob/main/README.md#tables)
+ [Articles & Resources](https://github.com/pradosh-arduino/PradoshOS#articles--resources)
+ [Common Logs](https://github.com/pradosh-arduino/PradoshOS/blob/main/README.md#common-logs)
+ [Problems & Q and A](https://github.com/pradosh-arduino/PradoshOS/#problems--q-and-a)
+ [Credits](https://github.com/pradosh-arduino/PradoshOS#credits)
+ [Contact](https://github.com/pradosh-arduino/PradoshOS#contact)

# Setup

 if your building any OS for the first time, you have a lot to install.
 
 ## Step 1: Install WSL
 
         - WSL emulates Linux System in Windows without any virtual machine (skip the step if you're using Linux)
 
 ## Step 2: Update WSL/Linux Environment (Optional but recommended)
 
         - Run `sudo apt update` (in terminal) to Update your WSL/Linux

 ## Step 3: Get Some Build tools
 
         - Run the following commands:
         - `sudo apt-get install build-essential mtools`
         - `you need cross compiler too here is a tutorial to set it up`
         - `https://www.youtube.com/watch?v=-v6uRjpR_0M`

 ## Step 4: Get Qemu Emulator
 
         - If you're using linux type this in terminal `sudo apt install qemu`
         - If you're using WSL goto https://www.qemu.org/ and download from there
         
# Compilation of Bootloader

 ## Step 1: Change Directory
   Use `cd <OS_path>` to get into the OS Dir, then use `cd gnu-efi` to enter gnu-efi directory
 
 ## Step 2: Build The Bootloader
   Use `make bootloader` to build the bootloader
 
# Compilation of Kernel

 ## Step 1: Change Directory
   Use `cd <OS_path>` to get into the OS Dir, then use `cd kernel` to enter kernel directory
   
 ## Step 2: Build The Kernel
   Use `make setup` to make some folders for you, Then use `make all` to compile the code, link the code, build the .img
  
# Setup of compile-all.sh
 if you get the error `permission denied`, no problem just type `chmod -x compile-all.sh` now you can run it with `./compile-all.sh`
 
# Setup of Limine
 
 ## Step 1: get Limine
   Use `make limine-update` to get the latest version of limine
   
## Steps
 1. build the bootloader
 2. build the limine
 3. build the kernel
 4. build the bootable image (.img)
 
## Running the OS

 Now the OS CAN run in VirtualBox or VMware
 so here are the steps to run in qemu
 if your in Windows run `run.bat`
 
## Pictures
 Main Screen:
 ![Capture](https://user-images.githubusercontent.com/69463173/146766504-466c7ae6-7b19-4bf5-bce7-37c42ee2aad7.PNG)

 
 Error Screen:
 ![newError](https://user-images.githubusercontent.com/69463173/145708579-c82beeb0-b04c-48eb-8073-2fe08262b041.png)
  
## Font Package
 Right now there are some fonts (that I can find) which works with PradoshOS. to install a diffrent font follow the steps below
 
 # Step 1: Get a Font
 
   + if you can't find a PSF type font there is https://github.com/pradosh-arduino/Font-Package right now there is some font if we find more PSF fonts we will add it
         
 # Step 2: Changing the Font
 
  + This is a tricky part, first download PowerISO and open the OS image file with PowerISO
  + then it's much like a folder there you can see zap-light16.psf replace it with your font but if the font name is TestFontLmao.psf
  + rename the file to exact same name zap-light16.psf and save the file and run again with qemu, now you should see the new font.
         
# Tables
 
 ## File Structure
   | Directory | Description |
   |-----------|-------------|
   | /EFI | The main EFI Directory |
   | /EFI/BOOT | The boot folder where the UEFI Shell is located (bootx64.efi) |
   | /EFI/BOOT/bootx64.efi | The UEFI Shell used for Real Machines |
   | /EFI/pradx-boot | This is the place where PradX Bootloader is located |
   | /EFI/pradx-boot/main.efi | The main PradX Bootloader |
   | /PradoshOS | Here will be some files that are lower level of kernel |
   | /kernel.elf | The Core PradoshOS Kernel |
   | /zap-light16.psf | The Font for PradoshOS |
   | /bootmgr.efi | The limine boot manager (doesn't work yet) |
   
 ## Build Structure
   | Build Name | Is Major Version |
   |------------|------------------|
   | Dev Build | No |
   | vbox-bootable | No |
   | Alpha | Sort Of |
   | Beta | Sort OF |
   | Pre-release | Yes |
   | Release Candidate | Yes |
   | Release | Most Major version |
   
 ## Kernel
   | Kernel Info | Values |
   | ------------|--------|
   | Stack Size | 0x1000 |
   | Kernel File Type | Elf64 |
   | Kernel Arch | 64 bit |
   | Kernel Type | Monolithic, Modular |
   | Kernel Stability | 6/10 |
   | Kernel Performance | 8/10 |
   
## Articles & Resources
   https://wiki.osdev.org/UEFI
   
   https://wiki.osdev.org/Bare_Bones
   
   https://wiki.osdev.org/Introduction
   
   https://wiki.osdev.org/Interrupts
   
   https://wiki.osdev.org/APIC
   
   https://wiki.osdev.org/AHCI
   
   https://wiki.osdev.org/PCI
   
   https://www.encyclopedia.com/science/encyclopedias-almanacs-transcripts-and-maps/development-computer-operating-systems
   
   https://www.geeksforgeeks.org/5-operating-system-concepts-you-should-know-as-a-developer/
   
   https://www.pcilookup.com/
   
   http://pciengine.com/
   
   https://www.wfbsoftware.de/realtek-rtl8139-network-interface-card/
   
  https://en.wikipedia.org/wiki/Sound_Blaster
  
  https://en.wikipedia.org/wiki/Bus_mastering
  
  https://wiki.osdev.org/Sound_Blaster_16
     
## Common Logs
   + 12/12/21 = Fixed a Release Date
      
## Problems & Q and A
 *after changing the file structure there is high chance of bootlooping, if it started bootlooping email me I will try to help you ASAP*

 *General protection fault, Page fault, Double Fault will occur various reasons it's recommended to Contact me or create a issue in https://github.com/pradosh-arduino/PradoshOS/issues*
 
 **Q: Qemu stuck while booting (Tiano Core)**
 
 A: That means UEFI binaries had corrupted which is a normal thing, goto
    https://github.com/pradosh-arduino/UEFI-Firmware and download the files
    then paste it in OVMFbin
    
 **Q: Will there be support for any other CPU Architectures than x86_64(64 bit)?**
 
 A: No, only x86_64(64 bit) maybe I will make for 32 bit but 99% I'm not gonna do it
 
 **Q: When Will the PradoshOS will get released?**
 
 A: Ok I Set the Fixed Date I started my OS on March 31 2021 so release date is March 31 2022
    
 
## Credits
 There were some awesome people who helped me in my OS Dev journey they are
 
 GAMINGNOOB#3589ㅤ![dc](https://img.shields.io/static/v1?label=&message=Discord&color=white&logo=Discord)
 
 🎅Konect#0496ㅤㅤㅤ![dc](https://img.shields.io/static/v1?label=&message=Discord&color=white&logo=Discord)
 
 PedroElFrijol#8628ㅤㅤ![dc](https://img.shields.io/static/v1?label=&message=Discord&color=white&logo=Discord)
 
 `__joel__#2911`ㅤㅤㅤ![dc](https://img.shields.io/static/v1?label=&message=Discord&color=white&logo=Discord)
 
# Contact
 E-Mail: pradoshnathan@gmail.com or pradoshgame@gmail.com
 
 Discord: **helloImPR#6776**
 
 Discord Server: https://discord.gg/ChP4RMgcKG
