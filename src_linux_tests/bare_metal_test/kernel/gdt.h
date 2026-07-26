#pragma once

#include "types.h"

/* 一个段描述符：8 字节 */
struct gdt_entry {
    u16 limit_low;
    u16 base_low;
    u8  base_middle;
    u8  access;
    u8  granularity;
    u8  base_high;
} __attribute__((packed));

/* GDTR 加载用的结构 */
struct gdt_ptr {
    u16 limit;
    u32 base;
} __attribute__((packed));

/* 初始化 GDT 并加载（在 kmain 中调用） */
void gdt_init(void);
