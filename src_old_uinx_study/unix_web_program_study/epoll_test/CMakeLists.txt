

aux_source_directory(. ${CURRENT_TASK}_SRCS)
include_directories(.)

add_executable(${CURRENT_TASK} ${${CURRENT_TASK}_SRCS}

        #以下为common_funcs 的cpp文件
        ${PROJECT_SOURCE_DIR}/common_funcs.cpp ${PROJECT_SOURCE_DIR}/boost_log_init.cpp
        #编译器不认aux到的cpp文件，不进行符号表处理，只能手动变一遍
        #如果发布，删除以下内容

        epoll_simple_test.hpp epoll_svr.cpp epoll_svr.h)
#copy required files to run path, if not needed, delete following
add_custom_command(
        TARGET ${CURRENT_TASK}
        COMMAND echo copying files:
        COMMAND cp -v ${PROJECT_SOURCE_DIR}/properties/boost_log_settings.ini `pwd`/
        COMMAND echo copying files is finished.
)

target_link_libraries(${CURRENT_TASK}  gtest pthread boost_log boost_log_setup boost_thread boost_system)
