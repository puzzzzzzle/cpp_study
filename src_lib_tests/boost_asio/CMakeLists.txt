file(GLOB_RECURSE  ${build_temp}cpps . "*.cpp")
include_directories(.)

# 可执行文件
add_executable(${build_temp} ${${build_temp}cpps} )

#通用动态链接库
target_link_libraries(${build_temp}  ${COMMON_LIBS})
