# startup-stm32l476
Bare-metal starting project for the STM32L433 MCU. Boots up, initializes the `data` and `bss` sections and jumps to main which does nothing mode than `while(1)`.

## What is what here

This project is the bare minimum set of files that should get you going with C programming for this microcontroller. No fancy libraries, no nothing. Just the 
man versus the machine. What are the contents:

* __stm32l476/__ - contains header files with peripheral/core registers bit definitions
* __compiler.h__ - contains aliases (#defines) for the compiler attributes, 
currently prepared for *gcc* but works with *clang* as well.
* __defhndl.c__ + __defhnfl.h__ - a place to store the implementation of the default exception/interrupt vector. May be used for debugging the situations when your code goes out of whack and causes the *HardFault* or something.
* __image.c__ + __image.h__ - binary image descriptor, contains all the info about the firmware (it's size and version information) and will be added just after the exception vector table (aligned to 16 bits). Other software may look for this header and recognize it by it's signature (a number and it's negation). There is also some space for the checksum if you would like your builds to be checksum-protected. After the build you could use the `objcopy` from your toolchain to fill the `.image_checksum` section with let's say md5 checksum. The command for updating should look something like this: `your-toolchain-objcopy --update-section .checksum=file_with_precomputed_md5.txt ./objs/image.o` Just remember that after updating you need to re-link the final elf file.
* __startup.c__ + __startup.h__ - contains the first ever executed routine `Startup_ResetHandler()` which in this implementation does only two things: Copy all the initialized data and code to ram, zero out all variables 
* __vectors.c__ + __vectors.h__ - this is the place to put all of your interrupt/exception vectors. Use the `SET_EXC_VEC` macro for setting up exceptions and `SET_EXC_INT` for setting up interrupts
* __version.h__ - this is a place where all of the version numbering helpers are defined. Software and Hardware versions are triplets in form *major.minor.build*. The final version number is taken from the *Makefile* so you don't need to worry about setting up anything within this file.

## Makefile

This project can be build using gcc or llvm (clang). This is how the Makefile and the linker script was prepared. Makefile is GNUMake compatible. You can configure all the tools used for building, add sources, libraries, etc..

## How to build

Two things are needed:

* Toolchain that contains C compiler, linker and supporting tools (like objcopy, objdump, nm, size) may be gcc arm embedded toolchain or clang/llvm equivalents with libraries such as libc, libg, libm or whatever you may require
* GNUMake to 'execute' the Makefile

Building using GCC: 
```
make TOOLCHAIN=gcc all
```
Builing using LLVM: 
```
make TOOLCHAIN=llvm all
```