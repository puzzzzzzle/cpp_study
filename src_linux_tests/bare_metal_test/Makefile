CC      = gcc
LD      = ld
ASM     = nasm
CFLAGS  = -m32 -ffreestanding -nostdlib -fno-builtin \
          -fno-stack-protector -Wall -Wextra -c
LDFLAGS = -m elf_i386 -T link.ld -nostdlib

BUILD_DIR = build
OBJS  = $(BUILD_DIR)/entry.o $(BUILD_DIR)/kernel.o $(BUILD_DIR)/gdt.o $(BUILD_DIR)/screen.o
TARGET = $(BUILD_DIR)/kernel.bin

.PHONY: all clean run

all: $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/entry.o: boot/entry.asm | $(BUILD_DIR)
	$(ASM) -f elf32 boot/entry.asm -o $@

$(BUILD_DIR)/kernel.o: kernel/kernel.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) kernel/kernel.c -o $@

$(BUILD_DIR)/gdt.o: kernel/gdt.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) kernel/gdt.c -o $@

$(BUILD_DIR)/screen.o: kernel/screen.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) kernel/screen.c -o $@

$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $@

run: all
	./run.sh

clean:
	rm -rf $(BUILD_DIR)
