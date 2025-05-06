# 设置模块缓存目录, 目前好像只有 CMAKE_BINARY_DIR 下才能查找到
set(GCM_CACHE_DIR "${CMAKE_BINARY_DIR}")

message(STATUS "GCM_CACHE_DIR: ${GCM_CACHE_DIR}")

# 目前还没找到设置环境变量的方法, 可能得用model-mapper
# You can specify a mapper with the -fmodule-mapper=val option or CXX_MODULE_MAPPER environment variable. The value may have one of the following forms:
#set(ENV{GCC_IMPORT_CACHE} ${GCM_CACHE_DIR})

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
