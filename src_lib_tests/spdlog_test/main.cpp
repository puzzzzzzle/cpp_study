#include "common_includes.h"

// 可选：在包含 spdlog 之前定义，编译期过滤掉低于此级别的日志（格式串和参数都不会求值）
// 取值: SPDLOG_LEVEL_TRACE(0) DEBUG(1) INFO(2) WARN(3) ERROR(4) CRITICAL(5) OFF(6)
// 也可在 CMake 里加: add_compile_definitions(SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_INFO)
// #define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_DEBUG
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

TEST(test_test, 1) { EXPECT_EQ(1, 1); }

// spdlog 使用样例
TEST(spdlog_example, basic_levels) {
  // 设置全局日志级别（只显示 info 及以上）
  spdlog::set_level(spdlog::level::info);

  spdlog::trace("trace: 最细粒度");
  spdlog::debug("debug: 调试信息");
  spdlog::info("info: 普通信息");
  spdlog::warn("warn: 警告");
  spdlog::error("error: 错误");
  spdlog::critical("critical: 严重错误");
}

TEST(spdlog_example, format) {
  spdlog::set_level(spdlog::level::debug);
  int x = 42;
  double y = 3.14;
  const char* name = "spdlog";

  // 格式化输出（类似 fmt/printf）
  spdlog::info("整数 x={}, 浮点 y={:.2f}", x, y);
  spdlog::info("Hello, {}!", name);
}

TEST(spdlog_example, custom_logger) {
  // 创建带颜色的控制台 logger
  auto console = spdlog::stdout_color_mt("my_logger");
  console->set_level(spdlog::level::debug);
  console->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] [%n] %v");

  console->info("自定义 logger 输出");
  console->debug("调试: 仅此 logger 可见");
}

// Logger level 层级关系（无 log4j 那种 root→child）：
// - 有一个全局 level（registry 里的 global_log_level_），用于新 logger 的初始 level。
// - spdlog::set_level(level)：会把这个 level 设给【当前已注册的所有 logger】+ 更新全局 level，
//   所以会影响到 default logger 和所有 named logger。
// - logger->set_level(level)：只影响该 logger；之后若再调 spdlog::set_level()，又会把该 logger 覆盖掉。
TEST(spdlog_example, level_hierarchy) {
  auto a = spdlog::stdout_color_mt("logger_a");
  auto b = spdlog::stdout_color_mt("logger_b");
  a->set_level(spdlog::level::debug);
  b->set_level(spdlog::level::warn);

  a->debug("a 的 debug 会输出");
  b->debug("b 的 debug 不会输出");

  spdlog::set_level(spdlog::level::info);  // 影响 default + logger_a + logger_b 全部变成 info
  a->debug("现在 a 的 debug 也不输出");
  a->info("a 的 info 会输出");
}

// 先检查级别再打：避免昂贵格式化（如 proto.DebugString()）在未输出时仍被执行
// spdlog 无内置此类宏，可自封装：if(should_log(level)) 再 log(...)，此时参数才求值
#define SPDLOG_LOGGER_DEBUG_IF(logger, ...) \
  do { \
    if ((logger) && (logger)->should_log(spdlog::level::debug)) \
      SPDLOG_LOGGER_DEBUG(logger, __VA_ARGS__); \
  } while (0)
#define SPDLOG_LOGGER_INFO_IF(logger, ...) \
  do { \
    if ((logger) && (logger)->should_log(spdlog::level::info)) \
      SPDLOG_LOGGER_INFO(logger, __VA_ARGS__); \
  } while (0)
#define SPDLOG_DEBUG_IF(...) \
  do { \
    if (spdlog::default_logger_raw()->should_log(spdlog::level::debug)) \
      SPDLOG_DEBUG(__VA_ARGS__); \
  } while (0)
#define SPDLOG_INFO_IF(...) \
  do { \
    if (spdlog::default_logger_raw()->should_log(spdlog::level::info)) \
      SPDLOG_INFO(__VA_ARGS__); \
  } while (0)

TEST(spdlog_example, macro_if_expensive) {
  spdlog::set_level(spdlog::level::info);  // 只输出 info 及以上
  auto log = spdlog::get("my_logger");
  if (!log) log = spdlog::default_logger();

  // 昂贵消息：只有 should_log 为 true 时才会求值 proto.DebugString()
  // SPDLOG_LOGGER_DEBUG(log, "proto: {}", proto.DebugString());  // 不好：会先算 DebugString
  SPDLOG_LOGGER_DEBUG_IF(log, "debug 不会输出，且不会求值后面的参数");
  SPDLOG_LOGGER_INFO_IF(log, "info 会输出: {}", "expensive_arg_only_when_needed");
  SPDLOG_DEBUG_IF("default logger debug 也不求值");
  SPDLOG_INFO_IF("default logger info: {}", 42);
}

// 宏包装：低于 SPDLOG_ACTIVE_LEVEL 的调用会展开为 (void)0，格式串和参数在编译期被去掉，零开销
TEST(spdlog_example, macro) {
  spdlog::set_level(spdlog::level::trace);
  // 默认 logger 的宏：SPDLOG_TRACE / DEBUG / INFO / WARN / ERROR / CRITICAL
  SPDLOG_TRACE("trace 宏");
  SPDLOG_DEBUG("debug 宏, 若 ACTIVE_LEVEL>DEBUG 则整行被优化掉");
  SPDLOG_INFO("info 宏: x={}", 42);
  SPDLOG_WARN("warn 宏");

  // 指定 logger 的宏：SPDLOG_LOGGER_xxx(logger, fmt, ...)
  auto log = spdlog::get("my_logger");
  if (log) {
    SPDLOG_LOGGER_DEBUG(log, "自定义 logger 的 debug 宏");
    SPDLOG_LOGGER_INFO(log, "自定义 logger: {}", "hello");
  }
}
int main(int argc, char** argv) {
  // 可选：程序启动时设置默认格式与级别
  spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] %v");
  spdlog::set_level(spdlog::level::info);

  testing::InitGoogleTest(&argc, argv);
  int iRet = RUN_ALL_TESTS();
  return iRet;
}
