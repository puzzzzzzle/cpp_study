#pragma once

#include "types.h"

/* vga 状态 */
typedef struct {
  u16* base;
  int curr_col;
  int curr_row;
} vga_state_t;
/* VGA 文本模式（80x25，黑底白字）写字符到 0xB8000 帧缓冲 */
void vga_clear(vga_state_t* vga_state);
void vga_puts(vga_state_t* vga_state, const char* s, u16 len);
