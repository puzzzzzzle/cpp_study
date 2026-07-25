#include "screen.h"
#include "types.h"

#define VGA_BASE   0xB8000
#define VGA_WIDTH  80
#define VGA_HEIGHT 25
#define WHITE_ON_BLACK 0x0F

#define COM1        0x3F8
#define COM1_LSR    0x3F8 + 5
#define LSR_THR_EMPTY 0x20

static u16 *const vga = (u16 *)VGA_BASE;

/* 端口 I/O（内联汇编） */
static u8 inb(u16 port)
{
    u8 v;
    asm volatile ("inb %1, %0" : "=a"(v) : "Nd"(port));
    return v;
}

static void outb(u16 port, u8 v)
{
    asm volatile ("outb %0, %1" : : "a"(v), "Nd"(port));
}

/* 等待 COM1 发送保持寄存器空，再写一个字节 */
static void serial_putc(char c)
{
    while ((inb(COM1_LSR) & LSR_THR_EMPTY) == 0)
        ;
    outb(COM1, (u8)c);
}

void screen_clear(void)
{
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++)
        vga[i] = (u16)(WHITE_ON_BLACK << 8) | ' ';
}

void screen_puts(const char *s)
{
    static int col = 0, row = 0;

    for (const char *p = s; *p; p++) {
        /* 同时输出到 VGA 文本模式与 serial（COM1） */
        serial_putc(*p);

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
