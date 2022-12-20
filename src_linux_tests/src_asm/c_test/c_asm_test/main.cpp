
#include <cstdio>
class Unuse{
  public:
  ~Unuse(){
    puts("~Unuse");
  }
};
int main(int argc, char **argv) {
  {
    Unuse unuse{};
    puts("s");
    int i =42;
    printf("%d\n",i);
    char temp[20];
    temp[10] = 'c';
  }
  puts("end");
  return 0;
}