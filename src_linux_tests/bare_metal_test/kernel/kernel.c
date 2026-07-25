#include "gdt.h"
#include "screen.h"
#include "types.h"

/* 内核入口（由 entry.asm 调用，ebx=multiboot info, eax=magic） */
void kmain(u32 magic, u32 mb_info)
{
    (void)magic;
    (void)mb_info;

    gdt_init();
    screen_clear();
    screen_puts("Hello from bare metal kernel!\n");
    screen_puts("32-bit protected mode, loaded by QEMU -kernel\n");
    screen_puts("echo mode: type something, it will be echoed back.\n");

    /* echo 模式：从 COM1 读字符并回显 */
    screen_puts("echo> ");
    for (;;) {
        int c = serial_getc();

        if (c == '\r' || c == '\n') {
            screen_puts("\necho> ");
        } else if (c == 0x7F || c == '\b') {
            /* 退格：回退一格并清字符 */
            screen_puts("\b \b");
        } else {
            char buf[2] = { (char)c, '\0' };
            screen_puts(buf);
        }
    }
}

