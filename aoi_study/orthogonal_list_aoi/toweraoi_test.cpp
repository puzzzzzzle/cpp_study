//
// Created by khalidzhang on 2019/12/7.
//

#include "common_includes.h"
#include "dyn_aspect.hpp"
#include "tower_aoi.h"
#include "time_gap.hpp"

TOWERIMPL(uint32_t, int)
namespace TowerCallBack {
    void ObjAddCallBack(const Object &obj, const WatcherTypeObjectMap &firstSet,
                        const WatcherTypeObjectMap &secondSet, bool IsDiffTower) {
        INFO("ObjAddCallBack")
    }

    void ObjRemoveCallBack(const Object &obj, const WatcherTypeObjectMap &firstSet,
                           const WatcherTypeObjectMap &secondSet, bool IsDiffTower) {
        INFO("ObjRemoveCallBack")

    }

    void ObjMoveCallBack(const Object &obj, const WatcherTypeObjectMap &firstSet,
                         const WatcherTypeObjectMap &secondSet, bool IsDiffTower) {
        INFO("ObjMoveCallBack")

    }

    void WatcherAddCallBack(const Watcher &watcher, const TypeObjectMap &firstSet,
                             const TypeObjectMap &secondSet, bool IsDiffTower) {
        INFO("WatcherAddCallBackT")

    }

    void WatcherRemoveCallBack(const Watcher &watcher, const TypeObjectMap &firstSet,
                                const TypeObjectMap &secondSet, bool IsDiffTower) {
        INFO("WatcherRemoveCallBackT")

    }

    void WatcherMoveCallBack(const Watcher &watcher, const TypeObjectMap &firstSet,
                              const TypeObjectMap &secondSet, bool IsDiffTower) {
        INFO("WatcherMoveCallBackT")

    }
}
struct TimeAspect
{
    void Before(...)
    {
    }

    void After(...)
    {
        INFO("time:" << m_t.gap())
    }

private:
    TimeGap m_t;
};
TowerAoi *towerAoi;
struct TowerLoggingAspect
{
    void Before(...)
    {
        std::ostringstream oss;
        oss<<"Before:\t";
        towerAoi->ToString(oss);
        oss <<"\t";
        INFO(oss.str())
    }

    void After(...)
    {
        std::ostringstream oss;
        oss<<"After:\t";
        towerAoi->ToString(oss);
        oss <<"\t";
        INFO(oss.str())
    }
};
#define AOPCALL(call) (AOP<bool,TimeAspect,TowerLoggingAspect>([&]()->bool{ return (call);}))

TEST(toweraoi, base) {
    TowerConfig config;
    config.GlobalWith=100;
    config.GlobalHeight=100;
    config.HalfTowerWith=5;
    config.HalfTowerHeight=5;

    ObjCallBack objCallBack[CallBackDef::OBJ_MAX]{TowerCallBack::ObjAddCallBack,TowerCallBack::ObjRemoveCallBack,TowerCallBack::ObjMoveCallBack};
    WatcherCallBack watcherCallBack[CallBackDef::WATCHER_MAX]{TowerCallBack::WatcherAddCallBack,TowerCallBack::WatcherRemoveCallBack,TowerCallBack::WatcherMoveCallBack,};

    TowerAoi towerAoi(config,objCallBack,watcherCallBack);
    INFO("init finish"<<&towerAoi)
    towerAoi.ToString(std::cout);
    towerAoi.AddObject(0,Point(0,0),0);
    towerAoi.ToString(std::cout);
//    ASSERT_TRUE(AOPCALL(towerAoi.AddObject(0,Point(0,0),0)));
}