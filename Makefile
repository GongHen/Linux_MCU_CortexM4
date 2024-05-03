# Makefile for PTPD master for NUCLEO-F429ZI.

# Project name
NAME = TuringF4
CPU = -mcpu=cortex-m4
# fpu
FPU = -mfpu=fpv4-sp-d16
 
# float-abi
FLOAT-ABI = -mfloat-abi=hard
 
# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# Path to the STM32 codebase, make sure to update the submodule to get the code
VENDOR_ROOT = ./STM32CubeF4/

# Project specific
SRC_DIR = ./UserApp/
INC_DIR = ./Configs/

# Outputs
BINMAP = $(NAME).map
BINELF = $(NAME).elf
BINHEX = $(NAME).hex
BINBIN = $(NAME).bin
BINCRC = $(NAME).crc
BINMAP = $(NAME).map

# GNU ARM Embedded Toolchain
PREFIX = arm-none-eabi-
ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)gcc
CXX = $(GCC_PATH)/$(PREFIX)g++
LD = $(GCC_PATH)/$(PREFIX)ld
AR = $(GCC_PATH)/$(PREFIX)ar
AS = $(GCC_PATH)/$(PREFIX)as
NM = $(GCC_PATH)/$(PREFIX)nm
SIZE = $(GCC_PATH)/$(PREFIX)size
A2L = $(GCC_PATH)/$(PREFIX)addr2line
OBJCOPY = $(GCC_PATH)/$(PREFIX)objcopy
OBJDUMP = $(GCC_PATH)/$(PREFIX)objdump
else
CC = $(PREFIX)gcc
CXX = $(PREFIX)g++
LD = $(PREFIX)ld
AR = $(PREFIX)ar
AS = $(PREFIX)as
NM = $(PREFIX)nm
SIZE = $(PREFIX)size
A2L = $(PREFIX)addr2line
OBJCOPY = $(PREFIX)objcopy
OBJDUMP = $(PREFIX)objdump
endif


# Project sources
SRCS = $(wildcard $(SRC_DIR)*.c) $(wildcard $(SRC_DIR)*/*.c)

# Drivers
# Startup
SRCS += $(VENDOR_ROOT)Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/gcc/startup_stm32f429xx.s
SRCS += $(VENDOR_ROOT)Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c
SRCS += $(VENDOR_ROOT)Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c
SRCS += $(VENDOR_ROOT)Drivers/STM32F7xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c
SRCS += $(VENDOR_ROOT)Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c
SRCS += $(VENDOR_ROOT)Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.c
SRCS += $(VENDOR_ROOT)Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c
SRCS += $(VENDOR_ROOT)Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c
SRCS += $(VENDOR_ROOT)Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c
SRCS += $(VENDOR_ROOT)Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c
SRCS += $(VENDOR_ROOT)Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c
SRCS += $(VENDOR_ROOT)Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c
SRCS += $(VENDOR_ROOT)Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c
SRCS += $(VENDOR_ROOT)Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.c

# RTOS Kernel
SRCS += $(VENDOR_ROOT)Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c
SRCS += $(VENDOR_ROOT)Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c
SRCS += $(VENDOR_ROOT)Middlewares/Third_Party/FreeRTOS/Source/tasks.c
SRCS += $(VENDOR_ROOT)Middlewares/Third_Party/FreeRTOS/Source/queue.c
SRCS += $(VENDOR_ROOT)Middlewares/Third_Party/FreeRTOS/Source/event_groups.c
SRCS += $(VENDOR_ROOT)Middlewares/Third_Party/FreeRTOS/Source/list.c
SRCS += $(VENDOR_ROOT)Middlewares/Third_Party/FreeRTOS/Source/stream_buffer.c
SRCS += $(VENDOR_ROOT)Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/cmsis_os.c
SRCS += $(VENDOR_ROOT)Middlewares/Third_Party/FreeRTOS/Source/croutine.c
SRCS += $(VENDOR_ROOT)Middlewares/Third_Party/FreeRTOS/Source/timers.c

# 如何一句代码包含同一路径下的的c文件


# List of directories that contain source code
SRC_PATHS = $(sort $(dir $(SRCS)))

# Specify the output path
OUTPATH = build

# Create the object list from the sources
OBJS = $(subst .s,.o,$(subst .S,.o,$(subst .c,.o,$(subst .cpp,.o,$(addprefix $(OUTPATH)/, $(notdir $(SRCS)))))))

#$(info SRCS=$(SRCS))
#$(info OBJS=$(OBJS))
#$(info SRC_PATHS=$(SRC_PATHS))

# Where to find source files.
# %表示通配符
vpath %.cpp $(SRC_PATHS)
vpath %.c $(SRC_PATHS)
vpath %.s $(SRC_PATHS)
vpath %.S $(SRC_PATHS)

# Project includes
INCLUDES = -I$(INC_DIR)

# Vendor includes
INCLUDES += -I$(VENDOR_ROOT)Middlewares/Third_Party/FreeRTOS/Source
INCLUDES += -I$(VENDOR_ROOT)Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F
INCLUDES += -I$(VENDOR_ROOT)Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS
INCLUDES += -I$(VENDOR_ROOT)Middlewares/Third_Party/FreeRTOS/Source/include
INCLUDES += -I$(VENDOR_ROOT)Drivers/CMSIS/Core/Include
INCLUDES += -I$(VENDOR_ROOT)Drivers/CMSIS/Device/ST/STM32F4xx/Include
INCLUDES += -I$(VENDOR_ROOT)Drivers/STM32F4xx_HAL_Driver/Inc

OPTFLAGS = -Os

MCFLAGS = -mcpu=cortex-m4
MCFLAGS += -mthumb
MCFLAGS += -mlittle-endian
MCFLAGS += -mfpu=fpv4-sp-d16
MCFLAGS += -mfloat-abi=hard
MCFLAGS += -g -O0 -Wall -Wextra -Warray-bounds -Wno-unused-parameter

# WFLAGS = -Wno-strict-aliasing

DEFINES = -DSTM32F429xx
DEFINES += -DNDEBUG
DEFINES += -DUSE_HAL_DRIVER

# LIBS = -lm

# CFLAGS
CFLAGS = -c $(OPTFLAGS) $(MCFLAGS) $(FFLAGS) $(WFLAGS) $(DEFINES) $(INCLUDES)
CXXFLAGS = -c $(OPTFLAGS) $(MCFLAGS) $(FFLAGS) $(WFLAGS) $(DEFINES) $(INCLUDES) -std=c++11

# LINKER FLAGS
LDSCRIPT = LinkScript/stm32f429xG.ld
LDFLAGS = -T $(LDSCRIPT)
LDFLAGS += $(MCFLAGS)
LDFLAGS += $(FFLAGS)
LDFLAGS += $(INCLUDES_LIBS)
LDFLAGS += $(LIBS)
LDFLAGS += -specs=nano.specs
#LDFLAGS += -Wl,--gc-sections -specs=nano.specs
LDFLAGS += -Wl,-Map=$(OUTPATH)/$(BINMAP),--cref 

###
# Build Rules
.PHONY: all release debug clean

all: $(OUTPATH) release

debug: CFLAGS += -DDEBUG -g -g3 -gdwarf-2 -gdwarf-3
debug: CXXFLAGS += -DDEBUG -g -g3 -gdwarf-2 -gdwarf-3
debug: LDFLAGS += -g -g3 -gdwarf-2 -gdwarf-3
debug: release

release: $(OUTPATH)/$(BINHEX) $(OUTPATH)/$(BINBIN) $(OUTPATH)/$(BINCRC)

$(OUTPATH):
	mkdir -p $(OUTPATH)

# compile
$(OUTPATH)/%.o : %.cpp
	@echo "[CC] $@"
	$(CXX) $(CXXFLAGS) $< -o $@

$(OUTPATH)/%.o : %.c
	@echo "[CC] $@"
	@$(CC) $(CFLAGS) -c $< -o $@
# $(CC) $(CFLAGS) $< -o $@

$(OUTPATH)/%.o : %.s
	@echo "[CC] $@"
	$(CC) $(CFLAGS) -c $< -o $@
# $(CC) $(CFLAGS) $< -o $@

## Link
# C linking is used. If C++ linker is required, change:
#   $(CC) $(OBJS) $(LDFLAGS) -o $@
# to:
#   $(CXX) $(OBJS) $(LDFLAGS) -o $@
#
$(OUTPATH)/$(BINELF): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@
	$(SIZE) $(OUTPATH)/$(BINELF)

$(OUTPATH)/$(BINHEX): $(OUTPATH)/$(BINELF)
	@echo "[LD] $@"
	$(OBJCOPY) -O ihex $< $@

$(OUTPATH)/$(BINBIN): $(OUTPATH)/$(BINELF)
	@echo "[LD] $@"
	$(OBJCOPY) -O binary $< $@

# $(OUTPATH)/$(BINCRC): $(OUTPATH)/$(BINBIN)
# 	cksum < $< > $@


clean:
	rm -f $(OBJS)
	rm -f $(OUTPATH)/$(BINELF)
	rm -f $(OUTPATH)/$(BINMAP)
	rm -f $(OUTPATH)/$(BINHEX)
	rm -f $(OUTPATH)/$(BINBIN)
	rm -f $(OUTPATH)/$(BINCRC)
	rm -f $(OUTPATH)/$(BINMAP)
	rm -f $(OUTPATH)/*.d
	rm -f $(OUTPATH)/*.su

flash: $(OUTPATH)/$(BINHEX) 
	st-flash --reset --format ihex write $(OUTPATH)/$(BINHEX)