# 打印编译选项
function(PrintCxxFlag)
    message("CMAKE_CXX_FLAGS flags:${CMAKE_CXX_FLAGS}")
    message("CMAKE_C_FLAGS flags:${CMAKE_C_FLAGS}")
endfunction()

# 打印所有变量
function(PrintAllVars)
    get_cmake_property(_variableNames VARIABLES)
    foreach (_variableName ${_variableNames})
        message(STATUS "${_variableName}=${${_variableName}}")
    endforeach ()
endfunction()


# 获取目录的子目录
function(GetSubCMakeDirs DIR RESULT)
    file(GLOB_RECURSE cmake_files "${DIR}/CMakeLists.txt")
    foreach (cmake_file ${cmake_files})
        get_filename_component(path ${cmake_file} DIRECTORY)
        list(APPEND ${RESULT} ${path})
    endforeach()
    set(${RESULT} ${${RESULT}} PARENT_SCOPE)
endfunction()

# 添加所有子目录到编译列表中
function(AddAllSubDir)
    foreach (SRC_DIR_ROOT ${SRC_DIR_ROOTS})
        message("- ${SRC_DIR_ROOT}")
        include_directories(${SRC_DIR_ROOT})
        set(SUB_DIRS "")
        GetSubCMakeDirs(${SRC_DIR_ROOT} SUB_DIRS)

        foreach (DIR ${SUB_DIRS})
            # 给个默认目标名字: 相对 CMAKE_SOURCE_DIR 路径
            string(REPLACE "${CMAKE_SOURCE_DIR}/" "" RELATIVE_DIR ${DIR})
            string(REGEX REPLACE "/" "_" CURRENT_TASK ${RELATIVE_DIR})
            set(BUILD_ABS_PATH ${DIR})
            message("  - ${CURRENT_TASK}")
            add_subdirectory(${BUILD_ABS_PATH})
        endforeach ()
    endforeach ()
endfunction()

# 设置二进制输出目录
function(SetBinDir Dir)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${Dir} PARENT_SCOPE)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${Dir} PARENT_SCOPE)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${Dir} PARENT_SCOPE)
endfunction()

# 开启 asm 支持
function(OpenAsmSupport)
    set(CAN_USE_ASSEMBLER TRUE PARENT_SCOPE)

    # 开启nasm支持
    enable_language(ASM_NASM)

    # 开启gas(at&t)支持
    enable_language(ASM)


    # message("ASM_COMPILER : <CMAKE_ASM${ASM_DIALECT}_COMPILER>")
    # TODO
    set(CMAKE_ASM${ASM_DIALECT}_COMPILE_OBJECT "<CMAKE_ASM${ASM_DIALECT}_COMPILER> <INCLUDES> <FLAGS> -o <OBJECT> <SOURCE>" PARENT_SCOPE)
    set(CMAKE_ASM${ASM_DIALECT}_CREATE_STATIC_LIBRARY
            "<CMAKE_AR> cr <TARGET> <LINK_FLAGS> <OBJECTS> "
            "<CMAKE_RANLIB> <TARGET> " PARENT_SCOPE)
    set(CMAKE_ASM${ASM_DIALECT}_LINK_EXECUTABLE
            "<CMAKE_LINKER> <FLAGS> <CMAKE_ASM${ASM_DIALECT}_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>" PARENT_SCOPE)

    # TODO
    set(CMAKE_ASM${ASM_DIALECT}_CREATE_SHARED_LIBRARY PARENT_SCOPE)
    set(CMAKE_ASM${ASM_DIALECT}_CREATE_SHARED_MODULE PARENT_SCOPE)
endfunction()

# 设置常用编译选项
function(SetCommonBuildFlag)
    # 公用定义,需要在设定完成后include
    if (WIN32)
        MESSAGE(STATUS "Now is windows")
    elseif (UNIX OR APPLE)
        MESSAGE(STATUS "Now is UNIX-like OS's.")
        message("cmake build type : ${CMAKE_BUILD_TYPE}")
        if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
            set(CMAKE_CXX_FLAGS " -ldl ${CMAKE_CXX_FLAGS} -fPIC -ggdb3 -g3 -fno-omit-frame-pointer" PARENT_SCOPE)
            set(CMAKE_C_FLAGS " -ldl ${CMAKE_C_FLAGS} -fPIC -ggdb3 -g3 -fno-omit-frame-pointer" PARENT_SCOPE)
        elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
            # 开O3了
            set(CMAKE_CXX_FLAGS "-ldl ${CMAKE_CXX_FLAGS} -fPIC -O3" PARENT_SCOPE)
            set(CMAKE_C_FLAGS "-ldl ${CMAKE_C_FLAGS} -fPIC -O3" PARENT_SCOPE)
        else ()
            message("unknow type:${CMAKE_BUILD_TYPE}")
        endif ()
        set(LINK_FLAGS "${LINK_FLAGS} -fPIC")

    endif ()

    if (STD_LOG_SYNC)
        message("std log use lock")
        add_definitions(-DSTD_LOG_SYNC)
    endif ()
endfunction()

#配置版本号的映射文件，方便代码中使用
function(GenConfig)
    configure_file(
            "${BOOTSTRAP_DIR}/common/common_include/common_configure.h.in"
            "${PROJECT_BINARY_DIR}/convent/common_configure.h"
    )
    ## 复制配置
    message("${BOOTSTRAP_DIR} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
    file(COPY ${CONFIG_DIR} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/)
    # 头文件
    include_directories(${BOOTSTRAP_DIR}/common/common_include)

    include_directories(${PROJECT_BINARY_DIR}/convent)
endfunction()

#设置compiler版本信息
function(SetCompilerVersion)
    if (CMAKE_COMPILER_IS_GNUCC)
        execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpfullversion -dumpversion
                OUTPUT_VARIABLE GCC_VERSION)
        string(REGEX MATCHALL "[0-9]+" GCC_VERSION_COMPONENTS ${GCC_VERSION})
        list(GET GCC_VERSION_COMPONENTS 0 GCC_MAJOR)
        list(GET GCC_VERSION_COMPONENTS 1 GCC_MINOR)
        message(STATUS "cmake version=${CMAKE_VERSION}")
        set(GCC_VERSION "${GCC_MAJOR}.${GCC_MINOR}" PARENT_SCOPE)
        message(STATUS "gcc version=${GCC_VERSION}")
        message(STATUS "gcc version major=${GCC_MAJOR}")
        message(STATUS "gcc version minor=${GCC_MINOR}")
    endif ()
    include(CheckCXXCompilerFlag)

    # 先检测C++23
    check_cxx_compiler_flag("-std=c++23" COMPILER_SUPPORTS_CXX23)
    if (COMPILER_SUPPORTS_CXX23)
        message(STATUS "this compiler supports C++23")
        set(CMAKE_CXX_STANDARD 23 PARENT_SCOPE)
    else()
        # 再检测C++20
        check_cxx_compiler_flag("-std=c++20" COMPILER_SUPPORTS_CXX20)
        if (COMPILER_SUPPORTS_CXX20)
            message(STATUS "this compiler supports C++20")
            set(CMAKE_CXX_STANDARD 20 PARENT_SCOPE)
        else()
            message(STATUS "falling back to C++17")
            set(CMAKE_CXX_STANDARD 17 PARENT_SCOPE)
        endif()
    endif()
endfunction()

# 查找公用依赖
function(FindCommonLib)
    set(LIBS_LIST ${COMMON_LIBS})

    add_library(before_main OBJECT ${BOOTSTRAP_DIR}/common/before_main_funcs/before_main.cpp)

    list(APPEND LIBS_LIST "before_main")

    list(APPEND LIBS_LIST "pthread")


    find_package(GTest REQUIRED)
    message("GTest find ${GTEST_INCLUDE_DIRS} ${GTEST_LIBRARIES}")
    list(APPEND LIBS_LIST ${GTEST_LIBRARIES})

    if (LOG_USE_BOOST)
        add_definitions(-DLOG_BOOST)
        list(APPEND CURR_BOOST log log_setup)
        set(BOOST_LIBS "")
        FindBoostLib(CURR_BOOST BOOST_LIBS)
        list(APPEND LIBS_LIST ${BOOST_LIBS})
    endif ()

    message("LIBS_LIST ${LIBS_LIST}")
    set(COMMON_LIBS ${LIBS_LIST} PARENT_SCOPE)

endfunction()

# 查找boost
function(FindBoostLib COMPONENTS_LIST RESULT)
    # boost log 需要的信息
    add_definitions(-DBOOST_LIB_DIAGNOSTIC)
    if (BOOST_USE_STATIC_LINK)
        set(Boost_USE_STATIC_LIBS ON)
    else ()
        #        add_definitions(-DBOOST_ALL_DYN_LINK)
    endif ()
    if (NOT ${COMPONENTS_LIST})
        return()
    endif ()
    # find libs
    set(BOOST_FIND_LIBS "")
    find_package(Boost CONFIG REQUIRED COMPONENTS ${${COMPONENTS_LIST}})
    if (Boost_FOUND)
        include_directories(${Boost_INCLUDE_DIRS})
        list(APPEND BOOST_FIND_LIBS ${Boost_LIBRARIES})
    endif ()
    set(${RESULT} ${BOOST_FIND_LIBS} PARENT_SCOPE)
endfunction()

# 开启协程
function(OpenCoroutine)
    if (APPLE)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcoroutines-ts" PARENT_SCOPE)
    elseif (WIN32 OR UNIX)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcoroutines" PARENT_SCOPE)
    endif ()
endfunction()