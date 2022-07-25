//
// Created by khalidzhang on 2021/6/23.
//
class Base {
  public:
  virtual void Hello() {}
  void Hello1() {}
};

class Child : public Base {
  public:
  void Hello() override {}
  void Hello1() { Base::Hello(); }
};
void cpp_test_func() {
  Base* ptr = new Child();
  ptr->Hello();
  ptr->Hello1();
  delete ptr;
}