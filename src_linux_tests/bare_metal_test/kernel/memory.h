#pragma once
#include "types.h"

/*
 * 简单 Free List 内存分配器
 *
 * 使用方式:
 *   static u8 heap_pool[4096];
 *   kmem_init(heap_pool, sizeof(heap_pool));
 *   void* p = kmalloc(128);
 *   kfree(p);
 */
void  kmem_init(void* pool, size_t pool_size);
void* kmalloc(size_t size);
void  kfree(void* ptr);
