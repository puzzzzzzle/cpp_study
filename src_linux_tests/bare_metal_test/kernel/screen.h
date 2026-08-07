#pragma once

#include "string.h"

/* 清屏 + 同时输出到 VGA 与 COM1 */
void screen_clear(void);
void screen_puts(bstring_view sv);
