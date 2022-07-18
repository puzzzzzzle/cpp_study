/************************************************
 * @author khalidzhang
 * @email khalidzhang@tencent.com
 * @desc
 * @time 2021/3/2
 * @file path_find_test_base.h
 * @version
 * version        author            desc
 * 1.0            khalidzhang       create
 ************************************************/

#pragma once
#include <dirent.h>
#include <sys/types.h>

#include <exception>
#include <fstream>

#include "common_includes.h"
#include "path_find_common.h"
#include "time_gap.hpp"

struct MapDataInit : public testing::Test {
  protected:
  DataType data{};
  std::set<Point> setPos{};
  bool needCheckData = false;
  virtual void SetUp() {}
  virtual void TearDown() {}
  void init_data(int x, int y) { data.init(x, y); }
  void add_block(int x, int y) {
    Point pos(x, y);
    if (needCheckData) {
      setPos.insert(pos);
    }
    data.set(x, y, false);
    //    LOG_DEBUG("addBlock \t" << pos.to_string() << "\tsize\t" <<
    //    setPos.size())
    if (needCheckData) {
      ASSERT_TRUE(setPos.find(pos) != setPos.end());
      ASSERT_TRUE(!data.check(x, y));
    }
  };
  void check_data() {
    for (int x = 0; x < data.m_xLen; ++x) {
      for (int y = 0; y < data.m_yLen; ++y) {
        if (data.check(x, y)) {
          ASSERT_TRUE(setPos.find(Point(x, y)) == setPos.end());
        } else {
          ASSERT_TRUE(setPos.find(Point(x, y)) != setPos.end());
        }
      }
    }
  }
  void build_map_1() {
    init_data(10, 10);
    add_block(8, 2);
    add_block(4, 2);
    add_block(5, 2);
    add_block(8, 7);
    add_block(8, 8);
    add_block(0, 9);
  }
  void build_from_string(const std::string &str) {
    std::vector<std::string> lines{}, currLine{}, filterLine{};
    Split(str, "\n", lines);
    ASSERT_TRUE(lines.size() >= 3);
    Split(lines[0], ",", currLine);
    ASSERT_TRUE(currLine.size() == 2);
    int xLen = atoi(currLine[0].c_str());
    int yLen = atoi(currLine[1].c_str());
    ASSERT_TRUE(xLen > 0 && yLen > 0);
    init_data(xLen, yLen);
    for (int y = 0; y < yLen; ++y) {
      Split(lines[y + 1], ",", currLine);
      filterLine.clear();
      std::copy_if(currLine.begin(), currLine.end(),
                   std::back_inserter(filterLine),
                   [](const std::string &item) { return !item.empty(); });
      ASSERT_TRUE(filterLine.size() == xLen);
      for (int x = 0; x < xLen; ++x) {
        if (filterLine[x] != "0") {
          add_block(x, y);
        }
      }
    }
  }
  void build_from_file(const std::string &path) {
    auto allStr = LoadFileStr(path);
    ASSERT_TRUE(allStr != "");
    build_from_string(allStr);
  }
};