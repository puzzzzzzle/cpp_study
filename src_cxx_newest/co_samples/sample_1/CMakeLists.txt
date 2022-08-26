aux_source_directory(. ${build_temp}cpps)
include_directories(.)
OpenCoroutine()

# 可执行文件
add_executable(${build_temp} ${${build_temp}cpps} )

#通用动态链接库
target_link_libraries(${build_temp}  ${COMMON_LIBS})
