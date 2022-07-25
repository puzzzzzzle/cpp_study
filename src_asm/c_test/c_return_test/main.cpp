int ret_int(int val) { return val; }
// size : 120
struct MyStruct {
  int i_val{}; // 4
  // 4
  double d_val{}; // 8
  char buff[100]{}; // 100
  // 4
}; // 120
MyStruct ret_struct(MyStruct in) { return in; }
MyStruct ret_struct_v() { return MyStruct{}; }

int main(int argc, char **argv) {
  asm("nop" /*main init*/);
  asm("nop;" /*start call ret_int*/);
  int i_ret = ret_int(42);
  asm("nop;" /*start call ret_struct*/);
  MyStruct st{};
  auto r_st = ret_struct(st);
  asm("nop;" /*start call ret_struct_v*/);
  auto r_st1 = ret_struct_v();
  asm("nop;" /* start return main*/);
  return 0;
}