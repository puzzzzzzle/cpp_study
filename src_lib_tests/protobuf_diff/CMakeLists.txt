aux_source_directory(. ${CURRENT_TASK}_SRCS)
include_directories(.)

# 可执行文件
add_executable(${CURRENT_TASK} ${${CURRENT_TASK}_SRCS} )

# Find Protobuf library
find_package(Protobuf REQUIRED)

# Add Protobuf include directory to include paths
include_directories(${PROTOBUF_INCLUDE_DIRS})


#通用动态链接库
target_link_libraries(${CURRENT_TASK}  ${COMMON_LIBS} ${PROTOBUF_LIBRARIES})
