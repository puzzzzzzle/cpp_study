/*
 * fmt_core.h — 格式化核心宏（X-Macro 模式）
 *
 * 在 include 前必须定义以下三个宏：
 *
 *   FMT_PUTC(c)    输出一个字符（会展开多次，需处理副作用）
 *   FMT_VARGS(t)   获取下一个可变参数，如 va_arg(ap, t)
 *   FMT_DONE       循环结束 goto 标签名
 *
 * 使用后必须依次 #undef 这三个宏。
 *
 * 示例:
 *   #define FMT_PUTC(c) do { if (dst < end) *dst++ = (c); n++; } while(0)
 *   #define FMT_VARGS(t) va_arg(ap, t)
 *   #define FMT_DONE done
 *   #include "fmt_core.h"
 *   #undef FMT_PUTC
 *   #undef FMT_VARGS
 *   #undef FMT_DONE
 * done:
 *   *dst = '\0';
 */

#include "types.h"

#ifndef FMT_PUTC
#error "must define FMT_PUTC(c) before including fmt_core.h"
#endif
#ifndef FMT_VARGS
#error "must define FMT_VARGS(t) before including fmt_core.h"
#endif
#ifndef FMT_DONE
#error "must define FMT_DONE before including fmt_core.h"
#endif

/* ---- 格式化循环 ---- */

for (; *fmt; fmt++) {
    if (*fmt != '%') {
        FMT_PUTC(*fmt);
        continue;
    }
    fmt++;
    switch (*fmt) {
    case '\0': goto FMT_DONE;
    case '%':  FMT_PUTC('%'); break;

    case 'c': {
        char _c = (char)FMT_VARGS(int);
        FMT_PUTC(_c);
        break;
    }

    case 's': {
        const char* _s = FMT_VARGS(const char*);
        if (!_s) _s = "(null)";
        while (*_s) FMT_PUTC(*_s++);
        break;
    }

    case 'd': {
        int _v = FMT_VARGS(int);
        if (_v < 0) { FMT_PUTC('-'); _v = -_v; }
        char _r[12]; int _i = 0;
        do { _r[_i++] = (char)('0' + (_v % 10)); _v /= 10; } while (_v);
        while (_i--) FMT_PUTC(_r[_i]);
        break;
    }

    case 'u': {
        u32 _v = FMT_VARGS(u32);
        char _r[12]; int _i = 0;
        do { _r[_i++] = (char)('0' + (_v % 10)); _v /= 10; } while (_v);
        while (_i--) FMT_PUTC(_r[_i]);
        break;
    }

    case 'x': {
        u32 _v = FMT_VARGS(u32);
        char _r[12]; int _i = 0;
        do {
            int _d = _v & 0xF;
            _r[_i++] = (char)(_d < 10 ? '0' + _d : 'a' + _d - 10);
        } while (_v >>= 4);
        while (_i--) FMT_PUTC(_r[_i]);
        break;
    }

    default:
        FMT_PUTC('?');
        break;
    }
}
