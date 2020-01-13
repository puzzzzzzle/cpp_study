//
// Created by tao on 19-1-17.
//
#include "log_init.hpp"
#include "log_macro.h"
#include <gtest/gtest.h>
#include <thread>


#include "udp_svr.h"
#include "udp_cli.h"

TEST(test_test, 1) {
    EXPECT_EQ(1, 1);
}

TEST(send_test, hello) {
    const char *hello = "hello";
    const char *echo_hello = "echo:hello";
    char receive_buff[MAX_LINE_LEN];
    int receive_len = do_request(hello, strlen(hello), receive_buff, sizeof(receive_buff));
    receive_buff[receive_len]='\0';
    EXPECT_EQ(receive_len, strlen(echo_hello));
    EXPECT_STREQ(echo_hello, receive_buff);
}

extern bool is_run;

int main(int argc, char **argv) {
    int result;
    log_init();
    INFO("log4cplus start!");
    testing::InitGoogleTest(&argc, argv);

    std::thread t([]() {
        if (start_svr()) {
            ERROR("start svr err,now quit!");
            exit(-1);
        }
    });

    //wait for the svr start finish
    sleep(1);

    result = RUN_ALL_TESTS();

    //stop the svr
    is_run = false;
    char buff[20];
    do_request("s", strlen("s"),buff , sizeof(buff));

    t.detach();
    return result;
}