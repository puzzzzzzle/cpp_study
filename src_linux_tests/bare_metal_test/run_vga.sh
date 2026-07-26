#!/bin/sh
# 开图形窗口运行，专门用来观察 VGA 文本模式输出（0xB8000 帧缓冲）
# 与 run.sh（-nographic，只看串口）不同，这里保留图形显示；
# 串口（COM1）仍接到当前终端，因此可以同时看 VGA 画面并交互。
set -e
cd "$(dirname "$0")"

qemu-system-i386 \
    -kernel kernel.bin \
    -serial stdio \
    -m 256M \
    -smp 1 \
    -device isa-debug-exit,iobase=0xF4
