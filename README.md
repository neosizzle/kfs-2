# /dev/log for kfs-2

[TOC]

# Week 1
## Implementation of rebooting and halt
For halting, just use the `hlt` instruction, which stops the CPU until an interrupt is received.

![image alt](https://i.imgur.com/WdWx3KX.gif)

For a reboot, just jump to the address `0FFFFh:0`, which is the [Reset Vector](https://en.wikipedia.org/wiki/Reset_vector)

![image alt](https://i.imgur.com/UrNyUZm.gif)

## Reading and planning of GDT implementation
Upon reading on some implementation methods of the GDT, I have boiled down the steps needed to execute this.

1. Set stack to a const address first / Apply a global offset for the GDT
2. Make a segment descriptor structure representation
3. Create the segment descriptors required with the appopriate flags
4. Arrange them in an array
5. Create a GDT structure which contains the pointer to the first segment descriptor and the length of the GDT
6. Load the GDT using `lgdt`
7. Copy the offsets of segments to the respective segment registers
8. Flush the code segment register by making a far jump

## GDT implementation mistake
I did everything in asm, since my final bin is elf32, I cant use the org instruction to set the intitial address of the GDT, but I got it to launch so thats cool, but need to fix the adderss of the gdt so ill need to move everything to c

![](https://i.imgur.com/pIbmKLC.png)

## System hang bug 
I managed to replicate something similar in C, however the system hangs upon setting the address to the required address `0x800`.

I inspected the kernel using GDB and it turns out that the kernel is stuck because it is calling to god-knows-what address `0x7a60098b` during the initialization of the IRQ handlers .

![](https://i.imgur.com/TZJ3rpe.png)

I thought this a compile error since the code instructions are generated via the compiler, but then it struck me - the instrction address of the faulty call is `0x7ff`, which is 1 away from `0x800`, our supposedly gdt start address.

Turns out during the initialization of GDT (which is before register irq handlers) modifies the address that points to the IRQ part of the code, causing said corruption.

![](https://i.imgur.com/fP8M5mK.png)

As a result, we needed to allocate empty padding at the beginning of the code data so that the GDT wont overwrite exising code data.

![](https://i.imgur.com/JXzVmU0.png)

This can be done via the linker, with just 1 line of change

![](https://i.imgur.com/IXtUw2t.png)

## GDT implementation and stack printer
With the execution in place and the fix above done, the GDT now works, and the address is now correct

![](https://i.imgur.com/t0Yb2L1.png)

I also implemented the stack printer, it just prints the contents near the GDT address.

![](https://i.imgur.com/5AJNln6.png)
