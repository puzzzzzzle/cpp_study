//
// Created by khalidzhang on 2021/6/23.
//
extern "C" {
void void_ret_func() { return; }
int ret_int_func() {
  int i = 42;
  return i;
}
void int_arg_func(int arg) {}
struct SmallStruct {
  int value_1{};
};
struct BigStruct {
#define LONG_VALUE(num) long int value_##num{};
  LONG_VALUE(1)
  LONG_VALUE(2)
  LONG_VALUE(3)
  LONG_VALUE(4)
  LONG_VALUE(5)
  LONG_VALUE(6)
  LONG_VALUE(7)
  LONG_VALUE(8)
  LONG_VALUE(9)
  LONG_VALUE(10)
};
struct CharBuffStruct {
  char buff[1024]{};
};
#define ReturnStruct(Struct) \
  Struct return_##Struct() { \
    Struct data{};           \
    return data;             \
  }
ReturnStruct(SmallStruct) ReturnStruct(BigStruct) ReturnStruct(CharBuffStruct)
#define InputStruct(Struct) \
  void input_##Struct(Struct st) {}
    InputStruct(SmallStruct) InputStruct(BigStruct) InputStruct(CharBuffStruct)

void test_func()
{
  auto obj =  return_BigStruct();
}
void input_BigStruct_1(BigStruct st) {
  st.value_1 = 1;
}
void test_func_1()
{
  BigStruct obj{};
  input_BigStruct_1(obj);
}
}