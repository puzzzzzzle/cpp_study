//
// Created by khalidzhang on 2019/12/8.
//


#include "common_includes.h"
#include "tower_aoi.h"
#include "time_gap.hpp"
#include <map>

namespace TestClient {
    TOWER_DEFINE(uint32_t, uint32_t)

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

    void ObjAddCallBack(const Object &obj, ObjectType type, const Point &pos, const WatcherTypeObjectMap &appear,
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

    void ObjRemoveCallBack(const Object &obj, ObjectType type, const Point &pos, const WatcherTypeObjectMap &appear,
                           const WatcherTypeObjectMap &disAppear, bool IsDiffTower) {
        if (disAppear.empty()) {
            return;
        }
        for (auto &watcherTypeMap : disAppear) {
            for (auto &watcherPos : watcherTypeMap.second) {
                (*pwatcherClients)[watcherPos.first.obj].viewObjects.erase(obj);
            }
        }
    }

    void ObjMoveCallBack(const Object &obj, ObjectType type, const Point &pos, const WatcherTypeObjectMap &appear,
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

    void WatcherAddCallBack(const Watcher &watcher, ObjectType type, const Point &pos,
                            const TypeObjectMap &appear,
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

    void WatcherRemoveCallBack(const Watcher &watcher, ObjectType type, const Point &pos,
                               const TypeObjectMap &appear,
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

    void WatcherMoveCallBack(const Watcher &watcher, ObjectType type, const Point &pos,
                             const TypeObjectMap &appear,
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
                    (*pwatcherClients)[watcher.obj].viewObjects[objPos.first] = objPos.second;
                }
            }
        } else {
            for (auto &objTypeMap : appear) {
                for (auto &objPos : objTypeMap.second) {
                    (*pwatcherClients)[watcher.obj].viewObjects[objPos.first] = objPos.second;
                }
            }
        }
    }

    void WatcherSetRangeCallBack(const Watcher &watcher, ObjectType type, const Point &pos,
                                 const TypeObjectMap &appear,
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
    private:
        TowerAoi *pAoi;

        // 判断依据，本地直接保存的位置信息
        std::map<Object, ObjectClient> baseObjClients;
        std::map<Object, WatcherClient> baseWatcherClients;      //这个里面没有 viewObjects

        // 回调函数生成的watcher视野范围内的物体位置信息
        std::map<Object, WatcherClient> watcherClients;

    public:
        ClientController(TowerAoi *_aoi) : pAoi(_aoi) {
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
            _watcherCallBacks[CallBackDef::WATCHER_VIEW_CHANGE] = &WatcherSetRangeCallBack;
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

        bool RemoveObj(const Object &obj) {
            bool ret = pAoi->RemoveObject(obj, baseObjClients[obj].type);
            baseObjClients.erase(obj);
            return ret;
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
            auto b = pAoi->MoveWatcher(watcherObj, newPos, baseWatcherClients[watcherObj].type);
            if (!b) {
                INFO("err" << watcherObj)
            }
            return b;
        }

        bool RemoveWatcher(const Object &watcherObj) {
            bool ret = pAoi->RemoveWatcher(watcherObj, baseWatcherClients[watcherObj].type);
            baseWatcherClients.erase(watcherObj);
            return ret;
        }

        bool WatcherSetViewRange(const Object &watcherObj, int newViewRange) {
            baseWatcherClients[watcherObj].viewRange = newViewRange;
            return pAoi->WatcherSetViewRange(watcherObj, baseWatcherClients[watcherObj].type, newViewRange);
        }

        bool CheckCorrect() {
            //step1 遍历本地watcher
            for (auto &watcher : baseWatcherClients) {
                WatcherClient &watcherClient = watcher.second;
                std::map<Object, Point> correctViewObjects;
                TowerIndex watcherTowerIndex = pAoi->TranslateTowerIndex(watcherClient.point);
                TowerIndexRegion watcherViewRegion = pAoi->GetTowerIndexRegion(watcherTowerIndex,
                                                                               watcherClient.viewRange);

                //step2 根据本地信息计算出watcher应该看到的样子
                for (auto &object : baseObjClients) {
                    TowerIndex objectTowerIndex = pAoi->TranslateTowerIndex(object.second.point);
                    if (IsInViewRegion(watcherViewRegion, objectTowerIndex)) {
                        //step3 和回调函数维护的进行比对
                        const auto &calcWatcherView = watcherClients[watcher.first].viewObjects;
                        auto it = watcherClients[watcher.first].viewObjects.find(object.first);
                        if (it == calcWatcherView.end()) {
                            return false;
                        }
                        if (
                                it->second.x != object.second.point.x
                                || it->second.y != object.second.point.y
                                ) {
                            return false;
                        }
                        //todo 类型判断,目前没有修改类型的逻辑，暂时不需要判断
                    }
                }
            }
            return true;
        }

    public:
        inline static bool
        IsInViewRegion(const TowerIndexRegion &watcherViewRegion, const TowerIndex &objectTowerIndex) {
            return objectTowerIndex.x >= watcherViewRegion.start.x && objectTowerIndex.y >= watcherViewRegion.start.y
                   && objectTowerIndex.x <= watcherViewRegion.end.x && objectTowerIndex.y <= watcherViewRegion.end.y;
        }
    };
}

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
    const int MAX_TYPE = 5;
    const int MAX_VIEW_RANGE = 2;
    TestClient::Object currAddObj = 0;
    TestClient::Object currAddWatcher = 0;
    TestClient::TowerAoi *pTowerAoi;
};

#define ADDOBJ(num)             for (Object i = 0; i <(num); ++i) {\
                                    EXPECT_TRUE(pController->AddObj(currAddObj++,\
                                    Point(rand() % pTowerAoi->GetConfig().GlobalWith,\
                                          rand() % pTowerAoi->GetConfig().GlobalHeight),\
                                    rand() % MAX_TYPE));\
                                }
#define ADDWATCHER(num)         for (Object i = 0; i < (num); ++i) {\
                                    EXPECT_TRUE(pController->AddWatcher(Watcher(currAddWatcher++, (rand() % MAX_VIEW_RANGE) +1),\
                                    Point(rand() % pTowerAoi->GetConfig().GlobalWith,\
                                          rand() % pTowerAoi->GetConfig().GlobalHeight), rand() % MAX_TYPE));\
                                }
#define MOVEOBJ(rate)           for (Object i = 0; i < currAddObj; ++i) {\
                                    if (rand() % 100 >= (rate)) {\
                                    EXPECT_TRUE(pController->MoveObj(i, Point(rand() % pTowerAoi->GetConfig().GlobalWith,\
                                                                              rand() % pTowerAoi->GetConfig().GlobalHeight)));\
                                    }\
                                }
#define MOVEWATCHER(rate)       for (Object i = 0; i < currAddWatcher; ++i) {\
                                    if (rand() % 100 >= (rate)) {\
                                    EXPECT_TRUE(pController->MoveWatcher(i, Point(rand() % pTowerAoi->GetConfig().GlobalWith,\
                                                                                  rand() % pTowerAoi->GetConfig().GlobalHeight)));\
                                    }\
                                }
#define REMOVEOBJ(rate)         for (Object i = 0; i < currAddObj; ++i) {\
                                    if (rand() % 100 >= (rate)) {\
                                        EXPECT_TRUE(pController->RemoveObj(i));\
                                    }\
                                }

#define REMOVEWATCHER(rate)     for (Object i = 0; i < currAddWatcher; ++i) {\
                                    if (rand() % 100 >= (rate)) {\
                                        EXPECT_TRUE(pController->RemoveWatcher(i));\
                                    }\
                                }
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

    ASSERT_TRUE(pController->CheckCorrect());
}