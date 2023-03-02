//
// Created by khalidzhang on 2021/3/1.
//
// !!! 注意, 这个文件每个可执行文件只能包含一次, 本来应该是cpp/inc的,
// 但是为了多个间复用, 强行用了.h, inc文件IDE没有代码提示... !!!
#pragma once
#include <dirent.h>
#include <sys/types.h>

#include <exception>
#include <fstream>

#include "common_includes.h"
#include "path_find_common.h"
#include "path_find_test_base.h"
#include "time_gap.hpp"
struct PathDataInit : public MapDataInit {
  PathFindTask tasks{};
  std::vector<PathFindResult> results{};
  int load_tasks(const std::string &path) { return tasks.load(path); }
  void run_tasks() {
    for (auto &item : tasks.tasks) {
      PathFindResult result{};
      result.task = item;
      TimeGap gap{};
      PathFindType search(item.first, item.second, &data);
      result.ret = search.searching();
      result.result = search.extract_path();
      result.time = gap.gap();
      results.push_back(result);
    }
  }
  void build_worse_case() {
    init_data(400, 400);
    add_block(0, 1);
    add_block(1, 0);
  }
  std::string get_report() {
    std::ostringstream oss{};
    for (auto &item : results) {
      oss << item.to_string();
    }
    return oss.str();
  }
  void run_tasks_file(const std::string &taskPath) {
    ASSERT_TRUE(load_tasks(taskPath) == 0);
    LOG_INFO("\trun in map " << tasks.mapPath)
    build_from_file(tasks.mapPath);
    run_tasks();
    LOG_INFO("\treport:\n" << results << "\n")
  }
};

TEST_F(PathDataInit, arrayInit) {
  needCheckData = true;
  build_map_1();
  check_data();
  LOG_DEBUG(data.to_string())
}
TEST_F(PathDataInit, loadTest) {
  needCheckData = true;
  build_from_file("data/path_find/map_file_simple.txt");
  check_data();
  LOG_DEBUG(data.to_string())
}

TEST_F(PathDataInit, pathFind_1) {
  run_tasks_file("data/path_find/path_find_1.txt");
}
TEST_F(PathDataInit, pathFind_all) {
  auto dirname = "data/path_find/";
  DIR *dir_ptr;
  struct dirent *direntp;
  dir_ptr = opendir(dirname);
  ASSERT_TRUE(dir_ptr != nullptr);
  while ((direntp = readdir(dir_ptr))) {
    std::string name = direntp->d_name;
    //    LOG_DEBUG("curr at " << name)
    if (startsWith(name, "path_find")) {
      LOG_INFO("\t\trun path find test file: " << name)
      tasks.clear();
      results.clear();
      run_tasks_file(dirname + name);
    }
  }
  closedir(dir_ptr);
}
TEST_F(PathDataInit, worse_400_400) {
  build_worse_case();
  CPosition p1(0, 0), p2(399, 399);

  TimeGap gap{};
  PathFindType search(p2, p1, &data);
  auto ret = search.searching();
  ASSERT_TRUE(ret != 0);
  LOG_INFO("time use (us)" << gap.gap() <<"\t(s)\t"<<gap.gapSec())
}