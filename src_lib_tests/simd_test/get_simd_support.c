//
// Created by root on 6/30/25.
//

#include "get_simd_support.h"
#include <stdint.h>
#if defined(_MSC_VER)
#include <intrin.h>
#else
#include <cpuid.h>
#endif


#ifdef __cplusplus
extern "C" {
#endif

// CPUID工具函数
static void cpuid(int info[4], int function_id, int subfunction_id) {
#if defined(_MSC_VER)
  __cpuidex(info, function_id, subfunction_id);
#else
  __cpuid_count(function_id, subfunction_id, info[0], info[1], info[2], info[3]);
#endif
}

// XGETBV工具函数
static uint64_t xgetbv(uint32_t xcr) {
#if defined(_MSC_VER)
  return _xgetbv(xcr);
#elif defined(__GNUC__) || defined(__clang__)
  uint32_t eax, edx;
  __asm__ volatile (".byte 0x0f, 0x01, 0xd0" // xgetbv
                   : "=a"(eax), "=d"(edx)
                   : "c"(xcr));
  return ((uint64_t)edx << 32) | eax;
#else
  return 0;
#endif
}

// 检测SSE支持
static bool cpu_supports_sse() {
  int info[4];
  cpuid(info, 1, 0);
  return (info[3] & (1 << 25)) != 0;
}

// 检测SSE2支持
static bool cpu_supports_sse2() {
  int info[4];
  cpuid(info, 1, 0);
  return (info[3] & (1 << 26)) != 0;
}

// 检测AVX支持
static bool cpu_supports_avx() {
  int info[4];
  cpuid(info, 1, 0);
  bool os_uses_xsave_xrstore = (info[2] & (1 << 27)) != 0;
  bool avx_support = (info[2] & (1 << 28)) != 0;
  if (!os_uses_xsave_xrstore || !avx_support)
    return false;
  // 检查XGETBV
  uint64_t xcr0 = xgetbv(0);
  // XMM (bit 1) and YMM (bit 2) state enabled by OS
  return ((xcr0 & 0x6) == 0x6);
}

// 检测AVX2支持
static bool cpu_supports_avx2() {
  if (!cpu_supports_avx())
    return false;
  int info[4];
  cpuid(info, 7, 0);
  return (info[1] & (1 << 5)) != 0;
}

// 检测AVX512支持
static bool cpu_supports_avx512() {
  if (!cpu_supports_avx())
    return false;
  int info[4];
  cpuid(info, 7, 0);
  bool avx512f = (info[1] & (1 << 16)) != 0;
  if (!avx512f)
    return false;
  // 检查XGETBV: Opmask (bit 5), ZMM_Hi256 (bit 6), Hi16_ZMM (bit 7)
  uint64_t xcr0 = xgetbv(0);
  return ((xcr0 & 0xE6) == 0xE6);
}

int get_simd_max_support()
{
  if (cpu_supports_avx512())
    return SIMD_SUPPORT_AVX512;
  else if (cpu_supports_avx2())
    return SIMD_SUPPORT_AVX2;
  else if (cpu_supports_avx())
    return SIMD_SUPPORT_AVX;
  else if (cpu_supports_sse2())
    return SIMD_SUPPORT_SSE2;
  else if (cpu_supports_sse())
    return SIMD_SUPPORT_SSE;
  else
    return SIMD_SUPPORT_NONE;
}
bool is_simd_support(int simd_type)
{
  switch (simd_type)
  {
    case SIMD_SUPPORT_NONE:
      return true;
    case SIMD_SUPPORT_SSE:
      return cpu_supports_sse();
    case SIMD_SUPPORT_SSE2:
      return cpu_supports_sse2();
    case SIMD_SUPPORT_AVX:
      return cpu_supports_avx();
    case SIMD_SUPPORT_AVX2:
      return cpu_supports_avx2();
    case SIMD_SUPPORT_AVX512:
      return cpu_supports_avx512();
    default:
      return false;
  }
}
#ifdef __cplusplus
}
#endif