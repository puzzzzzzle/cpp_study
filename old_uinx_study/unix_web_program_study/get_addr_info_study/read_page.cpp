//
// Created by tao on 19-2-22.
//

#include "boost_log_init.h"
#include <netdb.h>
#include "read_page.h"

int read_page(const char *host, const char *port) {

    addrinfo hints{}, *res, *iterator;
    char buff[1000];
    int client_fd;
    ssize_t read_len;
    const char *head = "GET / HTTP/1.1\nHost: www.baidu.com\nConnection: close\n\n";
    hints.ai_family = AF_INET;
    if (getaddrinfo(host, port, &hints, &res) || res == nullptr) {
        PERROR("err when get addr info")
        return -1;
    }

    if ((client_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        PERROR("err when socket")
        return -1;
    }

    iterator = res;
    while (iterator != nullptr && connect(client_fd, iterator->ai_addr, iterator->ai_addrlen)) {
        PERROR("err when socket")
        iterator = res->ai_next;
    }
    freeaddrinfo(res);
    if (iterator == nullptr) {
        FATAL("conn failed")
        return -1;
    }
    if (send(client_fd, head, strlen(head), 0) < 0) {
        PERROR("err when send")
        return -1;
    }

    while ((read_len = recv(client_fd, buff, sizeof(buff) - 1, 0)) > 0) {
        buff[read_len] = '\0';
        INFO("recv :\n" << buff)
    }
    close(client_fd);

    return 0;
}
