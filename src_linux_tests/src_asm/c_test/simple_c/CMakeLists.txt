
add_library(${CURRENT_TASK}_lib SHARED testdyn.cpp)

# 可执行文件
add_executable(${CURRENT_TASK} main.cpp)

#通用动态链接库
target_link_libraries(${CURRENT_TASK} ${CURRENT_TASK}_lib)
