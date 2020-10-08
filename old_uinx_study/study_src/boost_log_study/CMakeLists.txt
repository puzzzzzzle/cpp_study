aux_source_directory(. M_BOOST_LOG_SRCS)
message("BOOST_LOG_SRCS : ${M_BOOST_LOG_SRCS}")
add_library(LIBBOOST_LOG_TEST ${M_BOOST_LOG_SRCS})
add_definitions(-DBOOST_LOG_DYN_LINK)
#添加库文件连接
target_link_libraries(LIBBOOST_LOG_TEST
        boost_log boost_log_setup boost_system boost_thread pthread
        )