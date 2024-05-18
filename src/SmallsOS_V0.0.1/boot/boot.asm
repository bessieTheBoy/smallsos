MBALIGN  equ  0 ; Memory align (not needed)           
MEMINFO  equ  0 ; Meminfo (not needed)            
MBFLAGS  equ  MBALIGN | MEMINFO ; flags
MAGIC    equ  0x1BADB002        ; "magic" number
CHECKSUM equ -(MAGIC + MBFLAGS) ; checksum
section .multiboot
align 4
	dd MAGIC
	dd MBFLAGS
	dd CHECKSUM
section .bss
align 16
stack_bottom:
resb 16384 ; 16 KiB
stack_top:

section .text
global _start:function (_start.end - _start)
_start:
	mov esp, stack_top
	extern kernel_main
	call kernel_main
	cli
.hang:	hlt
	jmp .hang
.end: