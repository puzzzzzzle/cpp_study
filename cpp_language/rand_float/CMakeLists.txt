
aux_source_directory(./ ${build_temp}cpps)
include_directories(./)


# 可执行文件
add_executable(${build_temp} ${${build_temp}cpps} ${common_cpps})

#boost log 的宏
#通用动态链接库
target_link_libraries(${build_temp} pthread ${CONAN_LIBS})
