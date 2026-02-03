#if 0
#/* --- 自动编译脚本逻辑 --- */
SOURCE_NAME=$(basename "$0")
OUT_BIN="/tmp/${SOURCE_NAME}.out"

# 1. 这里放那些一定有 .pc 文件的第三方库 (如: sqlite3, opencv4)
EXTRA_LIBS="sqlite3 zlib"
# 检查库是否存在的逻辑
for lib in $EXTRA_LIBS; do
    if ! pkg-config --exists $lib; then
        echo "Error: library '$lib' not found. Please try to install the corresponding development package (e.g., lib${lib}-dev or ${lib}-devel)"
        exit 1
    fi
done
# 2. 这里放必须手动指定的链接标志 (如: -pthread, -lm)
# -pthread 是特殊标志，它不仅链接库，还会定义一些宏
MANUAL_FLAGS="-pthread -lm"

if [ ! -f "$OUT_BIN" ] || [ "$0" -nt "$OUT_BIN" ]; then
    # 只有当 EXTRA_LIBS 不为空时才调用 pkg-config
    PKG_CFLAGS=""
    PKG_LIBS=""
    if [ -n "$EXTRA_LIBS" ]; then
        PKG_CFLAGS=$(pkg-config --cflags $EXTRA_LIBS 2>/dev/null)
        PKG_LIBS=$(pkg-config --libs $EXTRA_LIBS 2>/dev/null)
    fi
    
    # 编译命令
    c++ -O3 -std=c++17 "$0" -o "$OUT_BIN" $MANUAL_FLAGS $PKG_CFLAGS $PKG_LIBS || exit 1
fi

exec "$OUT_BIN" "$@"
#endif

/* --- C++ 代码区 --- */
#include <cmath>  // 对应 m (math)
#include <iostream>
#include <thread>  // 对应 pthread
#include <sqlite3.h>

// SQLite 回调函数，用于打印查询结果
int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << " | ";
    }
    std::cout << std::endl;
    return 0;
}

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

  // --- SQLite 演示部分 ---
  sqlite3 *db;
  char *zErrMsg = 0;
  
  // 在内存中创建一个临时数据库
  if (sqlite3_open(":memory:", &db) == SQLITE_OK) {
      std::cout << "✅ SQLite: memory database connection successful." << std::endl;

      // 创建表并插入一条数据
      const char* sql_create = "CREATE TABLE USERS(ID INT, NAME TEXT);";
      const char* sql_insert = "INSERT INTO USERS VALUES (1, 'Gemini User');";
      const char* sql_select = "SELECT * FROM USERS;";

      sqlite3_exec(db, sql_create, 0, 0, &zErrMsg);
      sqlite3_exec(db, sql_insert, 0, 0, &zErrMsg);
      
      std::cout << "🔍 query results: ";
      sqlite3_exec(db, sql_select, callback, 0, &zErrMsg);

      sqlite3_close(db);
  } else {
      std::cerr << "❌ database open failed" << std::endl;
  }
  return 0;
}