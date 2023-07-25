#include <iostream>
#include <stdexcept>

// C++11 constexpr 函数使用递归而非迭代
// （C++14 constexpr 函数可使用局部变量和循环）
constexpr int factorial(int n)
{
  return n <= 1 ? 1 : (n * factorial(n - 1));
}

// 字面类
class conststr
{
  const char* p;
  std::size_t sz;
  public:
  template<std::size_t N>
  constexpr conststr(const char(&a)[N]): p(a), sz(N - 1) {}

  // constexpr 函数通过抛异常来提示错误
  // C++11 中，它们必须用条件运算符 ?: 来这么做
  constexpr char operator[](std::size_t n) const
  {
    return n < sz ? p[n] : throw std::out_of_range("");
  }

  constexpr std::size_t size() const { return sz; }
};

// C++11 constexpr 函数必须把一切放在单条 return 语句中
// （C++14 无此要求）
constexpr std::size_t countlower(conststr s, std::size_t n = 0,
                                 std::size_t c = 0)
{
  return n == s.size() ? c :
         'a' <= s[n] && s[n] <= 'z' ? countlower(s, n + 1, c + 1) :
                                    countlower(s, n + 1, c);
}

// 输出要求编译时常量的函数，用于测试
template<int n>
struct constN
{
  constN() { std::cout << n << '\n'; }
};

int main()
{
  std::cout << "4! = " ;
  constN<factorial(4)> out1; // 在编译时计算

  volatile int k = 8; // 使用 volatile 防止优化
  std::cout << k << "! = " << factorial(k) << '\n'; // 运行时计算

  std::cout << "\"Hello, world!\" 里小写字母的个数是 ";
  constN<countlower("Hello, world!")> out2; // 隐式转换到常量字符串
}