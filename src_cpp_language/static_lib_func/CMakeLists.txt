aux_source_directory(. ${build_temp}cpps)
include_directories(.)
include_directories(../adapter)

# 输出库
add_library(${build_temp}-shared-impl SHARED ${${build_temp}cpps} )
add_library(${build_temp}-static-impl STATIC ${${build_temp}cpps} )

#动态链接库依赖

# 动态库
target_link_libraries(${build_temp}-shared-impl  pthread ${COMMON_LIBS})
# 静态库
target_link_libraries(${build_temp}-static-impl  pthread ${COMMON_LIBS})

# 可执行文件
aux_source_directory(main ${build_temp}maincpps)
add_executable(${build_temp}-shared ${${build_temp}maincpps})
add_executable(${build_temp}-static ${${build_temp}maincpps})

#可执行文件的依赖动态库
target_link_libraries(${build_temp}-shared ${build_temp}-shared-impl)
#可执行文件的依赖静态库
target_link_libraries(${build_temp}-static ${build_temp}-static-impl)
