//
// Created by root on 6/30/25.
//
#include <immintrin.h>

#include <cstring>

#include "benchmark/benchmark.h"
#include "common_includes.h"
#include "get_simd_support.h"

// 数据规模
static int init_data(float src1[], float src2[], size_t n) {
  for (int i = 0; i < n; i++) {
    src1[i] = rand() / float(RAND_MAX);
    src2[i] = rand() / float(RAND_MAX);
  }
  return 0;
}
// 使用堆变量, 防止编译器过渡优化
const int n = 1024 * 1024;
float* src1 = static_cast<float*>(std::aligned_alloc(16, n * sizeof(float)));
float* src2 = static_cast<float*>(std::aligned_alloc(16, n * sizeof(float)));
float* out = static_cast<float*>(std::aligned_alloc(16, n * sizeof(float)));
int init = init_data(src1, src2, n);

#define TEST_TARGET_ADD_FUNC(func_name, simd_type)                            \
  static void BM_##func_name(benchmark::State& state) {                       \
    if (!is_simd_support(simd_type)) {                                        \
      std::string err_msg = std::string("SIMD not supported :") + #simd_type; \
      state.SkipWithError(err_msg.c_str());                                   \
    }                                                                         \
    for (auto _ : state) {                                                    \
      func_name(src1, src2, out, n);                                          \
    }                                                                         \
  }                                                                           \
  BENCHMARK(BM_##func_name)
// 标量实现
void add_scalar_restrict(const float* __restrict__ a,
                         const float* __restrict__ b, float* __restrict__ out,
                         size_t n) {
  for (size_t i = 0; i < n; ++i) out[i] = a[i] + b[i];
}
TEST_TARGET_ADD_FUNC(add_scalar_restrict, SIMD_SUPPORT_NONE);

void add_scalar_normal(const float* a, const float* b, float* out, size_t n) {
  for (size_t i = 0; i < n; ++i) out[i] = a[i] + b[i];
}
TEST_TARGET_ADD_FUNC(add_scalar_normal, SIMD_SUPPORT_NONE);

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

void add_sse2_aligned(const float* a, const float* b, float* out, size_t n) {
  // 假设a, b, out都16字节对齐
  size_t i = 0;
  for (; i + 3 < n; i += 4) {
    __m128 va = _mm_load_ps(a + i);  // 对齐加载
    __m128 vb = _mm_load_ps(b + i);
    __m128 vo = _mm_add_ps(va, vb);
    _mm_store_ps(out + i, vo);  // 对齐存储
  }
  for (; i < n; ++i) {
    out[i] = a[i] + b[i];
  }
}
TEST_TARGET_ADD_FUNC(add_sse2_aligned, SIMD_SUPPORT_SSE2);

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

// 关闭自动向量化优化, 对比下效果
// -o3 -march=native -fno-tree-vectorize
//--------------------------------------------------------
// Benchmark              Time             CPU   Iterations
//--------------------------------------------------------
// BM_add_scalar     501072 ns       501066 ns         1000
// BM_add_sse2       229486 ns       229483 ns         3011
// BM_add_avx2       227688 ns       227685 ns         3097

// o3 的自动向量化优化还行
// -o3 -march=native
//--------------------------------------------------------
// Benchmark              Time             CPU   Iterations
//--------------------------------------------------------
// BM_add_scalar     240029 ns       240016 ns         2472
// BM_add_sse2       227653 ns       227643 ns         3076
// BM_add_avx2       229425 ns       229406 ns         3085