#pragma once

#include "types.h"

/* 组合层：同时输出到 VGA 文本模式与 COM1 串口 */
void screen_clear(void);
void screen_puts(const char* s);
void screen_putc(char c);
void screen_putn(const char* s, u32 n);
