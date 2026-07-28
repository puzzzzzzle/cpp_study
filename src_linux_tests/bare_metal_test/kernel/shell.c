#include "shell.h"
#include "str.h"
#include "screen.h"
#include "com.h"

/* 请求 QEMU 退出：写 debug-exit 端口 0xF4（run.sh 需 -device isa-debug-exit）
 */
static void qemu_exit(void) {
  asm volatile("outb %0, %1" : : "a"((u8)0x00), "Nd"((u16)0xF4));
}
/* 关机 */
static void power_off(void) { qemu_exit(); }
/* 简单命令入口 */
static void cmd_parse(const char* line) {
  /* quit/exit */
  if (streq(line, "quit") || streq(line, "exit")) {
    screen_puts("\nbye.\n");
    power_off();
  }
  /* clear */
  if (streq(line, "clear")) {
    screen_clear();
    return;
  }
  /* default :echo */
  screen_puts("\n[got] ");
  screen_puts(line);
}


void shell_run(void) {
     /* 行缓冲区（echo 模式按行累积，用于 quit/exit 判断） */
  static char line[64];
  int len = 0;
  screen_puts("Hello from bare metal kernel!\n");
  char buf[64];
  screen_puts(fmt("Running on %s arch mode\n", ARCH_STR));
  screen_puts("echo mode: type something, it will be echoed back.\n");
  screen_puts("type 'quit' or 'exit' to halt.\n");

  /* echo 模式：从 COM1 读字符并回显 */
  screen_puts("echo> ");
  for (;;) {
    int c = com_getc();

    if (c == '\r' || c == '\n') {
      line[len] = '\0';
      /* 处理命令 */
      cmd_parse(line);
      /* 清空缓冲 */
      len = 0;
      screen_puts("\necho> ");
    } else if (c == 0x7F || c == '\b') {
      /* 退格：缓冲与屏幕各退一格 */
      if (len > 0) len--;
      screen_puts("\b \b");
    } else {
      if (len < (int)(sizeof(line) - 1)) line[len++] = (char)c;
      char buf[2] = {(char)c, '\0'};
      screen_puts(buf);
    }
  }
}