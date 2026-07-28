#pragma once

#include "types.h"

/* Granularity byte for 64-bit code segment: L=1, D=0, G=1 */
#define GDT_CODE_GRAN 0xAF

/* GDTR base field width (64-bit GDTR = 10 bytes total) */
#define GDTR_BASE_TYPE u64

/* Reload CS in 64-bit: push selector + push address + lretq */
#define GDT_CS_RELOAD()                \
  do {                                 \
    asm volatile(                      \
        "pushq %0\n"                   \
        "leaq 1f(%%rip), %%rax\n"      \
        "pushq %%rax\n"                \
        "lretq\n"                      \
        "1:\n"                         \
        :                              \
        : "i"((unsigned long)GDT_CODE) \
        : "rax", "memory");            \
  } while (0)
