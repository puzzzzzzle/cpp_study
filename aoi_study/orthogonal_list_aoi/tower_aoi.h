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

namespace TowerAoi
{
    /**
     * 灯塔配置
     * @tparam NumberT 坐标数值类型，全局保持统一
     */
    template<typename NumberT>
    struct TowerConfigT
    {
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
    struct PointT
    {
        typedef NumberT Number;

        Number x{};
        Number y{};

        PointT() = default;

        PointT(Number _x, Number _y) : x(_x), y(_y)
        {}

        PointT(const PointT &Point) : x(Point.x), y(Point.y)
        {}

        PointT(const PointT &&Point) : x(Point.x), y(Point.y)
        {}
    };

    /**
     * 区域
     * @tparam NumberT
     */
    template<typename NumberT>
    struct RegionT
    {
        typedef NumberT Number;
        PointT<Number> start{};
        PointT<Number> end{};

        RegionT() = default;

        RegionT(Number _startX, Number _startY, Number _endX, Number _endY) : start(_startX, _startY), end(_endX, _endY)
        {}

        RegionT(const PointT<Number> &_start, const PointT<Number> &_end) : start(_start), end(_end)
        {}

        RegionT(const PointT<Number> &&_start, const PointT<Number> &&_end) : start(_start), end(_end)
        {}
    };

    /**
     * 灯塔
     * @tparam NumberT
     * @tparam PayloadT 载荷，自己定义的结构体必须重载 < 和 ==
     */
    template<typename NumberT, typename PayloadT>
    class TowerT
    {
    public:
        typedef NumberT Number;

        typedef PayloadT Object;
        typedef PointT<Number> Point;
        typedef int ObjectType;

        typedef std::map<Object, Point> PositionMap;
        typedef std::map<ObjectType, PositionMap> TypeObjectMap;

    private:
        //灯塔的物体
        TypeObjectMap m_objs{};
        TypeObjectMap m_watcherObjs{};
        // 灯塔的坐标
        uint32_t m_id{};
        Point m_pos{};
    public:
        TowerT(uint32_t _id, const Point &_pos) : m_id(_id), m_pos(_pos)
        {}

        TowerT(uint32_t _id, const Point &&_pos) : m_id(_id), m_pos(_pos)
        {}

        ~TowerT()
        {}

    public:
        uint32_t GetId()
        { return m_id; }

        TypeObjectMap GetObjs()
        { return m_objs; }

        TypeObjectMap GetWatchers()
        { return m_watcherObjs; }

        Point GetPos()
        { return m_pos; }

    public:
        bool Add(const Object &obj, const Point &pos, ObjectType type)
        { return m_objs[type].insert(std::make_pair(obj, pos)).second; }

        bool Remove(const Object &obj, ObjectType type)
        { return m_objs[type].erase(obj) == 1; }

        bool AddWatcher(const Object &obj, const Point &pos, ObjectType type)
        { return m_watcherObjs[type].insert(std::make_pair(obj, pos)).second; }

        bool RemoveWatcher(const Object &obj, ObjectType type)
        { return m_watcherObjs[type].erase(obj) == 1; }

    public:
        bool ToString(std::ostream &os)
        {
            os << "objs:\t";
            for (const auto &i :m_objs)
            {
                os << "type:" << i.first << ";\t";
                for (const auto &j : i.second)
                {
                    os << "{" << j.first << ":(" << j.second.x << "," << j.second.y << ")}\t";
                }
            }
            os << "watcher objs:\t";
            for (const auto &i :m_watcherObjs)
            {
                os << "type:" << i.first << ";\t";
                for (const auto &j : i.second)
                {
                    os << "{" << j.first << ":(" << j.second.x << "," << j.second.y << ")}\t";
                }
            }
            return true;
        }
    };

    /**
     * AOI实现
     * @tparam NumberT
     * @tparam PayloadT
     */
    template<typename NumberT, typename PayloadT>
    class TowerAoiT
    {
    public:
        typedef NumberT Number;

        typedef TowerConfigT<Number> TowerConfig;
        typedef TowerT<Number, PayloadT> Tower;
        typedef typename Tower::Point Point;
        typedef typename Tower::PayloadT Object;
        typedef typename Tower::ObjectType ObjectType;
        typedef typename Tower::PositionMap PositionMap;
        typedef typename Tower::TypeObjectMap TypeObjectMap;
        typedef RegionT<Number> Region;


        typedef void (*CallBack)(const Object &obj, const TypeObjectMap &oldObjects,
                                 const TypeObjectMap &newObjects, bool IsDiffTower);//回调函数

        /**
         * 回调函数数组定义
         */
        class CallBackDef
        {
        public:
            enum
            {
                OBJ_ADD = 0,
                OBJ_REMOVE,
                OBJ_MOVED,
                WATCHER_MOVE,
                MAX,
            };
        };

    private:
        CallBack callBacks[CallBackDef::MAX]{0};
        TowerConfig config{};
        int m_towerXLen;
        int m_towerYLen;
        Tower ***m_towers;
        //空,用来填充回调函数中无用的位置
        TypeObjectMap empty;
        typedef PointT<size_t> TowerPos;
    private:
        void RegisterCallBacks(const CallBack _callBacks[CallBackDef::MAX])
        {
            for (int i = 0; i < CallBackDef::MAX; ++i)
            { callBacks[i] = _callBacks[i]; }
        }

        void SetConfig(const TowerConfig &_config)
        { config = _config; }

        TowerConfig GetConfig()
        { return config; }

    public:
        TowerAoiT() = delete;

        TowerAoiT(const TowerConfig &_config, const CallBack _callBacks[CallBackDef::MAX]) : config(_config)
        {
            RegisterCallBacks(_callBacks);
            m_towerXLen = config.GlobalWith / (2 * config.HalfTowerWith);
            if (config.GlobalWith % (2 * config.HalfTowerWith) != 0)
            {
                //地图大小不合适咋办？
                ++m_towerXLen;
            }
            m_towerYLen = config.GlobalHeight / (2 * config.HalfTowerHeight);
            if (config.GlobalHeight % (2 * config.HalfTowerHeight) != 0)
            {
                ++m_towerYLen;
            }
            for (int x = 0; x < m_towerXLen; ++x)
            {
                m_towers[x] = new Tower *[m_towerYLen];
                for (int y = 0; y < m_towerYLen; ++y)
                {
                    m_towers[x][y] = new Tower(x * m_towerXLen + y, Point(x, y));
                }
            }

        }

    public:
//        bool Add(const Object &obj, const Point &pos, ObjectType type)
//        { return m_objs[type].insert(std::make_pair(obj, pos)).second; }
//
//        bool Remove(const Object &obj, ObjectType type)
//        { return m_objs[type].erase(obj) == 1; }
//
//        bool AddWatcher(const Object &obj, const Point &pos, ObjectType type)
//        { return m_watcherObjs[type].insert(std::make_pair(obj, pos)).second; }
//
//        bool RemoveWatcher(const Object &obj, ObjectType type)
//        { return m_watcherObjs[type].erase(obj) == 1; }

        bool AddObject(const Object &obj, const Point &pos, ObjectType type)
        {
            TowerPos towerPos = TranslatePos(pos);
            auto ret = m_towers[towerPos.x][towerPos.y]->Add(obj, pos, type);
            if (ret && callBacks[CallBackDef::OBJ_ADD])
            {
                callBacks[CallBackDef::OBJ_ADD](obj, m_towers[towerPos.x][towerPos.y]->GetWatchers(), empty, false);
            }
            return ret;
        }

        bool RemoveObjects(const Object &obj, const Point &pos, ObjectType type)
        {
            TowerPos towerPos = TranslatePos(pos);
            auto ret = m_towers[towerPos.x][towerPos.y]->Remove(obj, type);
            if (ret && callBacks[CallBackDef::OBJ_ADD])
            {
                callBacks[CallBackDef::OBJ_REMOVE](obj, m_towers[towerPos.x][towerPos.y]->GetWatchers(), empty, false);
            }
            return ret;
        }

        bool UpdateObject(const Object &obj, const Point &oldPos, const Point &newPos, ObjectType type)
        {
            TowerPos oldTowerPos = TranslatePos(oldPos);
            TowerPos newTowerPos = TranslatePos(newPos);
            bool ret = false;
            if (oldTowerPos.x == newTowerPos.x && oldTowerPos.y == newTowerPos.y)
            {
                m_towers[oldTowerPos.x][oldTowerPos.y]->GetObjs()[type][obj] = newPos;
                callBacks[CallBackDef::OBJ_MOVED](obj, m_towers[oldTowerPos.x][oldTowerPos.y]->GetWatchers(), empty,
                                                  false);
            } else
            {
                if (!m_towers[oldTowerPos.x][oldTowerPos.y]->Remove(obj, type))
                {
                    return false;
                }
                if (!m_towers[newTowerPos.x][newTowerPos.y]->Add(obj, newPos, type))
                {
                    return false;
                }
                callBacks[CallBackDef::OBJ_MOVED](obj, m_towers[oldTowerPos.x][oldTowerPos.y]->GetWatchers(),
                                                  m_towers[newTowerPos.x][newTowerPos.y]->GetWatchers(), true);
            }
            return true;
        }

        bool AddWatcher(const Object &obj, const Point &pos, ObjectType type)
        {
//            TowerPos towerPos = TranslatePos(pos);
//            auto ret = m_towers[towerPos.x][towerPos.y]->Add(obj, pos, type);
//            if (ret && callBacks[CallBackDef::OBJ_ADD])
//            {
//                callBacks[CallBackDef::OBJ_ADD](obj, m_towers[towerPos.x][towerPos.y]->GetWatchers(), empty, false);
//            }
//            return ret;
        }

    private:
        Region GetRegion(const Point &pos, Number range)
        {
            Region region;
            if (pos.x - range < 0)
            {
                region.start.x = 0;
                region.end.x = 2 * range;
            } else if (pos.x + range >= config.GlobalWith)
            {
                region.end.x = config.GlobalWith;
                region.start.x = config.GlobalWith - 2 * range;
            } else
            {
                region.start.x = pos.x - range;
                region.end.x = pos.x + range;
            }
            if (pos.y - range < 0)
            {
                region.start.y = 0;
                region.end.y = 2 * range;
            } else if (pos.y + range >= config.GlobalHeight)
            {
                region.end.y = config.GlobalHeight;
                region.start.y = config.GlobalHeight - 2 * range;
            } else
            {
                region.start.y = pos.y - range;
                region.end.y = pos.y + range;
            }
            region.start.x = region.start.x >= 0 ? region.start.x : 0;
            region.end.x = region.end.x < config.GlobalWith ? region.end.x : config.GlobalWith;
            region.start.y = region.start.y >= 0 ? region.start.y : 0;
            region.end.y = region.end.y < config.GlobalHeight ? region.end.y : config.GlobalHeight;
            return region;
        }

        TowerPos TranslatePos(const Point &pos) const
        {
            return Point((size_t) pos.x / (config.HalfTowerWith * 2), (size_t) pos.y / (config.HalfTowerHeight * 2));
        }
    };
}

#endif //CPP_STUDY_ALL_TOWER_AOI_H
