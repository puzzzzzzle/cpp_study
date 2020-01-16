//
// Created by tao on 18-11-26.
//

#ifndef UNIXSTUDYCPP_SOCKET_MAIN_H
#define UNIXSTUDYCPP_SOCKET_MAIN_H

#include <thread>

#include "socket_client.hpp"
#include "socket_server.hpp"

using namespace std;

void socket_main() {
    std::thread t(socket_server_start);
    sleep(1);
    socket_client();
    //    t.join();
}

#endif  // UNIXSTUDYCPP_SOCKET_MAIN_H
