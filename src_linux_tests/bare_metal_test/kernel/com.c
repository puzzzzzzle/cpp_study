#include "com.h"
#include "types.h"

#define COM1        0x3F8
#define COM1_LSR    (COM1 + 5)
#define LSR_THR_EMPTY 0x20   /* 发送保持寄存器空 */
#define LSR_DATA_READY 0x01  /* 接收数据就绪 */

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

void com_putc(char c)
{
    while ((inb(COM1_LSR) & LSR_THR_EMPTY) == 0)
        ;
    outb(COM1, (u8)c);
}

int com_getc(void)
{
    while ((inb(COM1_LSR) & LSR_DATA_READY) == 0)
        ;
    return (int)inb(COM1);
}
