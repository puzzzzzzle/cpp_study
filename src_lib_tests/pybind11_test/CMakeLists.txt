aux_source_directory(. ${CURRENT_TASK}_SRCS)
include_directories(.)

find_package(Python COMPONENTS Interpreter Development)
find_package(pybind11 CONFIG)

# python 库
pybind11_add_module(${CURRENT_TASK} ${${CURRENT_TASK}_SRCS}  )
#通用动态链接库
target_link_libraries(${CURRENT_TASK} PRIVATE  ${COMMON_LIBS})


