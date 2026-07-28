#pragma once

#include <stdarg.h>

#include "types.h"

/* snprintf: format into a fixed-size buffer, always null-terminated */
ssize_t snprintf(char* buf, size_t size, const char* fmt, ...);
ssize_t vsnprintf(char* buf, size_t size, const char* fmt, va_list ap);

/* fmt: format into a thread local static buffer (1024 bytes)*/
char* fmt(const char* fmt, ...);

/* unsafe: strlen */
size_t strlen(const char* s);

/* unsafe: string equality */
int streq(const char* a, const char* b);