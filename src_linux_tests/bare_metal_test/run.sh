#!/bin/sh
# 用 QEMU 加载我们自己的裸机内核（替代 bzImage）
set -e
cd "$(dirname "$0")"

qemu-system-i386 \
    -kernel build/kernel.bin \
    -nographic \
    -m 256M \
    -smp 1 \
    -device isa-debug-exit,iobase=0xF4
