extern "C" int printf(const char* format, ...);

class TestException {};
class MyClass {
  public:
  MyClass(int id) : id_(id) {
    printf("Constructing object %d\n", id_);
    if (id_ == 4) {
      throw TestException{};
    }
  }
  ~MyClass() { printf("Destructing object %d\n", id_); }

  private:
  int id_;
};

void function() {
  MyClass obj1(1);
  MyClass obj2(2);
  MyClass obj3(3);
  MyClass obj4(4);  // 这里会抛出异常
  MyClass obj5(5);
}

int main() {
  try {
    function();
  } catch (const TestException& e) {
    printf("catch exception\n");
  }
  return 0;
}