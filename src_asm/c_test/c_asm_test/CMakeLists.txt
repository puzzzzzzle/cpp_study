

aux_source_directory(. ${build_temp}cpps)
include_directories(.)

# 可执行文件
add_executable(${build_temp} ${${build_temp}cpps} ${SRCS})
