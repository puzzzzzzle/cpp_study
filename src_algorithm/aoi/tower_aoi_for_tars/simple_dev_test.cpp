//
// Created by khalidzhang on 2019/12/7.
//

#include "common_includes.h"
#include "time_gap.hpp"
#include "tower_aoi.h"
#include "common_funcs.h"
#define INFO(msg) LOG_DEBUG(msg)

TOWER_DEFINE(int, int)

using PointType = Point;
TEST(correct_1, toweraoi_obj) {
  //构建一座塔
  TowerConfig config;
  config.GlobalWith = 1000;
  config.GlobalHeight = 1000;
  config.TowerWith = 100;
  config.TowerHeight = 100;

  ObjCallBack objCallBack[CallBackDef::OBJ_MAX]{};
  WatcherCallBack watcherCallBack[CallBackDef::WATCHER_MAX]{};
  TowerAoi towerAoi(config, objCallBack, watcherCallBack);
  //    INFO("init finish\t@" << &towerAoi)
  // towerAoi.ToString(std::cout);
  // done
  int size = 1000;

  Object objectBegin = 100;
  ObjectType maxType = 5;
  TypeObjectMap objectMap;

  // add obj
  for (int i = 0; i < size; ++i) {
    int type = rand() % maxType;
    objectMap[type][objectBegin + i] =
        PointType(rand() % config.GlobalWith, rand() % config.GlobalHeight);
    ASSERT_TRUE(towerAoi.AddObject(objectBegin + i,
                                   objectMap[type][objectBegin + i], type));
  }
  // towerAoi.ToString(std::cout);

  // move obj
  for (auto &itype : objectMap) {
    for (auto &obj : itype.second) {
      PointType p(rand() % config.GlobalWith, rand() % config.GlobalHeight);
      ASSERT_TRUE(towerAoi.MoveObject(obj.first, p, itype.first));
      obj.second = p;
    }
  }
  // towerAoi.ToString(std::cout);

  // remove obj
  for (auto &itype : objectMap) {
    for (auto &obj : itype.second) {
      PointType p(rand() % config.GlobalWith, rand() % config.GlobalHeight);
      ASSERT_TRUE(towerAoi.RemoveObject(obj.first, itype.first));
    }
  }
  // towerAoi.ToString(std::cout);
}

TEST(correct_1, toweraoi_watcher) {
  //构建一座塔
  TowerConfig config;
  config.GlobalWith = 1000;
  config.GlobalHeight = 1000;
  config.TowerWith = 100;
  config.TowerHeight = 100;
  ObjCallBack objCallBack[CallBackDef::OBJ_MAX]{nullptr, nullptr, nullptr};
  WatcherCallBack watcherCallBack[CallBackDef::WATCHER_MAX]{nullptr, nullptr,
                                                            nullptr, nullptr};
  TowerAoi towerAoi(config, objCallBack, watcherCallBack);
  //    INFO("init finish\t@" << &towerAoi)
  // towerAoi.ToString(std::cout);
  // done
  int size = 100000;

  Object objectBegin = 100;
  ObjectType maxType = 5;
  TypeObjectMap objectMap;
  WatcherTypeObjectMap watcherMap;

  // add obj
  for (int i = 0; i < size; ++i) {
    int type = rand() % maxType;
    objectMap[type][objectBegin + i] =
        PointType(rand() % config.GlobalWith, rand() % config.GlobalHeight);
    ASSERT_TRUE(towerAoi.AddObject(objectBegin + i,
                                   objectMap[type][objectBegin + i], type));
  }
  // towerAoi.ToString(std::cout);

  // add watcher
  for (int i = 0; i < size; ++i) {
    int type = rand() % maxType;
    Watcher watcher(objectBegin + i, 1);
    watcherMap[type][watcher] =
        PointType(rand() % config.GlobalWith, rand() % config.GlobalHeight);
    ASSERT_TRUE(towerAoi.AddWatcher(watcher, watcherMap[type][watcher], type));
  }
  // towerAoi.ToString(std::cout);

  // move watcher
  for (auto &itype : watcherMap) {
    for (auto &obj : itype.second) {
      PointType p(rand() % config.GlobalWith, rand() % config.GlobalHeight);
      ASSERT_TRUE(towerAoi.MoveWatcher(obj.first.obj, p, itype.first));
      obj.second = p;
    }
  }
  // towerAoi.ToString(std::cout);

  // change watcher range
  for (auto &itype : watcherMap) {
    for (auto &obj : itype.second) {
      ASSERT_TRUE(towerAoi.WatcherSetViewRange(obj.first.obj, itype.first, 2));
      const int *const_intp = &obj.first.viewRange;
      int *modifer = const_cast<int *>(const_intp);
      *modifer = 2;
    }
  }
  // remove obj
  for (auto &itype : objectMap) {
    for (auto &obj : itype.second) {
      PointType p(rand() % config.GlobalWith, rand() % config.GlobalHeight);
      ASSERT_TRUE(towerAoi.RemoveObject(obj.first, itype.first));
    }
  }

  // remove watcher
  for (auto &itype : watcherMap) {
    for (auto &obj : itype.second) {
      PointType p(rand() % config.GlobalWith, rand() % config.GlobalHeight);
      ASSERT_TRUE(towerAoi.RemoveWatcher(obj.first.obj, itype.first));
    }
  }
  //    towerAoi.ToString(std::cout);
}