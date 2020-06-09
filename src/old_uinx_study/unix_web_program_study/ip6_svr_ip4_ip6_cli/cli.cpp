//
// Created by tao on 19-1-18.
//

#include "cli.h"

#include <arpa/inet.h>
#include <log_macro.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>

ssize_t do_request(const char *msg, ssize_t len, char *receive_buff,
                   size_t buff_len, const char *addr, const char *port) {
  int client_fd, get_addr_res;
  ssize_t send_len;
  addrinfo hints, *res;

  if ((client_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) <= 0) {
    FATAL("svr socket get err fd : " << client_fd)
    exit(-1);
  }

  hints.ai_family = AF_INET;
  if ((get_addr_res = getaddrinfo(addr, port, &hints, &res)) != 0) {
    FATAL("getaddrinfo err!:" << strerror(get_addr_res))
    exit(-2);
  }
  if (connect(client_fd, res->ai_addr, res->ai_addrlen)) {
    FATAL("connect err! : " << strerror(errno))
    exit(-2);
  }

  freeaddrinfo(res);
  if ((send_len = send(client_fd, msg, len, 0)) != len) {
    ERROR("need to send : " << len << " real send : " << send_len)
  }

  return recv(client_fd, receive_buff, buff_len, 0);
}

// todo 在127.0.0.1 上使用ip4访问ip6失败(127.0.0.1   ::1)
ssize_t do_requestv4(const char *msg, ssize_t len, char *receive_buff,
                     size_t buff_len, const char *addr, int port) {
  // init addr
  int client_fd;
  sockaddr_in svr_addr{};
  ssize_t send_len;

  if ((client_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) <= 0) {
    FATAL("svr socket get err fd : " << client_fd)
    exit(-1);
  }

  svr_addr.sin_family = AF_INET;
  if (inet_pton(AF_INET, addr, &svr_addr.sin_addr.s_addr) != 1) {
    FATAL("translate ip address err!")
    exit(-2);
  }
  svr_addr.sin_port = htons(port);

  if (connect(client_fd, (sockaddr *)&svr_addr, sizeof(svr_addr))) {
    FATAL("connect err! : " << strerror(errno))
    exit(-2);
  }
  if ((send_len = send(client_fd, msg, len, 0)) != len) {
    ERROR("need to send : " << len << " real send : " << send_len)
  }

  shutdown(client_fd, SHUT_WR);
  return recv(client_fd, receive_buff, buff_len, 0);
}

ssize_t do_requestv6(const char *msg, ssize_t len, char *receive_buff,
                     size_t buff_len, const char *addr, int port) {
  // init addr
  int client_fd;
  sockaddr_in6 svr_addr{};
  ssize_t send_len;

  if ((client_fd = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP)) <= 0) {
    FATAL("svr socket get err fd : " << client_fd)
    exit(-1);
  }

  // address
  svr_addr.sin6_family = AF_INET6;
  if (inet_pton(AF_INET6, addr, &svr_addr.sin6_addr.__in6_u) != 1) {
    FATAL("translate host err" << strerror(errno))
    exit(-2);
  }
  svr_addr.sin6_port = htons(port);

  if (connect(client_fd, (sockaddr *)&svr_addr, sizeof(svr_addr))) {
    FATAL("connect err! : " << strerror(errno))
    exit(-2);
  }
  DEBUG("start send")
  if ((send_len = send(client_fd, msg, len, 0)) != len) {
    ERROR("need to send : " << len << " real send : " << send_len)
  }
  shutdown(client_fd, SHUT_WR);
  DEBUG("end send")
  return recv(client_fd, receive_buff, buff_len, 0);
}