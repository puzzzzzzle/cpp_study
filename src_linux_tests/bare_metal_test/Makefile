CC      = gcc
LD      = ld

ARCH    ?= x86_64

# Arch-specific flags
ifeq ($(ARCH),x86_64)
    ARCH_CFLAGS  = -m64 -mcmodel=small -mno-red-zone -mgeneral-regs-only
    ARCH_LDFLAGS = -m elf_x86_64
else
    ARCH_CFLAGS  = -m32
    ARCH_LDFLAGS = -m elf_i386
endif

# Common flags
COMMON_CFLAGS  = -ffreestanding -nostdlib -fno-builtin \
                 -fno-stack-protector -Wall -Wextra -c -MMD \
                 -I kernel -I arch/$(ARCH) -DARCH_STR=\"$(ARCH)\"
COMMON_LDFLAGS = -T link.ld -nostdlib

CFLAGS  = $(ARCH_CFLAGS) $(COMMON_CFLAGS)
LDFLAGS = $(ARCH_LDFLAGS) $(COMMON_LDFLAGS)

BUILD_DIR = build/$(ARCH)

ASM_SRCS := $(wildcard arch/$(ARCH)/*.S)
C_SRCS   := $(wildcard kernel/*.c)
OBJS     := $(patsubst arch/$(ARCH)/%.S,$(BUILD_DIR)/%.o,$(ASM_SRCS)) \
            $(patsubst kernel/%.c,$(BUILD_DIR)/%.o,$(C_SRCS))
DEPS     := $(OBJS:.o=.d)

TARGET = $(BUILD_DIR)/kernel.bin

.PHONY: all clean run

all: $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: arch/$(ARCH)/%.S | $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.o: kernel/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@

$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $@

run: all
	ARCH=$(ARCH) ./run.sh

clean:
	rm -rf $(BUILD_DIR)

-include $(DEPS)
