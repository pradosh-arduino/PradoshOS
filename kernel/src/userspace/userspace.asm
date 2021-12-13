; note: this code is for 64-bit long mode only.
;       it is unknown if it works in protected mode.
;       using intel assembly style
global jump_usermode
extern test_user_function
jump_usermode:
;enable system call extensions that enables sysret and syscall
	mov rcx, 0xc0000082
	wrmsr
	mov rcx, 0xc0000080
	rdmsr
	or eax, 1
	wrmsr
	mov rcx, 0xc0000081
	rdmsr
	mov edx, 0x00180008
	wrmsr
 
	mov ecx, test_user_function ; to be loaded into RIP
	mov r11, 0x202 ; to be loaded into EFLAGS
	o64 sysret ;use "o64 sysret" if you assemble with NASM

test_user_function:

