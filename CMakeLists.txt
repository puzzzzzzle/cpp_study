cmake_minimum_required(VERSION 3.14.3)
project(cpp_study_all)


################################## 通用配置 ####################################
# 环境
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#选项

option(boost_static
        "use static boost lib"
        ON)
option(use_boost_log
        "use boost log for logger"
        ON)

### 设置编译flags
message("cmake build type : ${CMAKE_BUILD_TYPE}")

set(CMAKE_CXX_FLAGS "-fPIC ${CMAKE_CXX_FLAGS}")

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "-Wall -O0  -g -ggdb ${CMAKE_CXX_FLAGS}")
elseif ("${CMAKE_BUILD_TYPE}}" STREQUAL "Release")
    set(CAKE_CXX_FLAGS "-O3 -Wall ${CMAKE_CXX_FLAGS}")
else ()
    message("unknow type:${CMAKE_BUILD_TYPE}")
endif ()
message("cmake cxx build flags:${CMAKE_CXX_FLAGS}\n")

#设置版本号
set(VERSION_MAJOR 1.1)
set(VERSION_MINOR 0)
#配置版本号的映射文件，方便代码中使用
configure_file(
        "${PROJECT_SOURCE_DIR}/common/common_include/common_configure.h.in"
        "${PROJECT_BINARY_DIR}/convent/common_configure.h"
)
## 复制配置文件
configure_file(${PROJECT_SOURCE_DIR}/common/properties/boost_log_settings.ini ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/configure/boost_log_settings.ini)

# 头文件
include_directories(${PROJECT_SOURCE_DIR}/common/common_include)
include_directories(${PROJECT_BINARY_DIR}/convent)
include_directories(${PROJECT_SOURCE_DIR}/common/third_party_include)

# 通用cpp文件
#set(common_cpps ${PROJECT_SOURCE_DIR}/common/common_include/common_funcs.cpp
#        ${PROJECT_SOURCE_DIR}/common/common_include/log_init.cpp)
aux_source_directory(${PROJECT_SOURCE_DIR}/common/common_include common_cpps)

# 私有库文件
link_directories(${PROJECT_SOURCE_DIR}/common/lib)

################################## 项目配置  ####################################

#log 选项
if (use_boost_log)
    add_definitions(-DLOG_BOOST)
endif ()


#boost dynamic
if (boost_static)
    message("boost log static")
    set(Boost_USE_STATIC_LIBS ON)
    # add_definitions(-DBOOST_LOG_NO_THREADS)     #单线程，多线程经常出问题
else ()
    message("boost log DYN")

    set(Boost_USE_STATIC_LIBS OFF)
    add_definitions(-DBOOST_ALL_DYN_LINK)
    add_definitions(-DBOOST_LOG_DYN_LINK)
    # add_definitions(-DBOOST_LOG_NO_THREADS)     #单线程，多线程经常出问题
endif ()

################################# 动态链接库 以废弃使用Conanfile 管理 #########################################

# #gtest
# find_package(gtest REQUIRED)
# include_directories(${GTEST_INCLUDE_DIRS})


# find_package(Boost REQUIRED COMPONENTS thread log_setup log system filesystem)
# include_directories(${Boost_INCLUDE_DIRS})


# #protobuf
# find_package(Protobuf REQUIRED)
# if(PROTOBUF_FOUND)
#    message(STATUS "protobuf library found")
# else()
#     message(FATAL_ERROR "protobuf library is needed but cant be found")
# endif()
# include_directories(${PROTOBUF_INCLUDE_DIRS})


# # set libs
# set(libs pthread ${GTEST_LIBRARIES} ${Boost_LIBRARIES})

# # show libs
# if (show_lib)
#     if (GTEST_FOUND)
#         message("gtest lib:    ${GTEST_LIBRARIES}")
#         message("gtest inc:    ${GTEST_INCLUDE_DIRS}")
#     endif ()
#     if (Boost_FOUND)
#         message("boost lib:    ${Boost_LIBRARIES}")
#         message("boost inc:    ${Boost_INCLUDE_DIRS}")
#     endif ()
#     message("all libs:    ${libs}")
# endif ()
################################## conan ####################################


include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()


################################## 遍历文件 begin ####################################


set(auto_analisis_dir_list ${PROJECT_SOURCE_DIR}/templates/ ${PROJECT_SOURCE_DIR}/old_stl/ ${PROJECT_SOURCE_DIR}/libgo_study/ ${PROJECT_SOURCE_DIR}/cpp_language/)
foreach (auto_analisis_dir ${auto_analisis_dir_list})
    execute_process(
            COMMAND ls ${auto_analisis_dir}
            OUTPUT_VARIABLE dirs)
    message("find files : \n${dirs}")
    string(REPLACE "\n" ";" RPLACE_LIST ${dirs})

    foreach (f ${RPLACE_LIST})
        message("process dir :${f}")
        add_subdirectory(${auto_analisis_dir}${f})
    endforeach (f ${RPLACE_LIST})
endforeach ()
