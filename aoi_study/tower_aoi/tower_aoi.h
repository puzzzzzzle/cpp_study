/********************************************************************

 * @time 2019/12/6 : 19:09
 * @version 1.0
 * @author khalidzhang
 * @e-mail khalidzhang@tencent.com
 * @description: 灯塔法AOI
 *               请自行保证object全局唯一，这里要处理的话得加一个全局的set保存所有object，由于频繁调用，开销会比较大，就不处理了！！！
 *
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
        Number TowerWith{};    //每个灯塔的长
        Number TowerHeight{};    //每个灯塔的宽
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

        PointT &operator=(const PointT &p) {
            x = p.x;
            y = p.y;
            return *this;
        }

        PointT &operator=(const PointT &&p) {
            x = p.x;
            y = p.y;
            return *this;
        }

        friend bool operator==(const PointT &lhs, const PointT &rhs) {
            return lhs.x == rhs.x && lhs.y == rhs.y;
        }

        friend bool operator<(const PointT &lhs, const PointT &rhs) {
            if (lhs.x < rhs.x) { return true; }
            if (lhs.x > rhs.x) { return false; }
            return lhs.y < rhs.y;
        }
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

        WatcherT() = default;

        WatcherT(const PayloadT &_obj, int _viewRange) : obj(_obj), viewRange(_viewRange) {}

        WatcherT(const WatcherT &watcher) : obj(watcher.obj), viewRange(watcher.viewRange) {}

        WatcherT(const WatcherT &&watcher) : obj(watcher.obj), viewRange(watcher.viewRange) {}

        WatcherT &operator=(const WatcherT &watcher) {
            obj = watcher.obj;
            viewRange = watcher.viewRange;
            return *this;
        }

        WatcherT &operator=(const WatcherT &&watcher) {
            obj = watcher.obj;
            viewRange = watcher.viewRange;
            return *this;
        }

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

        bool RemoveWatcher(const Watcher &watcher, ObjectType type) {
            return m_watcherObjs[type].erase(watcher) == 1;
        }

    public:
        bool ToString(std::ostream &os) {
            os << "tower" << m_id << ":{pos:(" << m_pos.x << "," << m_pos.y << "),";
            os << "objs:";
            for (const auto &i :m_objs) {
                os << "{type:" << i.first << ",objs:[";
                for (const auto &j : i.second) {
                    os << "{obj:" << j.first << ",pos:(" << j.second.x << "," << j.second.y << ")},";
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
        typedef std::map<Object, TowerIndex> ObjectTowerIndexMap;
        typedef std::map<ObjectType, ObjectTowerIndexMap> TypeObjectTowerIndexMap;

        typedef void (*ObjCallBackT)(const Object &obj, ObjectType type, const Point &pos,
                                     const WatcherTypeObjectMap &appear,
                                     const WatcherTypeObjectMap &disAppear, bool IsDiffTower);//obj变化回调函数
        typedef void (*WatcherCallBackT)(const Watcher &watcher, ObjectType type, const Point &pos,
                                         const TypeObjectMap &appear,
                                         const TypeObjectMap &disAppear, bool IsDiffTower);//watcher变化回调函数
        /**
         * 回调函数数组定义
         * OBJ_ADD  出现的对象, empty, false
         * OBJ_REMOVE  empty , 消失的对象, false
         * OBJ_MOVED  没有离开格子但是还是看到移动的对象, empty, false
         * OBJ_MOVED   出现的对象 ，消失的对象  , true
         *
         * WATCHER_ADD 出现的对象, empty, false
         * WATCHER_REMOVE empty , 消失的对象, false
         * WATCHER_MOVE 没有离开格子但是还是看到移动的对象, empty, false
         * WATCHER_MOVE  出现的对象, 消失的对象， true
         * WATCHER_VIEW_CHANGE 出现的对象， 消失的对象，false
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
                WATCHER_VIEW_CHANGE,
                WATCHER_MAX
            };
        };

    private:
        ObjCallBackT objectCallBacks[CallBackDef::OBJ_MAX]{0};
        WatcherCallBackT watcherCallBacks[CallBackDef::WATCHER_MAX]{0};
        TypeObjectTowerIndexMap typeObjectTowerIndexMap;
        TypeObjectTowerIndexMap typeWatcherTowerIndexMap;

        TowerConfig config{};
        int m_towerXLen;
        int m_towerYLen;
        Tower ***m_towers;
        //空,用来填充回调函数中无用的位置
        WatcherTypeObjectMap emptyWatcher;
        TypeObjectMap emptyObjects;
    public:
        void RegisterCallBacks(const ObjCallBackT _objCallBacks[CallBackDef::OBJ_MAX],
                               const WatcherCallBackT _watcherCallBacks[CallBackDef::WATCHER_MAX]) {
            for (int i = CallBackDef::OBJ_ADD; i < CallBackDef::OBJ_MAX; ++i) { objectCallBacks[i] = _objCallBacks[i]; }
            for (int i = CallBackDef::WATCHER_ADD;
                 i < CallBackDef::WATCHER_MAX; ++i) { watcherCallBacks[i] = _watcherCallBacks[i]; }

        }

        const TowerConfig &GetConfig() { return config; }

    private:
        void SetConfig(const TowerConfig &_config) { config = _config; }


    public:
        TowerAoiT() = delete;

        TowerAoiT(const TowerAoiT &) = delete;

        TowerAoiT(const TowerConfig &_config) : config(_config) {
            m_towerXLen = config.GlobalWith / config.TowerWith;
            if (config.GlobalWith % config.TowerWith != 0) {
                //地图大小不合适咋办？
                ++m_towerXLen;
            }
            m_towerYLen = config.GlobalHeight / config.TowerHeight;
            if (config.GlobalHeight % config.TowerHeight != 0) {
                ++m_towerYLen;
            }
            m_towers = new Tower **[m_towerXLen];
            for (int x = 0; x < m_towerXLen; ++x) {
                m_towers[x] = new Tower *[m_towerYLen];
                for (int y = 0; y < m_towerYLen; ++y) {
                    m_towers[x][y] = new Tower(x * m_towerXLen + y, TowerIndex(x, y));
                }
            }
        }

        TowerAoiT(const TowerConfig &_config, const ObjCallBackT _objCallBacks[CallBackDef::MAX],
                  const WatcherCallBackT _watcherCallBacks[CallBackDef::WATCHER_MAX]) : TowerAoiT(_config) {
            RegisterCallBacks(_objCallBacks, _watcherCallBacks);
        }

        ~TowerAoiT() {
            if (m_towers) {
                delete[] m_towers;
            }
        }

    public:
        bool AddObject(const Object &obj, const Point &pos, ObjectType type) {
            if (!CheckPos(pos)) { return false; }
            TowerIndex towerIndex = TranslateTowerIndex(pos);
            auto ret = m_towers[towerIndex.x][towerIndex.y]->Add(obj, pos, type);
            if (ret && objectCallBacks[CallBackDef::OBJ_ADD]) {
                objectCallBacks[CallBackDef::OBJ_ADD](obj, type, pos,
                                                      m_towers[towerIndex.x][towerIndex.y]->GetWatchers(),
                                                      emptyWatcher,
                                                      false);
            }
            typeObjectTowerIndexMap[type][obj] = towerIndex;
            return true;
        }

        bool RemoveObject(const Object &obj, ObjectType type) {
            TowerIndex towerIndex = GetObjectTowerIndex(obj, type, true);
            if (towerIndex.x < 0) { return false; }
            Point pos = m_towers[towerIndex.x][towerIndex.y]->GetObjs()[type][obj];
            auto ret = m_towers[towerIndex.x][towerIndex.y]->Remove(obj, type);
            if (ret && objectCallBacks[CallBackDef::OBJ_REMOVE]) {
                objectCallBacks[CallBackDef::OBJ_REMOVE](obj, type, pos, emptyWatcher,
                                                         m_towers[towerIndex.x][towerIndex.y]->GetWatchers(),
                                                         false);
            }
            if (ret) { ret = typeObjectTowerIndexMap[type].erase(obj); }
            return ret;
        }


        bool MoveObject(const Object &obj, const Point &newPos, ObjectType type) {
            if (!CheckPos(newPos)) { return false; }
            TowerIndex oldTowerIndex = GetObjectTowerIndex(obj, type, true);
            if (oldTowerIndex.x < 0) { return false; }
            TowerIndex newTowerIndex = TranslateTowerIndex(newPos);
            if (oldTowerIndex.x == newTowerIndex.x && oldTowerIndex.y == newTowerIndex.y) {
                m_towers[oldTowerIndex.x][oldTowerIndex.y]->GetObjs()[type][obj] = newPos;
                if (objectCallBacks[CallBackDef::OBJ_MOVED])
                    objectCallBacks[CallBackDef::OBJ_MOVED](obj, type, newPos,
                                                            m_towers[oldTowerIndex.x][oldTowerIndex.y]->GetWatchers(),
                                                            emptyWatcher,
                                                            false);
            } else {
                if (!m_towers[oldTowerIndex.x][oldTowerIndex.y]->Remove(obj, type)) { return false; }
                if (!typeObjectTowerIndexMap[type].erase(obj)) { return false; }
                if (!m_towers[newTowerIndex.x][newTowerIndex.y]->Add(obj, newPos, type)) { return false; }
                typeObjectTowerIndexMap[type][obj] = newTowerIndex;
                if (objectCallBacks[CallBackDef::OBJ_MOVED]) {
                    objectCallBacks[CallBackDef::OBJ_MOVED](obj, type, newPos,
                                                            m_towers[newTowerIndex.x][newTowerIndex.y]->GetWatchers(),
                                                            m_towers[oldTowerIndex.x][oldTowerIndex.y]->GetWatchers(),
                                                            true);
                }
            }
            return true;
        }

        bool AddWatcher(const Watcher &watcher, const Point &pos, ObjectType type) {
            if (!CheckPos(pos)) { return false; }

            TowerIndex towerIndex = TranslateTowerIndex(pos);
            TowerIndexRegion region = GetTowerIndexRegion(towerIndex, watcher.viewRange);

            bool ret = false;
            for (int x = region.start.x; x <= region.end.x; ++x) {
                for (int y = region.start.y; y <= region.end.y; ++y) {
                    ret = m_towers[x][y]->AddWatcher(watcher, pos, type);
                    if (!ret) {
                        return ret;
                    }
                    if (watcherCallBacks[CallBackDef::WATCHER_ADD]) {
                        watcherCallBacks[CallBackDef::WATCHER_ADD](watcher, type, pos, m_towers[x][y]->GetObjs(),
                                                                   emptyObjects,
                                                                   false);
                    }
                };
            }
            typeWatcherTowerIndexMap[type][watcher.obj] = towerIndex;
            return true;
        }

        bool RemoveWatcher(const Object &watcherObj, ObjectType type) {
            TowerIndex towerIndex = GetObjectTowerIndex(watcherObj, type, false);
            if (towerIndex.x < 0) { return false; }

            Watcher tmp{};
            tmp.obj = watcherObj;
            auto &watchers = m_towers[towerIndex.x][towerIndex.y]->GetWatchers()[type];
            auto it = watchers.find(tmp);
            if (it == watchers.end()) {
                return false;
            }
            const auto &watcher = it->first;

            TowerIndexRegion region = GetTowerIndexRegion(towerIndex, watcher.viewRange);
            bool ret = false;
            for (int x = region.start.x; x <= region.end.x; ++x) {
                for (int y = region.start.y; y <= region.end.y; ++y) {
                    ret = m_towers[x][y]->RemoveWatcher(watcher, type);
                    if (!ret) {
                        return ret;
                    }
                    if (watcherCallBacks[CallBackDef::WATCHER_REMOVE]) {
                        watcherCallBacks[CallBackDef::WATCHER_REMOVE](watcher, type, it->second, emptyObjects,
                                                                      m_towers[x][y]->GetObjs(),
                                                                      false);
                    }
                };
            }
            if (ret) { ret = typeWatcherTowerIndexMap[type].erase(watcherObj); }
            return ret;
        }


        /**
         * 移动观察者
         * @param watcher
         * @param oldPos
         * @param newPos
         * @param type
         * @return
         */
        bool MoveWatcher(const Object &watcherObj, const Point &newPos, ObjectType type) {

            if (!CheckPos(newPos)) {
                return false;
            }

            TowerIndex oldTowerIndex = GetObjectTowerIndex(watcherObj, type, false);
            if (oldTowerIndex.x < 0) {
                return false;
            }

            TowerIndex newTowerIndex = TranslateTowerIndex(newPos);

            Watcher tmp{};
            tmp.obj = watcherObj;
            auto &watchers = m_towers[oldTowerIndex.x][oldTowerIndex.y]->GetWatchers()[type];
            auto it = watchers.find(tmp);
            if (it == watchers.end()) {
                return false;
            }
            const auto watcher = it->first; //todo 用引用时 stl把内存写坏了???


            if (oldTowerIndex.x == newTowerIndex.x && oldTowerIndex.y == newTowerIndex.y) {
                m_towers[oldTowerIndex.x][oldTowerIndex.y]->GetWatchers()[type][watcher] = newPos;
                if (watcherCallBacks[CallBackDef::WATCHER_MOVE])
                    watcherCallBacks[CallBackDef::WATCHER_MOVE](watcher, type, newPos,
                                                                m_towers[oldTowerIndex.x][oldTowerIndex.y]->GetObjs(),
                                                                emptyObjects,
                                                                false);
            } else {

                TowerIndexRegion oldRegion = GetTowerIndexRegion(oldTowerIndex, watcher.viewRange);
                TowerIndexRegion newRegion = GetTowerIndexRegion(newTowerIndex, watcher.viewRange);


                // 从旧的灯塔中删除观察者
                bool ret = false;
                for (int x = oldRegion.start.x; x <= oldRegion.end.x; ++x) {
                    for (int y = oldRegion.start.y; y <= oldRegion.end.y; ++y) {
                        //过滤掉还在视野内的
                        if (x >= newRegion.start.x && y >= newRegion.start.y && x <= newRegion.end.x &&
                            y <= newRegion.end.y) {
                            m_towers[oldTowerIndex.x][oldTowerIndex.y]->GetWatchers()[type][watcher] = newPos;
                            if (watcherCallBacks[CallBackDef::WATCHER_MOVE])
                                watcherCallBacks[CallBackDef::WATCHER_MOVE](watcher, type, newPos,
                                                                            m_towers[oldTowerIndex.x][oldTowerIndex.y]->GetObjs(),
                                                                            emptyObjects,
                                                                            false);
                            continue;
                        }
                        ret = m_towers[x][y]->RemoveWatcher(watcher, type);
                        if (!ret) {
                            return ret;
                        }
                        if (watcherCallBacks[CallBackDef::WATCHER_MOVE]) {
                            watcherCallBacks[CallBackDef::WATCHER_MOVE](watcher, type, newPos,
                                                                        emptyObjects,
                                                                        m_towers[x][y]->GetObjs(),
                                                                        true);
                        }
                    };
                }
                // 加入到新的灯塔中
                for (int x = newRegion.start.x; x <= newRegion.end.x; ++x) {
                    for (int y = newRegion.start.y; y <= newRegion.end.y; ++y) {
                        //过滤掉还在视野内的
                        if (x >= oldRegion.start.x && y >= oldRegion.start.y && x <= oldRegion.end.x &&
                            y <= oldRegion.end.y) {
                            continue;
                        }

                        ret = m_towers[x][y]->AddWatcher(watcher, newPos, type);
                        if (!ret) {
                            return ret;
                        }
                        if (watcherCallBacks[CallBackDef::WATCHER_MOVE]) {
                            watcherCallBacks[CallBackDef::WATCHER_MOVE](watcher, type, newPos,
                                                                        m_towers[x][y]->GetObjs(),
                                                                        emptyObjects,
                                                                        true);
                        }
                    };
                }
            }
            typeWatcherTowerIndexMap[type][watcherObj] = newTowerIndex;
            return true;
        }

        bool WatcherSetViewRange(const Object &watcherObj, ObjectType type, int newViewRange) {
            TowerIndex towerIndex = GetObjectTowerIndex(watcherObj, type, false);
            if (towerIndex.x < 0) { return false; }

            Watcher tmp{};
            tmp.obj = watcherObj;
            auto &watchers = m_towers[towerIndex.x][towerIndex.y]->GetWatchers()[type];
            auto it = watchers.find(tmp);
            if (it == watchers.end()) {
                return false;
            }
            auto &watcher = it->first;


            if (watcher.viewRange == newViewRange) {
                return true;
            }

            TowerIndexRegion bigger;
            TowerIndexRegion smaller;

            bool ret = false;

            //计算视野变化后，发生改变的灯塔区域，只通知该区域的
            // 小的总是在范围内，所以通知范围为 (smaller,bigger]
            bool isBigger = newViewRange > watcher.viewRange;
            if (isBigger) {
                bigger = GetTowerIndexRegion(towerIndex, watcher.viewRange);
                smaller = GetTowerIndexRegion(towerIndex, newViewRange);
            } else {
                smaller = GetTowerIndexRegion(towerIndex, watcher.viewRange);
                bigger = GetTowerIndexRegion(towerIndex, newViewRange);
            }


            for (int bx = bigger.start.x; bx <= bigger.end.x; ++bx) {
                for (int by = bigger.start.y; by <= bigger.end.y; ++by) {
                    //过滤smaller 范围内的
                    if (bx >= smaller.start.x && by >= smaller.start.y && bx <= smaller.end.x && by <= smaller.end.y) {
                        continue;
                    }
                    if (isBigger) {
                        //视野扩大
                        ret = m_towers[bx][by]->AddWatcher(watcher,
                                                           m_towers[towerIndex.x][towerIndex.y]->GetWatchers()[type][watcher],
                                                           type);
                        if (!ret) {
                            return ret;
                        }
                        if (watcherCallBacks[CallBackDef::WATCHER_VIEW_CHANGE]) {
                            watcherCallBacks[CallBackDef::WATCHER_VIEW_CHANGE](watcher,
                                                                               type,
                                                                               it->second,
                                                                               m_towers[bx][by]->GetObjs(),
                                                                               emptyObjects,
                                                                               false);
                        }
                    } else {
                        //视野减小
                        ret = m_towers[bx][by]->RemoveWatcher(watcher, type);
                        if (!ret) {
                            return ret;
                        }
                        if (watcherCallBacks[CallBackDef::WATCHER_VIEW_CHANGE]) {
                            watcherCallBacks[CallBackDef::WATCHER_VIEW_CHANGE](watcher,
                                                                               type,
                                                                               it->second,
                                                                               emptyObjects,
                                                                               m_towers[bx][by]->GetObjs(),
                                                                               false);
                        }
                    }
                }
            }
            return true;
        }

        bool GetWatcherView() {
            //todo

            return false;
        }

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

        inline TowerIndex TranslateTowerIndex(const Point &pos) const {
            return TowerIndex((int) (pos.x / config.TowerWith), (int) (pos.y / config.TowerHeight));
        }

    private:
        inline TowerIndex GetObjectTowerIndex(const Object &obj, ObjectType type, bool IsObject) {
            auto &indexMap = IsObject ? typeObjectTowerIndexMap[type] : typeWatcherTowerIndexMap[type];
            auto it = indexMap.find(obj);
            if (it == indexMap.end()) {
                return TowerIndex(-1, -1);
            }
            return it->second;
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

#define TOWER_DEFINE(number, payload)\
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
typedef TowerAoi::CallBackDef CallBackDef;\
typedef TowerAoi::ObjectTowerIndexMap ObjectTowerIndexMap;\
typedef TowerAoi::TypeObjectTowerIndexMap TypeObjectTowerIndexMap;


#endif //CPP_STUDY_ALL_TOWER_AOI_H
