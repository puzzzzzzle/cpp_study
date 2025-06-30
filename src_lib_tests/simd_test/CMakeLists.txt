aux_source_directory(. ${CURRENT_TASK}_SRCS)
include_directories(.)
find_package(benchmark REQUIRED)

add_cxx_compiler_flag(-march=native) # 启用本机所有指令集
#add_cxx_compiler_flag(-fno-tree-vectorize) # 禁用自动向量化
#add_cxx_compiler_flag(-fopt-info-vec-all) # 输出自动向量化优化信息
add_cxx_compiler_flag(-fopt-info-vec-optimized) # 输出成功自动向量化优化信息

#add_c_compiler_flag(-march=native)

# 可执行文件
add_executable(${CURRENT_TASK} ${${CURRENT_TASK}_SRCS}
        compiler_simd_test.cpp)

#通用动态链接库
target_link_libraries(${CURRENT_TASK}  ${COMMON_LIBS} benchmark::benchmark)
