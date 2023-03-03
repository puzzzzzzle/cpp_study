file(GLOB_RECURSE ${CURRENT_TASK}_SRCS "c_lib_4_py/*.cpp")
include_directories(.)
include_directories(c_lib_4_py)

find_package(Python COMPONENTS Interpreter Development)
find_package(pybind11 CONFIG)

# 重设输出路径到当前目录下
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BUILD_ABS_PATH}/out_lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILD_ABS_PATH}/out_lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_ABS_PATH}/out_lib)

# 导出二进制名字给c++用, 需要设置为module name
add_definitions(-DCURRENT_BUILD_NAME=${CURRENT_TASK})
# python 库
pybind11_add_module(${CURRENT_TASK} ${${CURRENT_TASK}_SRCS})
#通用动态链接库
target_link_libraries(${CURRENT_TASK} PRIVATE ${COMMON_LIBS})


