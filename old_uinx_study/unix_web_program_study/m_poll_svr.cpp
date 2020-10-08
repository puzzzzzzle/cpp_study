//
// Created by tao on 19-1-16.
//
#include "m_poll_svr.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <poll.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>

void progress_one_request(int fd, const char *__restrict read_buff,
                          size_t read_len, char *write_buff,
                          size_t write_buff_len) {
  int append_len = 5;
  strncpy(write_buff, "echo:", write_buff_len);
  int write_buff_len_rest = write_buff_len - append_len;
  memcpy(write_buff + append_len, read_buff,
         read_len < write_buff_len_rest ? read_len : write_buff_len_rest);
  send(fd, write_buff,
       (read_len + append_len) < write_buff_len ? (read_len + append_len)
                                                : write_buff_len,
       0);
}

int main(int argc, char **argv) {
  // declarer variables
  int svr_fd, conn_fd;
  int i, maxi, ready_number;
  ssize_t read_size;
  socklen_t client_address_len;
  pollfd poll_conns[MAX_POLL_ITEM];
  char read_buff[MAX_LINE_LENGTH], write_buff[MAX_LINE_LENGTH],
      svr_buff[MAX_LINE_LENGTH];
  sockaddr_in svr_address{}, client_address{};

  // init variables
  svr_address.sin_family = AF_INET;
  if (inet_pton(AF_INET, SVR_ADDRESS, &svr_address.sin_addr.s_addr) != 1) {
    perror("err happened on inet_pton");
    exit(-1);
  }
  svr_address.sin_port = htons(PORT);
  printf("svr will start at : %s:%d\n",
         inet_ntop(AF_INET, &svr_address.sin_addr.s_addr, svr_buff,
                   sizeof(svr_buff)),
         ntohs(svr_address.sin_port));

  // to bind and listen
  if ((svr_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) <= 0) {
    perror("init svr socket err");
    exit(0);
  }

  if (bind(svr_fd, (sockaddr *)&svr_address, sizeof(svr_address))) {
    perror("bind err");
    exit(0);
  }
  if (listen(svr_fd, SVR_DEQUE)) {
    perror("listen err");
    exit(0);
  }

  // init poll
  for (pollfd &fd : poll_conns) {
    fd.fd = -1;
  }
  poll_conns[0].fd = svr_fd;
  poll_conns[0].events = POLLRDNORM;
  maxi = 1;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
  while (true) {
    ready_number = poll(poll_conns, maxi + 1, -1);

    // new conn comes
    if (poll_conns[0].revents & POLLRDNORM) {
      conn_fd =
          accept(svr_fd, (sockaddr *)&client_address, &client_address_len);
      for (i = 0; i < MAX_POLL_ITEM; i++) {
        if (poll_conns[i].fd < 0) {
          poll_conns[i].fd = conn_fd;
          i++;
          break;
        }
      }
      if (i == MAX_POLL_ITEM) {
        fprintf(stderr, "too many conns");
        exit(-2);
      }
      poll_conns[i - 1].events = POLLRDNORM;
      if (i > maxi) {
        maxi = i;
      }
      if (--ready_number <= 0) {
        continue;
      }
    }

    // produce result
    for (i = 0; i < maxi; i++) {
      if (poll_conns[i].fd <= 0) {
        continue;
      }
      if (poll_conns[i].revents & (POLLRDNORM | POLLERR)) {
        if ((read_size =
                 recv(poll_conns[i].fd, read_buff, sizeof(read_buff), 0)) < 0) {
          if (errno == ECANCELED) {
            // closed by client
            close(poll_conns[i].fd);
            poll_conns[i].fd = -1;
          } else {
            fprintf(stderr, "read err!");
          }

        } else if (read_size == 0) {
          close(poll_conns[i].fd);
          poll_conns[i].fd = -1;
        } else {
          progress_one_request(poll_conns[i].fd, read_buff, read_size,
                               write_buff, sizeof(write_buff));
        }
        if (--ready_number <= 0) {
          continue;
        }
      }
    }
  }
#pragma clang diagnostic pop

  close(svr_fd);
  return 0;
}