//
// Created by root on 6/30/25.
//

#pragma once
#ifdef __cplusplus
extern "C" {
#endif
enum {
  SIMD_SUPPORT_NONE=0,
  SIMD_SUPPORT_SSE,
  SIMD_SUPPORT_SSE2,
  SIMD_SUPPORT_AVX,
  SIMD_SUPPORT_AVX2,
  SIMD_SUPPORT_AVX512,
};
int get_simd_max_support();
bool is_simd_support(int simd_type);

#ifdef __cplusplus
}
#endif