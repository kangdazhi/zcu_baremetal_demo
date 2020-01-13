TARGET := zcu_baremetal_guest

CROSS_COMPILE := aarch64-elf-
CC:=$(CROSS_COMPILE)gcc
AS:=$(CROSS_COMPILE)as
LD:=$(CROSS_COMPILE)ld
OBJCOPY:=$(CROSS_COMPILE)objcopy
OBJDUMP:=$(CROSS_COMPILE)objdump

OPT_LEVEL = 0
DEBUG_LEVEL = 3

SRC_DIR:=src
BUILD_DIR:=build
INC_DIR:=$(SRC_DIR)/inc

LINKER_SCRIPT:=linker.ld
C_SRC = $(wildcard $(SRC_DIR)/*.c)
ASM_SRC = $(wildcard $(SRC_DIR)/*.S)
OBJS = $(C_SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)\
	$(ASM_SRC:$(SRC_DIR)/%.S=$(BUILD_DIR)/%.o)
DEPS = $(OBJS:%=%.d)

GENERIC_FLAGS = -march=armv8-a -O$(OPT_LEVEL) -g$(DEBUG_LEVEL)
ASFLAGS = $(GENERIC_FLAGS)
CFLAGS = $(GENERIC_FLAGS)
CPPFLAGS =	-I$(INC_DIR) -MD -MF $@.d
LDFLAGS = $(GENERIC_FLAGS) -nostartfiles

all: $(TARGET).bin

-include $(DEPS)

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

$(TARGET).elf: $(OBJS) $(LD_FILE)
	$(CC) $(LDFLAGS) -T$(LINKER_SCRIPT) $(OBJS) -o $@
	$(OBJDUMP) -S $@ > $(TARGET).asm
	$(OBJDUMP) -x -d --wide $@ > $(TARGET).lst

$(BUILD_DIR):
	mkdir $@

$(OBJS): | $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.S
	$(CC) $(ASFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	@rm -rf build
	@rm -f *.elf
	@rm -f *.bin	
	@rm -f *.asm
	@rm -f *.lst

.PHONY: all clean