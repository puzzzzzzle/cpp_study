# 设置模块缓存目录
set(GCM_CACHE_DIR "${CMAKE_BINARY_DIR}")

message(STATUS "GCM_CACHE_DIR: ${GCM_CACHE_DIR}")

# 设置模块编译环境变量, 注意: cmake 编译过程中地址比较复杂, 需要手动指定
set(ENV{GCC_IMPORT_CACHE} ${GCM_CACHE_DIR})

# 首先创建模块编译目标
add_custom_target(build_stdlib_modules
        # 编译标准库模块
        COMMAND ${CMAKE_CXX_COMPILER} -std=c++23 -fmodules-ts -xc++-system-header iostream
        COMMAND ${CMAKE_CXX_COMPILER} -std=c++23 -fmodules-ts -xc++-system-header vector
        # 设置工作目录
        WORKING_DIRECTORY ${GCM_CACHE_DIR}
)

# 编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmodules")

# 主程序
aux_source_directory(. ${CURRENT_TASK}_SRCS)
add_executable(${CURRENT_TASK} ${${CURRENT_TASK}_SRCS})

add_dependencies(${CURRENT_TASK} build_stdlib_modules)

target_link_libraries(${CURRENT_TASK} ${COMMON_LIBS})
