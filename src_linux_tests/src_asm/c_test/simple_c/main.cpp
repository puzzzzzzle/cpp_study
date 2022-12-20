#include <cstdio>
extern int test();
int main(int argc, char **argv) {
  printf("first%d\n",1);
  printf("second%d\n",2);
  test();
  return 0;
}