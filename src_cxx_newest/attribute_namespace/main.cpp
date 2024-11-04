#include "common_includes.h"

namespace MyAttr {
struct getter {
  bool is_public_{};
  getter(bool isPublic = true) : is_public_(isPublic) {}
};

struct setter {
  bool is_public_{};
  setter(bool isPublic = true) : is_public_(isPublic) {}
};

struct property {
  bool is_public_getter_{};
  bool is_public_setter_{};
  property(bool isPublicGetter, bool isPublicSetter)
      : is_public_getter_(isPublicGetter), is_public_setter_(isPublicSetter) {}
};
}  // namespace MyAttr

class Obj {
  private:
  [[using MyAttr: property()]] int val1_{};
  [[using MyAttr: getter()]] int val2_{};
};

TEST(test_test, 1) { EXPECT_EQ(1, 1); }

int main(int argc, char **argv) {
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}