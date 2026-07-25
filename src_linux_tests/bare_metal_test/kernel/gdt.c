#include "gdt.h"
#include "types.h"

/* GDT 表：索引 0 空，1 代码段，2 数据段（平坦 4GB） */
static struct gdt_entry gdt[3];
static struct gdt_ptr   gp;

#define GDT_CODE 0x08   /* 索引 1 << 3 */
#define GDT_DATA 0x10   /* 索引 2 << 3 */

static void gdt_set_entry(int idx, u32 base, u32 limit,
                          u8 access, u8 gran)
{
    gdt[idx].limit_low   = limit & 0xFFFF;
    gdt[idx].base_low    = base & 0xFFFF;
    gdt[idx].base_middle = (base >> 16) & 0xFF;
    gdt[idx].access      = access;
    gdt[idx].granularity = (limit >> 16) & 0x0F;
    gdt[idx].granularity |= gran & 0xF0;
    gdt[idx].base_high   = (base >> 24) & 0xFF;
}

void gdt_init(void)
{
    /* 0 号描述符必须为空 */
    gdt_set_entry(0, 0, 0, 0, 0);
    /* 代码段：base=0, limit=4G, 可执行/可读, 4K 粒度+32位 */
    gdt_set_entry(1, 0, 0xFFFFF, 0x9A, 0xCF);
    /* 数据段：base=0, limit=4G, 可读写 */
    gdt_set_entry(2, 0, 0xFFFFF, 0x92, 0xCF);

    gp.limit = sizeof(gdt) - 1;
    gp.base  = (u32)&gdt;

    /* 加载 GDT（lgdt 用汇编） */
    asm volatile ("lgdt (%0)" : : "r"(&gp));

    /* 刷新段寄存器，使用新数据/代码段 */
    asm volatile (
        "mov %0, %%ds\n"
        "mov %0, %%es\n"
        "mov %0, %%fs\n"
        "mov %0, %%gs\n"
        "mov %0, %%ss\n"
        : : "r"(GDT_DATA)
    );

    /* 远跳刷新 CS（用代码段选择子） */
    asm volatile (
        "ljmp %0, $1f\n"
        "1:\n"
        : : "i"(GDT_CODE)
    );
}
