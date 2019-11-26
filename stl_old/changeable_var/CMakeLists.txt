#子项目名 替换template_name为子项目名
set(build_temp changlable_var)

message("\n###############################\nstart cmake ${build_temp}")
aux_source_directory(./ ${build_temp}cpps)
include_directories(./)
message("${build_temp}cpps find cpps : ${${build_temp}cpps}")

# 可执行文件
add_executable(${build_temp} ${${build_temp}cpps} ${common_cpps})

#boost log 的宏
#通用动态链接库
target_link_libraries(${build_temp} pthread ${CONAN_LIBS})

message("${build_temp} cmake finish\n###############################\n")