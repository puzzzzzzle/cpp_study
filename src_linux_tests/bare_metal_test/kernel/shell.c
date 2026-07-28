#include "shell.h"

#include "com.h"
#include "screen.h"
#include "str.h"

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

typedef struct {
  // 行缓冲区
  char line[512];
  int len;
} shell_line_state_t;
void shell_line_state_reset(shell_line_state_t* state) { state->len = 0; }
void shell_line_state_putc(shell_line_state_t* state, char c) {
  if (state->len < (int)(sizeof(state->line) - 1)) {
    state->line[state->len++] = c;
  }
}
void shell_line_state_delete_last(shell_line_state_t* state) {
  if (state->len > 0) {
    state->len--;
  }
}
void shell_run(void) {
  /* 行缓冲区（echo 模式按行累积，用于 quit/exit 判断） */
  static shell_line_state_t line_state;
  screen_puts("Hello from bare metal kernel!\n");
  screen_puts(fmt("Running on %s arch mode\n", ARCH_STR));
  screen_puts("echo mode: type something, it will be echoed back.\n");
  screen_puts("type 'quit' or 'exit' to halt.\n");

  /* echo 模式：从 COM1 读字符并回显 */
  screen_puts("echo> ");
  for (;;) {
    int c = com_getc();

    if (c == '\r' || c == '\n') {
      shell_line_state_putc(&line_state, '\0');
      /* 处理命令 */
      cmd_parse(line_state.line);
      /* 清空缓冲 */
      shell_line_state_reset(&line_state);
      /* 输出提示符 */
      screen_puts("\necho> ");
    } else if (c == 0x7F || c == '\b') {
      /* 退格：缓冲与屏幕各退一格 */
      shell_line_state_delete_last(&line_state);
      screen_puts("\b \b");
    } else {
      shell_line_state_putc(&line_state, (char)c);
      char buf[2] = {(char)c, '\0'};
      screen_puts(buf);
    }
  }
}