CC      = gcc
LD      = ld
CFLAGS  = -m32 -ffreestanding -nostdlib -fno-builtin \
          -fno-stack-protector -Wall -Wextra -c -MMD
LDFLAGS = -m elf_i386 -T link.ld -nostdlib

BUILD_DIR = build

# 自动查找源文件：boot 下的 .S 与 kernel 下的 .c
ASM_SRCS := $(wildcard boot/*.S)
C_SRCS   := $(wildcard kernel/*.c)
OBJS     := $(patsubst boot/%.S,$(BUILD_DIR)/%.o,$(ASM_SRCS)) \
            $(patsubst kernel/%.c,$(BUILD_DIR)/%.o,$(C_SRCS))
DEPS     := $(OBJS:.o=.d)

TARGET = $(BUILD_DIR)/kernel.bin

.PHONY: all clean run

all: $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# 通用编译规则：boot/*.S -> build/*.o 与 kernel/*.c -> build/*.o
$(BUILD_DIR)/%.o: boot/%.S | $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.o: kernel/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@

$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $@

run: all
	./run.sh

clean:
	rm -rf $(BUILD_DIR)

# 自动包含头文件依赖（.d），改 .h 也能触发重编
-include $(DEPS)
