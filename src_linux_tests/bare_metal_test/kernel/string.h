#pragma once
#include "types.h"

/**
 * @brief 动态字符串实现
 */
typedef struct {
  const char* data;
  size_t len;
} string_view;

#define STRING_BUFFER_INLINE_CAP 32
// typedef struct {
//   size_t cap;
//   size_t len;
//   union {
//     char* heap_data;
//     char inline_data[STRING_BUFFER_INLINE_CAP]; /*
//     内联存储，避免小字符串频繁堆分配 */
//   };
// } string_buffer;

typedef struct {
  // 最高位标记为1表示使用内联存储
  size_t len;
  struct heap_string {
    size_t cap;
    char* data;
  };
  struct inline_string {
    char data[STRING_BUFFER_INLINE_CAP];
  };
  union {
    struct heap_string heap_string;
    struct inline_string inline_string;
  };
} string_buffer;
string_buffer string_buffer_create(size_t cap);
void string_buffer_destroy(string_buffer* sb);
ssize_t string_buffer_append(string_buffer* sb, const char* s, size_t len);
ssize_t string_buffer_append_string(string_buffer* sb, const string_view* sv);
ssize_t string_buffer_fmt(string_buffer* sb, const char* fmt, ...);

string_view string_view_create(const char* s, size_t len);