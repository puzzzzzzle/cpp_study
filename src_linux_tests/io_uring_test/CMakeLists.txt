aux_source_directory(. ${CURRENT_TASK}_SRCS)
include_directories(.)

# Find the liburing library
find_library(LIBURING_LIBRARY NAMES uring REQUIRED)
# Find the liburing include directory
find_path(LIBURING_INCLUDE_DIR NAMES liburing.h REQUIRED)

# Add the include directory
include_directories(${LIBURING_INCLUDE_DIR})

# 可执行文件
add_executable(${CURRENT_TASK} ${${CURRENT_TASK}_SRCS} )

#通用动态链接库
target_link_libraries(${CURRENT_TASK}  ${COMMON_LIBS} ${LIBURING_LIBRARY})
