#include "gdt.h"
#include "memory.h"
#include "screen.h"
#include "shell.h"

/* QEMU -m 256M → RAM 上限 256MB，内核之后全部用作堆 */
#define RAM_LIMIT (256ULL * 1024 * 1024)

/* 由链接脚本定义，标记内核镜像末尾 */
extern char _kernel_end;

/* 内核入口（由 entry.asm 调用，ebx=multiboot info, eax=magic） */
void kmain(u32 magic, u32 mb_info) {
  (void)magic;
  (void)mb_info;
  gdt_init();
  kmem_init(&_kernel_end, RAM_LIMIT - (size_t)&_kernel_end);
  screen_clear();
  shell_run();
}
