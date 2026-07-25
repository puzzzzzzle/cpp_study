#include "screen.h"
#include "vga.h"
#include "com.h"

void screen_clear(void)
{
    vga_clear();
}

void screen_puts(const char *s)
{
    /* 同时输出到 VGA 文本模式与 serial（COM1） */
    vga_puts(s);
    for (const char *p = s; *p; p++)
        com_putc(*p);
}
