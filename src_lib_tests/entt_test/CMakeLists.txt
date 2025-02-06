aux_source_directory(. ${CURRENT_TASK}_SRCS)
include_directories(.)

include(FetchContent)
FetchContent_Declare(
        entt
        GIT_REPOSITORY https://github.com/skypjack/entt.git
        GIT_TAG master
        SOURCE_DIR ${CMAKE_SOURCE_DIR}/exts/entt
)
FetchContent_MakeAvailable(entt)

include_directories(${CMAKE_SOURCE_DIR}/exts)

# 可执行文件
add_executable(${CURRENT_TASK} ${${CURRENT_TASK}_SRCS})

#通用动态链接库
target_link_libraries(${CURRENT_TASK} PRIVATE ${COMMON_LIBS} EnTT::EnTT)
