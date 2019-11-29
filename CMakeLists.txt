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
set(VERSION_MAJOR 1.2)
set(VERSION_MINOR 0)
#配置版本号的映射文件，方便代码中使用
configure_file(
        "${PROJECT_SOURCE_DIR}/common/common_include/common_configure.h.in"
        "${PROJECT_BINARY_DIR}/convent/common_configure.h"
)
## 复制配置
file(COPY ${PROJECT_SOURCE_DIR}/data DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/)

# 头文件
include_directories(${PROJECT_SOURCE_DIR}/common/common_include)
include_directories(${PROJECT_BINARY_DIR}/convent)
include_directories(${PROJECT_SOURCE_DIR}/common/third_party_include)

# 通用cpp文件
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
else ()
    message("boost log DYN")

    set(Boost_USE_STATIC_LIBS OFF)
    add_definitions(-DBOOST_ALL_DYN_LINK)
    add_definitions(-DBOOST_LOG_DYN_LINK)
endif ()

# 加载conan
set(CONAN_LIBS "")
#execute_process(
#        COMMAND conan remote add -f khalid https://api.bintray.com/conan/puzzzzzzle1/khalidzhang
#        COMMAND conan install libgo/v3.1-stable@tao/test -r khalid
#        COMMAND conan install libco/v1.0@libco/tao -r khalid
#
#        COMMAND conan install .. --build missing -r=conan-center
#        OUTPUT_VARIABLE conan_info)
#message("conan out: \n${conan_info}")
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
message("conan get libs\t${CONAN_LIBS}\n")

################################## 遍历文件 begin ####################################


set(auto_analisis_dir_list
        templates
        stl_old
        libgo_study
        cpp_language
        boost_study
        libco_study
        aoi_study
        )
foreach (auto_analisis_dir ${auto_analisis_dir_list})
    file(GLOB files RELATIVE ${PROJECT_SOURCE_DIR}/${auto_analisis_dir} CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/${auto_analisis_dir}/*)
    message("- ${auto_analisis_dir}")
    foreach (f ${files})
        set(build_temp ${auto_analisis_dir}_${f})
#        message("\t ${PROJECT_SOURCE_DIR}/${auto_analisis_dir}/${f}/CMakeLists.txt")
        if (EXISTS ${PROJECT_SOURCE_DIR}/${auto_analisis_dir}/${f}/CMakeLists.txt)
            message("\t - ${build_temp}")
            add_subdirectory(${auto_analisis_dir}/${f})
        else ()
            message("\t - !!!${build_temp} without CMakeLists.txt, ignore!")
        endif ()
        #        message("\t\t - done")
    endforeach (f ${RPLACE_LIST})
endforeach ()
