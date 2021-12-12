### Welcome To PradoshOS Github!

![Untitled-1](https://user-images.githubusercontent.com/69463173/144822865-e740934e-7358-4b68-9e23-b0591941c65d.png)

![Anurag's GitHub stats](https://github-readme-stats.vercel.app/api?username=pradosh-arduino&show_icons=true)

![Top Langs](https://github-readme-stats.vercel.app/api/top-langs/?username=pradosh-arduino&layout=compact&langs_count=10)

<a href="https://www.buymeacoffee.com/pradoshArduino"><img src="https://img.buymeacoffee.com/button-api/?text=Buy me a coffee&emoji=&slug=pradoshArduino&button_colour=FFDD00&font_colour=000000&font_family=Comic&outline_colour=000000&coffee_colour=ffffff"></a>

# Index

+ [Main heading](https://github.com/pradosh-arduino/PradoshOS#welcome-to-pradoshos-github)
+ [Setup](https://github.com/pradosh-arduino/PradoshOS#setup)
    + [Step 1](https://github.com/pradosh-arduino/PradoshOS#step-1-install-wsl)
    + [Step 2](https://github.com/pradosh-arduino/PradoshOS#step-2-update-wsllinux-environment-optional-but-recommended)
    + [Step 3](https://github.com/pradosh-arduino/PradoshOS#step-3-get-some-build-tools)
    + [Step 4](https://github.com/pradosh-arduino/PradoshOS#step-4-get-qemu-emulator)
+ [Compilation of Bootloader](https://github.com/pradosh-arduino/PradoshOS#compilation-of-bootloader)
+ [Compilation of Kernel](https://github.com/pradosh-arduino/PradoshOS#compilation-of-kernel)
+ [Compilation of Userland](https://github.com/pradosh-arduino/PradoshOS#compilation-of-userland)
+ [Setup of compile-all.sh](https://github.com/pradosh-arduino/PradoshOS#setup-of-compile-allsh)
+ [Steps](https://github.com/pradosh-arduino/PradoshOS#steps)
+ [Running the OS](https://github.com/pradosh-arduino/PradoshOS#running-the-os)
+ [Pictures](https://github.com/pradosh-arduino/PradoshOS#pictures)
+ [Font Package](https://github.com/pradosh-arduino/PradoshOS#font-package)
    + [Step 1](https://github.com/pradosh-arduino/PradoshOS#step-1-get-a-font)
    + [Step 2](https://github.com/pradosh-arduino/PradoshOS#step-2-changing-the-font)
+ [Articles & Resources](https://github.com/pradosh-arduino/PradoshOS#articles--resources)
+ [TODO](https://github.com/pradosh-arduino/PradoshOS#todo)
+ [Build Structure](https://github.com/pradosh-arduino/PradoshOS#build-structure)
+ [Problems](https://github.com/pradosh-arduino/PradoshOS#problems)
+ [Credits](https://github.com/pradosh-arduino/PradoshOS#credits)
+ [Contact](https://github.com/pradosh-arduino/PradoshOS#contact)

## Setup

 if your building any OS for first time, you have a lot to install
 
 # Step 1: Install WSL
 
         - WSL emulates Linux System in Windows without any virtual machine (skip the step if your using Linux)
 
 # Step 2: Update WSL/Linux Environment (Optional but recommended)
 
         - Run `sudo apt update` (in terminal) to Update your WSL/Linux

 # Step 3: Get Some Build tools
 
         - Run the following commands:
         - `sudo apt-get install build-essential mtools`
         - `you need cross compiler too here is a tutorial to set it up`
         - `https://www.youtube.com/watch?v=-v6uRjpR_0M`

 # Step 4: Get Qemu Emulator
 
         - If your in linux type this in terminal `sudo apt install qemu`
         - If your in WSL goto https://www.qemu.org/ and download from there
         
## Compilation of Bootloader

 now open WSL/Linux terminal and goto your directory by typing `cd <path/to/os/dir>`
 then type `cd gnu-efi` to get in to bootloader's directory
 then type `make bootloader`
 DONE You compiled the bootloader but that's not enough that leads to compilation of kernel
 
## Compilation of Kernel

 now type `cd ../kernel` to exit bootloader's Directory and enter Kernel Directory
 now type `make setup` it will give you 2 errors but that's not a problem the command
 `make setup` will create a new folder where compiled objects will get stored
 then type `make all` to compile the kernel in to object file then it will link the objects into a bootloader
 understandable kernel executable (.elf) and takes the startup.nsh (a small script that calls bootloader), zap-light16.psf (font file), kernel.elf (sys kernel), main.efi 
 (bootloader) and makes these files into a bootable Floppy Disk Image
 
## Compilation of Userland
 go into your kernel dir then type this command `cd userland` then type `make all`
 
## Setup of compile-all.sh
 if you get the error `permission denied` no problem just type `chmod -x compile-all.sh` now you can run it with `./compile-all.sh`
 
## Steps
 1. build the bootloader
 2. build the userland
 3. build the kernel
 4. build the bootable image (.img)
 
## Running the OS

 Now the OS cannot run in VirtualBox or VMware, it only run on qemu and real hardware
 so here are the steps to run in qemu
 if your in linux you need to run `make run` (implemented make run for linux users)
 if your in Windows run `run.bat`
 
## Pictures
 Main Screen:
 ![Capture](https://user-images.githubusercontent.com/69463173/145718242-a4c97c46-8d3e-4294-a8aa-c48de1bd57e4.PNG)
 
 Error Screen:
 ![newError](https://user-images.githubusercontent.com/69463173/145708579-c82beeb0-b04c-48eb-8073-2fe08262b041.png)
 
 Bootloader:
 
 ![bootld](https://user-images.githubusercontent.com/69463173/144696398-f3120243-5879-47fc-b79f-46b46bf5608c.png)
 
## Font Package
 Right now there are some fonts (that I can find) which works with PradoshOS. to install a diffrent font follow the steps below
 
 # Step 1: Get a Font
 
         - if you can't find a PSF type font there is https://github.com/pradosh-arduino/Font-Package right now there is some font if we find more PSF fonts we will add it
         
 # Step 2: Changing the Font
 
         - This is a tricky part, first download PowerISO and open the OS image file with PowerISO
         - then it's much like a folder there you can see zap-light16.psf replace it with your font but like if the font name is TestFontLmao.psf
         - rename the file to exact same name zap-light16.psf and save the file and run again with qemu now you should see the new font
         
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
   
   more at: https://wiki.osdev.org
   
## TODO
   + Implement TSAD in Ethernet
   + Complete types.h
   + Fill the structs in ACPI
   + Complete Folder in FS

## Build Structure
   + Dev Build
   + vbox-bootable
   + Alpha
   + Beta
   + Pre-release
   + Release Canditate
   + Main Release
      
## Problems
 **Q: Qemu stuck while booting (Tiano Core)**
 
 A: That means UEFI binaries had corrupted which is a normal thing, goto
    https://github.com/pradosh-arduino/UEFI-Firmware and download the files
    then paste it in OVMFbin
    
 *after changing the file structure there is high chance of bootlooping, if it started bootlooping email me I will try to help you ASAP*

 *General protection fault, Page fault, Double Fault will occur various reasons it's recommended to Contact me or create a issue in https://github.com/pradosh-arduino/PradoshOS/issues*
 
## Credits
 There were some awesome people who helped me in my OS Dev journey they are
 
 Peko#5633 ㅤㅤㅤㅤㅤ![dc](https://img.shields.io/static/v1?label=&message=Discord&color=white&logo=Discord)
 
 GAMINGNOOB#3589ㅤ![dc](https://img.shields.io/static/v1?label=&message=Discord&color=white&logo=Discord)
 
 🎅Konect#0496ㅤㅤㅤ![dc](https://img.shields.io/static/v1?label=&message=Discord&color=white&logo=Discord)
 
 PedroElFrijol#8628ㅤㅤ![dc](https://img.shields.io/static/v1?label=&message=Discord&color=white&logo=Discord)

# Contact
 E-Mail: pradoshnathan@gmail.com or pradoshgame@gmail.com
 
 Discord: **helloImPR#6776**
 
 Discord Server: https://discord.gg/ChP4RMgcKG
