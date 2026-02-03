#if 0
#/* 自动检查更新并运行的 C++ 脚本模式 */
SOURCE_NAME=$(basename "$0")
OUT_BIN="/tmp/${SOURCE_NAME}.out"

#只有当二进制文件不存在，或者源代码比二进制文件更新时，才进行编译
if [ ! -f "$OUT_BIN" ] || [ "$0" -nt "$OUT_BIN" ]; then
    c++ -O3 -std=c++11 "$0" -o "$OUT_BIN" || exit 1
fi

#运行并传递所有参数
exec "$OUT_BIN" "$@"
#endif

#include <iostream>

int main(int argc, char* argv[]) {
  std::cout << "C++ script running..." << std::endl;

  if (argc > 1) {
    std::cout << "Received parameters: " << std::endl;
    for (int i = 1; i < argc; ++i) {
      std::cout << "  - [" << i << "]: " << argv[i] << std::endl;
    }
  } else {
    std::cout << "No external parameters detected." << std::endl;
  }

  return 0;
}