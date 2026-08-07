#include "str.h"

#include <stdarg.h>

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

    char*   dst = buf;
    char*   end = buf + size - 1;
    ssize_t n   = 0;

    #define FMT_PUTC(c)  do { if (dst < end) *dst++ = (c); n++; } while (0)
    #define FMT_VARGS(t) va_arg(ap, t)
    #define FMT_DONE     fmt_done
    #include "fmt_core.h"
    #undef FMT_PUTC
    #undef FMT_VARGS
    #undef FMT_DONE

fmt_done:
    *dst = '\0';
    return n;
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
