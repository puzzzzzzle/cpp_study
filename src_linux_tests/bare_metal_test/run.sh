#!/bin/sh
# 用 QEMU 加载裸机内核（支持 32/64 位，由 Makefile ARCH 变量控制）
set -e
cd "$(dirname "$0")"

ARCH=${ARCH:-x86_64}

qemu-system-x86_64 \
    -kernel build/${ARCH}/kernel.bin \
    -nographic \
    -m 256M \
    -smp 1 \
    -device isa-debug-exit,iobase=0xF4
