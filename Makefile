# --------------------------- TARGET NAME ---------------------------
# output name (final elf/bin will be named after this)
TARGET = radio

# -------------------------- LINKER SCRIPT --------------------------
# linker script
LD_SCRIPT = stm32l476rgt6.ld

# ----------------------- OPTIMIZATION LEVEL ------------------------
# use '-O0' (no optimization) for debugging or (-Os) for release
OPT_LEVEL = -Os

# -------------------------- VERSION NUMBER -------------------------
# software version
SW_VER_MAJOR = 0
SW_VER_MINOR = 0
SW_VER_BUILD = 1

# hardware version
HW_VER_MAJOR = 1
HW_VER_MINOR = 0
HW_VER_BUILD = 0

# ----------------------------- SOURCES -----------------------------
# put all of your sources here (use / as path separator)
SRC += ./startup.c ./vectors.c ./defhndl.c ./image.c ./main.c ./debug.c
SRC += ./reset.c

# at protocol
SRC += ./at/src/at.c ./at/src/cmd.c
SRC += ./at/src/rxtx_usart2.c ./at/src/rxtx.c
SRC += ./at/src/ntfy.c

# at prococol command submodules
SRC += ./at/cmd/src/gen.c ./at/cmd/src/bl.c

# at protocol notification submodules
SRC += ./at/ntfy/src/debug.c

# device drivers
SRC += ./dev/src/usart2.c ./dev/src/watchdog.c
SRC += ./dev/src/cpuclock.c ./dev/src/fpu.c
SRC += ./dev/src/dec.c
SRC += ./dev/src/analog.c ./dev/src/i2c1.c
SRC += ./dev/src/cs43l22.c ./dev/src/rfin.c
SRC += ./dev/src/sai1a.c ./dev/src/display.c
SRC += ./dev/src/extimux.c ./dev/src/joystick.c
SRC += ./dev/src/await.c ./dev/src/systime.c
SRC += ./dev/src/timemeas.c ./dev/src/led.c
SRC += ./dev/src/invoke.c ./dev/src/lsi.c

# digital signal processing
SRC += ./dsp/src/biquad.c

# radio modules
SRC += ./radio/src/mix1.c
SRC += ./radio/src/mix2.c ./radio/src/demod_am.c
SRC += ./radio/src/radio.c

# system files
SRC += ./sys/src/critical.c ./sys/src/ev.c
SRC += ./sys/src/sem.c

# tests
SRC += ./test/src/usart2.c ./test/src/dac_sine.c
SRC += ./test/src/dec.c ./test/src/radio.c
SRC += ./test/src/am_radio.c ./test/src/float_fixp.c
SRC += ./test/src/dynamic_int.c

# utilities
SRC += ./util/src/string.c ./util/src/stdio.c
SRC += ./util/src/strerr.c

# ----------------------------- INCLUDES ----------------------------
# put all used include directories here (use / as path separator)
INC_DIRS = .

# ---------------------------- LIBRARIES ----------------------------
# put all used libraries here starting with 'l[name]', like lm
LIBS = lm lc lgcc
# library search directories (use / as path separator)
LIB_DIRS = .

# ----------------------- OUTPUT DIRECTORIES ------------------------
# object files directory (use / as path separator)
OBJ_DIR = ../.objs
# final binaries directory (use / as path separator)
OUT_DIR = ./.outs

# --------------------- TOOLS && CONFIGURATION ----------------------
# windows tools configuration
ifeq ($(OS),Windows_NT)
    PATH_SEP = $(strip \\)
    SHELL = cmd
    CP = copy
    RM = del /f
    RMDIR = rmdir
    ECHO = echo
    MKDIR = mkdir
# *nix tools configuration
else
    PATH_SEP = /
    SHELL = sh
    CP = cp
    RM = rm -f
    RMDIR = rm -r
    ECHO = echo
    MKDIR = mkdir -p
endif

# ------------------------- BUILD TOOLS -----------------------------
# build tools (set to 'gcc' or 'llvm')
TOOLCHAIN = gcc
# proper system path for selected build tools (leave empty if these are in 
# system PATH)
TOOLCHAIN_PATH =

# build tools for the clang/llvm approach
ifeq ($(TOOLCHAIN),llvm)
    CC = $(TOOLCHAIN_PATH)clang
    AS = $(TOOLCHAIN_PATH)clang
    LD = $(TOOLCHAIN_PATH)ld
    OBC = $(TOOLCHAIN_PATH)llvm-objcopy
    OBD = $(TOOLCHAIN_PATH)llvm-objdump
    NM = $(TOOLCHAIN_PATH)llvm-nm
    SIZE = $(TOOLCHAIN_PATH)llvm-size
endif

# buildtools for the gcc approach
ifeq ($(TOOLCHAIN),gcc)
    CC = $(TOOLCHAIN_PATH)arm-none-eabi-gcc
    AS = $(TOOLCHAIN_PATH)arm-none-eabi-gcc
    LD = $(TOOLCHAIN_PATH)arm-none-eabi-ld
    OBC = $(TOOLCHAIN_PATH)arm-none-eabi-objcopy
    OBD = $(TOOLCHAIN_PATH)arm-none-eabi-objdump
    NM = $(TOOLCHAIN_PATH)arm-none-eabi-nm
    SIZE = $(TOOLCHAIN_PATH)arm-none-eabi-size
endif

# ------------------------ PREPARE PATHS ----------------------------
# string versions of the 'versions'
SW_VER = $(SW_VER_MAJOR).$(SW_VER_MINOR).$(SW_VER_BUILD)
HW_VER = $(HW_VER_MAJOR).$(HW_VER_MINOR).$(HW_VER_BUILD)

# output directory with valid path separator
OUT_DIR_PATH = $(subst /,$(PATH_SEP),$(OUT_DIR))
OBJ_DIR_PATH = $(subst /,$(PATH_SEP),$(OBJ_DIR))

# target name with directory
TARGET_PATH = $(OUT_DIR_PATH)$(PATH_SEP)$(TARGET)
# output file name with version information
TARGET_VER = $(TARGET)_$(HW_VER)_$(SW_VER)
# target file name with path and version information 
TARGET_VER_PATH = $(OUT_DIR_PATH)$(PATH_SEP)$(TARGET_VER)

# sources converted to objs with valid path separator
OBJ = $(subst /,$(PATH_SEP), $(SRC:%.c=$(OBJ_DIR_PATH)$(PATH_SEP)%.o))

# --------------------------- BUILD FLAGS ---------------------------
# optimization level and C standard
CC_FLAGS += $(OPT_LEVEL) --std=c18
# target architecture flags
CC_FLAGS  = -mcpu=cortex-m4 -march=armv7e-m -mthumb $(OPT_LEVEL)
CC_FLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16
# additional architecture flags for clang/llvm
ifeq ($(TOOLCHAIN),llvm)
    CC_FLAGS += --target=thumbv7em-unknown-none-eabihf
    CC_FLAGS += -Wno-keyword-macro
endif
# warning levels
CC_FLAGS += -g3 -ggdb -fdata-sections -ffunction-sections
CC_FLAGS += -Wall -Wno-format
CC_FLAGS += -pedantic-errors -Wno-implicit-fallthrough
# use defines such as M_PI from math.h
CC_FLAGS += -D_USE_MATH_DEFINES
CC_FLAGS += $(addprefix -I,$(INC_DIRS))
# development flag
CC_FLAGS += -DDEVELOPMENT=$(DEVELOPMENT)
# version information (software)
CC_FLAGS += -DSW_VER_MAJOR=$(SW_VER_MAJOR)
CC_FLAGS += -DSW_VER_MINOR=$(SW_VER_MINOR)
CC_FLAGS += -DSW_VER_BUILD=$(SW_VER_BUILD)
# version information (hardware)
CC_FLAGS += -DHW_VER_MAJOR=$(HW_VER_MAJOR)
CC_FLAGS += -DHW_VER_MINOR=$(HW_VER_MINOR)
CC_FLAGS += -DHW_VER_MINOR=$(HW_VER_BUILD)
 
# linker flags 
LD_FLAGS  = -T$(LD_SCRIPT) 
LD_FLAGS += $(addprefix -,$(LIBS)) $(addprefix -L,$(LIB_DIRS))
LD_FLAGS +=  -Wl,-Map=$(TARGET_PATH).map
LD_FLAGS += -Wl,--gc-sections -nostdlib

# object dump flags
OBD_FLAGS  = -j ".flash_code" -j ".ram_code" -S
# additional flags for clang/llvm
ifeq ($(BUILD_TOOLS),llvm)
    OBD_FLAGS += -mcpu=cortex-m4 -mattr=vfp4 
    OBD_FLAGS += --triple=thumbv7em-unknown-none-eabihf
endif

# object copy flags 
OBC_FLAGS  = -O binary

# -------------------------- BUILD PROCESS --------------------------
# generate elf and bin and all other files
all: $(TARGET_PATH).elf $(TARGET_PATH).lst $(TARGET_PATH).sym \
	 $(TARGET_PATH).bin size

# compile all sources
$(OBJ_DIR_PATH)$(PATH_SEP)%.o : %.c
	@ $(ECHO) --------------------- Compiling $< ---------------------
	-@ $(MKDIR) $(dir $@)
	$(CC) -c $(CC_FLAGS) $< -o $@

# link all thogether and generate elf file from objs and *.map file
$(TARGET_PATH).elf: $(OBJ)
	@ $(ECHO) ---------------------    Linking   ---------------------
	-@ $(MKDIR) $(dir $@)
	$(CC) $(CC_FLAGS) $(OBJ) --output $@ $(LD_FLAGS) 

# geneate listing
$(TARGET_PATH).lst: $(TARGET_PATH).elf
	@ $(ECHO) ---------------------    Listing   ---------------------
	$(OBD) $(OBD_FLAGS) $< > $@

# generate symbol list
$(TARGET_PATH).sym: $(TARGET_PATH).elf
	@ $(ECHO) --------------------- Symbol map ---------------------
	$(NM) -n -o $(TARGET_PATH).elf > $(TARGET_PATH).sym

# generate bin file
$(TARGET_PATH).bin: $(TARGET_PATH).elf
	@ $(ECHO) --------------------   Converting   --------------------
	$(OBC) $(OBC_FLAGS) $< $@
	$(CP) $(TARGET_PATH).bin $(TARGET_VER_PATH).bin

# show size information
size: $(TARGET_PATH).elf
	@ $(ECHO) --------------------- Section size ---------------------
	$(SIZE) $(TARGET_PATH).elf

# clean build products
clean:
	- $(RM) $(OBJ) 
	- $(RM) $(TARGET_PATH).elf $(TARGET_PATH).bin $(TARGET_VER_PATH).bin
	- $(RM) $(TARGET_PATH).map $(TARGET_PATH).sym $(TARGET_PATH).lst
	- $(RMDIR) $(OBJ_DIR_PATH) $(OUT_DIR_PATH)
