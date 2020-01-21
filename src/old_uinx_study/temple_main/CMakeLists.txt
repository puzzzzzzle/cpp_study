
aux_source_directory(. ${build_temp}cpps)
include_directories(.)

add_executable(${build_temp} ${${build_temp}cpps}

        #以下为common_funcs 的cpp文件
        ${PROJECT_SOURCE_DIR}/common_funcs.cpp ${PROJECT_SOURCE_DIR}/log_init_new.cpp

        #编译器不认aux到的cpp文件，不进行符号表处理，只能手动变一遍
        #如果发布，删除以下内容

        )
#copy required files to run path, if not needed, delete following
add_custom_command(
        TARGET ${build_temp}
        COMMAND echo copying files:
        COMMAND cp -v ${PROJECT_SOURCE_DIR}/properties/log4cplus_root.properties `pwd`/
        COMMAND echo copying files is finished.
)

target_link_libraries(${build_temp} log4cplus gtest pthread)
