aux_source_directory(. ${CURRENT_TASK}_SRCS)
include_directories(.)
find_package(benchmark REQUIRED)

add_compile_options(-march=native) # 启用本机所有指令集
#add_compile_options(-fno-tree-vectorize) # 禁用自动向量化
#add_compile_options(-fopt-info-vec-all) # 输出自动向量化优化信息
#add_compile_options(-fopt-info-vec-optimized) # 输出成功自动向量化优化信息


# 可执行文件
add_executable(${CURRENT_TASK} ${${CURRENT_TASK}_SRCS})

#通用动态链接库
target_link_libraries(${CURRENT_TASK}  ${COMMON_LIBS} benchmark::benchmark)
