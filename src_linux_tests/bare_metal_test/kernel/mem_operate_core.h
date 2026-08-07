#pragma once
#include "types.h"

/* 逐字节拷贝, 依赖编译器进行 SIMD 优化 */
static inline void byte_copy(char* dst, const char* src, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        dst[i] = src[i];
    }
}
static inline size_t strlen(const char* s)
{
    size_t len = 0;
    while (*s++)
        len++;
    return len;
}