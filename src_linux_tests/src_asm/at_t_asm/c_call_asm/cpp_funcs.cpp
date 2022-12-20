//
// Created by khalidzhang on 2021/6/23.
//
void test_cpp_func() {
  int i = 4;
  int v[100];
  auto f = [&](int t) { v[1] = t; };
  f(5);

  auto g = [&v](int t) { v[2] = t; };
  g(6);

  auto h = [=](int t) {};
  h(7);

  auto l = []() {};
  l();
}