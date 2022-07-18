aux_source_directory(. ${build_temp}cpps)
include_directories(.)
include_directories(${CMAKE_SOURCE_DIR}/src/algorithm/design/csharp_event_with_args)
# 可执行文件
add_executable(${build_temp} ${${build_temp}cpps} ${common_cpps})

#通用动态链接库
target_link_libraries(${build_temp} pthread rt ${CONAN_LIBS})
