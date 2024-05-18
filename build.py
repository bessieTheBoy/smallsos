import os
import sys
import argparse

VERSION_DIR = "src/SmallsOS_V0.0.1"
BUILD_DIR = "build"
INCLUDE_DIR = f"{VERSION_DIR}/include"
C_FILES = [(f"{VERSION_DIR}/kernel/kernel.c", f"{BUILD_DIR}/kernel/kernel.o"), (f"{VERSION_DIR}/drivers/i386/hal/hal.c", f"{BUILD_DIR}/drivers/i386/hal/hal.o"), (f"{VERSION_DIR}/drivers/i386/gdt/gdt.c", f"{BUILD_DIR}/drivers/i386/gdt/gdtc.o")]
ASM_FILES = [(f"{VERSION_DIR}/boot/boot.asm", f"{BUILD_DIR}/boot/boot.o"), (f"{VERSION_DIR}/drivers/i386/gdt/gdt.s", f"{BUILD_DIR}/drivers/i386/gdt/gdtasm.o")]
O_FILES = f"{BUILD_DIR}/boot/boot.o {BUILD_DIR}/drivers/i386/gdt/gdtasm.o {BUILD_DIR}/drivers/i386/gdt/gdtc.o {BUILD_DIR}/kernel/kernel.o {BUILD_DIR}/drivers/i386/hal/hal.o"
for ASM_FILE in ASM_FILES:
    os.system(f"nasm -f elf32 {ASM_FILE[0]} -o {ASM_FILE[1]}")
for C_FILE in C_FILES:
    os.system(f"i686-elf-gcc -m32 -ffreestanding -I {VERSION_DIR}/include -c {C_FILE[0]} -o {C_FILE[1]}")
os.system(f"i686-elf-ld -m elf_i386 -T linker.ld -o smallsk.bin {O_FILES}")
os.system("dd if=smallsk.bin of=smalls_flp.img bs=1440k")
