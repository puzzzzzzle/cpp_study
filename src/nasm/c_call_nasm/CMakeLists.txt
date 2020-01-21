aux_source_directory(. ${build_temp}cpps)
include_directories(.)
file(GLOB_RECURSE SRCS *.nasm *.asm *.S)

# 可执行文件
add_executable(${build_temp} ${${build_temp}cpps} ${common_cpps} ${SRCS})

#通用动态链接库
target_link_libraries(${build_temp} pthread ${CONAN_LIBS})