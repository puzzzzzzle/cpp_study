# 环境
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 开启nasm支持
set(CMAKE_NASM_LINK_EXECUTABLE "ld <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")
set(CAN_USE_ASSEMBLER TRUE)
set(CMAKE_ASM_NASM_OBJECT_FORMAT elf64)
enable_language(ASM_NASM)

# 开启gas(at&t)支持
enable_language(ASM)
if(UNIX)
    set(CMAKE_ASM${ASM_DIALECT}_OUTPUT_EXTENSION .o)
else()
    set(CMAKE_ASM${ASM_DIALECT}_OUTPUT_EXTENSION .obj)
endif()

set(CMAKE_ASM${ASM_DIALECT}_COMPILE_OBJECT "<CMAKE_ASM${ASM_DIALECT}_COMPILER> <INCLUDES> <FLAGS> -o <OBJECT> <SOURCE>")

set(CMAKE_ASM${ASM_DIALECT}_CREATE_STATIC_LIBRARY
        "<CMAKE_AR> cr <TARGET> <LINK_FLAGS> <OBJECTS> "
        "<CMAKE_RANLIB> <TARGET> ")

set(CMAKE_ASM${ASM_DIALECT}_LINK_EXECUTABLE
        "<CMAKE_LINKER> <FLAGS> <CMAKE_ASM${ASM_DIALECT}_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")

# to be done
set(CMAKE_ASM${ASM_DIALECT}_CREATE_SHARED_LIBRARY)
set(CMAKE_ASM${ASM_DIALECT}_CREATE_SHARED_MODULE)

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

#配置版本号的映射文件，方便代码中使用
configure_file(
        "${PROJECT_SOURCE_DIR}/common/common_include/common_configure.h.in"
        "${PROJECT_BINARY_DIR}/convent/common_configure.h"
)
## 复制配置
file(COPY common/data DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/)
# 头文件
include_directories(${PROJECT_SOURCE_DIR}/common/common_include)
include_directories(${PROJECT_SOURCE_DIR}/common/platform)

include_directories(${PROJECT_BINARY_DIR}/convent)
include_directories(${PROJECT_SOURCE_DIR}/common/third_party_include)
# 通用cpp文件
aux_source_directory(${PROJECT_SOURCE_DIR}/common/common_include common_cpps)
# 私有库文件
link_directories(${PROJECT_SOURCE_DIR}/common/lib)



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
