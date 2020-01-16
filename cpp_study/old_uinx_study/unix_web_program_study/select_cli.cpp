//
// Created by tao on 18-12-30.
//

#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>

const char *SVR_ADDRESS = "127.0.0.1";
const int   PORT        = 8951;
#define MAX_LINE_LENGTH 1024

int main(int argc, char **argv) {
    char svr_buff[MAX_LINE_LENGTH];
    //设置地址
    sockaddr_in svr_address{};
    svr_address.sin_family = AF_INET;
    if (inet_pton(AF_INET, SVR_ADDRESS, &svr_address.sin_addr.s_addr) != 1) {
        perror("init address wrong");
        exit(0);
    }
    svr_address.sin_port = htons(PORT);
    printf("svr will start at : %s:%d\n", inet_ntop(AF_INET, &svr_address.sin_addr.s_addr, svr_buff, sizeof(svr_buff)), ntohs(svr_address.sin_port));

    //创建套接字
    int client_fd;
    if ((client_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        perror("create socket err:");
        return -1;
    }
    //连接
    if (connect(client_fd, (sockaddr *)&svr_address, sizeof(svr_address))) {
        perror("conn err:");
        close(client_fd);
        return -1;
    }
    printf("conn finish\n");

    //数据
    char send_buff[MAX_LINE_LENGTH], receive_buff[MAX_LINE_LENGTH];
    memset(send_buff, 0, sizeof(send_buff));
    memset(receive_buff, 0, sizeof(receive_buff));

    size_t receive_size;

    //    while (true) {
    //    read_size=readn(STDIN_FILENO,send_buff, sizeof(send_buff))
    scanf("%s", send_buff);
    //        if (strcmp(send_buff, "bye") == 0) {
    //            break;
    //        }
    if (send(client_fd, send_buff, strlen(send_buff), 0) <= 0) {
        perror("write err!");
        exit(-1);
    }
    shutdown(client_fd, SHUT_WR);
    if ((receive_size = recv(client_fd, receive_buff, sizeof(receive_buff), 0)) < 0) {
        perror("get err!");
        exit(-1);
    }
    write(STDOUT_FILENO, receive_buff, receive_size);
    putc('\n', stdout);
    //    }
    close(client_fd);
    return 0;
}