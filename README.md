# stm32l476-radio-receiver

All on-board digital AM radio receiver implemented on the stm32l4discovery board. No external components needed. Well maybe besides the looooong antenna wire.

## Principle of operation

TODO

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