#include "vga.h"

#include "types.h"

#define VGA_BASE 0xB8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define WHITE_ON_BLACK 0x0F

/* 获取 VGA 缓冲区索引 */
#define VGA_IDX(row, col) ((row) * VGA_WIDTH + (col))

/* 清屏 */
void vga_clear(vga_state_t* vga_state) {
  vga_state->base = (u16*)VGA_BASE;
  vga_state->curr_col = 0;
  vga_state->curr_row = 0;
  for (u16 i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
    vga_state->base[i] = (u16)(WHITE_ON_BLACK << 8) | (u8)' ';
  }
}
/* 滚动屏幕 */
static void vga_scroll(vga_state_t* vga_state, u16 n) {
  // 滚动 n 行
  for (u16 row = 0; row < VGA_HEIGHT - n; row++) {
    for (u16 col = 0; col < VGA_WIDTH; col++) {
      u16 src_idx = VGA_IDX(row + n, col);
      u16 dst_idx = VGA_IDX(row, col);
      vga_state->base[dst_idx] = vga_state->base[src_idx];
    }
  }
  // 清空最后 n 行
  for (u16 row = VGA_HEIGHT - n; row < VGA_HEIGHT; row++) {
    for (u16 col = 0; col < VGA_WIDTH; col++) {
      u16 idx = VGA_IDX(row, col);
      vga_state->base[idx] = (u16)(WHITE_ON_BLACK << 8) | (u8)' ';
    }
  }
}
/* 检查是否需要滚动 */
static void check_scroll(vga_state_t* vga_state) {
  if (vga_state->curr_row >= VGA_HEIGHT) {
    vga_scroll(vga_state, 1);
    vga_state->curr_row = VGA_HEIGHT - 1;
  }
}
/* 打印字符串 */
void vga_puts(vga_state_t* vga_state, const char* s, u16 len) {
  for (u16 i = 0; i < len; i++) {
    char c = s[i];
    if (c == '\n') {
      vga_state->curr_col = 0;
      vga_state->curr_row++;
      check_scroll(vga_state);
      continue;
    }
    u16 idx = VGA_IDX(vga_state->curr_row, vga_state->curr_col);
    vga_state->base[idx] = (u16)(WHITE_ON_BLACK << 8) | (u8)c;
    vga_state->curr_col++;
    if (vga_state->curr_col >= VGA_WIDTH) {
      vga_state->curr_col = 0;
      vga_state->curr_row++;
      check_scroll(vga_state);
    }
  }
}
