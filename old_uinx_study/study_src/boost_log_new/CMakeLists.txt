### copy all cmakelist and main to your dir,rename 'temple_executable_name',add_subdir in your own cmakelist
set(build_temp boost_log_settings)

message("\n###############################\nstart cmake ${build_temp}")
aux_source_directory(. ${build_temp}cpps)
include_directories(.)
message("${build_temp}cpps find cpps : ${${build_temp}cpps}")
add_executable(${build_temp} ${${build_temp}cpps}

        #以下为common_funcs 的cpp文件
        ${PROJECT_SOURCE_DIR}/common_funcs.cpp ${PROJECT_SOURCE_DIR}/boost_log_init.cpp

        #编译器不认aux到的cpp文件，不进行符号表处理，只能手动变一遍
        #如果发布，删除以下内容

        )
#copy required files to run path, if not needed, delete following
add_custom_command(
        TARGET ${build_temp}
        COMMAND echo copying files:
        COMMAND cp -v ${PROJECT_SOURCE_DIR}/properties/boost_log_settings.ini `pwd`/
        COMMAND echo copying files is finished.
)
add_definitions(-DBOOST_LOG_DYN_LINK)

target_link_libraries(${build_temp}  gtest pthread boost_log boost_log_setup boost_thread boost_system)

message("${build_temp} cmake finish\n###############################\n")