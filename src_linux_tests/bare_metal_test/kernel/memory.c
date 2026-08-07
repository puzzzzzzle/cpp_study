#include "memory.h"

/*
 * Free List 内存分配器 — 首次适配 + 立即合并相邻空闲块
 *
 *   Block 物理布局 (8 字节对齐):
 *
 *   ┌─────────────┬──────────────────────────┐
 *   │ header(8B)  │     user data (N 字节)    │
 *   │  size|tag   │                          │
 *   └─────────────┴──────────────────────────┘
 *                    ↑ kmalloc 返回这里
 *
 *   Free block 额外在 user data 头部存 next 指针:
 *
 *   ┌─────────────┬───────────┬──────────────┐
 *   │ header(8B)  │ next(8B)  │  (填充)       │
 *   │ size|tag=0  │           │              │
 *   └─────────────┴───────────┴──────────────┘
 *
 *   tag = header.size_tag 的 LSB:  1=已用, 0=空闲
 *   分配: free_list 首次适配, 大块从头部切分
 *   释放: 标记空闲 → 加入 free_list 头部 → 与物理邻居合并
 */

#define BLOCK_ALIGN  8
#define BLOCK_TAG    0x1ULL

/* 块头部: 块总大小(含头部), LSB 为占用标记 */
typedef struct {
    size_t size_tag;
} block_hdr;

/* 空闲块链表节点, 位于 user data 起始处 */
typedef struct free_blk {
    struct free_blk* next;
} free_blk;

#define HDR_SIZE  ((sizeof(block_hdr) + BLOCK_ALIGN - 1) & ~(BLOCK_ALIGN - 1ULL))

static char*       g_heap      = NULL;
static size_t      g_heap_sz   = 0;
static free_blk*   g_free_list = NULL;

/* -------------------------------------------------------
 * 内部辅助函数
 * -----------------------------------------------------*/

static inline size_t align8(size_t n) {
    return (n + 7) & ~7ULL;
}

static inline block_hdr* ptr_hdr(void* p) {
    return (block_hdr*)((char*)p - HDR_SIZE);
}

static inline void* hdr_ptr(block_hdr* h) {
    return (char*)h + HDR_SIZE;
}

static inline size_t blk_size(block_hdr* h) {
    return h->size_tag & ~BLOCK_TAG;
}

static inline int blk_used(block_hdr* h) {
    return h->size_tag & BLOCK_TAG;
}

static inline void blk_set(block_hdr* h, size_t sz, int used) {
    h->size_tag = sz | (used ? BLOCK_TAG : 0);
}

/* 获取物理上下一个 block (跨过当前块) */
static inline block_hdr* blk_next(block_hdr* h) {
    return (block_hdr*)((char*)h + blk_size(h));
}

/* 从空闲块获取其 free_blk 节点指针 */
static inline free_blk* hdr_free(block_hdr* h) {
    return (free_blk*)hdr_ptr(h);
}

/* 从 free_list 中移除指定节点 */
static void fl_remove(free_blk* target) {
    free_blk** p = &g_free_list;
    while (*p) {
        if (*p == target) { *p = target->next; return; }
        p = &(*p)->next;
    }
}

/* -------------------------------------------------------
 * 公共 API
 * -----------------------------------------------------*/

void kmem_init(void* pool, size_t pool_sz) {
    g_heap_sz = pool_sz & ~(BLOCK_ALIGN - 1ULL);
    g_heap    = (char*)pool;

    /* 整个池作为一个大空闲块 */
    block_hdr* h = (block_hdr*)g_heap;
    blk_set(h, g_heap_sz, 0);
    free_blk* fb = hdr_free(h);
    fb->next = NULL;
    g_free_list = fb;
}

void* kmalloc(size_t size) {
    if (!size || !g_heap) return NULL;

    size_t need = align8(size + HDR_SIZE);

    free_blk** prev = &g_free_list;
    free_blk*  cur  = g_free_list;

    while (cur) {
        block_hdr* h = ptr_hdr(cur);
        size_t sz = blk_size(h);

        if (sz >= need) {
            if (sz >= need + HDR_SIZE + BLOCK_ALIGN) {
                /* 切分: [分配块 | 剩余空闲块] */
                block_hdr* rem = (block_hdr*)((char*)h + need);
                blk_set(rem, sz - need, 0);
                blk_set(h, need, 1);

                free_blk* rfb = hdr_free(rem);
                rfb->next = cur->next;
                *prev = rfb;
            } else {
                /* 精确匹配, 整块分配 */
                *prev = cur->next;
                blk_set(h, sz, 1);
            }
            return hdr_ptr(h);
        }

        prev = &cur->next;
        cur  = cur->next;
    }

    return NULL;   /* 无足够连续空间 */
}

void kfree(void* ptr) {
    if (!ptr) return;

    block_hdr* h = ptr_hdr(ptr);
    blk_set(h, blk_size(h), 0);   /* 标记为 Free */

    /* 向前合并: 与物理下一个块合并 */
    block_hdr* nxt = blk_next(h);
    if ((char*)nxt < g_heap + g_heap_sz && !blk_used(nxt)) {
        fl_remove(hdr_free(nxt));
        blk_set(h, blk_size(h) + blk_size(nxt), 0);
    }

    /* 向后合并: 扫描 free_list 找物理前一个空闲块 */
    {
        free_blk** p = &g_free_list;
        while (*p) {
            block_hdr* ph = ptr_hdr(*p);
            if (blk_next(ph) == h) {
                *p = (*p)->next;   /* 移除前驱 */
                blk_set(ph, blk_size(ph) + blk_size(h), 0);
                h = ph;            /* 合并后以 ph 为准 */
                break;
            }
            p = &(*p)->next;
        }
    }

    /* 合并后的块插入 free_list 头部 */
    free_blk* fb = hdr_free(h);
    fb->next = g_free_list;
    g_free_list = fb;
}