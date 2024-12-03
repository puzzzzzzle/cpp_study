#include <unifex/detail/prologue.hpp>

#include "common_includes.h"

class TestService {
  public:
  int Req(int v1) {};
};
class TestService1 {
  public:
  int Req(int v1, double v2) {};
  int Req(char *v1) {}
};
template <class T>
class TemplateCall {
  public:
  T service_;
  template <class ReqFunction, class... Args>
  int Call(ReqFunction req, Args... reqArgs) {
    return (service_.*req)(reqArgs...);
  }
};
int main(int argc, char **argv) {
  TemplateCall<TestService> t;
  t.Call(&TestService::Req, 1);

  TemplateCall<TestService1> t1;

  typedef int (TestService1::*ReqType)(int v1, double v2);
  ReqType reqFunc = &TestService1::Req;
  t1.Call(reqFunc, 1, 2);

  // t1.Call(&TestService1::Req, 1, 2);  // error 重载决议无法生效, 必须手动处理
  return 0;
}