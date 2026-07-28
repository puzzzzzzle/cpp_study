#include "str.h"

#include <stdarg.h>

size_t strlen(const char* s)
{
    size_t len = 0;
    while (*s++)
        len++;
    return len;
}

/*
 * vsnprintf — core formatting engine (takes va_list directly).
 * Supported: %s %d %u %x %c %%
 * Always null-terminates. Returns chars written (excl. '\0'),
 * or negative on error.
 */
ssize_t vsnprintf(char* buf, size_t size, const char* fmt, va_list ap)
{
    if (!buf || !size)
        return -1;

    char*       dst  = buf;
    char*       end  = buf + size - 1;       /* reserve space for '\0' */
    ssize_t     n    = 0;

#define PUT(c)                        \
    do {                              \
        if (dst < end) *dst++ = (c);  \
        n++;                          \
    } while (0)

    for (; *fmt; fmt++) {
        if (*fmt != '%') {
            PUT(*fmt);
            continue;
        }
        fmt++;   /* skip '%' */
        switch (*fmt) {
        case '\0': goto done;
        case '%':  PUT('%'); break;

        case 'c': {
            char c = (char)va_arg(ap, int);
            PUT(c);
            break;
        }

        case 's': {
            const char* s = va_arg(ap, const char*);
            if (!s) s = "(null)";
            while (*s) PUT(*s++);
            break;
        }

        case 'd': {
            int val = va_arg(ap, int);
            if (val < 0) { PUT('-'); val = -val; }
            char rev[12]; int i = 0;
            do { rev[i++] = (char)('0' + (val % 10)); val /= 10; } while (val);
            while (i--) PUT(rev[i]);
            break;
        }

        case 'u': {
            u32 val = va_arg(ap, u32);
            char rev[12]; int i = 0;
            do { rev[i++] = (char)('0' + (val % 10)); val /= 10; } while (val);
            while (i--) PUT(rev[i]);
            break;
        }

        case 'x': {
            u32 val = va_arg(ap, u32);
            char rev[12]; int i = 0;
            do {
                int d = val & 0xF;
                rev[i++] = (char)(d < 10 ? '0' + d : 'a' + d - 10);
            } while (val >>= 4);
            while (i--) PUT(rev[i]);
            break;
        }

        default:
            PUT('?');
            break;
        }
    }

done:
    *dst = '\0';
    return n;

#undef PUT
}

/*
 * snprintf — convenience wrapper around vsnprintf.
 */
ssize_t snprintf(char* buf, size_t size, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    ssize_t n = vsnprintf(buf, size, fmt, args);
    va_end(args);
    return n;
}

/*
 * fmt — format into a static buffer and return it.
 * Not re-entrant; caller should consume or copy before next call.
 */
char* fmt(const char* fmt, ...)
{
    static char buf[1024];

    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);

    return buf;
}

int streq(const char* a, const char* b) {
  while (*a && *a == *b) {
    a++;
    b++;
  }
  return *a == *b;
}
