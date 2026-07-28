#pragma once

#include <stdarg.h>

#include "types.h"

/* string_view */
struct string_view {
  const char* data;
  size_t len;
};

/* strlen */
size_t strlen(const char* s, size_t max_len);

/* snprintf: format into a fixed-size buffer, always null-terminated */
ssize_t snprintf(char* buf, size_t size, const char* fmt, ...);
ssize_t vsnprintf(char* buf, size_t size, const char* fmt, va_list ap);

/* fmt: format into a thread local static buffer (1024 bytes)*/
char* fmt(const char* fmt, ...);

/* string equality */
int streq(const char* a, const char* b);