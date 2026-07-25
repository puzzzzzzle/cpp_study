/* link.ld - 裸机内核链接脚本（Multiboot 加载到 1MB） */
ENTRY(_start)

SECTIONS
{
    . = 0x100000;   /* 1MB，Multiboot 默认加载地址 */

    .text : {
        *(.multiboot)   /* multiboot 头必须最前 */
        *(.text)
    }

    .rodata : { *(.rodata) }
    .data   : { *(.data) }

    .bss : {
        _bss_start = .;
        *(.bss)
        *(COMMON)
        _bss_end = .;
    }

    /DISCARD/ : { *(.eh_frame) *(.comment) }
}
