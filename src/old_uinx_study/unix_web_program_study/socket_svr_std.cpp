//
// Created by tao on 18-12-30.
//
//#include <in/>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <cerrno>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include "server_confg.h"

int create_and_listen(int &server_fd, u_short port) {
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));

    //设置地址
    addr.sin_family      = AF_INET;  // ip4
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port        = htons(SVR_PORT);

    //创建socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) <= 0) {
        perror("create socket error:");
        return -1;
    }

    //绑定
    if (bind(server_fd, (sockaddr *)(&addr), sizeof(addr))) {
        perror("bind err :");
        return -1;
    }
    if (listen(server_fd, 1024)) {
        perror("listen error!:");
        return -1;
    }
    return 0;
}

int process_one(int client_fd) {
    //准备缓存
    char     buff[SHARE_BUFF_SIZE];
    size_t   read_size;
    tcp_info info;
    int      len = sizeof(info);
    getsockopt(client_fd, IPPROTO_TCP, TCP_INFO, &info, (socklen_t *)&len);
    while ((info.tcpi_state == TCP_ESTABLISHED)) {
        //读取数据
        printf("start process:%d\n", client_fd);
        if ((read_size = readn(client_fd, buff, sizeof(buff))) < 0) {
            perror("read eror :");
            return -1;
        }
        printf("received from cli :%s\n", buff);
        //写入时间信息
        time_t ticks;
        ticks = time(nullptr);
        snprintf(buff + read_size, sizeof(buff) - read_size, "\ttime:\t%s\r\n", ctime(&ticks));

        //检查结束位置
        if (buff[sizeof(buff) - 3] != '\r') {
            buff[sizeof(buff) - 3] = '\r';
            buff[sizeof(buff) - 2] = '\n';
            buff[sizeof(buff) - 1] = '\0';
        }
        printf("begin to write back :%s\n", buff);
        //写回数据
        if (writen(client_fd, buff, strlen(buff))) {
            perror("write err :");
            return -1;
        }
        printf("write back finish\n");
    }
    close(client_fd);
    return 0;
}

void m_accept(bool *run_stat, int server_fd) {
    int client_fd, child_pid;

    sockaddr_in client_addr;
    memset(&client_addr, 0, sizeof(client_addr));
    socklen_t client_addr_len = sizeof(client_addr);

    char buff[SHARE_BUFF_SIZE];

    printf("start server!%d\n", server_fd);

    while (*run_stat) {
        client_fd = accept(server_fd, (sockaddr *)&client_addr, &client_addr_len);
        if (client_fd < 0) {
            if (errno == EISCONN) {
                printf(__PRETTY_FUNCTION__);
                continue;
            }
            perror("conn err :");
            printf(__PRETTY_FUNCTION__);
            printf("\nerr number : %d\n", client_fd);
            continue;
        }
        // start process
        printf("conn from : %s:%d\n", inet_ntop(AF_INET, &client_addr.sin_addr, buff, sizeof(buff)),
               ntohs(client_addr.sin_port));
        if ((child_pid = fork()) == 0) {
            close(server_fd);
            process_one(client_fd);
            exit(0);
        }
        close(client_fd);
    }
}
void child_wait_sig(int sig) {
    pid_t child_pid;
    int   stat;
    child_pid = wait(&stat);
    printf("child no %d end! on signal %d\n", child_pid, sig);
}
int main(int argc, char **argv) {
    //创建存储
    bool run_stat = true;
    int  server_fd;
    if (signal(SIGCHLD, child_wait_sig)) {
        perror("something wrong happened when sin SIGCHLD");
        return -1;
    }
    if (create_and_listen(server_fd, SVR_PORT)) {
        perror("create svr err");
        return -1;
    }
    m_accept(&run_stat, server_fd);

    close(server_fd);
    return 0;
}