#pragma once

/* 裸机环境无系统头，使用编译器原生定宽类型 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef signed char i8;
typedef signed short i16;
typedef signed int i32;
typedef signed long long i64;

/* size_t */
#ifdef __x86_64__
typedef u64 size_t;
typedef i64 ssize_t;
#else
typedef u32 size_t;
typedef i32 ssize_t;
#endif

/* Stringify helper: STR(ARCH) → "X86_64" */
#define _STR(s) #s
#define STR(s) _STR(s)
