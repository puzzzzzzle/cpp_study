aux_source_directory(. ${CURRENT_TASK}_SRCS)
include_directories(.)

# 关掉pie pic 调试符号 优化项
# g++ main.cpp -ldl -O0 -fno-pie -no-pie
set(CMAKE_CXX_FLAGS " -ldl -O0 -fno-pie -no-pie")
set(CMAKE_C_FLAGS " -ldl -O0 -fno-pie -no-pie")

# 可执行文件
add_executable(${CURRENT_TASK} ${${CURRENT_TASK}_SRCS} )

#通用动态链接库
target_link_libraries(${CURRENT_TASK})
