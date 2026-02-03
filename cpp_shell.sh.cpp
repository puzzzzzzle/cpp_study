#if 0
#/* --- 自动编译脚本逻辑 --- */
SOURCE_NAME=$(basename "$0")
OUT_BIN="/tmp/${SOURCE_NAME}.out"

#在这里添加你想链接的库(例如 : pthread, m, ncurses, opencv4, sqlite3)
#只要是 pkg - config 能找到的库都可以写在这里
LIBS="pthread m"

#检查更新
if [ ! -f "$OUT_BIN" ] || [ "$0" -nt "$OUT_BIN" ]; then
#使用 pkg - config 自动获取编译和链接参数
#如果库不存在，pkg - config 会报错并停止编译
    PKG_CFLAGS=$(pkg-config --cflags $LIBS 2>/dev/null)
    PKG_LIBS=$(pkg-config --libs $LIBS 2>/dev/null)

#编译命令：加上 - pthreads 和基础库支持
    c++ -O3 -std=c++17 "$0" -o "$OUT_BIN" $PKG_CFLAGS $PKG_LIBS || exit 1
fi

exec "$OUT_BIN" "$@"
#endif

/* --- C++ 代码区 --- */
#include <cmath>  // 对应 m (math)
#include <iostream>
#include <thread>  // 对应 pthread
#include <vector>

int main(int argc, char* argv[]) {
  // 演示获取参数
  std::cout << "C++ script running..." << std::endl;

  if (argc > 1) {
    std::cout << "Received parameters: " << std::endl;

    for (int i = 1; i < argc; ++i) {
      std::cout << " - [" << i << "]: " << argv[i] << std::endl;
    }
  } else {
    std::cout << "No external parameters detected." << std::endl;
  }

  // 演示 pthread  math 支持
  std::thread t([]() {
    std::cout << "Thread: calculating in background..." << std::endl;
    std::cout << "Math: sqrt(2) = " << std::sqrt(2.0) << std::endl;
  });

  std::cout << "Main: C++ script has loaded common libraries." << std::endl;
  t.join();

  return 0;
}