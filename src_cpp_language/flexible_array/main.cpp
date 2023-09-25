#include "common_includes.h"
extern "C" {
typedef struct {
  int length;
  int array[];
} FlexArray;
}

TEST(test_test, 1) {
  int n = 5;  // 我们希望的数组长度
  FlexArray* fa = (FlexArray*)malloc(sizeof(FlexArray) + sizeof(int) * n);
  fa->length = n;

  for (int i = 0; i < n; i++) {
    fa->array[i] = i;
  }

  for (int i = 0; i < n; i++) {
    printf("%d ", fa->array[i]);
  }

  free(fa);
}

int main(int argc, char** argv) {
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  sleep(1);
  return iRet;
}