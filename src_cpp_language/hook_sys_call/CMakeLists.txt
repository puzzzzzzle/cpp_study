aux_source_directory(. ${CURRENT_TASK}_SRCS)
include_directories(.)
include_directories(${CMAKE_SOURCE_DIR}/src/cpp_language/static_lib_func)

# 可执行文件
add_executable(${CURRENT_TASK} ${${CURRENT_TASK}_SRCS} )

#通用动态链接库
#SET_TARGET_PROPERTIES(cpp_language_static_lib_func-static-impl PROPERTIES LINK_FLAGS "-rdynamic -L")
target_link_libraries(${CURRENT_TASK}  ${COMMON_LIBS} "cpp_language_static_lib_func-static-impl")
