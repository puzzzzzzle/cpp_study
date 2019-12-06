aux_source_directory(./ ${build_temp}cpps)
include_directories(./)

# 可执行文件
add_executable(${build_temp}_test aoi.c test.c ${common_cpps})
add_executable(${build_temp}_map_test aoi.c ${common_cpps})

#通用动态链接库
target_link_libraries(${build_temp}_test pthread ${CONAN_LIBS})
target_link_libraries(${build_temp}_map_test pthread ${CONAN_LIBS})
