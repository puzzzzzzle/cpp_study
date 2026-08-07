#include "shell.h"

#include "com.h"
#include "screen.h"
#include "string.h"

/* QEMU debug-exit */
static void qemu_exit(void) {
    asm volatile("outb %0, %1" : : "a"((u8)0x00), "Nd"((u16)0xF4));
}

/* 命令解析 */
static void cmd_parse(bstring_view cmd) {
    if (bstring_view_eq_cstr(cmd, "quit") || bstring_view_eq_cstr(cmd, "exit")) {
        screen_puts(SV("\nbye.\n"));
        qemu_exit();
    }
    if (bstring_view_eq_cstr(cmd, "clear")) {
        screen_clear();
        return;
    }
    screen_puts(SV("\n[got] "));
    screen_puts(cmd);
}

/* shell 主循环：行编辑 + 命令解析 */
void shell_run(void) {
    /* 行缓冲区：bstring 借出堆栈空间，不分配堆内存 */
    char    line_buf[512];
    bstring cmd_line;
    bstring_init_from_buffer(&cmd_line, line_buf, sizeof(line_buf));

    screen_puts(SV("Hello from bare metal kernel!\n"));

    bstring tmp;
    bstring_init(&tmp, 64);
    bstring_fmt(&tmp, "Running on %s arch mode\n", ARCH_STR);
    screen_puts(bstring_view_create(&tmp));
    bstring_destroy(&tmp);

    screen_puts(SV("echo mode: type something, it will be echoed back.\n"));
    screen_puts(SV("type 'quit' or 'exit' to halt.\n"));
    screen_puts(SV("echo> "));

    for (;;) {
        int c = com_getc();

        if (c == '\r' || c == '\n') {
            cmd_parse(bstring_view_create(&cmd_line));
            bstring_clear(&cmd_line);
            screen_puts(SV("\necho> "));
        } else if (c == 0x7F || c == '\b') {
            bstring_pop_back(&cmd_line, 1);
            screen_puts(SV("\b \b"));
        } else {
            char ch = (char)c;
            bstring_append(&cmd_line, &ch, 1);
            screen_puts(bstring_view_from_cstr(&ch, 1));
        }
    }
}