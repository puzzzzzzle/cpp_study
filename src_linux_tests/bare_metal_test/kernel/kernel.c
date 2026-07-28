#include "gdt.h"
#include "screen.h"
#include "shell.h"

/* 内核入口（由 entry.asm 调用，ebx=multiboot info, eax=magic） */
void kmain(u32 magic, u32 mb_info) {
  (void)magic;
  (void)mb_info;
  gdt_init();
  screen_clear();
  shell_run();
}
