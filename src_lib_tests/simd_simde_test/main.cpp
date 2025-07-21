#include <stdio.h>
#include <simde/x86/sse.h> // 包含SIMDe的SSE头文件

int main() {
  // 定义两个4元素float向量
  simde__m128 a = simde_mm_set_ps(4.0f, 3.0f, 2.0f, 1.0f);
  simde__m128 b = simde_mm_set_ps(8.0f, 7.0f, 6.0f, 5.0f);

  // 向量加法
  simde__m128 c = simde_mm_add_ps(a, b);

  // 取出结果
  float result[4];
  simde_mm_storeu_ps(result, c);

  // 打印结果
  printf("Result: %f %f %f %f\n", result[0], result[1], result[2], result[3]);
  return 0;
}