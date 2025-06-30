//
// Created by root on 6/30/25.
//
#include <immintrin.h>

#include <cstring>

#include "benchmark/benchmark.h"
#include "common_includes.h"
#include "get_simd_support.h"

// 数据规模
const int n = 1024 * 1024;
float src1[n], src2[n], out[n];
static void init_data() {
  for (int i = 0; i < n; i++) {
    src1[i] = 1.0f;
    src2[i] = 2.0f;
  }
}

#define TEST_TARGET_ADD_FUNC(func_name, simd_type)                            \
  static void BM_##func_name(benchmark::State& state) {                       \
    if (!is_simd_support(simd_type)) {                                        \
      std::string err_msg = std::string("SIMD not supported :") + #simd_type; \
      state.SkipWithError(err_msg.c_str());                                   \
    }                                                                         \
    init_data();                                                              \
    for (auto _ : state) {                                                    \
      func_name(src1, src2, out, n);                                          \
    }                                                                         \
  }                                                                           \
  BENCHMARK(BM_##func_name)
// 标量实现
void add_scalar(const float* a, const float* b, float* out, size_t n) {
  for (size_t i = 0; i < n; ++i) out[i] = a[i] + b[i];
}
TEST_TARGET_ADD_FUNC(add_scalar, SIMD_SUPPORT_NONE);

// SSE2实现（4个float一组）
void add_sse2(const float* a, const float* b, float* out, size_t n) {
  size_t i = 0;
  for (; i + 3 < n; i += 4) {
    __m128 va = _mm_loadu_ps(a + i);
    __m128 vb = _mm_loadu_ps(b + i);
    __m128 vsum = _mm_add_ps(va, vb);
    _mm_storeu_ps(out + i, vsum);
  }
  // 处理剩余
  for (; i < n; ++i) out[i] = a[i] + b[i];
}
TEST_TARGET_ADD_FUNC(add_sse2, SIMD_SUPPORT_SSE2);

// AVX2实现（8个float一组）
void add_avx2(const float* a, const float* b, float* out, size_t n) {
  size_t i = 0;
  for (; i + 7 < n; i += 8) {
    __m256 va = _mm256_loadu_ps(a + i);
    __m256 vb = _mm256_loadu_ps(b + i);
    __m256 vsum = _mm256_add_ps(va, vb);
    _mm256_storeu_ps(out + i, vsum);
  }
  // 处理剩余
  for (; i < n; ++i) out[i] = a[i] + b[i];
}
TEST_TARGET_ADD_FUNC(add_avx2, SIMD_SUPPORT_AVX2);