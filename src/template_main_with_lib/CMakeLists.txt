#子项目名 替换template_name为子项目名
set(build_temp dynamic_templete)

message("\n###############################\nstart cmake ${build_temp}")
aux_source_directory(./ ${build_temp}cpps)
include_directories(./)
message("${build_temp}cpps find cpps : ${${build_temp}cpps}")

# 输出库
add_library(${build_temp}-impl SHARED ${${build_temp}cpps} ${common_cpps})
#动态链接库依赖
message("libs : ${libs}")
target_link_libraries(${build_temp}-impl  pthread ${CONAN_LIBS})

# 可执行文件
add_executable(${build_temp} main/main.cpp)
#可执行文件的依赖动态库
target_link_libraries(${build_temp} ${build_temp}-impl)



message("${build_temp} cmake finish\n###############################\n")