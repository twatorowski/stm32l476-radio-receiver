# stm32l476-radio-receiver

All digital AM radio receiver implemented on the stm32l4-discovery board. All the information is here: 
https://mightydevices.com/index.php/2020/02/stm32l4-discovery-radio-receiver/


## How to build

This project can be build using arm-none-eabi-gcc. This is how the Makefile and the linker script were prepared for. Makefile is GNUMake compatible.

Two things are needed:

* Toolchain that contains C compiler, like the one from developer.arm.com
* GNUMake to 'execute' the Makefile

If you into dockerization then please read: https://mightydevices.com/index.php/2019/09/stm32-development-env-for-windows-vscode-arm-gcc-toolchain-openocd/


Building command: 
```
make all
```

The firmware will be put into `./outs` directory