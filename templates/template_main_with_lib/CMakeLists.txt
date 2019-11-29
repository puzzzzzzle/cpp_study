aux_source_directory(./ ${build_temp}cpps)
include_directories(./)


# 输出库
add_library(${build_temp}-impl SHARED ${${build_temp}cpps} ${common_cpps})
#动态链接库依赖
target_link_libraries(${build_temp}-impl  pthread ${CONAN_LIBS})

# 可执行文件
add_executable(${build_temp} main/main.cpp)
#可执行文件的依赖动态库
target_link_libraries(${build_temp} ${build_temp}-impl)
