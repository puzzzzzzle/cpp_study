#pragma once
#include <stdbool.h>
#include <stdarg.h>
#include "types.h"

/*
 * 参考 fbstring 设计的动态字符串 — 24 字节，三态存储。
 *
 *   Small  ( 0 ~ 23 字符) : 内联存储在 u.small.data[23]，Byte[23] MSB=0
 *                            flags = 23 - len，零成本获取剩余容量
 *   Medium (24 ~4G 字符)  : 堆分配，flags=0x80 固定标记
 *                            capacity 存在 heap.med_cap(u32)
 *   Large  (≥ 4G 字符)     : 堆分配，flags=0xFF 标记
 *                            u.heap.ptr 指向堆头（cap + data）
 *
 * 需要外部分配器:
 *   extern void* kmalloc(size_t size);
 *   extern void  kfree(void* ptr);
 */

#define BSTRING_INLINE_CAP 23

/*
 * heap 结构体 padding 分为两段，使 med_cap/heap_flags 在 32/64 位下偏移一致：
 *   _pad1 — 补到 size 之后，确保 med_cap 始终 @byte[16]
 *   _pad2 — 补到 heap_flags 之后，确保 flags 始终 @byte[23]
 */
#ifdef __x86_64__
#define BSTRING_SIZE_PAD 0    /* ptr(8)+size(8)=16，已对齐 */
#define BSTRING_TAIL_PAD 2    /* med_cap(4)+hf(1)=5 → gap 到23 = 2 */
#else
#define BSTRING_SIZE_PAD 8    /* ptr(4)+size(4)=8 → 补8对齐到16 */
#define BSTRING_TAIL_PAD 2    /* med_cap(4)+hf(1)=5 → gap 到23 = 2 */
#endif

/* ---- 只读字符串视图 ---- */
typedef struct {
    const char* data;
    size_t len;
} bstring_view;

/*
 * Byte[23]（即 small.flags）决定三态，bit 分布如下：
 *
 *   bit7  bit6  bit5  bit4 bit3 bit2 bit1 bit0
 *   MSB   NG    (空)  ───── rem ──────────
 *
 * ── Small (0 ~ 23 字符) ──
 *   MSB=0, NG=no_grow, rem=23-len（剩余容量，最大 23，仅用 5bit）
 *   data[] 内联存储，flags 同时作为 len=23 时的 '\0', 兼容 C 字符串
 *
 *   Byte:  0 ───────────────────── 22  [23]
 *         ┌────────────────────────────┬────┐
 *         │        data[23]           │0x12│  例: len=5, NG=0 → rem=18
 *         │     (inline 字符)          │0 0 010010│  rem=(flags & 0x1F)
 * ── Medium (24 ~ 4294967295 字符) ──
 *   flags=0x80(固定标记), capacity 在 med_cap(u32), heap_flags bit0=NG
 *
 *   Byte(64):  0───────7  8─────────15  16──────19  20    21─22   23
 *   Byte(32):  0───3      4───7          8───15      16─19 20    21─22   23
 *            ┌────────────┬───────────────┬──────────┬────┬───┬──────┬────┐
 *            │    ptr     │     size      │  _pad1   │mcap│HF │_pad2 │0x80│
 *            │  4B / 8B   │   4B / 8B    │ 0B / 8B  │u32 │1B │ 2B   │固定│
 *            └─────┬──────┴───────────────┴──────────┴────┴───┴──────┴────┘
 *                  │              ← med_cap @16, HF @20 →
 *                  ▼
 *         ┌────────────────────────┐
 *         │  heap data (cap+1 字节) │ +1 给 '\0'
 *         └────────────────────────┘
 *
 * ── Large (≥ 4294967296 或 >u32 范围) ──
 *   flags=0xFF, heap_flags bit0=NG, 真 cap 在堆头 sizeof(size_t), med_cap 未使用
 *
 *   Byte(64):  0───────7  8─────────15  16──────19  20    21─22   23
 *   Byte(32):  0───3      4───7          8───15      16─19 20    21─22   23
 *            ┌────────────┬───────────────┬──────────┬────┬───┬──────┬────┐
 *            │    ptr     │     size      │  _pad1   │(─) │HF │_pad2 │0xFF│
 *            │  4B / 8B   │   4B / 8B    │ 0B / 8B  │空闲 │1B │ 2B   │固定│
 *            └─────┬──────┴───────────────┴──────────┴────┴───┴──────┴────┘
 *                  │              ← med_cap @16, HF @20 →
 *                  ▼
 *         ┌──────┬─────────────────────────────┐
 *         │ cap  │     heap data (cap+1 字节)   │ +1 给 '\0'
 *         │(8B)  │                             │
 *         └──────┴─────────────────────────────┘
 *          ptr 指向此处
 *
 * 判定伪代码:
 *   is_small  = (flags & 0x80) == 0
 *   is_medium = flags == 0x80
 *   is_large  = flags == 0xFF
 *   no_grow   = is_small ? (flags & 0x40) : (heap_flags & 1)
 */
typedef struct {
    union {
        struct {
            char data[BSTRING_INLINE_CAP];   /* [ 0..22] 内联字符数据           */
            u8   flags;                       /* [23]    bit7:MSB bit6:NG bit5:(空) bit4~0:rem */
        } small;
        struct {
            char*  ptr;                       /* [ 0.. 7/0..3] 堆指针              */
            size_t size;                      /* [ 8..15/4..7] 当前长度           */
            u8     _pad1[BSTRING_SIZE_PAD];   /* [—/8..15] 32位补齐到16对齐       */
            u32    med_cap;                   /* [16..19]      Medium 容量(u32)    */
            u8     heap_flags;                /* [20]          堆模式额外标志(NG)  */
            u8     _pad2[BSTRING_TAIL_PAD];   /* [21..22]      补齐flags到byte23   */
            u8     flags;                     /* [23]          Medium:0x80 Large:0xFF */
        } heap;
    } u;
} bstring;
/* 编译时确保 bstring 为 24 字节，不对齐会导致内存布局错误 */
static_assert(sizeof(bstring) == 24, "bstring must be exactly 24 bytes");

/* ---- 生命周期 ---- */
// 初始化 bstring, 默认设置为可增长
ssize_t bstring_init(bstring* sb, size_t cap);
// 销毁 bstring
void    bstring_destroy(bstring* sb);
// 初始化 bstring 从预分配的缓冲区, 默认设置为不可增长, destroy 不释放 buf
ssize_t bstring_init_from_buffer(bstring* sb, char* buf, size_t cap);

// 复制, 非 small 字符串, 直接从堆上申请空间, small 直接字节拷贝, 失败返回空bstring
bstring bstring_clone(const bstring* sb);

/* ---- 访问器 ---- */
size_t      bstring_len(const bstring* sb);
size_t      bstring_cap(const bstring* sb);
// 是否 small 模式
bool        bstring_is_small(const bstring* sb);
// 是否 no_grow 模式
bool        bstring_is_no_grow(const bstring* sb);
// 是否 borrowed 模式
bool        bstring_is_borrowed(const bstring* sb);
// 设置 no_grow 模式
void        bstring_set_no_grow(bstring* sb, bool v);
// 获取数据指针
char*       bstring_data(bstring* sb);
// 获取常量数据指针
const char* bstring_cdata(const bstring* sb);
// 获取 bstring_view
bstring_view bstring_view_create(const bstring* sb);

/* ---- 变更操作 ---- */
ssize_t bstring_append(bstring* sb, const char* s, size_t len);
ssize_t bstring_append_cstr(bstring* sb, const char* c);
ssize_t bstring_append_bstring(bstring* sb, const bstring* other);
ssize_t bstring_append_sv(bstring* sb, const bstring_view* sv);
ssize_t bstring_change_len(bstring* sb, size_t len);
// 从末尾删除 n 个字节（超过当前长度则清空）
void    bstring_pop_back(bstring* sb, size_t n);
void    bstring_clear(bstring* sb);
// 预留容量
ssize_t bstring_reserve(bstring* sb, size_t cap);

/* ---- 格式化（调用 str.h 中的 vsnprintf） ---- */
ssize_t bstring_fmt(bstring* dst, const char* fmt, ...);
ssize_t bstring_vfmt(bstring* dst, const char* fmt, va_list ap);

/* ---- bstring_view ---- */
// 从 C 字符串常量创建, 注意: 不持有 c 的所有权
bstring_view bstring_view_from_cstr(const char* c, size_t len);
// 比较两个 bstring_view 是否相等
bool bstring_view_eq(bstring_view a, bstring_view b);
// bstring_view 与 C 字符串比较（C 串以 \0 结尾）
bool bstring_view_eq_cstr(bstring_view a, const char* b);

// 便捷宏：从字符串字面量创建 bstring_view（不含末尾 \0）
#define SV(s) ((bstring_view){(s), sizeof(s) - 1})