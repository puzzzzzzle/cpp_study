### copy all cmakelist and main to your dir,add_subdir in your own cmakelist
set(build_temp ip6_svr_ip4_cli)

message("\n###############################\nstart cmake ${build_temp}")
aux_source_directory(. ${build_temp}cpps)
include_directories(.)
message("${build_temp}cpps find cpps : ${${build_temp}cpps}")
add_executable(${build_temp} ${${build_temp}cpps}
        #编译器不认aux到的cpp文件，不进行符号表处理，只能手动变一遍
        #如果发布，删除以下内容

        svr.cpp svr.h cli.cpp cli.h)

add_custom_command(
        TARGET ${build_temp}
        COMMAND echo copying files:
        COMMAND cp -v ${PROJECT_SOURCE_DIR}/properties/log4cplus_root.properties `pwd`/
        COMMAND echo copying files is finished.
)

target_link_libraries(${build_temp} log4cplus gtest pthread)

message("${build_temp} cmake finish\n###############################\n")