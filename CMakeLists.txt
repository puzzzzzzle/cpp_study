cmake_minimum_required(VERSION 3.7)
set(project_name cpp_study)
project(${project_name})

include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-std=c++20" COMPILER_SUPPORTS_CXX20)

if (COMPILER_SUPPORTS_CXX20)
    message("this compile support cxx 20")
    set(CMAKE_CXX_STANDARD 20)
else ()
    set(CMAKE_CXX_STANDARD 17)
endif ()

#设置版本号
set(VERSION_MAJOR 1.2)
set(VERSION_MINOR 0)
# 开启汇编支持
option(ENABLE_ASM "is enable asm" OFF)

# boost 选项
option(boost_static "use static boost lib" ON)

# 编译输出地址
include(cpp_bootstrap/common/CMake/FuncDefs.cmake)
set(DEFAULT_BIN_DIR ${CMAKE_BINARY_DIR}/bin)
SetBinDir(${DEFAULT_BIN_DIR})

#log 选项
#add_definitions(-DLOG_BOOST)

# 设置源码根目录(包含cmake的文件夹将被解析为一个编译target)
set(SRC_DIR_ROOTS "")
list(APPEND SRC_DIR_ROOTS ${CMAKE_SOURCE_DIR}/src)

# c++ 20 的一些测试
if (COMPILER_SUPPORTS_CXX20)
    message("this compile support cxx 20")
    list(APPEND SRC_DIR_ROOTS ${CMAKE_SOURCE_DIR}/src_cxx20)
endif ()

message("all roots ${SRC_DIR_ROOTS}")
# 设置配目录(运行时拷贝)
set(CONFIG_DIR ${CMAKE_SOURCE_DIR}/data)
# 设置 boostStrap 文件夹名
set(BOOTSTRAP_DIR ${CMAKE_SOURCE_DIR}/cpp_bootstrap)

# 开始加载
include(cpp_bootstrap/BasicCmake.cmake)
message("----------- ${CMAKE_CXX_FLAGS}")
AddAllSubDir()