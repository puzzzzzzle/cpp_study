#include "gdt.h"

/* GDT table: index 0 = null, 1 = code, 2 = data (flat model) */
static struct gdt_entry gdt[3];
static struct gdt_ptr gp;

static void gdt_set_entry(int idx, u32 base, u32 limit, u8 access, u8 gran) {
  gdt[idx].limit_low = limit & 0xFFFF;
  gdt[idx].base_low = base & 0xFFFF;
  gdt[idx].base_middle = (base >> 16) & 0xFF;
  gdt[idx].access = access;
  gdt[idx].granularity = (limit >> 16) & 0x0F;
  gdt[idx].granularity |= gran & 0xF0;
  gdt[idx].base_high = (base >> 24) & 0xFF;
}

void gdt_init(void) {
  /* Descriptor 0 must be null */
  gdt_set_entry(0, 0, 0, 0, 0);
  /* Code segment: base=0, limit=4G, exec/read, granularity from arch */
  gdt_set_entry(1, 0, 0xFFFFF, 0x9A, GDT_CODE_GRAN);
  /* Data segment: base=0, limit=4G, read/write */
  gdt_set_entry(2, 0, 0xFFFFF, 0x92, 0xCF);

  gp.limit = sizeof(gdt) - 1;
  gp.base = (GDTR_BASE_TYPE)(unsigned long)&gdt;

  /* Load GDTR */
  asm volatile("lgdt (%0)" : : "r"(&gp));

  /* Refresh data segment registers */
  asm volatile(
      "mov %0, %%ds\n"
      "mov %0, %%es\n"
      "mov %0, %%fs\n"
      "mov %0, %%gs\n"
      "mov %0, %%ss\n"
      :
      : "r"(GDT_DATA));

  /* Reload CS — platform-specific far jump */
  GDT_CS_RELOAD();
}
