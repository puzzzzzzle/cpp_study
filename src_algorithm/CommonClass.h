#include <string>
#include <common_includes.h>

class OperatorLogClass {
  public:
  std::string name{};
  char* data{nullptr};
  std::string ToString() const {
    return "OperatorLogClass:" + name + "\t@" + std::to_string((intptr_t)this);
  }
  OperatorLogClass(){LOG_DEBUG(ToString())};
  OperatorLogClass(const std::string& _name) {
    name = _name;
    LOG_DEBUG(ToString())
  }
  OperatorLogClass(const OperatorLogClass& obj) {
    name = obj.name;
    LOG_DEBUG("this: " << ToString() << "\tobj: " << obj.ToString())
  };
  OperatorLogClass(OperatorLogClass&& obj) {
    LOG_DEBUG("\tobj: " << obj.ToString())
    std::swap(name, obj.name);
    LOG_DEBUG("this: " << ToString())
  };
  virtual ~OperatorLogClass(){LOG_DEBUG(ToString())};
  OperatorLogClass& operator=(const OperatorLogClass& obj) {
    LOG_DEBUG("this: " << ToString() << "\tobj: " << obj.ToString())
    name = obj.name;
    LOG_DEBUG("this: " << ToString() << "\tobj: " << obj.ToString())
    return *this;
  };

  OperatorLogClass& operator=(OperatorLogClass&& obj) {
    LOG_DEBUG("\tobj: " << obj.ToString())
    std::swap(name, obj.name);
    LOG_DEBUG("this: " << ToString())
    return *this;
  };
};


struct CPosition {
  int x = 0;
  int y = 0;

  CPosition() = default;
  CPosition(int _x, int _y) {
    x = _x;
    y = _y;
  }
  std::string to_string() const {
    std::ostringstream oss{};
    oss << "[" << x << "," << y << "]";
    return oss.str();
  }
  static int compare(const CPosition& lhs, const CPosition& rhs) {
    if (lhs.x != rhs.x) {
      return lhs.x - rhs.x;
    }
    return lhs.y - rhs.y;
  }
  friend bool operator<(const CPosition& lhs, const CPosition& rhs) {
    return compare(lhs, rhs) < 0;
  }
  friend bool operator==(const CPosition& lhs, const CPosition& rhs) {
    return compare(lhs, rhs) == 0;
  }
  friend std::ostream& operator<<(std::ostream& os, const CPosition& pos) {
    os << pos.to_string();
    return os;
  }
};