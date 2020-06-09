//
// Created by tao on 19-1-17.
//

#include <arpa/inet.h>
#include <gtest/gtest.h>
#include <netdb.h>
#include <netinet/in.h>
#include <syslog.h>

#include <thread>

#include "common_funcs.h"
#include "test_alarm.h"
#include "timeout_socket_operator.h"

TEST(test_test, 1) { EXPECT_EQ(1, 1); }

int test_timeout() {
  int clifd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (clifd < 0) {
    FATAL("socket init err")
    return -1;
  }
  sockaddr_in addr{};
  socklen_t socklen;
  ssize_t read_len;
  char buff[1024];

  addr.sin_family = AF_INET;
  if (inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr.s_addr) != 1) {
    FATAL("tramslate addr err")
    return -1;
  }
  addr.sin_port = htons(8899);
  socklen = sizeof(addr);

  if (test_read_timeout(clifd, 1)) {
    INFO("timeout")
  } else {
    read_len =
        recvfrom(clifd, buff, sizeof(buff), 0, (sockaddr *)&addr, &socklen);
    buff[read_len] = '\0';
    INFO("read " << read_len << ":" << buff)
  }
  return 0;
}

int test_xxxmsg_func(const char *host, const char *port) {
  int client_fd;
  char buff[200];

  if ((client_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
    FATAL("err when init socket")
    return -1;
  }
  addrinfo hints{}, *res, *iterator;
  hints.ai_family = AF_INET;

  if (getaddrinfo(host, port, &hints, &res)) {
    FATAL("err when getaddrinfo")
    return -1;
  }
  iterator = res;

  while (iterator != nullptr) {
    if (connect(client_fd, iterator->ai_addr, iterator->ai_addrlen)) {
      ERROR(
          "conn to " << inet_ntop(AF_INET,
                                  &((sockaddr_in *)&iterator)->sin_addr.s_addr,
                                  buff, sizeof(buff))
                     << " err")
      continue;
    }
    break;
  }
  freeaddrinfo(res);

  if (iterator == nullptr) {
    FATAL("conn all address err")
    return -2;
  }

  // start write
  if (test_write_timeout(client_fd, 1)) {
    FATAL("write timeout")
    return -3;
  }

  ssize_t len = 0, total_len = 0;
  msghdr msg{};

  msg.msg_name = nullptr;
  msg.msg_namelen = 0;

  char read_buff[200], write_buff[1024];
  snprintf(read_buff, sizeof(read_buff),
           "GET /index.html HTTP/1.1\nHost: www.baidu.com\n\n\n");
  iovec datas{read_buff, strlen(read_buff)};
  //    datas.iov_base = read_buff;
  //    datas.iov_len = strlen(read_buff);

  msg.msg_iov = &datas;
  msg.msg_iovlen = 1;

  msg.msg_control = nullptr;
  msg.msg_controllen = 0;

  msg.msg_flags = 0;  //用于返回flags，一般别在这里设置flags，recvmsg会把sendmmsg
                      //中的flags拷贝到这里，在调用，而sendmsg直接忽略

  if ((len = sendmsg(client_fd, &msg, 0)) != (ssize_t)strlen(read_buff)) {
    ERROR("not send enough msg! " << len)
  }

  msg.msg_name = nullptr;
  msg.msg_namelen = 0;

  iovec write_iov{write_buff, sizeof(write_buff)};
  msg.msg_iov = &write_iov;
  msg.msg_iovlen = 1;

  msg.msg_control = nullptr;
  msg.msg_controllen = 0;

  msg.msg_flags = 0;

  if (test_read_timeout(client_fd, 3)) {
    FATAL("read timeout!")
    return -1;
  }

  while ((len = recvmsg(client_fd, &msg, 0)) >= 0) {
    if (len == 0) {
      if (errno == EINTR) {
        INFO("paused by EINTR")
        continue;
      }
      INFO("recvmsg finish")
      break;
    }
    write_buff[len] = '\0';
    total_len += len;
    printf("%s\n#len:%zi#\n", write_buff, len);
  }
  if (len < 0) {
    FATAL("read err!")
    return -1;
  }
  DEBUG("total len: " << total_len)
  return 0;
}

int main(int argc, char **argv) {
  int result;
  log_init();
  INFO("log4cplus start!");
  testing::InitGoogleTest(&argc, argv);

  result = RUN_ALL_TESTS();

  // test syslog(need to config syslog/rsyslog)

  openlog("tao_01", LOG_PERROR, LOG_LOCAL1);
  syslog(LOG_WARNING, "logger works!");
  closelog();

  //    test_timeout();

  test_xxxmsg_func("www.baidu.com", "80");

  return result;
}