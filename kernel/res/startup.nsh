@echo -off
mode 240 56

set path %CWD%\efi\tools\;%CWD%\efi\boot\;%CWD%\efi\pradx-boot\;%CWD%\;
set PradX_Bootloader_Version v1.0
set PradoshOS_Kernel_Version under-construction

cls

if exist .\efi\pradx-boot\main.efi then
 .\efi\pradx-boot\main.efi
 goto END
endif

if exist fs0:\efi\pradx-boot\main.efi then
 fs0:
 efi\pradx-boot\main.efi
 goto END
endif

if exist fs1:\efi\pradx-boot\main.efi then
 fs1:
 efi\pradx-boot\main.efi
 goto END
endif

if exist fs2:\efi\pradx-boot\main.efi then
 fs2:
 efi\pradx-boot\main.efi
 goto END
endif

if exist fs3:\efi\pradx-boot\main.efi then
 fs3:
 efi\pradx-boot\main.efi
 goto END
endif

if exist fs4:\efi\pradx-boot\main.efi then
 fs4:
 efi\pradx-boot\main.efi
 goto END
endif

if exist fs5:\efi\pradx-boot\main.efi then
 fs5:
 efi\pradx-boot\main.efi
 goto END
endif

if exist fs6:\efi\pradx-boot\main.efi then
 fs6:
 efi\pradx-boot\main.efi
 goto END
endif

if exist fs7:\efi\pradx-boot\main.efi then
 fs7:
 efi\pradx-boot\main.efi
 goto END
endif

 echo "Unable to find Shell".
 
:END
