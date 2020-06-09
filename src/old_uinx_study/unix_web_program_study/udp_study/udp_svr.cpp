//
// Created by tao on 19-1-17.
//

#include "udp_svr.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#include <csignal>
#include <cstring>

#include "log_macro.h"

bool is_run = true;

static int svr_fd = -1;
static const char *echo = "echo:";

void exit_to_clear() {
  INFO("svr exited,will clean the env!")
  if (svr_fd > 0) {
    close(svr_fd);
  }
}

int start_svr() {
  atexit(exit_to_clear);
  signal(SIGINT, [](int sig) {
    is_run = false;
    exit(0);
  });
  // init addr
  sockaddr_in svr_addr{};

  if ((svr_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) <= 0) {
    ERROR("svr socket get err fd : " << svr_fd)
    exit(-1);
  }

  svr_addr.sin_family = AF_INET;
  if (inet_pton(AF_INET, ADDR, &svr_addr.sin_addr.s_addr) != 1) {
    ERROR("translate ip address err!")
    exit(-2);
  }
  svr_addr.sin_port = htons(PORT);
  if (bind(svr_fd, (sockaddr *)&svr_addr, sizeof(svr_addr))) {
    ERROR("bind err!")
    exit(-2);
  }

  // start svr
  sockaddr_in client_addr{};
  socklen_t client_addr_len;
  char read_buff[MAX_LINE_LEN], write_buff[MAX_LINE_LEN],
      svr_buff[MAX_LINE_LEN];
  ssize_t read_len;

  while (is_run) {
    client_addr_len = sizeof(client_addr);
    read_len = recvfrom(svr_fd, read_buff, sizeof(read_buff), 0,
                        (sockaddr *)&client_addr, &client_addr_len);
    INFO("receive from " << inet_ntop(AF_INET, &client_addr.sin_addr.s_addr,
                                      svr_buff, sizeof(svr_buff))
                         << ":" << ntohs(client_addr.sin_port))
    if (read_len <= 0) {
      ERROR("read err!")
      continue;
    }
    do_response(svr_fd, &client_addr, client_addr_len, read_buff, read_len,
                write_buff, sizeof(write_buff));
  }

  return 0;
}

void do_response(int fd, sockaddr_in *client_addr, socklen_t len,
                 char *read_buff, ssize_t read_len, char *write_buff,
                 ssize_t write_len) {
  strncpy(write_buff, echo, strlen(echo));
  strncpy(write_buff + strlen(echo), read_buff, write_len - strlen(echo));
  sendto(fd, write_buff, strlen(write_buff), 0, (sockaddr *)client_addr, len);
}
