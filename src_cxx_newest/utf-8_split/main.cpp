#include <codecvt>

#include "common_includes.h"
class invalid_u8_character_error: public std::runtime_error{
  using std::runtime_error::runtime_error;
};
/**
 * 把一个u8字符串分割为单个'字符'
 * @param utf8_string
 * @return
 */
std::vector<std::string> splitUtf8String(const std::string &utf8_string) {
  std::vector<std::string> result;
  size_t i = 0;

  while (i < utf8_string.size()) {
    unsigned char c = utf8_string[i];

    // 根据 UTF-8 编码规则判断字符的字节数
    if (c < 0x80) {
      // 1 字节字符 (ASCII) 0xxxxxxx
      result.push_back(utf8_string.substr(i, 1));
      i += 1;
    } else if ((c & 0xE0) == 0xC0) {
      // 2 字节字符 110xxxxx 10xxxxxx
      result.push_back(utf8_string.substr(i, 2));
      i += 2;
    } else if ((c & 0xF0) == 0xE0) {
      // 3 字节字符 1110xxxx 10xxxxxx 10xxxxxx
      result.push_back(utf8_string.substr(i, 3));
      i += 3;
    } else if ((c & 0xF8) == 0xF0) {
      // 4 字节字符 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
      result.push_back(utf8_string.substr(i, 4));
      i += 4;
    } else {
      // 无效字符
      throw invalid_u8_character_error("Invalid UTF-8 character at position " +
                               std::to_string(i));
    }
  }

  return result;
}
/**
 * 检查一个u8字符串是否合法
 * @param str
 * @return
 */
bool isValidUtf8(const std::string &str) {
  int bytes_to_process = 0;

  for (unsigned char c : str) {
    if (bytes_to_process == 0) {
      if ((c & 0x80) == 0) {
        // 1 字节字符 (ASCII) 0xxxxxxx
        continue;
      } else if ((c & 0xE0) == 0xC0) {
        // 2 字节字符 110xxxxx 10xxxxxx
        bytes_to_process = 1;
      } else if ((c & 0xF0) == 0xE0) {
        // 3 字节字符 1110xxxx 10xxxxxx 10xxxxxx
        bytes_to_process = 2;
      } else if ((c & 0xF8) == 0xF0) {
        // 4 字节字符 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
        bytes_to_process = 3;
      } else {
        // 无效字符处理
        return false;
      }
    } else {
      // 多字符的, 检查后续字符, 直到最后一个字符, 必须都为 10xxxxxx
      if ((c & 0xC0) != 0x80) {
        return false;
      }
      bytes_to_process--;
    }
  }

  return bytes_to_process == 0;
}
TEST(test_test, 1) {
  std::string str = "hello, 这是一个utf-8字符串, 包含复杂的字符.";
  ASSERT_TRUE(isValidUtf8(str));
  auto ret = splitUtf8String(str);
  for (const auto &item : ret) {
    LOG_DEBUG(item << "    " << item.size())
  }
}

TEST(c20test, 1) {
  // char8_t 本质上也是1个字符, 和char 一样, 只是用于强制区分类型
  ASSERT_EQ(sizeof(char8_t), 1);
  std::u8string str = u8"hello, 这是一个utf-8字符串, 包含复杂的字符.";
  ASSERT_TRUE(isValidUtf8(std::string(str.begin(), str.end())));
  auto ret = splitUtf8String(std::string(str.begin(), str.end()));
  for (const auto &item : ret) {
    LOG_DEBUG(item << "    " << item.size())
  }
}
TEST(c17new, 1) {
  // 创建一个 UTF-8 编码的字符串
  std::u8string u8str = u8"hello, 这是一个utf-8字符串, 包含复杂的字符.";

  // 使用 std::wstring_convert 和 std::codecvt_utf8 转换为 UTF-32
  std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
  std::u32string u32str = converter.from_bytes(
      reinterpret_cast<const char *>(u8str.data()),
      reinterpret_cast<const char *>(u8str.data() + u8str.size()));

  // 输出 UTF-32 字符串的每个字符
  for (char32_t ch : u32str) {
    std::wcout << L"Character: " << static_cast<wchar_t>(ch)
               << std::endl;  // 输出 UTF-32 字符
  }
}

int main(int argc, char **argv) {
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}