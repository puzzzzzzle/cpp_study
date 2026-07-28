#pragma once

#include "gdt_arch.h"
#include "types.h"

/* Code / data segment selectors (architecture-independent: index << 3) */
#define GDT_CODE 0x08
#define GDT_DATA 0x10

/* A segment descriptor: 8 bytes, packed, same layout for 32/64-bit */
struct gdt_entry {
  u16 limit_low;
  u16 base_low;
  u8 base_middle;
  u8 access;
  u8 granularity;
  u8 base_high;
} __attribute__((packed));

/* GDTR structure: 6 bytes (32-bit) or 10 bytes (64-bit), controlled by
 * gdt_arch.h */
struct gdt_ptr {
  u16 limit;
  GDTR_BASE_TYPE base;
} __attribute__((packed));

/* Initialize and load the GDT (called from kmain) */
void gdt_init(void);
