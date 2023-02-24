aux_source_directory(. ${CURRENT_TASK}_SRCS)
include_directories(.)
file(GLOB_RECURSE SRCS *.nasm *.asm *.S)

OpenAsmSupport()

# 可执行文件
add_executable(${CURRENT_TASK} ${${CURRENT_TASK}_SRCS} ${SRCS})

#通用动态链接库
target_link_libraries(${CURRENT_TASK}  ${COMMON_LIBS})