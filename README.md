# Libblitter.library

## Introduction

This project is to provide the chipset feature as service, in 1980’s Amiga was made for gaming market, accidently it got right talent of software developers to allow it to have a cooperative multitasking operating system, but developers ignore the OS, any overhead, can slow down games, beside they wanted their own custom DRM code, to protect their games from being copied. Starting with Draco, AmigaONE and Amitalon system the chipset was being taken out. now we have next generation AmigaOS for PowerPC, and OS replicas like MorphOS and AROS, that run on hardware does not include a chipset. To solve the problem, we need hardware features in software.

A number of different tricks has been tried, emulation, and mmu based software patches, on the operating system that run some compatible big-endian byte code (the PowerPC CPU chips), this are the AmigaOS4 and MorphOS operating systems, running on modern / half modern hardware.
Emulation needs huge overhead, and it’s a bad integration, in addition needs configuration, and copyrighted roms, or system files. 

If you’re using MMU patches, it often does not work at all, or make the system unstable. 

While interesting approaches, there is less intrusive ways to deal with this. And is writing software routines that can do what hardware was doing.

The way Amiga work is that some of address space is used by custom chips, so when you write to the $DFF0xxx, the write triggers a hardware interrupt, or hardware copy features, line draw or fill features provided by chipset, and other stuff.

AmigaOS4.1 SDK provides a struct declares all address and name of this parameters in custom hardware, this what most will be using working on C code.

I tried first to use UAE code as bases for library, it was bit too complexed, then I tried to use code from another project Blitzen by Peter Gordon. This resulted in software license change to Open-Source Freeware license.

I also speculated about writing my own from ground up, but it probably be waste of time, I hope to be forgiven :-), for not wasting my time.|

**Best Regards**

Kjetil Hvalstrand  
also known as LiveForIt and  
NutsAboutAmiga on Amiga forums.

# Exsamples

## 680x0 assembler exsample.

    ;insted of A6 pointing to $DFF0000, 
    ;you point it some memory, you have allocated.
    
    move.l #$09F0000,BLTCON0(a6)
    move.l #$FFFFFFFF,BLTAFWM(a6)
    move.l #Font,BLTAPTH(a6)
    move.l #screen,BLTDPTH(a6)
    move.w #FontBpl-4,BLTAMOD(a6)
    move.w #ScrBpl-4,BLTDMOD(a6)
    move.w #20*64+4+2,BLTSIZE(a6)
    
    ;Setting BLTSIZE should start blitter, but nothing happens, because no chipset is used,
    ;so we call doBlitter, do blitter takes A6 as first and only argument.
      
    lea libBlitter(pc),a1
    jsr doBlitter(a1)


# Compiling..

    You need to have AmigaOS4.1 SDK installed.
    find the directory with makefile, and do.

    make clean
    make all
    make install
    
    Update script should not be used unless you adding feature to the library.
    If you then need RPL tool to replace the incorrect text in the auto generated header files.
    you should find it on project page on github.
