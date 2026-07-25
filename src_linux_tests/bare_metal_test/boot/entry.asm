; entry.asm - 32 位保护模式裸机内核入口（Multiboot 约定）
; 由 qemu -kernel 加载：CPU 已在保护模式，eax=0x2BADB002, ebx=multiboot info

BITS 32

; kmain 在 C 文件中定义，需声明为外部符号
extern kmain

; ---- Multiboot 头（GRUB/QEMU 识别用）----
; 结构：magic(4) + flags(4) + checksum(4) + 其余可选字段
MAGIC   equ 0x1BADB002
FLAGS   equ 0x00000000      ; 不要求额外信息
CHECKSUM equ -(MAGIC + FLAGS)

section .multiboot
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

; ---- 代码段 ----
section .text
global _start
_start:
    ; 1. 设置栈指针（栈向低地址增长）
    mov esp, stack_top

    ; 2. 清 BSS 段（C 未初始化全局变量必须清零）
    mov edi, _bss_start
    mov ecx, _bss_end
    sub ecx, edi
    xor eax, eax
    shr ecx, 2              ; 按 4 字节清
    cld
    rep stosd

    ; 3. 进入 C 主体（multiboot magic 在 eax，info 指针在 ebx）
    push ebx
    push eax
    call kmain

    ; 4. kmain 不应返回；若返回则停机
.hang:
    cli
    hlt
    jmp .hang

; ---- BSS 段（栈空间在此预留）----
section .bss
align 16
_bss_start:
    resb 16 * 1024          ; 16KB 栈
stack_top:
_bss_end:
