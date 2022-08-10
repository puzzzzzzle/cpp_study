//
// Created by tao on 19-1-17.
//
#include <immintrin.h>

#include "common_includes.h"

void avx_add() {
  __m256 a = _mm256_set_ps(8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0);
  __m256 b = _mm256_set_ps(108.0, 17.0, 16.0, 15.0, 14.0, 13.0, 12.0, 11.0);

  __m256 c = _mm256_add_ps(a, b);

  std::array<float, 8> d{};
  _mm256_storeu_ps(d.data(), c);
  std::reverse(d.begin(), d.end());
  LOG_DEBUG(d)
}
TEST(avx, 256_add) { avx_add(); }
void float_calc() {
  float f = 3.14;
  float g = f / 2;
}
void double_calc() {
//  double f = 3.14;
//  float g = f / 2;
  printf("%d,%f, %f, %d",1024,3.1,3.2,3);
}
TEST(row_call, float_div) { double_calc(); }

int main(int argc, char **argv) {
  int iRet = 0;
  iRet = beforeRun();
  if (iRet) {
    std::cerr << "init fail with " << iRet << std::endl;
  }
  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}