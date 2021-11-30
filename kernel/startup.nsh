@echo -off
mode 240 56

cls
if exist .\efi\boot\main.efi then
 .\efi\boot\main.efi
 goto END
endif

if exist fs0:\efi\boot\main.efi then
 fs0:
 efi\boot\main.efi
 goto END
endif

if exist fs1:\efi\boot\main.efi then
 fs1:
 efi\boot\main.efi
 goto END
endif

if exist fs2:\efi\boot\main.efi then
 fs2:
 efi\boot\main.efi
 goto END
endif

if exist fs3:\efi\boot\main.efi then
 fs3:
 efi\boot\main.efi
 goto END
endif

if exist fs4:\efi\boot\main.efi then
 fs4:
 efi\boot\main.efi
 goto END
endif

if exist fs5:\efi\boot\main.efi then
 fs5:
 efi\boot\main.efi
 goto END
endif

if exist fs6:\efi\boot\main.efi then
 fs6:
 efi\boot\main.efi
 goto END
endif

if exist fs7:\efi\boot\main.efi then
 fs7:
 efi\boot\main.efi
 goto END
endif

 echo "Unable to find bootloader".
 
:END
