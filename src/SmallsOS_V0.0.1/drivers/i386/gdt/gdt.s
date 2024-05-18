[bits 32]

gdtr:
    dw 0
    dd 0

global loadGDT
loadGDT:
    mov ax, [esp + 4]
    mov [gdtr], ax
    mov eax, [esp + 8]
    mov [gdtr + 2], eax
    lgdt [gdtr]
    ret

global reloadSegments
reloadSegments:
    jmp 0x08:.reload_cs
.reload_cs:
   mov   ax, 0x10
   mov   ds, ax
   mov   es, ax
   mov   fs, ax
   mov   gs, ax
   mov   ss, ax
   ret
