aux_source_directory(. ${build_temp}cpps)
include_directories(.)
include_directories(${CMAKE_SOURCE_DIR}/src/cpp_language/static_lib_func)

# 可执行文件
add_executable(${build_temp} ${${build_temp}cpps} ${common_cpps})

#通用动态链接库
#SET_TARGET_PROPERTIES(cpp_language_static_lib_func-static-impl PROPERTIES LINK_FLAGS "-rdynamic -L")
target_link_libraries(${build_temp} ${THREAD_LIB} ${CONAN_LIBS} "cpp_language_static_lib_func-static-impl")
