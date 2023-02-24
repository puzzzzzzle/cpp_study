aux_source_directory(. ${CURRENT_TASK}_SRCS)
include_directories(.)

include_directories(${CMAKE_SOURCE_DIR}/src/path_search)
include_directories(${CMAKE_SOURCE_DIR}/src/cluster/union_find)

# 可执行文件
add_executable(${CURRENT_TASK} ${${CURRENT_TASK}_SRCS} )

#通用动态链接库
target_link_libraries(${CURRENT_TASK}  ${COMMON_LIBS})
