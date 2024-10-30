#include "save_vtable_class.h"
#include "common_includes.h"

class Base {
  public:
  int val_;
  Base(int val) : val_(val) {}
  Base() = default;

  public:
  virtual ~Base() { LOG_DEBUG("dst called"); }
  virtual std::string Show() { return std::format("Base val is {}", val_); }
};
class Child : public Base {
  public:
  int val2_;

  public:
  Child(int val, int val2) : Base(val), val2_(val2) {
    LOG_DEBUG("called " << __PRETTY_FUNCTION__);
  }
  Child() { LOG_DEBUG("called " << __PRETTY_FUNCTION__); }

  public:
  //  NULL_PLACEMENT_NEW();
  std::string Show() override {
    return std::format("Chile val is {} {}", val_, val2_);
  }
};
class NoVirtualBase {
  public:
  int val_{};
};
class NoVirtualChild : public NoVirtualBase {
  public:
  NoVirtualChild() { LOG_DEBUG("called " << __PRETTY_FUNCTION__); }
  ~NoVirtualChild() { LOG_DEBUG("called " << __PRETTY_FUNCTION__); }
  int val2_{};
  std::string Show() {
    return std::format("NoVirtualChild val is {} {}", val_, val2_);
  }
};
TEST(test_test, save) {
  //  LOG_DEBUG(std::filesystem::absolute(std::filesystem::path("test.bin"))
  //                .parent_path()
  //                .string());
  Child c1(11, 22);
  LOG_DEBUG(c1.Show())
  write_to_file(&c1, "child1.bin");

  NoVirtualChild nc1;
  nc1.val_ = 11;
  nc1.val2_ = 22;
  LOG_DEBUG(nc1.Show())
  write_to_file(&nc1, "child2.bin");
}
TEST(test_test, load) {
  {
    LOG_DEBUG("======")
    auto* c1_1 = load_from_file<Child>("child1.bin");
    LOG_DEBUG(c1_1->Show());
    delete c1_1;

    Child c1_2;
    LOG_DEBUG("pre: " << c1_2.Show());
    load_from_file("child1.bin", &c1_2);
    LOG_DEBUG(c1_2.Show());
  }
  {
    LOG_DEBUG("======")
    auto* c1_1 = load_from_file<NoVirtualChild>("child2.bin");
    LOG_DEBUG(c1_1->Show());
    delete c1_1;

    NoVirtualChild c1_2;
    LOG_DEBUG("pre: " << c1_2.Show());
    load_from_file("child2.bin", &c1_2);
    LOG_DEBUG(c1_2.Show());
  }
}

int main(int argc, char** argv) {
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}