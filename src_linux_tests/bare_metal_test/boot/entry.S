/* entry.S - 32 位保护模式裸机内核入口（Multiboot 约定）
 * 由 qemu -kernel 加载：CPU 已在保护模式，eax=0x2BADB002, ebx=multiboot info
 * GNU as (AT&T) 语法，与 com.c 内联汇编风格统一
 */

/* kmain 在 C 文件中定义，需声明为外部符号 */
.extern kmain

/* ---- Multiboot 头（GRUB/QEMU 识别用）---- */
/* 结构：magic(4) + flags(4) + checksum(4) + 其余可选字段 */
#define MAGIC    0x1BADB002
#define FLAGS    0x00000000      /* 不要求额外信息 */
#define CHECKSUM (-(MAGIC + FLAGS))

.section .multiboot
    .long MAGIC
    .long FLAGS
    .long CHECKSUM

/* ---- 代码段 ---- */
.section .text
.global _start
_start:
    /* 1. 设置栈指针（栈向低地址增长） */
    movl $stack_top, %esp

    /* 2. 清 BSS 段（C 未初始化全局变量必须清零） */
    movl $_bss_start, %edi
    movl $_bss_end, %ecx
    subl %edi, %ecx
    xorl %eax, %eax
    shrl $2, %ecx              /* 按 4 字节清 */
    cld
    rep stosl

    /* 3. 进入 C 主体（multiboot magic 在 eax，info 指针在 ebx） */
    pushl %ebx
    pushl %eax
    call kmain

    /* 4. kmain 不应返回；若返回则停机 */
1:
    cli
    hlt
    jmp 1b

/* ---- BSS 段（栈空间在此预留）---- */
.section .bss
.align 16
_bss_start:
    .space 16 * 1024          /* 16KB 栈 */
stack_top:
_bss_end:
