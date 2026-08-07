#include "string.h"
#include "mem_operate_core.h"


/* -------------------------------------------------------
 * 外部分配器 —— 在你的 kernel/memory.c 中实现
 * -----------------------------------------------------*/
extern void* kmalloc(size_t size);
extern void  kfree(void* ptr);


/* -------------------------------------------------------
 * 内部辅助函数
 * -----------------------------------------------------*/
/*
 * Byte[23]（即 small.flags）的位布局：
 *
 *   bit7  bit6  bit5  bit4..0
 *   ────  ────  ────  ──────
 *   MSB   NG   (空)   rem
 *
 *   MSB=0 → Small:  bit6=no_grow, bit4~0=23-len（剩余容量，最大23）
 *   MSB=1 → Medium/Large: no_grow 存在 heap_flags bit0
 *          Medium:  flags=0x80(固定), capacity 在 med_cap(u32, 24~4294967295)
 *          Large:   flags=0xFF，真 cap 在堆头
 */
#define FLAG_SMALL_MASK  0x1Fu   /* 掩掉 MSB+NG+bit5 得到 Small 剩余容量 */
#define FLAG_MSB         0x80u   /* Byte 最高位（bit7），0=Small, 1=堆     */
#define FLAG_LARGE       0xFFu   /* 全字节 0xFF，唯一标识 Large 模式       */
#define FLAG_NO_GROW     0x40u   /* bit6(Small)/byte[16]bit0(Heap)        */
#define FLAG_MEDIUM_MAX  0xFFFFFFFFu  /* u32 最大值，Medium 最大 capacity      */
#define HEAP_FLAG_NO_GROW 0x01u  /* heap_flags bit0: 禁止自动扩容           */
#define HEAP_FLAG_BORROWED 0x02u /* heap_flags bit1: 外部借出buf,销毁时不释放 */

static inline bool is_small(u8 flags)
{
    return (flags & FLAG_MSB) == 0;
}

static inline bool is_large(const bstring* sb)
{
    return sb->u.small.flags == FLAG_LARGE;
}

/* 获取任意模式下字符数据的只读指针 */
static inline const char* get_data(const bstring* sb)
{
    if (is_small(sb->u.small.flags))
        return sb->u.small.data;
    if (is_large(sb))
        return sb->u.heap.ptr + sizeof(size_t);  /* 跳过堆头 */
    return sb->u.heap.ptr;                        /* Medium: ptr 即数据指针 */
}

static inline char* get_data_mut(bstring* sb)
{
    return (char*)get_data(sb);
}

/* no_grow: Small 存在 small.flags bit6，Medium/Large 存在 heap_flags bit0 */
static inline bool get_no_grow(const bstring* sb)
{
    if (is_small(sb->u.small.flags))
        return (sb->u.small.flags & FLAG_NO_GROW) != 0;
    return (sb->u.heap.heap_flags & HEAP_FLAG_NO_GROW) != 0;
}

static inline void set_no_grow(bstring* sb, bool v)
{
    if (is_small(sb->u.small.flags)) {
        if (v) sb->u.small.flags |= FLAG_NO_GROW;
        else   sb->u.small.flags &= ~FLAG_NO_GROW;
    } else {
        if (v) sb->u.heap.heap_flags |= HEAP_FLAG_NO_GROW;
        else   sb->u.heap.heap_flags &= ~HEAP_FLAG_NO_GROW;
    }
}


/* 不做检查的内部版本：调用方保证 sb/s 有效、len>0、容量足够 */
static inline void append_unsafe(bstring* sb, const char* s, size_t len)
{
    size_t old_len = bstring_len(sb);
    size_t need    = old_len + len;

    char* dst = get_data_mut(sb) + old_len;
    byte_copy(dst, s, len);
    dst[len] = '\0';

    if (is_small(sb->u.small.flags))
        sb->u.small.flags = (u8)(BSTRING_INLINE_CAP - need);
    else
        sb->u.heap.size = need;
}

/*
 * grow_heap — 创建新 bstring（init + append），转移所有权到 sb，释放旧内存。
 * 复用 bstring_init / append_unsafe 消除重复的分配/拷贝/字段设置逻辑。
 */
static inline ssize_t grow_heap(bstring* sb, size_t old_len, size_t needed)
{
    if (get_no_grow(sb)) return -1;               /* 禁止扩容，统一在此拦截 */

    size_t old_cap = bstring_cap(sb);
    size_t new_cap = old_cap * 2;
    if (new_cap < needed)
        new_cap = needed;

    const char* old_data = get_data(sb);

    /* 用 init + append 创建新 bstring，复用现有的分配/拷贝逻辑 */
    bstring tmp;
    if (bstring_init(&tmp, new_cap) < 0)
        return -1;
    append_unsafe(&tmp, old_data, old_len);       /* 不会递归 grow：new_cap >= old_len */

    /* 销毁旧内存（内部判断 small/borrowed），然后转移所有权 */
    bstring_destroy(sb);
    *sb = tmp;
    return (ssize_t)new_cap;
}

/* -------------------------------------------------------
 * 生命周期
 * -----------------------------------------------------*/

ssize_t bstring_init(bstring* sb, size_t cap)
{
    if (!sb) return -1;

    if (cap <= BSTRING_INLINE_CAP) {
        sb->u.small.flags  = (u8)BSTRING_INLINE_CAP;   /* len=0, 剩余容量=23 */
        sb->u.small.data[0] = '\0';
        return BSTRING_INLINE_CAP;
    }

    if (cap <= FLAG_MEDIUM_MAX) {
        size_t alloc = cap;
        char* p = (char*)kmalloc(alloc + 1);         /* +1 给 \0 */
        if (!p) return -1;
        p[0] = '\0';
        sb->u.heap.ptr  = p;
        sb->u.heap.size = 0;
        sb->u.small.flags = FLAG_MSB;                /* Medium 固定标记 */
        sb->u.heap.med_cap = (u32)alloc;             /* 容量存 med_cap */
        sb->u.heap.heap_flags = 0;                   /* 清零 heap_flags */
        return (ssize_t)alloc;
    }

    /* Large */
    size_t alloc = cap + sizeof(size_t) + 1;         /* +1 给 \0 */
    char* p = (char*)kmalloc(alloc);
    if (!p) return -1;
    *(size_t*)p = cap;                               /* 堆头存 capacity */
    p[sizeof(size_t)] = '\0';
    sb->u.heap.ptr  = p;
    sb->u.heap.size = 0;
    sb->u.small.flags = 0xFFu;                         /* Large 标记 */
    sb->u.heap.heap_flags = 0;                      /* 清零 heap_flags */
    return (ssize_t)cap;
}

void bstring_destroy(bstring* sb)
{
    if (!sb) return;
    if (!is_small(sb->u.small.flags)
        && !(sb->u.heap.heap_flags & HEAP_FLAG_BORROWED))
        kfree(sb->u.heap.ptr);
}

ssize_t bstring_init_from_buffer(bstring* sb, char* buf, size_t cap)
{
    if (!sb || !buf || cap == 0) return -1;

    sb->u.heap.ptr  = buf;
    sb->u.heap.size = 0;
    sb->u.small.flags    = FLAG_MSB;                              /* Medium 固定标记 */
    sb->u.heap.med_cap   = (u32)cap;                              /* 容量存 med_cap */
    sb->u.heap.heap_flags = HEAP_FLAG_NO_GROW | HEAP_FLAG_BORROWED; /* 不可扩容 + 不释放 */
    buf[0] = '\0';
    return (ssize_t)cap;
}

bstring bstring_clone(const bstring* sb)
{
    bstring dst;
    if (!sb) {
        bstring_init(&dst, 0);
        return dst;
    }

    if (is_small(sb->u.small.flags)) {
        /* Small: 24 字节结构体直接按值拷贝，data + flags 全在里面 */
        dst = *sb;
        return dst;
    }

    /* Heap (Medium / Large): 独立分配 + 拷贝 */
    size_t len = bstring_len(sb);
    size_t cap = bstring_cap(sb);
    if (bstring_init(&dst, cap) < 0) {
        bstring_init(&dst, 0);
        return dst;
    }
    append_unsafe(&dst, get_data(sb), len);    return dst;
}

/* -------------------------------------------------------
 * 访问器
 * -----------------------------------------------------*/

size_t bstring_len(const bstring* sb)
{
    if (!sb) return 0;
    if (is_small(sb->u.small.flags))
        return BSTRING_INLINE_CAP - (sb->u.small.flags & FLAG_SMALL_MASK);
    return sb->u.heap.size;
}

size_t bstring_cap(const bstring* sb)
{
    if (!sb) return 0;
    u8 f = sb->u.small.flags;
    if (is_small(f))
        return BSTRING_INLINE_CAP;
    if (is_large(sb))
        return *(size_t*)sb->u.heap.ptr;   /* 堆头取 capacity */
    return (size_t)sb->u.heap.med_cap;              /* Medium: capacity 在 med_cap */
}

bool bstring_is_small(const bstring* sb)
{
    return sb && is_small(sb->u.small.flags);
}

bool bstring_is_no_grow(const bstring* sb)
{
    return sb && get_no_grow(sb);
}

bool bstring_is_borrowed(const bstring* sb)
{
    return sb && !is_small(sb->u.small.flags)
           && (sb->u.heap.heap_flags & HEAP_FLAG_BORROWED);
}

void bstring_set_no_grow(bstring* sb, bool v)
{
    if (sb) set_no_grow(sb, v);
}

char* bstring_data(bstring* sb)
{
    return sb ? get_data_mut(sb) : NULL;
}

const char* bstring_cdata(const bstring* sb)
{
    return sb ? get_data(sb) : NULL;
}

bstring_view bstring_view_create(const bstring* sb)
{
    if (!sb) {
        bstring_view empty = {NULL, 0};
        return empty;
    }
    bstring_view sv = {get_data(sb), bstring_len(sb)};
    return sv;
}

bstring_view bstring_view_from_cstr(const char* c, size_t len)
{
    bstring_view sv = {c, len};
    return sv;
}

bool bstring_view_eq(bstring_view a, bstring_view b)
{
    if (a.len != b.len) return false;
    for (size_t i = 0; i < a.len; i++)
        if (a.data[i] != b.data[i]) return false;
    return true;
}

bool bstring_view_eq_cstr(bstring_view a, const char* b)
{
    for (size_t i = 0; i < a.len; i++) {
        if (b[i] == '\0' || a.data[i] != b[i]) return false;
    }
    return b[a.len] == '\0';
}

/* -------------------------------------------------------
 * 变更操作
 * -----------------------------------------------------*/

ssize_t bstring_append(bstring* sb, const char* s, size_t len)
{
    if (!sb || !s) return -1;
    if (len == 0) return (ssize_t)bstring_len(sb);

    size_t old_len = bstring_len(sb);
    size_t need    = old_len + len;

    if (need > bstring_cap(sb)) {
        ssize_t rc = grow_heap(sb, old_len, need);
        if (rc < 0) return -1;
    }

    append_unsafe(sb, s, len);
    return (ssize_t)need;
}

ssize_t bstring_append_cstr(bstring* sb, const char* c)
{
    if (!sb || !c) return -1;
    return bstring_append(sb, c, strlen(c));
}

ssize_t bstring_append_bstring(bstring* sb, const bstring* other)
{
    if (!sb || !other) return -1;
    return bstring_append(sb, get_data(other), bstring_len(other));
}

ssize_t bstring_append_sv(bstring* sb, const bstring_view* sv)
{
    if (!sb || !sv) return -1;
    return bstring_append(sb, sv->data, sv->len);
}

ssize_t bstring_change_len(bstring* sb, size_t len)
{
    if (!sb) return -1;
    if (len > bstring_cap(sb)) return -1;

    if (is_small(sb->u.small.flags)) {
        sb->u.small.flags  = (u8)(BSTRING_INLINE_CAP - len);
        sb->u.small.data[len] = '\0';
    } else {
        sb->u.heap.size = len;
        get_data_mut(sb)[len] = '\0';
    }
    return (ssize_t)len;
}

void bstring_pop_back(bstring* sb, size_t n)
{
    if (!sb) return;
    size_t len = bstring_len(sb);
    if (n > len) n = len;
    if (n > 0) bstring_change_len(sb, len - n);
}

void bstring_clear(bstring* sb)
{
    if (!sb) return;
    if (is_small(sb->u.small.flags)) {
        sb->u.small.flags  = (u8)BSTRING_INLINE_CAP;
        sb->u.small.data[0] = '\0';
    } else {
        sb->u.heap.size = 0;
        get_data_mut(sb)[0] = '\0';
    }
}

ssize_t bstring_reserve(bstring* sb, size_t cap)
{
    if (!sb) return -1;
    size_t cur_cap = bstring_cap(sb);
    if (cap <= cur_cap) return (ssize_t)cur_cap;
    return grow_heap(sb, bstring_len(sb), cap);
}

/* -------------------------------------------------------
 * 格式化
 * -----------------------------------------------------*/

ssize_t bstring_vfmt(bstring* dst, const char* fmt, va_list ap)
{
    if (!dst || !fmt) return -1;

    bstring* _sb  = dst;
    size_t   _pos = bstring_len(dst);
    size_t   _cap = bstring_cap(dst);
    ssize_t  n    = 0;

    #define FMT_PUTC(c)  do {                                 \
        if (_pos >= _cap) {                                   \
            ssize_t _rc = grow_heap(_sb, _pos, _pos + 1);     \
            if (_rc < 0) { n = -1; goto fmt_done; }           \
            _cap = (size_t)_rc;                               \
        }                                                     \
        get_data_mut(_sb)[_pos++] = (char)(c);                 \
        n++;                                                  \
    } while (0)
    #define FMT_VARGS(t) va_arg(ap, t)
    #define FMT_DONE     fmt_done
    #include "fmt_core.h"
    #undef FMT_PUTC
    #undef FMT_VARGS
    #undef FMT_DONE

fmt_done:
    if (n >= 0) {
        bstring_change_len(_sb, _pos);
        get_data_mut(_sb)[_pos] = '\0';
    }
    return n;
}

ssize_t bstring_fmt(bstring* dst, const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    ssize_t n = bstring_vfmt(dst, fmt, ap);
    va_end(ap);
    return n;
}