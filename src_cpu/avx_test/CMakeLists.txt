aux_source_directory(. ${build_temp}cpps)
include_directories(.)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mavx2")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mavx2")
# 可执行文件
add_executable(${build_temp} ${${build_temp}cpps} )

#通用动态链接库
target_link_libraries(${build_temp}  ${COMMON_LIBS})
