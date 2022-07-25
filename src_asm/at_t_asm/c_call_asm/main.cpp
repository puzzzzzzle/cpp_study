//
// Created by khalidzhang on 2021/6/18.
//

extern "C"
{
void cpu_id();
void c_void_func()
{

}
void test_func();
}
int main(int argc, char* argv[])
{
  cpu_id();
  c_void_func();
  test_func();
  return 0;
}