aux_source_directory(. ${CURRENT_TASK}_SRCS)
include_directories(.)

find_package(unifex REQUIRED)

# 可执行文件
add_executable(${CURRENT_TASK} ${${CURRENT_TASK}_SRCS}
        test_simple_co.cpp)

#通用动态链接库
target_link_libraries(${CURRENT_TASK}  ${COMMON_LIBS} unifex)
