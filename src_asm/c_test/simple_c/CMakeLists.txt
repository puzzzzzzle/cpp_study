
add_library(${build_temp}_lib SHARED testdyn.cpp)

# 可执行文件
add_executable(${build_temp} main.cpp)

#通用动态链接库
target_link_libraries(${build_temp} ${build_temp}_lib)
