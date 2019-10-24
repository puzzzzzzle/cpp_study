//
// Created by tao on 18-11-26.
//

#ifndef UNIXSTUDYCPP_SOCKET_CLIENT_HPP
#define UNIXSTUDYCPP_SOCKET_CLIENT_HPP

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include "../log4cplus_init/log_macro.h"

int socket_client() {
    //创建套接字
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    //向服务器（特定的IP和端口）发起请求
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));  //每个字节都用0填充
    serv_addr.sin_family = AF_INET;  //使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
    serv_addr.sin_port = htons(8082);  //端口
    connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

    //读取服务器传回的数据
    char buffer[40];
    read(sock, buffer, sizeof(buffer) - 1);
    printf("%s\n",buffer);
    INFO("Message form server: " << buffer << "\n");

    //关闭套接字
    close(sock);
    return 0;
}

#endif //UNIXSTUDYCPP_SOCKET_CLIENT_HPP
