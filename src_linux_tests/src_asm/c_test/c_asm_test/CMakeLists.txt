

aux_source_directory(. ${CURRENT_TASK}_SRCS)
include_directories(.)

# 可执行文件
add_executable(${CURRENT_TASK} ${${CURRENT_TASK}_SRCS} ${SRCS})
