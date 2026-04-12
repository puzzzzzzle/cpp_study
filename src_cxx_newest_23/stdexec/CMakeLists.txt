include(FetchContent)
FetchContent_Declare(
    stdexec
    GIT_REPOSITORY https://github.com/NVIDIA/stdexec.git
    GIT_TAG        main
    GIT_SHALLOW    TRUE
)
set(STDEXEC_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(STDEXEC_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(stdexec)

aux_source_directory(. ${CURRENT_TASK}_SRCS)
include_directories(.)

message("SRCS: ${${CURRENT_TASK}_SRCS}")
add_executable(${CURRENT_TASK} ${${CURRENT_TASK}_SRCS})

target_link_libraries(${CURRENT_TASK} ${COMMON_LIBS} STDEXEC::stdexec)
