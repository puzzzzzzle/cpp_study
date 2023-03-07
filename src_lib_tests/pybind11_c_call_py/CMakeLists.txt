aux_source_directory(. ${CURRENT_TASK}_SRCS)
include_directories(.)

find_package(pybind11 REQUIRED)

# 可执行文件
add_executable(${CURRENT_TASK} ${${CURRENT_TASK}_SRCS})
#file(GLOB_RECURSE PY_SRCS RELATIVE ${BUILD_ABS_PATH} *.py)
add_custom_command(
        TARGET ${CURRENT_TASK}
        PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E rm -r "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/py_module"
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${BUILD_ABS_PATH}/py_module" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/py_module"
)
#通用动态链接库
target_link_libraries(${CURRENT_TASK} PRIVATE ${COMMON_LIBS} PRIVATE pybind11::embed)
