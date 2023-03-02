//
// Created by khalidzhang on 2019/12/8.
//

#include <map>

#include "common_includes.h"
#include "time_gap.hpp"
#include "tower_aoi.h"
#include "common_funcs.h"
#include "common_funcs.h"

#define INFO(msg) LOG_DEBUG(msg)

namespace TestClient {
TOWER_DEFINE(uint32_t, uint32_t)
const int MAX_TYPE = 5;
const int MAX_VIEW_RANGE = 2;
using PointType = Point;

class ObjectClient {
  public:
  Object obj{};
  ObjectType type{};
  Point point{};
};

class WatcherClient {
  public:
  Object obj{};
  ObjectType type{};
  Point point{};
  int viewRange{};
  std::map<Object, Point> viewObjects;
};

static std::map<Object, WatcherClient> *pwatcherClients;

void ObjAddCallBack(const Object &obj, ObjectType type, const Point &pos,
                    const WatcherTypeObjectMap &appear,
                    const WatcherTypeObjectMap &disAppear, bool IsDiffTower) {
  if (appear.empty()) {
    return;
  }
  for (auto &watcherTypeMap : appear) {
    for (auto &watcherPos : watcherTypeMap.second) {
      (*pwatcherClients)[watcherPos.first.obj].viewObjects[obj] = pos;
    }
  }
}

void ObjRemoveCallBack(const Object &obj, ObjectType type, const Point &pos,
                       const WatcherTypeObjectMap &appear,
                       const WatcherTypeObjectMap &disAppear,
                       bool IsDiffTower) {
  if (disAppear.empty()) {
    return;
  }
  for (auto &watcherTypeMap : disAppear) {
    for (auto &watcherPos : watcherTypeMap.second) {
      (*pwatcherClients)[watcherPos.first.obj].viewObjects.erase(obj);
    }
  }
}

void ObjMoveCallBack(const Object &obj, ObjectType type, const Point &pos,
                     const WatcherTypeObjectMap &appear,
                     const WatcherTypeObjectMap &disAppear, bool IsDiffTower) {
  if (IsDiffTower) {
    for (auto &watcherTypeMap : disAppear) {
      for (auto &watcherPos : watcherTypeMap.second) {
        (*pwatcherClients)[watcherPos.first.obj].viewObjects.erase(obj);
      }
    }

    for (auto &watcherTypeMap : appear) {
      for (auto &watcherPos : watcherTypeMap.second) {
        (*pwatcherClients)[watcherPos.first.obj].viewObjects[obj] = pos;
      }
    }

  } else {
    for (auto &watcherTypeMap : appear) {
      for (auto &watcherPos : watcherTypeMap.second) {
        (*pwatcherClients)[watcherPos.first.obj].viewObjects[obj] = pos;
      }
    }
  }
}

void WatcherAddCallBack(const Watcher &watcher, ObjectType type,
                        const Point &pos, const TypeObjectMap &appear,
                        const TypeObjectMap &disAppear, bool IsDiffTower) {
  if (appear.empty()) {
    return;
  }
  for (auto &objTypeMap : appear) {
    for (auto &objPos : objTypeMap.second) {
      (*pwatcherClients)[watcher.obj].viewObjects[objPos.first] = objPos.second;
    }
  }
}

void WatcherRemoveCallBack(const Watcher &watcher, ObjectType type,
                           const Point &pos, const TypeObjectMap &appear,
                           const TypeObjectMap &disAppear, bool IsDiffTower) {
  if (disAppear.empty()) {
    return;
  }
  for (auto &objTypeMap : disAppear) {
    for (auto &objPos : objTypeMap.second) {
      (*pwatcherClients)[watcher.obj].viewObjects.erase(objPos.first);
    }
  }
}

void WatcherMoveCallBack(const Watcher &watcher, ObjectType type,
                         const Point &pos, const TypeObjectMap &appear,
                         const TypeObjectMap &disAppear, bool IsDiffTower) {
  // 先删除，后添加，必须是这个顺序，因为全量推了。。。后面得改下
  if (IsDiffTower) {
    for (auto &objTypeMap : disAppear) {
      for (auto &objPos : objTypeMap.second) {
        (*pwatcherClients)[watcher.obj].viewObjects.erase(objPos.first);
      }
    }

    for (auto &objTypeMap : appear) {
      for (auto &objPos : objTypeMap.second) {
        (*pwatcherClients)[watcher.obj].viewObjects[objPos.first] =
            objPos.second;
      }
    }
  } else {
    for (auto &objTypeMap : appear) {
      for (auto &objPos : objTypeMap.second) {
        (*pwatcherClients)[watcher.obj].viewObjects[objPos.first] =
            objPos.second;
      }
    }
  }
}

void WatcherSetRangeCallBack(const Watcher &watcher, ObjectType type,
                             const Point &pos, const TypeObjectMap &appear,
                             const TypeObjectMap &disAppear, bool IsDiffTower) {
  for (auto &objTypeMap : disAppear) {
    for (auto &objPos : objTypeMap.second) {
      (*pwatcherClients)[watcher.obj].viewObjects.erase(objPos.first);
    }
  }

  for (auto &objTypeMap : appear) {
    for (auto &objPos : objTypeMap.second) {
      (*pwatcherClients)[watcher.obj].viewObjects[objPos.first] = objPos.second;
    }
  }
}

class ClientController {
  public:
  TowerAoi *pAoi;

  // 判断依据，本地直接保存的位置信息
  std::map<Object, ObjectClient> baseObjClients;
  std::map<Object, WatcherClient>
      baseWatcherClients;  //这个里面没有 viewObjects

  // 回调函数生成的watcher视野范围内的物体位置信息
  std::map<Object, WatcherClient> watcherClients;

  public:
  ClientController(TowerAoi *_aoi, bool registerCallBack = true) : pAoi(_aoi) {
    if (!registerCallBack) {
      return;
    }
    pwatcherClients = &watcherClients;
    //注册回调函数
    ObjCallBack _objCallBacks[CallBackDef::OBJ_MAX];
    WatcherCallBack _watcherCallBacks[CallBackDef::WATCHER_MAX];
    _objCallBacks[CallBackDef::OBJ_ADD] = &ObjAddCallBack;
    _objCallBacks[CallBackDef::OBJ_REMOVE] = &ObjRemoveCallBack;
    _objCallBacks[CallBackDef::OBJ_MOVED] = &ObjMoveCallBack;
    _watcherCallBacks[CallBackDef::WATCHER_ADD] = &WatcherAddCallBack;
    _watcherCallBacks[CallBackDef::WATCHER_REMOVE] = &WatcherRemoveCallBack;
    _watcherCallBacks[CallBackDef::WATCHER_MOVE] = &WatcherMoveCallBack;
    _watcherCallBacks[CallBackDef::WATCHER_VIEW_CHANGE] =
        &WatcherSetRangeCallBack;
    pAoi->RegisterCallBacks(_objCallBacks, _watcherCallBacks);
  }

  bool AddObj(const Object &obj, const Point &pos, ObjectType type) {
    ObjectClient client;
    client.obj = obj;
    client.type = type;
    client.point = pos;
    baseObjClients.insert(std::make_pair(obj, client));
    return pAoi->AddObject(obj, pos, type);
  }

  bool MoveObj(const Object &obj, const Point &newPos) {
    baseObjClients[obj].point = newPos;
    return pAoi->MoveObject(obj, newPos, baseObjClients[obj].type);
  }

  bool MoveSomeObj(int rate) {
    for (auto it = baseObjClients.begin(); it != baseObjClients.end(); it++) {
      if (rand() % rate) {
        baseObjClients[it->first].point =
            Point(rand() % pAoi->GetConfig().GlobalWith,
                  rand() % pAoi->GetConfig().GlobalHeight);
        if (!pAoi->MoveObject(it->first, baseObjClients[it->first].point,
                              baseObjClients[it->first].type)) {
          return false;
        }
      }
    }
    return true;
  }

  bool RemoveObj(const Object &obj) {
    bool ret = pAoi->RemoveObject(obj, baseObjClients[obj].type);
    baseObjClients.erase(obj);
    return ret;
  }

  bool RemoveSomeObj(int rate) {
    for (auto it = baseObjClients.begin(); it != baseObjClients.end();) {
      if (rand() % rate) {
        if (!pAoi->RemoveObject(it->first, baseObjClients[it->first].type)) {
          return false;
        }
        it = baseObjClients.erase(it);
      } else {
        it++;
      }
    }
    return true;
  }

  bool AddWatcher(const Watcher &watcher, const Point &pos, ObjectType type) {
    WatcherClient client;
    client.obj = watcher.obj;
    client.viewRange = watcher.viewRange;
    client.type = type;
    client.point = pos;
    baseWatcherClients.insert(std::make_pair(watcher.obj, client));
    return pAoi->AddWatcher(watcher, pos, type);
  }

  bool MoveWatcher(const Object &watcherObj, const Point &newPos) {
    baseWatcherClients[watcherObj].point = newPos;
    auto b = pAoi->MoveWatcher(watcherObj, newPos,
                               baseWatcherClients[watcherObj].type);
    if (!b) {
      INFO("err" << watcherObj)
    }
    return b;
  }

  bool MoveSomeWatcher(int rate) {
    for (auto it = baseWatcherClients.begin(); it != baseWatcherClients.end();
         it++) {
      if (rand() % rate) {
        baseWatcherClients[it->first].point =
            Point(rand() % pAoi->GetConfig().GlobalWith,
                  rand() % pAoi->GetConfig().GlobalHeight);
        if (!pAoi->MoveWatcher(it->first, baseWatcherClients[it->first].point,
                               baseWatcherClients[it->first].type)) {
          return false;
        }
      }
    }
    return true;
  }

  bool RemoveWatcher(const Object &watcherObj) {
    bool ret =
        pAoi->RemoveWatcher(watcherObj, baseWatcherClients[watcherObj].type);
    baseWatcherClients.erase(watcherObj);
    return ret;
  }

  bool RemoveSomeWatcher(int rate) {
    for (auto it = baseWatcherClients.begin();
         it != baseWatcherClients.end();) {
      if (rand() % rate) {
        if (!pAoi->RemoveWatcher(it->first,
                                 baseWatcherClients[it->first].type)) {
          return false;
        }
        it = baseWatcherClients.erase(it);
      } else {
        it++;
      }
    }
    return true;
  }

  bool WatcherSetViewRange(const Object &watcherObj, int newViewRange) {
    baseWatcherClients[watcherObj].viewRange = newViewRange;
    return pAoi->WatcherSetViewRange(
        watcherObj, baseWatcherClients[watcherObj].type, newViewRange);
  }

  bool WatcherSetSomeViewRange(int rate) {
    for (auto it = baseWatcherClients.begin(); it != baseWatcherClients.end();
         it++) {
      if (rand() % rate) {
        int newViewRange = (rand() % MAX_VIEW_RANGE);
        if (!pAoi->WatcherSetViewRange(
                it->first, baseWatcherClients[it->first].type, newViewRange)) {
          return false;
        }
        baseWatcherClients[it->first].viewRange = newViewRange;
      }
    }
    return true;
  }

  bool CheckCorrect() {
    // step1 遍历本地watcher
    for (auto &watcher : baseWatcherClients) {
      WatcherClient &watcherClient = watcher.second;
      std::map<Object, Point> correctViewObjects;
      TowerIndex watcherTowerIndex =
          pAoi->TranslateTowerIndex(watcherClient.point);
      TowerIndexRegion watcherViewRegion =
          pAoi->GetTowerIndexRegion(watcherTowerIndex, watcherClient.viewRange);

      // step2 根据本地信息计算出watcher应该看到的样子
      for (auto &object : baseObjClients) {
        TowerIndex objectTowerIndex =
            pAoi->TranslateTowerIndex(object.second.point);
        if (IsInViewRegion(watcherViewRegion, objectTowerIndex)) {
          // step3 和回调函数维护的进行比对
          const auto &calcWatcherView =
              watcherClients[watcher.first].viewObjects;
          auto it =
              watcherClients[watcher.first].viewObjects.find(object.first);
          if (it == calcWatcherView.end()) {
            return false;
          }
          if (it->second.x != object.second.point.x ||
              it->second.y != object.second.point.y) {
            return false;
          }
        }
      }
    }
    return true;
  }

  public:
  inline static bool IsInViewRegion(const TowerIndexRegion &watcherViewRegion,
                                    const TowerIndex &objectTowerIndex) {
    return objectTowerIndex.x >= watcherViewRegion.start.x &&
           objectTowerIndex.y >= watcherViewRegion.start.y &&
           objectTowerIndex.x <= watcherViewRegion.end.x &&
           objectTowerIndex.y <= watcherViewRegion.end.y;
  }
};
}  // namespace TestClient

class CorrectClientTest : public testing::Test {
  protected:
  virtual void SetUp() override {
    //构建一座塔
    TestClient::TowerConfig config;
    config.GlobalWith = 1000;
    config.GlobalHeight = 1000;
    config.TowerWith = 100;
    config.TowerHeight = 100;

    pTowerAoi = new TestClient::TowerAoi(config);
    pController = new TestClient::ClientController(pTowerAoi);
  }

  virtual void TearDown() override {
    delete pController;
    delete pTowerAoi;
  }

  TestClient::ClientController *pController;

  TestClient::Object currAddObj = 0;
  TestClient::Object currAddWatcher = 0;
  TestClient::TowerAoi *pTowerAoi;
};

#define ADDOBJ(num)                                          \
  for (Object i = 0; i < (num); ++i) {                       \
    EXPECT_TRUE(pController->AddObj(                         \
        currAddObj++,                                        \
        Point(rand() % pTowerAoi->GetConfig().GlobalWith,    \
              rand() % pTowerAoi->GetConfig().GlobalHeight), \
        rand() % MAX_TYPE));                                 \
  }
#define ADDWATCHER(num)                                           \
  for (Object i = 0; i < (num); ++i) {                            \
    EXPECT_TRUE(pController->AddWatcher(                          \
        Watcher(currAddWatcher++, (rand() % MAX_VIEW_RANGE) + 1), \
        Point(rand() % pTowerAoi->GetConfig().GlobalWith,         \
              rand() % pTowerAoi->GetConfig().GlobalHeight),      \
        rand() % MAX_TYPE));                                      \
  }
#define MOVEOBJ(rate) EXPECT_TRUE(pController->MoveSomeObj(rate));

#define MOVEWATCHER(rate) EXPECT_TRUE(pController->MoveSomeWatcher(rate));

#define REMOVEOBJ(rate) EXPECT_TRUE(pController->RemoveSomeObj(rate));

#define REMOVEWATCHER(rate) EXPECT_TRUE(pController->RemoveSomeWatcher(rate));

#define SETVIEWRANGE(rate) \
  EXPECT_TRUE(pController->WatcherSetSomeViewRange(rate));

TEST_F(CorrectClientTest, add) {
  using namespace TestClient;
  ADDOBJ(100)
  ADDWATCHER(100)
  ADDOBJ(1000)
  ADDWATCHER(100)
  ADDOBJ(100)
  ADDOBJ(100)
  ADDWATCHER(100)

  ASSERT_TRUE(pController->CheckCorrect());
}

TEST_F(CorrectClientTest, move) {
  using namespace TestClient;
  ADDOBJ(1000)
  ADDWATCHER(1000)
  MOVEOBJ(30)
  MOVEWATCHER(50)
  ASSERT_TRUE(pController->CheckCorrect());
}

TEST_F(CorrectClientTest, remove) {
  using namespace TestClient;
  ADDOBJ(1000)
  ADDWATCHER(1000)
  REMOVEOBJ(50)
  REMOVEWATCHER(50)
  ADDWATCHER(1000)
  ADDOBJ(1000)
  REMOVEOBJ(30)
  REMOVEWATCHER(30)

  ASSERT_TRUE(pController->CheckCorrect());
}

TEST_F(CorrectClientTest, ViewRangaChange) {
  using namespace TestClient;
  ADDOBJ(1000)
  ADDWATCHER(1000)
  SETVIEWRANGE(50)
  ASSERT_TRUE(pController->CheckCorrect());
}

TEST_F(CorrectClientTest, mix) {
  using namespace TestClient;
  int action;
  ADDOBJ(1000)
  ADDWATCHER(1000)
  int loopSize = 50000;
  uint32_t objGrowLimit = 10000 * 1000;
  uint32_t watcherGrowLimit = 10000 * 10;
  uint64_t total_op_times = 0;
  TimeGap timeGap;
  int eachTimes[CallBackDef::OBJ_MAX + CallBackDef::WATCHER_MAX]{0};
  for (int i = 0; i < loopSize; ++i) {
    action = rand() % (CallBackDef::OBJ_MAX + CallBackDef::WATCHER_MAX);
    switch (action) {
      case CallBackDef::OBJ_ADD: {
        ADDOBJ(10)
        ++eachTimes[CallBackDef::OBJ_ADD];
        total_op_times += 10;
        ASSERT_TRUE(pController->CheckCorrect());
        break;
      }
      case CallBackDef::OBJ_MOVED: {
        MOVEOBJ(70)
        ++eachTimes[CallBackDef::OBJ_MOVED];
        total_op_times += pController->baseObjClients.size() * 0.7;
        ASSERT_TRUE(pController->CheckCorrect());

        break;
      }
      case CallBackDef::OBJ_REMOVE: {
        if (pController->baseObjClients.size() > objGrowLimit) {
          REMOVEOBJ(55)
          total_op_times += pController->baseObjClients.size() * 0.55;
        } else {
          total_op_times += pController->baseObjClients.size() * 0.3;

          REMOVEOBJ(30)
        }
        ++eachTimes[CallBackDef::OBJ_REMOVE];
        ASSERT_TRUE(pController->CheckCorrect());

        break;
      }
      case CallBackDef::OBJ_MAX + CallBackDef::WATCHER_ADD: {
        ADDWATCHER(5)
        total_op_times += 5;

        ++eachTimes[CallBackDef::OBJ_MAX + CallBackDef::WATCHER_ADD];
        ASSERT_TRUE(pController->CheckCorrect());
        break;
      }
      case CallBackDef::OBJ_MAX + CallBackDef::WATCHER_MOVE: {
        MOVEWATCHER(70)
        total_op_times += pController->baseObjClients.size() * 0.7;
        ++eachTimes[CallBackDef::OBJ_MAX + CallBackDef::WATCHER_MOVE];
        ASSERT_TRUE(pController->CheckCorrect());
        break;
      }
      case CallBackDef::OBJ_MAX + CallBackDef::WATCHER_REMOVE: {
        if (pController->baseWatcherClients.size() > watcherGrowLimit) {
          REMOVEWATCHER(55)
          total_op_times += pController->baseObjClients.size() * 0.55;

        } else {
          REMOVEWATCHER(30)
          total_op_times += pController->baseObjClients.size() * 0.3;
        }
        ++eachTimes[CallBackDef::OBJ_MAX + CallBackDef::WATCHER_REMOVE];
        ASSERT_TRUE(pController->CheckCorrect());
        break;
      }
      case CallBackDef::OBJ_MAX + CallBackDef::WATCHER_VIEW_CHANGE: {
        SETVIEWRANGE(20)
        total_op_times += 20;
        ++eachTimes[CallBackDef::OBJ_MAX + CallBackDef::WATCHER_VIEW_CHANGE];
        ASSERT_TRUE(pController->CheckCorrect());
        break;
      }
    }
    ASSERT_TRUE(pController->CheckCorrect());
  }
  INFO("use time :" << timeGap.gap())
  std::ostringstream oss;
  printArr(oss, sizeof(eachTimes) / sizeof(eachTimes[0]), eachTimes);
  oss << "\t";
  sumArr(oss, sizeof(eachTimes) / sizeof(eachTimes[0]), eachTimes);
  INFO("each times:\t" << oss.str())
  INFO("total op times :\t" << total_op_times)
}