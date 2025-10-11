cmake_minimum_required(VERSION 3.17)
project(
        math_vec
        VERSION 1.0
        LANGUAGES CXX)
#  cmake -DCMAKE_INSTALL_PREFIX=`pwd`/install ..
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# 库源文件
file(GLOB_RECURSE SRC
        ${CMAKE_SOURCE_DIR}/math_vec/*.cpp
        ${CMAKE_SOURCE_DIR}/math_vec/*.c
)
# 添加库
add_library(math_vec ${SRC})
# 头文件路径
target_include_directories(math_vec PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/math_vec> $<INSTALL_INTERFACE:include>)

# 添加可执行文件
add_executable(math_vec_tool main.cpp)
target_link_libraries(math_vec_tool math_vec)

# 安装头文件
install(
        DIRECTORY math_vec/
        DESTINATION include/math_vec
        FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp"
)

# 安装库文件
install(
        TARGETS math_vec math_vec_tool
        EXPORT math_vecTargets
        ARCHIVE DESTINATION lib           # 静态库(.a)
        LIBRARY DESTINATION lib           # 动态库(.so)
        RUNTIME DESTINATION bin           # 可执行文件
)

# 安装README和许可证（可选）
install(
        FILES README.md
        DESTINATION share/doc/math_vec
)

# CMake库目标导出，供 find_package 使用
install(EXPORT math_vecTargets
        DESTINATION lib/cmake/math_vec
        NAMESPACE math_vec::
)