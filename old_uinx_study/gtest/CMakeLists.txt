aux_source_directory(. GTEST_CPPS)
include_directories(.)
message("find cpps : ${GTEST_CPPS}")
add_executable(gtest_study ${GTEST_CPPS})

add_custom_command(
        TARGET gtest_study
        COMMAND cp -v ${PROJECT_SOURCE_DIR}/gtest/log4cplus_root.properties `pwd`/
        )

target_link_libraries(gtest_study log4cplus gtest pthread)

message("gtest cmake finish\n")