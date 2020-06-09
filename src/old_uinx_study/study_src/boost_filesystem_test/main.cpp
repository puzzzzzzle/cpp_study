//
// Created by tao on 19-1-17.
//
#include <gtest/gtest.h>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <thread>

#include "boost_log_init.h"

namespace fs = boost::filesystem;

TEST(test_test, 1) { EXPECT_EQ(1, 1); }

int main(int argc, char **argv) {
  int result = 0;
  log_init();
  testing::InitGoogleTest(&argc, argv);
  result = RUN_ALL_TESTS();
  fs::path home("/home/tao");
  INFO(home.string());
  INFO(home.parent_path().string())
  INFO((home / "tao").string());
  INFO((home += "/tao").string());

  home = "/home";
  home /= "tao/hello";
  INFO(home.string());
  INFO(fs::exists(home))

  fs::ifstream in(home);
  char buff[100];
  while (in.getline(buff, sizeof(buff))) {
    INFO(buff)
  }
  return result;
}