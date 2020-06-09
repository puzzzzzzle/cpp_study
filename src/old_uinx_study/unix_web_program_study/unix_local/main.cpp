//
// Created by tao on 19-1-17.
//
#include <gtest/gtest.h>
#include <sys/socket.h>

#include <thread>

#include "boost_log_init.h"

TEST(test_test, 1) { EXPECT_EQ(1, 1); }

int test_unix_local(const char *str, char buff_recv[], size_t buff_len) {
  int fds[2];
  size_t recv_len, write_len;
  if (socketpair(PF_LOCAL, SOCK_STREAM, 0, fds)) {
    FATAL("cannot make pair:" << strerror(errno))
    return -1;
  }
  if ((write_len = send(fds[0], str, strlen(str), 0)) != strlen(str)) {
    FATAL("cannot send:" << strerror(errno) << "\tsend back:" << write_len)
    return -1;
  }
  if ((recv_len = recv(fds[1], buff_recv, buff_len - 1, 0)) != strlen(str)) {
    FATAL("cannot recv:" << strerror(errno))
    return -1;
  }
  buff_recv[recv_len] = '\0';
  return 0;
}

TEST(test_unix_local, test_1) {
  const char *str = "hahahaha";
  char buff[100];
  test_unix_local(str, buff, sizeof(buff));
  EXPECT_STREQ(str, buff);
}

int main(int argc, char **argv) {
  int result = 0;
  log_init();
  testing::InitGoogleTest(&argc, argv);
  result = RUN_ALL_TESTS();

  //    test_main();
  return result;
}