aux_source_directory(. ${CURRENT_TASK}_SRCS)
include_directories(.)
include_directories(../adapter)

# 输出库
add_library(${CURRENT_TASK}-shared-impl SHARED ${${CURRENT_TASK}_SRCS} )
add_library(${CURRENT_TASK}-static-impl STATIC ${${CURRENT_TASK}_SRCS} )

#动态链接库依赖

# 动态库
target_link_libraries(${CURRENT_TASK}-shared-impl  pthread ${COMMON_LIBS})
# 静态库
target_link_libraries(${CURRENT_TASK}-static-impl  pthread ${COMMON_LIBS})

# 可执行文件
aux_source_directory(main ${CURRENT_TASK}maincpps)
add_executable(${CURRENT_TASK}-shared ${${CURRENT_TASK}maincpps})
add_executable(${CURRENT_TASK}-static ${${CURRENT_TASK}maincpps})

#可执行文件的依赖动态库
target_link_libraries(${CURRENT_TASK}-shared ${CURRENT_TASK}-shared-impl)
#可执行文件的依赖静态库
target_link_libraries(${CURRENT_TASK}-static ${CURRENT_TASK}-static-impl)
