//
// Created by tao on 18-12-30.
//

#include <netinet/in.h>
#include <cstring>
#include <arpa/inet.h>
#include <cstdio>
#include <string.h>
#include <unistd.h>
#include "server_confg.h"


int main(int argc, char **argv) {
    //设置地址
    sockaddr_in svr_addr;
    memset(&svr_addr, 0, sizeof(svr_addr));
    svr_addr.sin_family = AF_INET;
//    if (inet_pton(AF_INET, SVR_ADDS, &svr_addr)) {
//        perror("change SVR_ADDRESS err ");
//        return -1;
//    }
    svr_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    svr_addr.sin_port = htons(SVR_PORT);

    //创建套接字
    int client_fd;
    if ((client_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        perror("create socket err:");
        return -1;
    }
    //连接
    if (connect(client_fd, (sockaddr *) &svr_addr, sizeof(svr_addr))) {
        perror("conn err:");
        close(client_fd);
        return -1;
    }
    printf("conn finish\n");
    //数据
    char send_buff[SHARE_BUFF_SIZE], receive_buff[SHARE_BUFF_SIZE];
    memset(send_buff, 0, sizeof(send_buff));
    memset(receive_buff, 0, sizeof(receive_buff));

    size_t receive_size;
    while (true) {
        //    read_size=readn(STDIN_FILENO,send_buff, sizeof(send_buff))
        scanf("%s", send_buff);
        if(strcmp(send_buff, "bye") == 0){
            break;
        }

        if (writen(client_fd, send_buff, strlen(send_buff))) {
            perror("write err!");
            break;
        }
        if ((receive_size = readn(client_fd, receive_buff, sizeof(receive_buff))) < 0) {
            perror("get err!");
            break;
        }
        printf("received from svr : %s", receive_buff);
    }

    close(client_fd);
    return 0;
}