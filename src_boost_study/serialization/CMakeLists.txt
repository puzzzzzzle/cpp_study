aux_source_directory(. ${CURRENT_TASK}_SRCS)
include_directories(.)

# 查找Boost库
find_package(Boost CONFIG REQUIRED COMPONENTS serialization)
include_directories(${Boost_INCLUDE_DIRS})

# 可执行文件
add_executable(${CURRENT_TASK} ${${CURRENT_TASK}_SRCS} )

#通用动态链接库
target_link_libraries(${CURRENT_TASK}  ${COMMON_LIBS} ${Boost_LIBRARIES})
