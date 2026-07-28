#pragma once

#include "types.h"

/* Granularity byte for 32-bit code segment: D=1, G=1 */
#define GDT_CODE_GRAN 0xCF

/* GDTR base field width (32-bit GDTR = 6 bytes total) */
#define GDTR_BASE_TYPE u32

/* Reload CS in 32-bit: ljmp */
#define GDT_CS_RELOAD()   \
  do {                    \
    asm volatile(         \
        "ljmp %0, $1f\n"  \
        "1:\n"            \
        :                 \
        : "i"(GDT_CODE)); \
  } while (0)
