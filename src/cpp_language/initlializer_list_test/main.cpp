//
// Created by tao on 19-1-17.
//
#include "common_includes.h"
enum class TestEnum : unsigned  int {
  HELLO=0,
  WORLD =1
};
TEST(test_test, 1) { EXPECT_EQ(1, 1); }
TEST(vec_test, 1) {
  std::vector<double> vec{};
  vec = {1.5, 1.9, 15, 11.6, 12};
  std::cout << vec;
}
TEST(init_list_int, 1) {
  class MyClassInner {
public:
    MyClassInner(std::initializer_list<int> args) {
      int index{};
      for (auto i : args) {
        LOG_DEBUG("get one init args at:\t" << index << "\t:\t" << i)
        ++index;
      }
    }
  };
  MyClassInner temp = {3, 2, 33, 56};
}
TEST(init_void_p, 1) {
  class TypeWarper {
public:
    int int_v{};
    std::string str_v{};
    double double_v{};
    TypeWarper(int v) : int_v(v) {}
    TypeWarper(const std::string &v) : str_v(v) {}
    TypeWarper(double v) : double_v(v) {}
  };
  class MyClassInner {
public:
    MyClassInner(std::initializer_list<TypeWarper> args) {
      auto it = args.begin();
      LOG_DEBUG("get one init args :\t" << it->int_v)
      LOG_DEBUG("get one init args :\t" << (++it)->str_v)
      LOG_DEBUG("get one init args :\t" << (++it)->double_v)
    }
  };
  MyClassInner temp = {{3}, {"hello"}, {33.8}};
}
// c++17 support
// TEST(init_any_p, 1) {
//  class MyClassInner {
// public:
//    MyClassInner(std::initializer_list<std::any> args) {
//      int index{};
//      for (auto i : args) {
//        LOG_DEBUG("get one init args at:\t" << index << "\t:\t" << i)
//        ++index;
//      }
//    }
//  };
//  MyClassInner temp = {3, "hello", 33.8};
//}

TEST(init_tuple_1, 1) {
  class MyClassInner {
public:
    MyClassInner(std::tuple<int, std::string, double> args) {
      int int_v{};
      std::string str_v{};
      double double_v{};
      std::tie(int_v, str_v, double_v) = args;
      LOG_DEBUG("get one init args :\t" << int_v)
      LOG_DEBUG("get one init args :\t" << str_v)
      LOG_DEBUG("get one init args :\t" << double_v)
    }
  };
  MyClassInner temp = {std::make_tuple(3, "hello", 33.6)};
}
TEST(init_constor_1, 1) {
  class MyClassInner {
public:
    MyClassInner(int int_v, std::string str_v, double double_v) {
      LOG_DEBUG("get one init args :\t" << int_v)
      LOG_DEBUG("get one init args :\t" << str_v)
      LOG_DEBUG("get one init args :\t" << double_v)
    }
  };
  MyClassInner temp = {3, "hello", 33.6};
}

class NestedInteger final {
  public:
  NestedInteger(int i) : type_(INT), val_int_(i) {}
  NestedInteger(const std::initializer_list<int>& ni) : type_(VECTOR) {
    for (auto it = ni.begin(); it != ni.end(); it++) {
      val_vec_.template emplace_back(*it);
    }
  }
  NestedInteger(const std::initializer_list<std::initializer_list<int>> & ni) : type_(VECTOR) {
    for (auto it = ni.begin(); it != ni.end(); it++) {
      val_vec_.template emplace_back(*it);
    }
  }
  template <class T>
  NestedInteger(const std::initializer_list<T>& ni) : type_(VECTOR) {
    for (auto it = ni.begin(); it != ni.end(); it++) {
      val_vec_.template emplace_back(*it);
    }
  }

  private:
  enum { INT, VECTOR } type_{};
  int val_int_;
  std::vector<NestedInteger> val_vec_{};
};

TEST(type1, type1) {
  NestedInteger ni1{1};
  NestedInteger ni2{1, 2, 3};
  NestedInteger ni3{{1}, 2, 3};
  NestedInteger ni4{{1, 2, 3}};
  std::initializer_list<std::initializer_list<int>> t = {{1, 2, 3}};
  std::initializer_list<std::initializer_list<int>> t1 = {{1, 2, 3},
                                                          {4, 5, 6, 7}};
  std::initializer_list<std::initializer_list<std::initializer_list<int>>> t2 =
      {{{1, 2, 3}, {4, 5, 6, 7}}};

  NestedInteger ni5(t);
  NestedInteger ni6(t1);
  NestedInteger ni7(t2);

  {
    NestedInteger ni8({{1, 2, 3}, {4, 5, 6, 7}}); // error without NestedInteger(const std::initializer_list<std::initializer_list<int>> & ni)
    NestedInteger ni9({{{1, 2, 3}, {4, 5, 6, 7}}});  // error without NestedInteger(const std::initializer_list<std::initializer_list<int>> & ni)
  }

  {
    NestedInteger ni8((std::initializer_list<std::initializer_list<int>>){
        {1, 2, 3}, {4, 5, 6, 7}});
    NestedInteger ni9((std::initializer_list<
                       std::initializer_list<std::initializer_list<int>>>){
        {{1, 2, 3}, {4, 5, 6, 7}}});
  }
  {
    NestedInteger ni8({
        {{1, 2, 3}, {1, 2, 3}, {1, 2, 3}}, {{1, 2, 3}, {1, 2, 3}, {1, 2, 3}}});  // ERROR without <<<int>>>
    NestedInteger ni9((std::initializer_list<
                       std::initializer_list<std::initializer_list<int>>>){
        {{1, 2, 3}, {4, 5, 6, 7}}});
  }
  //    NestedInteger ni6{{{{1, 2, 3}, {4, 5, 6, 7}}}};
}

int main(int argc, char **argv) {
    class MyClassInner {
public:
    MyClassInner(int int_v, std::string str_v, double double_v) {
      LOG_DEBUG("get one init args :\t" << int_v)
      LOG_DEBUG("get one init args :\t" << str_v)
      LOG_DEBUG("get one init args :\t" << double_v)
    }
  };
  MyClassInner temp = {3, "hello", 33.6};
  int iRet = 0;
  iRet = beforeRun();
  if (iRet) {
    std::cerr << "init fail with " << iRet << std::endl;
  }
  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}