aux_source_directory(. ${CURRENT_TASK}_SRCS)
include_directories(.)
# 查找ICU库
find_package(ICU REQUIRED COMPONENTS uc i18n data)

# 可执行文件
add_executable(${CURRENT_TASK} ${${CURRENT_TASK}_SRCS} )

#通用动态链接库
target_link_libraries(${CURRENT_TASK} ${COMMON_LIBS} ${ICU_LIBRARIES})
# 打印链接命令
get_target_property(LINK_LIBS ${CURRENT_TASK} LINK_LIBRARIES)
message("Link libraries for ${CURRENT_TASK}: ${LINK_LIBS}")