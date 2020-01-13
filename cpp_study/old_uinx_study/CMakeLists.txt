cmake_minimum_required(VERSION 3.10)
project(UnixStudy)
set(CMAKE_CXX_STANDARD 11)


message("cmake env flags ${CMAKE_BUILD_TYPE}")

set(CMAKE_CXX_FLAGS "-fPIC ${CMAKE_CXX_FLAGS}")

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    message("build type debug!")
    set(CMAKE_CXX_FLAGS "-Wall -O0  -g -ggdb ${CMAKE_CXX_FLAGS}")
elseif ("${CMAKE_BUILD_TYPE}}" STREQUAL "Release")
    message("build type release!")
    set(CAKE_CXX_FLAGS "-O3 -Wall ${CMAKE_CXX_FLAGS}")
else ()
    message("unknow type:${CMAKE_BUILD_TYPE}")
endif ()

#设置版本号
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
#配置版本号的映射文件，方便代码中使用
configure_file(
        "${PROJECT_SOURCE_DIR}/cmake_test_configure.h.in"
        "${PROJECT_BINARY_DIR}/cmake_test_configure.h"
)

############################old unix stud endy####################
set(unix_std_old unix_std)
#头文件默认实现的
include_directories(../..)
include_directories(${PROJECT_SOURCE_DIR}/study_src/cpp_grammer)
include_directories(${PROJECT_SOURCE_DIR}/study_src/dynamtic_lib)
include_directories(${PROJECT_SOURCE_DIR}/study_src/expert_c_programmer)
include_directories(${PROJECT_SOURCE_DIR}/study_src/fileio)
include_directories(${PROJECT_SOURCE_DIR}/study_src/log4cplus_init)
include_directories(${PROJECT_SOURCE_DIR}/study_src/public_object)
include_directories(${PROJECT_SOURCE_DIR}/study_src/socket_study)
include_directories(${PROJECT_SOURCE_DIR}/study_src/sql_study)
include_directories(${PROJECT_SOURCE_DIR}/study_src/stl)
include_directories(${PROJECT_SOURCE_DIR}/study_src/thread_study)
#include_directories(${PROJECT_SOURCE_DIR}/study_src/boost_compute_test)


#通过动态链接库实现的 include_directories -> add_subdirectory -> target_link_libraries
include_directories(${PROJECT_SOURCE_DIR}/study_src/libgo_study) #包含头文件检索范围
add_subdirectory(${PROJECT_SOURCE_DIR}/study_src/libgo_study) #将子项目包含进来，一起编译

include_directories(${PROJECT_SOURCE_DIR}/study_src/boost_log_study)
add_subdirectory(${PROJECT_SOURCE_DIR}/study_src/boost_log_study)

#直接编译到目标文件 include_directories -> aux_source_directory -> add_executable
#不在演示

#解main包的目录
aux_source_directory(../.. DIRSRCS)
#添加main为可执行文件入口,并编译mian同一级的所有cpp（只能有一个main，有多个main函数的话手动指定那个
add_executable(unix_study ${DIRSRCS} log_init_new.cpp log_init_new.h)

add_definitions(-DBOOST_LOG_DYN_LINK)

#添加库文件连接
target_link_libraries(unix_study
        dl pthread
        #下面的最好由对应的子项目引用
        hiredis libgo log4cplus
        LIBGO_TEST LIBBOOST_LOG_TEST
        )

message("cxx falgs : ${CMAKE_CXX_FLAGS}")

############################old unix stud endy####################


############################unix web study#######################

include_directories(${PRIJECT_SOURTH_DIR})

aux_source_directory(unix_web_program_study unix_web)

add_executable(unix_web
        #        ${unix_web}
        #删除掉 由于IDE问题导致不在这里添加无法解析到符号 所以特意添加一次
        unix_web_program_study/io_mutiplexing_impl.cpp)
#添加库文件连接
target_link_libraries(unix_web
        dl pthread
        log4cplus
        )

add_executable(unix_svr_std ${PROJECT_SOURCE_DIR}/unix_web_program_study/socket_svr_std.cpp)
add_executable(unix_cli_std ${PROJECT_SOURCE_DIR}/unix_web_program_study/server_cli_std.cpp)

add_executable(select_svr ${PROJECT_SOURCE_DIR}/unix_web_program_study/select_svr.cpp)
add_executable(select_cli ${PROJECT_SOURCE_DIR}/unix_web_program_study/select_cli.cpp)

add_executable(poll_svr unix_web_program_study/m_poll_svr.cpp)

##### 子类可执行
add_subdirectory(${PROJECT_SOURCE_DIR}/gtest)

add_subdirectory(${PROJECT_SOURCE_DIR}/unix_web_program_study/udp_study)

add_subdirectory(${PROJECT_SOURCE_DIR}/unix_web_program_study/sctp_study)

add_subdirectory(${PROJECT_SOURCE_DIR}/unix_web_program_study/get_addr_info_study)

add_subdirectory(${PROJECT_SOURCE_DIR}/unix_web_program_study/ip6_svr_ip4_ip6_cli)

add_subdirectory(${PROJECT_SOURCE_DIR}/unix_web_program_study/nup_14)

add_subdirectory(${PROJECT_SOURCE_DIR}/unix_web_program_study/epoll_test)

add_subdirectory(${PROJECT_SOURCE_DIR}/study_src/boost_log_new)

add_subdirectory(${PROJECT_SOURCE_DIR}/c_traps)

add_subdirectory(${PROJECT_SOURCE_DIR}/unix_web_program_study/unix_local)

add_subdirectory(${PROJECT_SOURCE_DIR}/study_src/boost_filesystem_test)

########################### unix web study end ################


###########################cmake 学习与项目无关######################
#option 修改后需要删除cmake cache 从新生成，不然不会刷新状态
option(SHOW_INFO
        "show basic info"
        OFF)
if (SHOW_INFO)
    message("\n\ncmake 学习与项目无关")

    message("project path: \"${PROJECT_SOURCE_DIR}\"")
    message("SRC DIR : ${DIRSRCS}\n")

    #找文件 从指定的位置找，不会找ldconfig
    find_file(BOOST_CO libboost_coroutine.so.1.69.0 /usr/lib)
    message("BOOST_CO:${BOOST_CO}\n")

    #找一个库 必须使用库的全名
    find_library(BOOST_CO_LIB boost_coroutine)
    message("BOOST_CO_LIB : ${BOOST_CO_LIB}\n")

    #找一个库集合 通过REQUIRED找子库
    #find_package(Boost REQUIRED coroutine)

    #只会在cmakekist中生效
    macro(hello msg)
        message(${msg})
    endmacro()
    hello("tao")

    #增加一个全局宏定义
    add_definitions(-DSAY_HELLO)

endif (SHOW_INFO)
###################################################################
