/********************************************************************

 * @time 2019/12/6 : 19:09
 * @version 1.0
 * @author khalidzhang
 * @e-mail khalidzhang@tencent.com
 * @description: 灯塔法AOI
 *               请自行保证object全局唯一，这里要处理的话得加一个全局的set保存所有object，由于频繁调用，开销会比较大，就不处理了！！！
 *              //todo 边界大小检查
 ********************************************************************/

#ifndef CPP_STUDY_ALL_TOWER_AOI_H
#define CPP_STUDY_ALL_TOWER_AOI_H

#include <set>
#include <map>
#include <vector>

namespace TowerAoiImpl {
    /**
     * 灯塔配置
     * @tparam NumberT 坐标数值类型，全局保持统一
     */
    template<typename NumberT>
    struct TowerConfigT {
        typedef NumberT Number;

        Number GlobalWith{};
        Number GlobalHeight{};
        Number HalfTowerWith{};    //每个灯塔的长的一半。可以省去大量的除法运算
        Number HalfTowerHeight{};    //每个灯塔的宽长的一半。可以省去大量的除法运算
    };

    /**
     * 点
     * @tparam NumberT
     */
    template<typename NumberT>
    struct PointT {
        typedef NumberT Number;

        Number x{};
        Number y{};

        PointT() = default;

        PointT(Number _x, Number _y) : x(_x), y(_y) {}

        PointT(const PointT &Point) : x(Point.x), y(Point.y) {}

        PointT(const PointT &&Point) : x(Point.x), y(Point.y) {}
    };

    /**
     * 区域
     * @tparam NumberT
     */
    template<typename NumberT>
    struct RegionT {
        typedef NumberT Number;
        PointT<Number> start{};
        PointT<Number> end{};

        RegionT() = default;

        RegionT(Number _startX, Number _startY, Number _endX, Number _endY) : start(_startX, _startY),
                                                                              end(_endX, _endY) {}

        RegionT(const PointT<Number> &_start, const PointT<Number> &_end) : start(_start), end(_end) {}

        RegionT(const PointT<Number> &&_start, const PointT<Number> &&_end) : start(_start), end(_end) {}
    };

    /**
     * 观察者需要额外的信息
     * @tparam NumberT
     */
    template<typename PayloadT>
    struct WatcherT {
        PayloadT obj;
        int viewRange{};
    public:
        friend bool operator==(const WatcherT &lhs, const WatcherT &rhs) {
            return lhs.obj == rhs.obj;
        }

        friend bool operator<(const WatcherT &lhs, const WatcherT &rhs) {
            return lhs.obj < rhs.obj;

        }
    };

    /**
     * 灯塔
     * @tparam NumberT
     * @tparam PayloadT 载荷，自己定义的结构体必须重载 < 和 ==
     */
    template<typename NumberT, typename PayloadT>
    class TowerT {
    public:
        typedef NumberT Number;

        typedef PayloadT Object;
        typedef WatcherT<Object> Watcher;

        typedef PointT<Number> Point;
        typedef int ObjectType;

        typedef std::map<Object, Point> PositionMap;
        typedef std::map<ObjectType, PositionMap> TypeObjectMap;

        typedef std::map<Watcher, Point> WatcherPositionMap;
        typedef std::map<ObjectType, WatcherPositionMap> WatcherTypeObjectMap;

        typedef PointT<int> TowerIndex;
        typedef RegionT<int> TowerIndexRegion;

    private:
        //灯塔的物体
        TypeObjectMap m_objs{};
        WatcherTypeObjectMap m_watcherObjs{};
        // 灯塔的坐标
        uint32_t m_id{};
        TowerIndex m_pos{};
    public:
        TowerT(uint32_t _id, const TowerIndex &_pos) : m_id(_id), m_pos(_pos) {}

        TowerT(uint32_t _id, const TowerIndex &&_pos) : m_id(_id), m_pos(_pos) {}

        ~TowerT() {}

    public:
        uint32_t GetId() { return m_id; }

        TypeObjectMap &GetObjs() { return m_objs; }

        WatcherTypeObjectMap &GetWatchers() { return m_watcherObjs; }

        TowerIndex GetPos() { return m_pos; }

    public:
        bool Add(const Object &obj, const Point &pos, ObjectType type) {
            return m_objs[type].insert(std::make_pair(obj, pos)).second;
        }

        bool Remove(const Object &obj, ObjectType type) { return m_objs[type].erase(obj) == 1; }

        bool AddWatcher(const Watcher &watcher, const Point &pos, ObjectType type) {
            return m_watcherObjs[type].insert(std::make_pair(watcher, pos)).second;
        }

        bool RemoveWatcher(const Watcher &watcher, ObjectType type) { return m_watcherObjs[type].erase(watcher) == 1; }

    public:
        bool ToString(std::ostream &os) {
            os << "tower" << m_id << ":{pos:(" << m_pos.x << "," << m_pos.y << "),";
            os << "objs:";
            for (const auto &i :m_objs) {
                os << "{type:" << i.first << ",objs:[";
                for (const auto &j : i.second) {
                    os << "{obj:" << j.first << "pos:(" << j.second.x << "," << j.second.y << ")},";
                }
                os << "]},";
            }
            os << "\t";
            os << "watchers:";
            for (const auto &i :m_watcherObjs) {
                os << "{type:" << i.first << ", watchers:[";
                for (const auto &j : i.second) {
                    os << "{ obj:" << j.first.obj << ", viewRange:" << j.first.viewRange << ", pos:(" << j.second.x
                       << "," << j.second.y << ")},";
                }
                os << "]}";
            }
            os << "}";
            return true;
        }
    };

    /**
     * AOI实现
     * @tparam NumberT
     * @tparam PayloadT
     */
    template<typename NumberT, typename PayloadT>
    class TowerAoiT {
    public:
        typedef NumberT Number;

        typedef TowerConfigT<Number> TowerConfig;
        typedef TowerT<Number, PayloadT> Tower;
        typedef typename Tower::Point Point;
        typedef typename Tower::Object Object;
        typedef typename Tower::ObjectType ObjectType;
        typedef typename Tower::PositionMap PositionMap;
        typedef typename Tower::TypeObjectMap TypeObjectMap;
        typedef typename Tower::Watcher Watcher;
        typedef typename Tower::WatcherPositionMap WatcherPositionMap;
        typedef typename Tower::WatcherTypeObjectMap WatcherTypeObjectMap;
        typedef RegionT<Number> Region;
        typedef typename Tower::TowerIndex TowerIndex;
        typedef typename Tower::TowerIndexRegion TowerIndexRegion;

        typedef void (*ObjCallBackT)(const Object &obj, const WatcherTypeObjectMap &firstSet,
                                     const WatcherTypeObjectMap &secondSet, bool IsDiffTower);//obj变化回调函数
        typedef void (*WatcherCallBackT)(const Watcher &watcher, const TypeObjectMap &firstSet,
                                         const TypeObjectMap &secondSet, bool IsDiffTower);//watcher变化回调函数
        /**
         * 回调函数数组定义
         * OBJ_ADD firstSet 影响到的wacther, empty, false
         * OBJ_REMOVE firstSet 影响到的wacther, empty, false
         * OBJ_MOVED firstSet 没有离开格子，但是还是看到移动的对象, empty, false
         * OBJ_MOVED firstSet 离开视野对象， secondSet 进入视野对象, ture
         *
         * WATCHER_ADD
         * WATCHER_REMOVE
         * WATCHER_MOVE
         */
        class CallBackDef {
        public:
            enum {
                OBJ_ADD = 0,
                OBJ_REMOVE,
                OBJ_MOVED,
                OBJ_MAX,
            };
            enum {
                WATCHER_ADD = 0,
                WATCHER_REMOVE,
                WATCHER_MOVE,
                WATCHER_MAX
            };
        };

    private:
        ObjCallBackT objectCallBacks[CallBackDef::OBJ_MAX]{0};
        WatcherCallBackT watcherCallBacks[CallBackDef::WATCHER_MAX]{0};

        TowerConfig config{};
        int m_towerXLen;
        int m_towerYLen;
        Tower ***m_towers;
        //空,用来填充回调函数中无用的位置
        WatcherTypeObjectMap emptyWatcher;
        TypeObjectMap emptyObjects;
    private:
        void RegisterCallBacks(const ObjCallBackT _objCallBacks[CallBackDef::OBJ_MAX],
                               const WatcherCallBackT _watcherCallBacks[CallBackDef::WATCHER_MAX]) {
            for (int i = CallBackDef::OBJ_ADD; i < CallBackDef::OBJ_MAX; ++i) { objectCallBacks[i] = _objCallBacks[i]; }
            for (int i = CallBackDef::WATCHER_ADD;
                 i < CallBackDef::WATCHER_MAX; ++i) { watcherCallBacks[i] = _watcherCallBacks[i]; }

        }

        void SetConfig(const TowerConfig &_config) { config = _config; }

        TowerConfig GetConfig() { return config; }

    public:
        TowerAoiT() = delete;

        TowerAoiT(const TowerConfig &_config, const ObjCallBackT _objCallBacks[CallBackDef::MAX],const WatcherCallBackT _watcherCallBacks[CallBackDef::WATCHER_MAX]) : config(_config) {
            RegisterCallBacks(_objCallBacks,_watcherCallBacks);
            m_towerXLen = config.GlobalWith / (2 * config.HalfTowerWith);
            if (config.GlobalWith % (2 * config.HalfTowerWith) != 0) {
                //地图大小不合适咋办？
                ++m_towerXLen;
            }
            m_towerYLen = config.GlobalHeight / (2 * config.HalfTowerHeight);
            if (config.GlobalHeight % (2 * config.HalfTowerHeight) != 0) {
                ++m_towerYLen;
            }
            m_towers = new Tower**[m_towerXLen];
            for (int x = 0; x < m_towerXLen; ++x) {
                m_towers[x] = new Tower *[m_towerYLen];
                for (int y = 0; y < m_towerYLen; ++y) {
                    m_towers[x][y] = new Tower(x * m_towerXLen + y, TowerIndex(x, y));
                }
            }

        }

    public:
        bool AddObject(const Object &obj, const Point &pos, ObjectType type) {
            if (!CheckPos(pos)) { return false; }
            TowerIndex towerIndex = TranslateTowerIndex(pos);
            auto ret = m_towers[towerIndex.x][towerIndex.y]->Add(obj, pos, type);
            if (ret && objectCallBacks[CallBackDef::OBJ_ADD]) {
                objectCallBacks[CallBackDef::OBJ_ADD](obj, m_towers[towerIndex.x][towerIndex.y]->GetWatchers(),
                                                      emptyWatcher,
                                                      false);
            }
            return ret;
        }

        bool RemoveObject(const Object &obj, const Point &pos, ObjectType type) {
            if (!CheckPos(pos)) { return false; }
            TowerIndex towerIndex = TranslateTowerIndex(pos);
            auto ret = m_towers[towerIndex.x][towerIndex.y]->Remove(obj, type);
            if (ret && objectCallBacks[CallBackDef::OBJ_REMOVE]) {
                objectCallBacks[CallBackDef::OBJ_REMOVE](obj, m_towers[towerIndex.x][towerIndex.y]->GetWatchers(),
                                                         emptyWatcher,
                                                         false);
            }
            return ret;
        }

        bool RemoveObject(const Object &obj, ObjectType type) {
            //todo

            return false;
        }

        bool MoveObject(const Object &obj, const Point &oldPos, const Point &newPos, ObjectType type) {
            if (!CheckPos(oldPos)) { return false; }
            if (!CheckPos(newPos)) { return false; }

            TowerIndex oldTowerIndex = TranslateTowerIndex(oldPos);
            TowerIndex newTowerIndex = TranslateTowerIndex(newPos);
            if (oldTowerIndex.x == newTowerIndex.x && oldTowerIndex.y == newTowerIndex.y) {
                m_towers[oldTowerIndex.x][oldTowerIndex.y]->GetObjs()[type][obj] = newPos;
                if (objectCallBacks[CallBackDef::OBJ_MOVED])
                    objectCallBacks[CallBackDef::OBJ_MOVED](obj,
                                                            m_towers[oldTowerIndex.x][oldTowerIndex.y]->GetWatchers(),
                                                            emptyWatcher,
                                                            false);
            } else {
                if (!m_towers[oldTowerIndex.x][oldTowerIndex.y]->Remove(obj, type)) { return false; }
                if (!m_towers[newTowerIndex.x][newTowerIndex.y]->Add(obj, newPos, type)) { return false; }
                if (objectCallBacks[CallBackDef::OBJ_MOVED]) {
                    objectCallBacks[CallBackDef::OBJ_MOVED](obj,
                                                            m_towers[oldTowerIndex.x][oldTowerIndex.y]->GetWatchers(),
                                                            m_towers[newTowerIndex.x][newTowerIndex.y]->GetWatchers(),
                                                            true);
                }
            }
            return true;
        }

        bool AddWatcher(const Watcher &watcher, const Point &pos, ObjectType type, size_t range) {
            if (!CheckPos(pos)) { return false; }

            TowerIndex towerIndex = TranslateTowerIndex(pos);
            TowerIndexRegion region = GetTowerIndexRegion(towerIndex, range);
            bool ret = false;
            for (int x = region.start.x; x <= region.end.x; ++x) {
                for (int y = region.start.y; y <= region.end.y; ++y) {
                    ret = m_towers[x][y]->AddWatcher(watcher, pos, type);
                    if (ret && watcherCallBacks[CallBackDef::WATCHER_ADD]) {
                        watcherCallBacks[CallBackDef::WATCHER_ADD](watcher.obj, m_towers[x][y]->GetObjs(), emptyObjects,
                                                                   false);
                    } else {
                        return ret;
                    }
                };
            }
            return ret;
        }

        bool RemoveWatcher(const Watcher &watcher, const Point &pos, ObjectType type) {
            if (!CheckPos(pos)) { return false; }

            TowerIndex towerIndex = TranslateTowerIndex(pos);
            TowerIndexRegion region = GetTowerIndexRegion(towerIndex, watcher.viewRange);
            bool ret = false;
            for (int x = region.start.x; x <= region.end.x; ++x) {
                for (int y = region.start.y; y <= region.end.y; ++y) {
                    ret = m_towers[x][y]->RemoveWatcher(watcher, type);
                    if (!ret) {
                        return ret;
                    }
                    if (watcherCallBacks[CallBackDef::WATCHER_REMOVE]) {
                        watcherCallBacks[CallBackDef::WATCHER_REMOVE](watcher.obj, m_towers[x][y]->GetObjs(),
                                                                      emptyObjects,
                                                                      false);
                    }
                };
            }
            return ret;
        }

        bool RemoveWatcher(const Watcher &watcher, ObjectType type) {
            //todo
            return false;
        }

        /**
         * 移动观察者
         * @param watcher
         * @param oldPos
         * @param newPos
         * @param type
         * @return
         */
        bool MoveWatcher(const Watcher &watcher, const Point &oldPos, const Point &newPos, ObjectType type) {
            if (!CheckPos(oldPos)) { return false; }
            if (!CheckPos(newPos)) { return false; }

            TowerIndex oldTowerIndex = TranslateTowerIndex(oldPos);
            TowerIndex newTowerIndex = TranslateTowerIndex(newPos);
            if (oldTowerIndex.x == newTowerIndex.x && oldTowerIndex.y == newTowerIndex.y) {
                m_towers[oldTowerIndex.x][oldTowerIndex.y]->GetObjs()[type][watcher] = newPos;
                if (watcherCallBacks[CallBackDef::WATCHER_MOVE])
                    watcherCallBacks[CallBackDef::WATCHER_MOVE](watcher,
                                                                m_towers[oldTowerIndex.x][oldTowerIndex.y]->GetObjs(),
                                                                emptyWatcher,
                                                                false);
            } else {

                TowerIndexRegion oldRegion = GetTowerIndexRegion(oldTowerIndex, watcher.viewRange);
                TowerIndexRegion newRegion = GetTowerIndexRegion(newTowerIndex, watcher.viewRange);

                //todo 区分下没有离开的

                // 从旧的灯塔中删除观察者
                bool ret = false;
                for (int x = oldRegion.start.x; x <= oldRegion.end.x; ++x) {
                    for (int y = oldRegion.start.y; y <= oldRegion.end.y; ++y) {
                        ret = m_towers[x][y]->RemoveWatcher(watcher, type);
                        if (!ret) {
                            return ret;
                        }
                        if (watcherCallBacks[CallBackDef::WATCHER_MOVE]) {
                            watcherCallBacks[CallBackDef::WATCHER_MOVE](watcher.obj, m_towers[x][y]->GetObjs(),
                                                                        emptyObjects,
                                                                        true);
                        }
                    };
                }
                // 加入到新的灯塔中
                for (int x = newRegion.start.x; x <= newRegion.end.x; ++x) {
                    for (int y = newRegion.start.y; y <= newRegion.end.y; ++y) {
                        ret = m_towers[x][y]->RemoveWatcher(watcher, type);
                        if (!ret) {
                            return ret;
                        }
                        if (watcherCallBacks[CallBackDef::WATCHER_MOVE]) {
                            watcherCallBacks[CallBackDef::WATCHER_MOVE](emptyObjects,
                                                                        watcher.obj, m_towers[x][y]->GetObjs(),
                                                                        true);
                        }
                    };
                }
            }
            return true;
        }

        bool ResetWatcherViewRange(const Watcher &watcher, const Point &pos, ObjectType type, int newViewRange) {
            //todo
            return false;
        }

        bool ResetWatcherViewRange(const Watcher &watcher, ObjectType type, int newViewRange) {
            //todo
            return false;
        }

    private:
        TowerIndexRegion GetTowerIndexRegion(const TowerIndex &towerIndex, int range) {
            if (range <= 0) {
                range = 1;
            }
            TowerIndexRegion region{};
            region.start.x = towerIndex.x - range;
            region.end.x = towerIndex.x + range;

            region.start.y = towerIndex.y - range;
            region.end.y = towerIndex.y + range;
            region.start.x = region.start.x < 0 ? 0 : region.start.x;
            region.start.y = region.start.y < 0 ? 0 : region.start.y;

            region.end.x = region.end.x >= m_towerXLen ? m_towerXLen - 1 : region.end.x;
            region.end.y = region.end.y >= m_towerYLen ? m_towerYLen - 1 : region.end.y;
            return region;

        }

        inline bool CheckPos(const Point &pos) const {
            return !(pos.x < 0 || pos.y < 0 || pos.x >= config.GlobalWith || pos.y >= config.GlobalHeight);
        }

//        Region GetRegion(const TowerIndex &pos, Number range) {
//            Region region;
//            if (pos.x - range < 0) {
//                region.start.x = 0;
//                region.end.x = 2 * range;
//            } else if (pos.x + range >= config.GlobalWith) {
//                region.end.x = config.GlobalWith;
//                region.start.x = config.GlobalWith - 2 * range;
//            } else {
//                region.start.x = pos.x - range;
//                region.end.x = pos.x + range;
//            }
//            if (pos.y - range < 0) {
//                region.start.y = 0;
//                region.end.y = 2 * range;
//            } else if (pos.y + range >= config.GlobalHeight) {
//                region.end.y = config.GlobalHeight;
//                region.start.y = config.GlobalHeight - 2 * range;
//            } else {
//                region.start.y = pos.y - range;
//                region.end.y = pos.y + range;
//            }
//            region.start.x = region.start.x >= 0 ? region.start.x : 0;
//            region.end.x = region.end.x < config.GlobalWith ? region.end.x : config.GlobalWith;
//            region.start.y = region.start.y >= 0 ? region.start.y : 0;
//            region.end.y = region.end.y < config.GlobalHeight ? region.end.y : config.GlobalHeight;
//            return region;
//        }

        TowerIndex TranslateTowerIndex(const Point &pos) const {
            return TowerIndex((int) (pos.x / (config.HalfTowerWith * 2)), (int) (pos.y / (config.HalfTowerHeight * 2)));
        }

    public:
        bool ToString(std::ostream &os) {
            os << "\n";
            os << "tows:\n";
            for (int x = 0; x < this->m_towerXLen; ++x) {
                for (int y = 0; y < this->m_towerYLen; ++y) {
                    m_towers[x][y]->ToString(os);
                    os << "\n";
                }
            }
            os << "\n";
            return true;
        }
    };
}

#define TOWERIMPL(number, payload)\
typedef TowerAoiImpl::TowerAoiT<number ,payload> TowerAoi;\
typedef TowerAoi::Number Number;\
typedef TowerAoi::TowerConfig TowerConfig;\
typedef TowerAoi::Tower Tower;\
typedef TowerAoi::Point Point;\
typedef TowerAoi::Object Object;\
typedef TowerAoi::ObjectType ObjectType;\
typedef TowerAoi::PositionMap PositionMap;\
typedef TowerAoi::TypeObjectMap TypeObjectMap;\
typedef TowerAoi::Watcher Watcher;\
typedef TowerAoi::WatcherPositionMap WatcherPositionMap;\
typedef TowerAoi::WatcherTypeObjectMap WatcherTypeObjectMap;\
typedef TowerAoi::Region Region;\
typedef TowerAoi::TowerIndex TowerIndex;\
typedef TowerAoi::TowerIndexRegion TowerIndexRegion;\
typedef TowerAoi::ObjCallBackT ObjCallBack;\
typedef TowerAoi::WatcherCallBackT WatcherCallBack;\
typedef TowerAoi::CallBackDef CallBackDef;

#endif //CPP_STUDY_ALL_TOWER_AOI_H
