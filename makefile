TARGET = program

SOURCE = src
BUILD = build
LINKER_SCRIPT = STM32F411CEU6.ld
MCU_SPEC = cortex-m4

CC = arm-none-eabi-gcc
OC = arm-none-eabi-objcopy
OD = arm-none-eabi-objdump

# C compilation directives
CFLAGS += -mcpu=$(MCU_SPEC)
CFLAGS += -mthumb
CFLAGS += -Wall
CFLAGS += -g
# (Set error messages to appear on a single line.)
CFLAGS += -fmessage-length=0
# (Set system to ignore semihosted junk)
CFLAGS += --specs=nosys.specs

# Linker directives.
LSCRIPT = ./$(LINKER_SCRIPT)
LFLAGS += -mcpu=$(MCU_SPEC)
LFLAGS += -mthumb
LFLAGS += -Wall
LFLAGS += --specs=nosys.specs
LFLAGS += -nostdlib
LFLAGS += -lgcc
LFLAGS += -T$(LSCRIPT)

C_SRC = main.c start.c
OBJS = $(C_SRC:.c=.o)
OBJ_PATHS = $(addprefix $(BUILD)/, $(OBJS))

.PHONY: .all
all: $(BUILD)/$(TARGET).bin

$(BUILD)/%.o: $(SOURCE)/%.c
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD)/$(TARGET).elf: $(OBJ_PATHS)
	$(CC) $^ $(LFLAGS) -o $@

$(BUILD)/$(TARGET).bin: $(BUILD)/$(TARGET).elf
	$(OC) -S -O binary $< $@

# %.o: %.c
# 	arm-none-eabi-gcc -mcpu=cortex-m4 -c $< -o $@
# 	
# 	arm-none-eabi-gcc -T $(LINKER_SCRIPT) -nostdlib $(BUILD)/main.o $(BUILD)/start.o -o $(BUILD)/program.elf
# 	
# 	arm-none-eabi-objcopy -O binary $(BUILD)/program.elf $(BUILD)/program.bin
# 	
# 	arm-none-eabi-objdump -h build/program.elf
# 
# elf:
#	arm-none-eabi-gcc -mcpu=cortex-m4 $(SOURCE)/main.c -c -o $(BUILD)/main.o
#	arm-none-eabi-gcc -T $(LINKER_SCRIPT) -nostdlib $(BUILD)/main.o -o $(BUILD)/program.elf
#
# compile:
#	arm-none-eabi-gcc -mcpu=cortex-m4 $(SOURCE)/main.c -c -o $(BUILD)/main.o
#
# link:
#	arm-none-eabi-gcc -T $(LINKER_SCRIPT) -nostdlib $(BUILD)/main.o -o $(BUILD)/program.elf
#
# bin:
#	arm-none-eabi-objcopy -O binary $(BUILD)/program.elf $(BUILD)/program.bin