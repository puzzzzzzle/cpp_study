#include <immintrin.h>

#include "common_includes.h"

// 数据规模
static int init_data(float src1[], float src2[], size_t n) {
  for (int i = 0; i < n; i++) {
    src1[i] = rand() / float(RAND_MAX);
    src2[i] = rand() / float(RAND_MAX);
  }
  return 0;
}

// 标量实现
__attribute__((target("default"))) void add(const float* __restrict__ a,
                                            const float* __restrict__ b,
                                            float* __restrict__ out, size_t n) {
  LOG_INFO("default")
  for (size_t i = 0; i < n; ++i) {
    out[i] = a[i] + b[i];
  }
}

// SSE2实现（4个float一组）
__attribute__((target("sse2"))) void add(const float* __restrict__ a,
                                         const float* __restrict__ b,
                                         float* __restrict__ out, size_t n) {
  LOG_INFO("sse2")
  size_t i = 0;
  for (; i + 3 < n; i += 4) {
    __m128 va = _mm_loadu_ps(a + i);
    __m128 vb = _mm_loadu_ps(b + i);
    __m128 vsum = _mm_add_ps(va, vb);
    _mm_storeu_ps(out + i, vsum);
  }
  // 处理剩余
  for (; i < n; ++i) {
    out[i] = a[i] + b[i];
  }
}

// AVX2实现（8个float一组）
__attribute__((target("avx2"))) void add(const float* __restrict__ a,
                                         const float* __restrict__ b,
                                         float* __restrict__ out, size_t n) {
  LOG_INFO("avx2")
  size_t i = 0;
  for (; i + 7 < n; i += 8) {
    __m256 va = _mm256_loadu_ps(a + i);
    __m256 vb = _mm256_loadu_ps(b + i);
    __m256 vsum = _mm256_add_ps(va, vb);
    _mm256_storeu_ps(out + i, vsum);
  }
  // 处理剩余
  for (; i < n; ++i) {
    out[i] = a[i] + b[i];
  }
}

__attribute__((target("avx512f"))) void add(const float* __restrict__ a,
                                            const float* __restrict__ b,
                                            float* __restrict__ out, size_t n) {
  LOG_INFO("avx512")
  size_t i = 0;
  for (; i + 15 < n; i += 16) {
    __m512 va = _mm512_loadu_ps(a + i);
    __m512 vb = _mm512_loadu_ps(b + i);
    __m512 vsum = _mm512_add_ps(va, vb);
    _mm512_storeu_ps(out + i, vsum);
  }
  // 处理剩余
  for (; i < n; ++i) {
    out[i] = a[i] + b[i];
  }
}
TEST(test_test, 1) {
  // 使用堆变量, 防止编译器过渡优化
  const int n = 1024 * 1024;
  float* src1 = static_cast<float*>(std::aligned_alloc(16, n * sizeof(float)));
  float* src2 = static_cast<float*>(std::aligned_alloc(16, n * sizeof(float)));
  float* out = static_cast<float*>(std::aligned_alloc(16, n * sizeof(float)));
  init_data(src1, src2, n);
  add(src1, src2, out, n);
}

int main(int argc, char** argv) {
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}