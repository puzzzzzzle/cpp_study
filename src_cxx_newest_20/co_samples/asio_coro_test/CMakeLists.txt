aux_source_directory(. ${CURRENT_TASK}_SRCS)
include_directories(.)

# 可执行文件
add_executable(${CURRENT_TASK} ${${CURRENT_TASK}_SRCS} )

#通用动态链接库
target_link_libraries(${CURRENT_TASK}  ${COMMON_LIBS})

# 开启c++23 和 协程
target_compile_features(${CURRENT_TASK} PRIVATE cxx_std_23)
target_compile_options(${CURRENT_TASK} PRIVATE -fcoroutines)