
aux_source_directory(. ${CURRENT_TASK}_SRCS)
include_directories(.)

add_executable(${CURRENT_TASK} ${${CURRENT_TASK}_SRCS}

        #以下为common_funcs 的cpp文件
        ../../common_funcs.cpp ../../log_init_new.cpp

        #编译器不认aux到的cpp文件，不进行符号表处理，只能手动变一遍
        #如果发布，删除以下内容
        main.cpp
        test_alarm.cpp test_alarm.h

        )

add_custom_command(
        TARGET ${CURRENT_TASK}
        COMMAND echo copying files:
        COMMAND cp -v ${PROJECT_SOURCE_DIR}/properties/log4cplus_root.properties `pwd`/
        COMMAND echo copying files is finished.
)

target_link_libraries(${CURRENT_TASK} log4cplus gtest pthread)

