//
// Created by tao on 19-1-17.
//
#include <arpa/inet.h>
#include <gtest/gtest.h>
#include <netdb.h>
#include <netinet/in.h>

#include <thread>

#include "boost_log_init.h"
#include "read_page.h"

TEST(test_test, 1) { EXPECT_EQ(1, 1); }

int main(int argc, char **argv) {
    int result, back;
    log_init();
    testing::InitGoogleTest(&argc, argv);

    result = RUN_ALL_TESTS();

    const char *name = "www.baidu.com";
    const char *port = "80";
    addrinfo    hints{}, *res, *res_itertor;
    hints.ai_family   = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    if ((back = getaddrinfo(name, port, &hints, &res)) || res == nullptr) {
        ERROR("something wrong heppened :" << gai_strerror(back))
    }
    res_itertor = res;
    char addr_buff[256];
    while (res_itertor != nullptr) {
        //        const char *i= inet_ntop(res_itertor->ai_family, &res_itertor->ai_addr, addr_buff,
        //                   sizeof(addr_buff));
        INFO("result : " << inet_ntop(res_itertor->ai_family, &res_itertor->ai_addr, addr_buff, sizeof(addr_buff)))
        res_itertor = res_itertor->ai_next;
    }

    freeaddrinfo(res);

    read_page("www.baidu.com", "80");

    return result;
}