#pragma once
#include <string>
#include <sstream>
/**
 * stringable 非虚函数版
* 继承它不打破 TriviallyCopyable & StandardLayoutType 具名要求 (POD 同理)
 * 假定每个继承子Stringable的都实现了 std::ostream &ToStringImpl(std::ostream &os) const 这个函数
 * 使用 CRTP 实现静态多态
 * eg:
 struct Data : public Stringable<Data>
{
    int m_var{};
    std::ostream& ToStringImpl(std::ostream& os) const
    {
        os << "m_var:" << m_var;
        return os;
    }
};
 *
 * @tparam T
 */
template <class T>
class Stringable {
public:
  // 假定每个继承子Stringable的都实现了这个函数
  //    std::ostream &ToStringImpl(std::ostream &os) const
  //    {
  //        return os;
  //    }
public:
  std::string ToString() const {
    std::ostringstream oss{};
    GetRImpl()->ToStringImpl(oss);
    return oss.str();
  }

  friend std::ostream& operator<<(std::ostream& os, const Stringable<T>& obj) {
    return obj.GetRImpl()->ToStringImpl(os);
  }

  // 按照函数查找规则, 共享指针可以绑定普通指针的operator, 当然也可以使用自己的
  friend std::ostream& operator<<(std::ostream& os,
                                  const Stringable<T>* const obj) {
    if (obj != nullptr) {
      obj->GetRImpl()->ToStringImpl(os);
    } else {
      os << "nullptr";
    }
    return os;
  }

private:
  inline const T* GetRImpl() const {
    return static_cast<const T*>(this);
  }
};