#include "vga.h"
#include "types.h"

#define VGA_BASE   0xB8000
#define VGA_WIDTH  80
#define VGA_HEIGHT 25
#define WHITE_ON_BLACK 0x0F

static u16 *const vga = (u16 *)VGA_BASE;

void vga_clear(void)
{
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++)
        vga[i] = (u16)(WHITE_ON_BLACK << 8) | ' ';
}

void vga_puts(const char *s)
{
    static int col = 0, row = 0;

    for (const char *p = s; *p; p++) {
        if (*p == '\n') {
            col = 0;
            row++;
            if (row >= VGA_HEIGHT) row = 0;
            continue;
        }
        int idx = row * VGA_WIDTH + col;
        vga[idx] = (u16)(WHITE_ON_BLACK << 8) | (u8)*p;
        col++;
        if (col >= VGA_WIDTH) {
            col = 0;
            row++;
            if (row >= VGA_HEIGHT) row = 0;
        }
    }
}
