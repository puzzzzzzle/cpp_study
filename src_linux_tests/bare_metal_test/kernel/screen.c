#include "screen.h"
#include "vga.h"
#include "com.h"
#include "str.h"

static vga_state_t vga_state;

void screen_clear(void)
{
    vga_clear(&vga_state);
}

void screen_puts(const char *s)
{
    /* 同时输出到 VGA 文本模式与 serial（COM1） */
    vga_puts(&vga_state, s, strlen(s));
    for (const char *p = s; *p; p++)
        com_putc(*p);
}
