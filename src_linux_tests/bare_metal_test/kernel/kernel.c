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

    /* 停机：避免 CPU 跑飞 */
    for (;;) {
        asm volatile ("cli; hlt");
    }
}
