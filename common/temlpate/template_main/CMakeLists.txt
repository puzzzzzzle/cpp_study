#子项目名 替换template_name为子项目名
set(build_temp template_name)


message("\n###############################\nstart cmake ${build_temp}")
aux_source_directory(./ ${build_temp}cpps)
include_directories(./)
message("${build_temp}cpps find cpps : ${${build_temp}cpps}")

set(common_cpps ${PROJECT_SOURCE_DIR}/common/common_include/common_funcs.cpp
        ${PROJECT_SOURCE_DIR}/common/common_include/log_init.cpp)

# 可执行文件
add_executable(${build_temp} ${${build_temp}cpps} ${common_cpps}
        )

# 复制配置文件
add_custom_command(
        TARGET ${build_temp}
        COMMAND echo copying files to ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        COMMAND rm -rf ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/configure/
        COMMAND mkdir ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/configure/
        COMMAND cp -v ${PROJECT_SOURCE_DIR}/common/properties/boost_log_settings.ini ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/configure/
        COMMAND echo copying files is finished.
)
#boost log 的宏
add_definitions(-DBOOST_LOG_DYN_LINK)
#通用动态链接库
target_link_libraries(${build_temp} gtest pthread boost_log boost_log_setup boost_thread boost_system)

message("${build_temp} cmake finish\n###############################\n")