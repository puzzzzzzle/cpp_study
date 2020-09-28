cmake_minimum_required(VERSION 3.7)
set(project_name cpp_study_all)
project(${project_name})

#option(USE_32BITS "Compile for 32bits processors(linux only)" ON)
#
#if(USE_32BITS)
#    message(STATUS "using 32bits")
#    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32")
#
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
#
#else()
#endif(USE_32BITS)


include(${CMAKE_SOURCE_DIR}/common/CMake/FuncDefs.cmake)

#设置版本号
set(VERSION_MAJOR 1.2)
set(VERSION_MINOR 0)
# 选项
option(boost_static "use static boost lib" ON)
#log 选项
#add_definitions(-DLOG_BOOST)


# 公用定义,需要在设定完成后include
include(${CMAKE_SOURCE_DIR}/common/CMake/CommonInclude.cmake)

# 加载conan
set(CONAN_LIBS "")
execute_process(
        COMMAND conan install ..
)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
message("conan get libs\t${CONAN_LIBS}\n")

# 编译ptoro, 所有proto 打包为一个定义 PTOTO_CPPS
set(PROTO_CPP_DIR ${CMAKE_BINARY_DIR}/proto)
BuildProto(${CMAKE_SOURCE_DIR}/src ${PROTO_CPP_DIR})
include_directories(${PROTO_CPP_DIR})
aux_source_directory(${PROTO_CPP_DIR} PROTO_CPPS)

# 遍历文件
AddAllSubDir()



