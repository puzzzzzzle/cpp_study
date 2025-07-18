cmake_minimum_required(VERSION 3.22)
project(
        cpp_study
        VERSION 0.1.1
        DESCRIPTION "cpp study project"
        LANGUAGES C CXX
        )

# 详细编译信息开关
set(CMAKE_VERBOSE_MAKEFILE ON)
# boost 库静态链接选项
set(BOOST_USE_STATIC_LINK ON)
#log 选项 使用boostlog 还是 std out
set(LOG_USE_BOOST OFF)
# std log 打印log时， 是否加锁
set(STD_LOG_SYNC OFF)
# 生成 command json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 引用函数库
include(cpp_bootstrap/common/CMake/FuncDefs.cmake)
# 设置配目录(运行时拷贝)
set(CONFIG_DIR ${CMAKE_SOURCE_DIR}/data)
# 设置 boostStrap 文件夹名
set(BOOTSTRAP_DIR ${CMAKE_SOURCE_DIR}/cpp_bootstrap)
# 设置运行时输出文件地址
SetBinDir(${CMAKE_BINARY_DIR}/bin)

# 设置通用编译选项
SetCommonBuildFlag()
message("CMAKE_CXX_FLAGS : ${CMAKE_CXX_FLAGS}")
# 生成配置
GenConfig()
# 设置编译版本号
SetCompilerVersion()

# 查找依赖
FindCommonLib()
message("COMMON_LIBS ${COMMON_LIBS}")

# 设置源码根目录(包含cmake的文件夹将被解析为一个编译target)
set(SRC_DIR_ROOTS "")
# 一些算法
list(APPEND SRC_DIR_ROOTS ${CMAKE_SOURCE_DIR}/src_algorithm)
# c++ header tool 测试
list(APPEND SRC_DIR_ROOTS ${CMAKE_SOURCE_DIR}/src_boost_study)
# c++ 语法测试
list(APPEND SRC_DIR_ROOTS ${CMAKE_SOURCE_DIR}/src_cpp_language)
# c++ 工具类
list(APPEND SRC_DIR_ROOTS ${CMAKE_SOURCE_DIR}/src_cpp_tools)
# 最新c++特性
list(APPEND SRC_DIR_ROOTS ${CMAKE_SOURCE_DIR}/src_cxx_newest_20)
list(APPEND SRC_DIR_ROOTS ${CMAKE_SOURCE_DIR}/src_cxx_newest_23)

# 一些c++工具库
list(APPEND SRC_DIR_ROOTS ${CMAKE_SOURCE_DIR}/src_lib_tests)
# linux 函数测试
list(APPEND SRC_DIR_ROOTS ${CMAKE_SOURCE_DIR}/src_linux_tests)

message("all roots ${SRC_DIR_ROOTS}")

# 开始加载
AddAllSubDir()