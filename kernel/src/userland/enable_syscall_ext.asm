[bits 64]

_enable_system_call_extensions:
    mov		rax, syscall_entry
	mov		rdx, rax
	shr		rdx, 0x20
	mov		rcx, 0xc0000082
	wrmsr
	mov		rcx, 0xc0000080
	rdmsr
	or		eax, 1
	wrmsr
	mov		rcx, 0xc0000081
	rdmsr
	mov		edx, 0x00180008
	wrmsr
	ret      

syscall_entry:
    cli
    push r11
    push rcx
    pop rcx
    pop r11
    o64 sysret

GLOBAL _enable_system_call_extensions