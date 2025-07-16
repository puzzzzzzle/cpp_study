#include <memory>

#include "common_includes.h"
#include "proxy/proxy.h"

struct Formattable : pro::facade_builder
                     ::support<pro::skills::format>
                     ::build {};


TEST(format, 1) {
  std::string str = "Hello World";
  pro::proxy<Formattable> p1 = &str;
  FLOG_DEBUG("p1 = {}", *p1);  // Prints "p1 = Hello World"

  pro::proxy<Formattable> p2 = std::make_unique<int>(123);
  FLOG_DEBUG("p2 = {}", *p2);  // Prints "p2 = 123"

  pro::proxy<Formattable> p3 = pro::make_proxy<Formattable>(3.14159);
  FLOG_DEBUG("p3 = {:.2f}", *p3);  // Prints "p3 = 3.14"
}

PRO_DEF_MEM_DISPATCH(MemDraw, Draw);
PRO_DEF_MEM_DISPATCH(MemArea, Area);

struct Drawable : pro::facade_builder
    ::add_convention<MemDraw, void(std::ostream& output)>
    ::add_convention<MemArea, double() noexcept>
    ::support_copy<pro::constraint_level::nontrivial>
    ::build {};

class Rectangle {
public:
  Rectangle(double width, double height) : width_(width), height_(height) {}
  Rectangle(const Rectangle&) = default;

  void Draw(std::ostream& out) const {
    out << "{Rectangle: width = " << width_ << ", height = " << height_ << "}";
  }
  double Area() const noexcept { return width_ * height_; }

private:
  double width_;
  double height_;
};

std::string PrintDrawableToString(pro::proxy<Drawable> p) {
  std::stringstream result;
  result << "entity = ";
  p->Draw(result);
  result << ", area = " << p->Area();
  return std::move(result).str();
}

TEST(draw, 1) {
  pro::proxy<Drawable> p = pro::make_proxy<Drawable, Rectangle>(3, 5);
  std::string str = PrintDrawableToString(p);
  std::cout << str << "\n";  // Prints "entity = {Rectangle: width = 3, height = 5}, area = 15"
}

int main(int argc, char **argv) {
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}