#pragma once
#include "types.h"

/**
 * @brief 动态字符串实现
 */
typedef struct {
  const char* data;
  size_t len;
} string_view;

typedef struct {
  char* data;
  size_t len;
  size_t cap;
} string_buffer;

string_buffer string_buffer_create(size_t cap);
void string_buffer_destroy(string_buffer* sb);
ssize_t string_buffer_append(string_buffer* sb, const char* s, size_t len);
ssize_t string_buffer_append_string(string_buffer* sb, const string_view* sv);
ssize_t string_buffer_fmt(string_buffer* sb, const char* fmt, ...);

string_view string_view_create(const char* s, size_t len);