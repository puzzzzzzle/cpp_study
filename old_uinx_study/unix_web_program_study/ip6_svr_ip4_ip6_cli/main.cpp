//
// Created by tao on 19-1-17.
//
#include "log_init.hpp"
#include "log_macro.h"
#include <gtest/gtest.h>
#include <thread>

#include "svr.h"
#include "cli.h"

extern bool is_run;
static const char *hostv6 = "::1";
static const char *hostv4 = "127.0.0.1";

static const short port = 8965;
static char port_s[30];

TEST(test_test, 1) {
    EXPECT_EQ(1, 1);
}


TEST(send_testv6_select, hello) {
    const char *hello = "hello";
    const char *echo_hello = "echo:hello";
    char receive_buff[MAX_LINE_LEN];
//    ssize_t receive_len = do_request(hello, strlen(hello), receive_buff, sizeof(receive_buff), hostv4, port_s);
//    ssize_t receive_len = do_requestv4(hello, strlen(hello), receive_buff, sizeof(receive_buff), hostv4, port);
    ssize_t receive_len = do_requestv6(hello, strlen(hello), receive_buff, sizeof(receive_buff), hostv6, port);

    receive_buff[receive_len] = '\0';
    EXPECT_EQ(receive_len, strlen(echo_hello));
    EXPECT_STREQ(echo_hello, receive_buff);

//    std::vector<std::thread *> ts;
//    for (int i = 0; i < 4; i++) {
//        std::thread t([&ts]() {
//
//            const char *hello = "hello";
//            const char *echo_hello = "echo:hello";
//            char receive_buff[MAX_LINE_LEN];
//            ssize_t receive_len = do_requestv6(hello, strlen(hello), receive_buff, sizeof(receive_buff), hostv6,
//                                               port);
//
//            receive_buff[receive_len] = '\0';
//            EXPECT_EQ(receive_len, strlen(echo_hello));
//            EXPECT_STREQ(echo_hello, receive_buff);
//        });
//        ts.push_back(&t);
//    }
}
//TEST(send_testv4, hello) {
//    const char *hello = "hello";
//    const char *echo_hello = "echo:hello";
//    char receive_buff[MAX_LINE_LEN];
////    ssize_t receive_len = do_request(hello, strlen(hello), receive_buff, sizeof(receive_buff), hostv4, port_s);
////    ssize_t receive_len = do_requestv4(hello, strlen(hello), receive_buff, sizeof(receive_buff), hostv4, port);
//    ssize_t receive_len = do_requestv4(hello, strlen(hello), receive_buff, sizeof(receive_buff), hostv4, port);
//
//    receive_buff[receive_len] = '\0';
//    EXPECT_EQ(receive_len, strlen(echo_hello));
//    EXPECT_STREQ(echo_hello, receive_buff);
//}

int g_test(int argc, char **argv) {
    int result;
    result = RUN_ALL_TESTS();
    return result;
}

int thread_test() {
    for (int i = 0; i < 10; i++) {
        std::thread st1([]() {
            const char *hello = "hello";
            const char *echo_hello = "echo:hello";
            char receive_buff[MAX_LINE_LEN];
            ssize_t receive_len = do_requestv6(hello, strlen(hello), receive_buff, sizeof(receive_buff), hostv6, port);
            receive_buff[receive_len] = '\0';
            if(strcmp(echo_hello,receive_buff)){
                TRACE("###compare eq")
            } else{
                ERROR("###not eq get :"<<receive_buff)
            }

        });
        st1.detach();
    }
    return 0;
}

int main(int argc, char **argv) {
    log_init();
    INFO("log4cplus start!");

    snprintf(port_s, sizeof(port_s), "%d", port);

    testing::InitGoogleTest(&argc, argv);

    std::thread t([]() {
        if (start_svr_v6(hostv6, port)) {
            FATAL("start svr fail!")
            exit(-1);
        }
    });


    //wait for the svr start
    sleep(1);


    thread_test();
    //stop the svr

    sleep(1);
    is_run = false;
//    char buff[20];
//    do_requestv6("s", strlen("s"), buff, sizeof(buff), hostv6, port);
    if (t.joinable()) {
        t.join();
    }
    return 0;
}