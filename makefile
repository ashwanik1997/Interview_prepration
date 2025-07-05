################################################################################
# STM32F429ZI + STM32CubeMX HAL + Micrium OS v3.04.05 + GCC Toolchain
################################################################################

# Tools
CC       = arm-none-eabi-gcc
AS       = arm-none-eabi-as
LD       = arm-none-eabi-gcc
OBJCOPY  = arm-none-eabi-objcopy
SIZE     = arm-none-eabi-size

# Target
TARGET = build/firmware.elf

# MCU Flags
MCU = -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard

# Paths
BUILD_DIR  = build
OBJ_DIR    = $(BUILD_DIR)/obj

# Micrium Paths
MICRIUM_ROOT = Middlewares/Micrium
CPU_SRC      = $(MICRIUM_ROOT)/uC-CPU/Source
CPU_PORT     = $(MICRIUM_ROOT)/uC-CPU/ARM-Cortex-M4
LIB_SRC      = $(MICRIUM_ROOT)/uC-LIB/Source
OS3_SRC      = $(MICRIUM_ROOT)/uC-OS3/Source
PORT_SRC     = $(MICRIUM_ROOT)/Ports/ARM-Cortex-M4/ST/STM32F4xx

# HAL and Core Paths
CORE_SRC     = Core/Src
CORE_INC     = Core/Inc
CMSIS_DEV    = Drivers/CMSIS/Device/ST/STM32F4xx
CMSIS_INC    = Drivers/CMSIS/Include
HAL_SRC      = Drivers/STM32F4xx_HAL_Driver/Src
HAL_INC      = Drivers/STM32F4xx_HAL_Driver/Inc

# Linker Script and Startup
LINKER_SCRIPT = STM32F429ZI_FLASH.ld
STARTUP_FILE  = startup_stm32f429xx.s

# Source files
C_SOURCES = \
  $(wildcard $(CORE_SRC)/*.c) \
  $(wildcard $(HAL_SRC)/*.c) \
  $(wildcard $(CMSIS_DEV)/Source/Templates/gcc/*.c) \
  $(wildcard $(CPU_SRC)/*.c) \
  $(wildcard $(LIB_SRC)/*.c) \
  $(wildcard $(OS3_SRC)/*.c) \
  $(wildcard $(PORT_SRC)/*.c)

ASM_SOURCES = \
  $(STARTUP_FILE) \
  $(CPU_PORT)/os_cpu_a.s \
  $(LIB_SRC)/lib_mem_a.s

# Object files
C_OBJECTS   = $(addprefix $(OBJ_DIR)/, $(notdir $(C_SOURCES:.c=.o)))
ASM_OBJECTS = $(addprefix $(OBJ_DIR)/, $(notdir $(ASM_SOURCES:.s=.o)))
OBJECTS     = $(C_OBJECTS) $(ASM_OBJECTS)

# Includes
INCLUDES = \
  -I$(CORE_INC) \
  -I$(HAL_INC) \
  -I$(CMSIS_INC) \
  -I$(CMSIS_DEV)/Include \
  -I$(CPU_SRC) \
  -I$(CPU_PORT) \
  -I$(LIB_SRC) \
  -I$(OS3_SRC) \
  -I$(PORT_SRC)

# Flags
CFLAGS  = $(MCU) -Wall -O0 -g3 -ffunction-sections -fdata-sections -std=c99 $(INCLUDES)
ASFLAGS = $(MCU)
LDFLAGS = $(MCU) -T$(LINKER_SCRIPT) -Wl,-Map=$(BUILD_DIR)/firmware.map -Wl,--gc-sections

################################################################################
# Build Rules
################################################################################

all: $(BUILD_DIR) $(OBJ_DIR) $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# C source compilation
$(OBJ_DIR)/%.o: $(CORE_SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(HAL_SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(CMSIS_DEV)/Source/Templates/gcc/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(CPU_SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(LIB_SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(OS3_SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(PORT_SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# ASM source compilation
$(OBJ_DIR)/%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

$(OBJ_DIR)/%.o: $(CPU_PORT)/%.s
	$(AS) $(ASFLAGS) $< -o $@

$(OBJ_DIR)/%.o: $(LIB_SRC)/%.s
	$(AS) $(ASFLAGS) $< -o $@

# Linking
$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^
	$(OBJCOPY) -O ihex   $@ $(BUILD_DIR)/firmware.hex
	$(OBJCOPY) -O binary $@ $(BUILD_DIR)/firmware.bin
	$(SIZE) $@

# Clean
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean