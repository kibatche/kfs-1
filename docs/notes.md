# Notes

This document is a notepad.

## Table Of Content

- [Context](#context)
- [VM Creation](#vm-creation)
- [GCC Cross-Compiler](#gcc-cross-compiler)
- [Bootstraping the kernel](#bootstraping-the-kernel)
    1. [Prodiving multiboot information for the boot loader](#1-prodiving-multiboot-information-for-the-boot-loader)
    2. [Create the stack](#2-create-the-stack)
    3. [Declare the entry point](#3-declare-the-entry-point)
    4. [For the moment](#4-for-the-moment)
- [Implementing the kernel](#implementing-the-kernel)
- [Linking the Kernel](#linking-the-kernel)
- [Booting the Kernel](#booting-the-kernel)
- [Resources](#resources)

## Context

These tutorials are good starting points:

- [Bare Bones Tutorial](https://wiki.osdev.org/Bare_Bones)
- [Meaty Skeleton](https://wiki.osdev.org/Meaty_Skeleton)

## VM Creation (VirtualBox)

The chosen image is Ubuntu 24.04 "Noble Numbat".

1. [Download the 64-bit PC (AMD64) desktop image](https://releases.ubuntu.com/noble/) and create the VM in VirtualBox.
2. Install the VirtualBox guest additions:
    - ```
      # apt-get install virtualbox-guest-additions-iso
      ```
    - Mount the device located at `/usr/share/virtualbox/VBoxGuestAdditions.iso`.
    - Open the directory and look for the `VBoxLinuxAdditions.run` file. Run it:
      ```
      # sh VBoxLinuxAdditions.run
      ```
    - Reboot the system.
3. Install required tools for the projects: Vim, Git, VSCodium, NASM, and so forth.
4. Do some setup: configure the web browser and VSCodium, the dotfiles, generate a SSH key pair.

## GCC Cross-Compiler

The assignment requires the following options:

- `-fno-builtin`: Disables built-ins. Don’t recognize built-in functions that do not begin with `__builtin_` as prefix
- `-fno-exceptions`: Disables exception handling ([reading for later](https://mmomtchev.medium.com/the-true-cost-of-c-exceptions-7be7614b5d84)).
- `-fno-stack-protector`: Disables the [Stack Smashing Protector](https://wiki.osdev.org/Stack_Smashing_Protector).
- `-nostdlib`: Do not use the standard system startup files or libraries when linking.
- `-nodefaultlibs`: Do not use the standard system libraries when linking.

C++ options:

- `-fno-rtti`: Disables [RTTI (RunTime Type Identification)](https://pvs-studio.com/en/blog/posts/cpp/0998/), a mechanism that allows to determine the data type of a variable at runtime (used with the identification features `dynamic_cast` and `typeid`).

Resources:

- [Why do I need a Cross Compiler?](https://wiki.osdev.org/Why_do_I_need_a_Cross_Compiler%3F)
- [GCC Cross-Compiler Tutorial](https://wiki.osdev.org/GCC_Cross-Compiler)

## Bootstraping the kernel

We chose [NASM](https://wiki.osdev.org/NASM) as assembler.

Resources:

- [NASM Manual - posix.nl](http://www.posix.nl/linuxassembly/nasmdochtml/nasmdoca.html)
- [x86 Architecture](https://learn.microsoft.com/en-us/windows-hardware/drivers/debugger/x86-architecture)

### 1. Prodiving multiboot information for the boot loader

The `boot.asm` file starts as follows:

```asm
MBALIGN  equ  1 << 0
MEMINFO  equ  1 << 1
FLAGS    equ  MBALIGN | MEMINFO
MAGIC    equ  0x1BADB002
CHECKSUM equ -(MAGIC + FLAGS)

section .multiboot
align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM
```

The instructions at the beginning use the `equ` operand to assign values to symbols, which can be seen as constants. Before assembly, these symbols are **replaced in the code by their values or by addresses** by the assembler. Thus, they take no place in memory.

These assignments are placed before the section to separate the computation of the value from its allocation in memory and improve clarity.

Right after, a section `.multiboot` is declared. It contains the **[header](https://www.gnu.org/software/grub/manual/multiboot/multiboot.html#Header-layout) defined by the [Multiboot specification](https://en.wikipedia.org/wiki/Multiboot_specification)**. This open standard enables boot loaders to load any kernel without having to know about their inner mechanisms. GRUB implements it and was one of the first boot loaders to do so.

The instruction `align 4` is necessary since the standard [specifies that the data must be **longword-aligned**](https://www.gnu.org/software/grub/manual/multiboot/multiboot.html#OS-image-format) (32 bits, or 4 bytes). It was defined at a time 32-bit architectures were the norm. Even if it could be aligned on 64 bits nowadays, the requirements must be met, header included.

The Multiboot header section name is **conventional** otherwise the section could be called anything. What matter is the magic number, the flags and the checksum are present and ordered as expected:

- **Magic number**: must be `0x1BADB002` ('1 BAD BOOT' in l33t) for Multiboot or `0xE85250D6` for Multiboot2.
- **Flags**: to specify multibooting features.
- **Checksum**: a 32-bit unsigned value which should equal to zero when added to other fields (like the magic number and the flags, but they can be more) to confirm this is a multiboot header. Why not rely only on the magic number? It should be enough, right? It's because this value has a chance to appear in programs randomly so the checksum makes sure this data is indeed a multiboot specification header.

The header flags from [GNU documentation](https://www.gnu.org/software/grub/manual/multiboot/multiboot.html#multiboot_002eh):

```c
/* Flags set in the ’flags’ member of the multiboot header. */

/* Align all boot modules on i386 page (4KB) boundaries. */
#define MULTIBOOT_PAGE_ALIGN                    0x00000001

/* Must pass memory information to OS. */
#define MULTIBOOT_MEMORY_INFO                   0x00000002

/* Must pass video information to OS. */
#define MULTIBOOT_VIDEO_MODE                    0x00000004

/* This flag indicates the use of the address fields in the header. */
#define MULTIBOOT_AOUT_KLUDGE                   0x00010000
```

The `a.out` kludge flag is a [relic from the times of `a.out` kernels](https://f.osdev.org/viewtopic.php?t=9772). Linux used this format until kernel 1.2 (Mar. 1995), before transitioning to ELF.

### 2. Create the stack

The C language needs a stack to function. The stack pointer points to the top of the stack and is commonly stored in `ESP` (32-bit) or `RSP` (64-bit). Since the Multiboot specification doesn't handle the stack pointer, the kernel has to do create the stack and assign the stack pointer. Because the stack is empty at first, it is common to initialize it in the BSS section that allows to reserve uninitialized data and fill it with zeroes.

```asm
section .bss
align 16
stack_bottom:
resb 16384 ; 16 KiB is reserved for stack
stack_top:
```

The [System V](https://en.wikipedia.org/wiki/UNIX_System_V) [ABI (Application Binary Interface)](https://wiki.osdev.org/System_V_ABI#i386) standard establishes conventions for object file formats, executable file formats, function calls, stack alignment and so forth. On newer systems, the stack should be **16-byte aligned**, instead of 4-byte aligned, and grow downwards.

### 3. Declare the entry point

What comes next is executable code, thus lies in the `.text` section.

```asm
section .text
```

By default, the linker looks for a [`start` symbol as entry point](https://ftp.gnu.org/old-gnu/Manuals/ld-2.9.1/html_node/ld_24.html), or `_start`. The underscore prefix is a convention to avoid conflicts and is reserved for functions and types used by the compiler and standard library.

This symbol must be exported so the linker and the boot loader can find it. The `global` keyword informs that the symbol must be exported but a second information is also required: whether the symbol is a function or data (read more [here](https://www.nasm.us/doc/nasm11.html#section-11.2.4)). Since the `_start` function won't be part of the [PLT (Procedure Linkage Table)](https://refspecs.linuxfoundation.org/ELF/zSeries/lzsabi0_zSeries/x2251.html), declaring its size is useful only for debugging purposes.

```asm
global _start:function (_start.end - _start)
_start:
    mov esp, stack_top
    extern kernel_main
    call kernel_main
    cli
```

The `ESP` (Extended Stack Pointer) register is set to point to the top of the stack (learn more [here](https://www.prowaretech.com/articles/current/assembly/x86/tutorial/page-07)).

`kernel_main` is the name of the Kernel entry point C function we will define later.

`CLI` clears the interrupt flag (whereas `STI` sets the interrupt flag), thus disables [interrupts](https://wiki.osdev.org/Interrupts). We want to avoid interrupts while the kernel has not configured interrupt handlers yet and has no [IDT (Interrupt Descriptor Table)](https://wiki.osdev.org/Interrupt_Descriptor_Table). This is a sagety measure since the boot loader disables them.

### 4. For the moment

```asm
.hang: hlt
    jmp .hang
.end:
```

`HLT` (Halt Processor) puts the processor into a halted state, where it will perform no more operations until restarted by an interrupt or a reset.

This infinite loop blocks the processor safely and avoids unattended behaviours. This is a temporary alternative, common in minimalist Kernel From Scratch development.

## Implementing the kernel

We are going to write a very simple kernel. Since we are in a freestanding environment that lacks standard libraries (the kernel won't have any memory allocator for instance), we also have to write the functions needed by the kernel, such as `putchar`. A few headers are available, like `stdbool.h`, `stddef.h` or `stdint.h` for data types, used by the compiler.

The [VGA text mode](https://en.wikipedia.org/wiki/VGA_text_mode) buffer will be used as an output device. VGA (Video Graphics Array) is a display standard made by IBM in 1987. *Text mode* means the screen is organized as a table of characters (the most common mode being 80 columns x 25 rows), each cell representing a character. The screen is mapped in memory to a fixed address, like `0xB8000`, so its content can be modified in this buffer.

This standard being old and limited, it isn't widely used anymore but comes in handy for a minimalist kernel project.

## Linking the Kernel

Once `boot.asm` is assembled and `kernel.c` is compiled, the the object files need to be linked into the final binary file. To do so, we have to create a simple linker.

We will use [GRUB](https://wiki.osdev.org/GRUB) to boot the OS. The Multiboot header will enable GRUB to identify our kernel and boot it. Run the following command and check the return code (0 upon success) to check whether GRUB finds the Multiboot header:

```sh
grub-file --is-x86-multiboot uselOS.bin
```

Resources:

- [Linker Scripts](https://www.math.utah.edu/docs/info/ld_3.html#SEC4)
- [The 20 part linker essay](https://lwn.net/Articles/276782/)

## Booting the Kernel

The [Bare Bones tutorial](https://wiki.osdev.org/Bare_Bones#Booting_the_Kernel) details how to create a ISO file.

First, create a `grub.cfg` file that contains:

```
menuentry "uselOS" {
	multiboot /boot/uselOS.bin
}
```

Install the requirements:

```sh
sudo apt install xorriso qemu-system-x86
```

Then, run the following commands:

```sh
mkdir -p isodir/boot/grub
cp uselOS.bin isodir/boot/uselOS.bin
cp grub.cfg isodir/boot/grub/grub.cfg
grub-mkrescue -o uselOS.iso isodir
```

The output message should end by something like:

```
Writing to 'stdio:uselOS.iso' completed successfully.
```

Since we don't want to restart our virtual machine and boot our OS every time we make a change and want to test it, we will use QEMU to emulate it and see the result.

```sh
qemu-system-i386 -cdrom uselOS.iso
```

## Resources

- [Text Mode Cursor](https://wiki.osdev.org/Text_Mode_Cursor)
- [Operating Systems Development - System Architecture](https://brokenthorn.com/Resources/OSDev7.html)
- [Interrupt request](https://en.wikipedia.org/wiki/Interrupt_request)
- [Keyboard scancodes](https://aeb.win.tue.nl/linux/kbd/scancodes-1.html)
- [Scancodes C arrays](https://f.osdev.org/viewtopic.php?p=310348&sid=4a20bdf2ac22b71256fac50c1fd8d439#p310348) (The `I/O SubSystem` chapter)
- [x86 Instruction Set Reference: IN](https://c9x.me/x86/html/file_module_x86_id_139.html)
- [x86 Instruction Set Reference: OUT](https://c9x.me/x86/html/file_module_x86_id_222.html)
