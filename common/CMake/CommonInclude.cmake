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

### 设置编译flags
message("cmake build type : ${CMAKE_BUILD_TYPE}")
set(CMAKE_CXX_FLAGS "-fPIC ${CMAKE_CXX_FLAGS}")
if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "-Wall -O0  -g -ggdb -Warray-bounds=2 ${CMAKE_CXX_FLAGS}")
elseif ("${CMAKE_BUILD_TYPE}}" STREQUAL "Release")
    set(CAKE_CXX_FLAGS "-O3 -Wall -Warray-bounds=2 ${CMAKE_CXX_FLAGS}")
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
include_directories(${PROJECT_BINARY_DIR}/convent)
include_directories(${PROJECT_SOURCE_DIR}/common/third_party_include)
# 通用cpp文件
aux_source_directory(${PROJECT_SOURCE_DIR}/common/common_include common_cpps)
# 私有库文件
link_directories(${PROJECT_SOURCE_DIR}/common/lib)


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
