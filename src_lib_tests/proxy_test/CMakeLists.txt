aux_source_directory(. ${CURRENT_TASK}_SRCS)
include_directories(.)

include(FetchContent)
FetchContent_Declare(
        proxy
        GIT_REPOSITORY https://github.com/microsoft/proxy.git
        GIT_TAG main
        SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/proxy
)
FetchContent_MakeAvailable(proxy)

# 可执行文件
add_executable(${CURRENT_TASK} ${${CURRENT_TASK}_SRCS})

#通用动态链接库
target_link_libraries(${CURRENT_TASK} ${COMMON_LIBS})
