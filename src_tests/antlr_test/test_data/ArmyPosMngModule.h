/************************************************
 * @author khalidzhang
 * @email khalidzhang@tencent.com
 * @desc
 * @time 2021/8/23
 * @file ArmyPosMngModule.h
 * @version
 * version        author            desc
 * 1.0            khalidzhang       create
 ************************************************/

#pragma once

#include "AOIObjectDefine.h"
#include "AOICommonInclude.h"
#include "ArmyPosMngModuleExport.h"
#include "GeographyModuleExport.h"
#include "MovableAdaptorFactoryModuleExport.h"
#include "DynArmyPosHelper.h"
#include "AOITypeUtils.h"
#include "GeographyModuleExport.h"
#include "MoveModuleExport.h"
#include "Algorithm/UseVisionLine.h"
#include "FightLimitHandle.h"
namespace BigWorld
{
class ArmyPosMngModule : public ModuleInterface, public ArmyPosMngModuleExport
{
private:
    GeographyModuleExport* m_geography{};
    MovableAdaptorFactoryModuleExport* m_adaptorFactory{};
//    MoveModuleExport* m_moveModule{};
    ArmyFightLimitHandle m_fightLimit{};

    AUTO_WIRED(MoveModule, m_moveModule)
    int m_fightLeaveLenGap{2};
    // 卡主脱离最大正方形边长的一半
    int m_escapeMaxSize{50};

public:
    int Init() override
    {
        CALL_IF_TRUE_RETURN(m_fightLimit.Init(GetMng()))
        return 0;
    }
    int InitModuleDependency() override
    {
        GET_MODULE_BY_NAME(GetMng(), geographyModule, GeographyModule, 0)
        m_geography = geographyModule;
        GET_MODULE_BY_NAME(GetMng(), adaptorFactory, MovableAdaptorFactoryModule, 0);
        m_adaptorFactory = adaptorFactory;

        GET_MODULE_BY_NAME(GetMng(), moveModule, MoveModule, 0);
        m_moveModule = moveModule;
        return 0;
    }
    ModuleExportInterface* GetExportPtr() override
    {
        return this;
    }

public:
    int GetObjMoveRadius(PBTowerAOI* tower, const ConstPBObjectSPtr& obj) override
    {
        return m_geography->GetObjMoveRadius(tower, obj);
    }
    /**
     * CalcFightLen
     * 计算进入战斗/脱战的距离
     * @param type
     * @return
     */
    int GetFightLen(PBTowerAOI* tower, WritableObjHandle& mover, WritableObjHandle& target, FightLenType type) override
    {
        return GetFightLen(tower, mover.Get(), target.Get(), type);
    };
    int GetFightLen(PBTowerAOI* tower,
        const ConstPBObjectSPtr& mover,
        const ConstPBObjectSPtr& target,
        FightLenType type) override
    {
        auto len = GetObjMoveRadius(tower, mover) + GetObjMoveRadius(tower, target);
        switch (type)
        {
            case FightLenType::FIGHT_LEN_START:
            {
                len += 1;
            }
            case FightLenType::FIGHT_LEN_MOVE_STOP:
            {
                break;
            }
            case FightLenType::FIGHT_LEN_LEAVE:
            {
                len += m_fightLeaveLenGap;
                break;
            }
            default:
            {
                break;
            }
        }
        return len;
    }
    int GetPathFindOffsetLen(PBTowerAOI* tower,
        WritableObjHandle& mover,
        WritableObjHandle& target,
        FightLenType type = FightLenType::FIGHT_LEN_MOVE_STOP) override
    {
        return GetPathFindOffsetLen(tower, mover.Get(), target.Get(), type);
    }
    int GetPathFindOffsetLen(PBTowerAOI* tower,
        const ConstPBObjectSPtr& mover,
        const ConstPBObjectSPtr& target,
        FightLenType type = FightLenType::FIGHT_LEN_MOVE_STOP) override
    {
        // 空地类的不需要偏移
        if (target->aoi_type() == AOIObjectType::AOI_TYPE_SPACE ||
            target->aoi_type() == AOIObjectType::AOI_TYPE_DEFAULT ||
            target->aoi_type() == AOIObjectType::AOI_TYPE_FOG ||
            target->aoi_type() == AOIObjectType::AOI_TYPE_RURBAN_FOG)
        {
            return 0;
        }
        return GetFightLen(tower, mover, target, type);
    }
    void GetJumpOutPos(PBTowerAOI* tower,
        WritableObjHandle& mover,
        WritableObjHandle& buildPos,
        const AOIPoint targetPos,
        AOIPoint* outPos) override
    {
        GetJumpOutPos(tower, mover.Get(), buildPos.Get(), targetPos, outPos);
    }
    void GetJumpOutPos(PBTowerAOI* tower,
        const ConstPBObjectSPtr& mover,
        const ConstPBObjectSPtr& buildPos,
        const AOIPoint targetPos,
        AOIPoint* outPos) override
    {
        // 位置相同
        if (ComparePos(buildPos->pos(), targetPos) == 0)
        {
            outPos->CopyFrom(buildPos->pos());
        }
        else
        {
            int distance = GetPathFindOffsetLen(tower, mover, buildPos);

            if (distance > 0)
            {
                GetPointOnRay(buildPos->pos(), targetPos, distance, outPos, true);
                if (!m_geography->CheckPos(outPos->x(), outPos->y()))
                {
                    HTLOG_ERROR("!m_geography->CheckPos(outPos->x(),outPos->y())")
                    outPos->CopyFrom(buildPos->pos());
                    return;
                }

                if (!m_geography->CheckPosWalkable(tower, *outPos))
                {
                    HTLOG_WARN("jump out pos is blocked, so use building size")
                    // 跳出点被阻挡了, 使用建筑的领地半径
                    distance = m_geography->GetEffectRadius(buildPos, GeographyLayer::GEOGRAPHY_LAYER_BUILD) - 1;
                    GetPointOnRay(buildPos->pos(), targetPos, distance, outPos, true);
                }
            }
            else
            {
                outPos->CopyFrom(buildPos->pos());
            }
        }
    }

    void SetObjectTowardsAngle(const HGame::AOIPoint& startPos,
        const HGame::AOIPoint& endPos,
        BigWorld::MoveData* mutableMoveData) override
    {
        if ((endPos.x() < 0 && endPos.y() < 0) || (startPos.x() == endPos.x() && startPos.y() == endPos.y()) ||
            !mutableMoveData)
            return;
        float angle = BigWorld::GetTowardsAngle(startPos, endPos);
        // 有目标的设置朝向
        mutableMoveData->set_towards_angle(angle);
        return;
    }

    AOIPoint GetPathFindOffsetPos(PBTowerAOI* tower, WritableObjHandle& mover, WritableObjHandle& target) override
    {
        return GetPathFindOffsetPos(tower, mover.Get(), target.Get());
    }
    AOIPoint GetPathFindOffsetPos(PBTowerAOI* tower,
        const ConstPBObjectSPtr& mover,
        const ConstPBObjectSPtr& target) override
    {
        AOIPoint resultPos{};
        double gapLen = GetPathFindOffsetLen(tower, mover, target);
        double lineLen = GetLineLen(mover->pos(), target->pos());
        double len = std::min(lineLen, gapLen);
        if (len <= 0)
        {
            resultPos.CopyFrom(target->pos());
        }
        else
        {
            GetPointOnRay(target->pos(), mover->pos(), len, &resultPos, true);
        }
        return resultPos;
    }
    bool NeedArrangePos(AOIObjectType type)
    {
        switch (type)
        {
            case AOIObjectType::AOI_TYPE_PLAYER_ARMY:
            case AOIObjectType::AOI_TYPE_MONSTER:
            case AOIObjectType::AOI_TYPE_ARMY_GROUP:
                HTLOG_DEBUG("need move back for this aoiType " << type)
                return true;
            default:
                HTLOG_DEBUG("do not need move back for this aoiType " << type)
                return false;
        }
    }
    virtual int NotifyArmyFormationRadiusChange(PBTowerAOI* towerPtr, WritableObjHandle& mover) override
    {
        NotifyTargetArrangeFollowersPos(towerPtr, mover);
        // 需要重寻路的部队进行重寻路
        auto* adaptor = m_adaptorFactory->GetAdaptor(mover->aoi_type());
        for (const auto& followerID : adaptor->follower_objs(mover))
        {
            if (followerID.is_fighting())
            {
                continue;
            }
            if (followerID.is_binding())
            {
                continue;
            }
            HTLOG_DEBUG("notify restart move by NotifyArmyFormationRadiusChange " << followerID)
            m_moveModule->MoveTo(followerID.follower_id(), BigWorldUtils::MakeIdent(mover.Get()));
        }
        return 0;
    }
    int NotifyTargetArrangeFollowersPos(PBTowerAOI* towerPtr, WritableObjHandle& mover) override
    {
        return NotifyTargetArrangeFollowersPos(towerPtr, mover, m_fightLimit.GetLimitNum(mover.Get()));
    }
    int NotifyTargetArrangeFollowersPos(PBTowerAOI* towerPtr, WritableObjHandle& mover, int maxNum) override
    {
        auto moverAdaptor = m_adaptorFactory->GetAdaptor(mover->aoi_type());
        WritableObjHandle processer(moverAdaptor->pursue_target_id(mover), towerPtr);
        CALL_IF_TRUE_RETURN(!processer.IsFind())
        return ArrangeFollowersPos(towerPtr, processer, maxNum, mover);
    }
    bool IsBindMoveType(AOIObjectType type) override
    {
        switch (type)
        {
            case AOIObjectType::AOI_TYPE_PLAYER_ARMY:
            case AOIObjectType::AOI_TYPE_ARMY_GROUP:
            case AOIObjectType::AOI_TYPE_MONSTER:
            {
                return true;
            }
            default:
            {
                return false;
            }
        }
    }
    bool CanStartBindMove(PBTowerAOI* tower, WritableObjHandle& mover, WritableObjHandle& target) override
    {
        HTLOG_DEBUG("start check " << mover.Get() << "\t" << target.Get())
        // 类型过滤
        if (!IsBindMoveType(mover->aoi_type()) || !IsBindMoveType(target->aoi_type()))
        {
            return false;
        }
        auto moverAdaptor = m_adaptorFactory->GetAdaptor(mover->aoi_type());
        auto paraInfo = moverAdaptor->parasitic_data(mover);
        if (paraInfo.identification().aoi_type() != AOIObjectType::AOI_TYPE_DEFAULT)
        {
            return false;
        }
        // 已经处于绑定中
        if (moverAdaptor->is_move_fight_flag_enable(mover, MoveData::MOVE_FIGHT_FLAG_BINDING_MOVE))
        {
            return false;
        }
        // 距离判断
        // 够开战就行了
        double gapLen = GetPathFindOffsetLen(tower, mover, target, FightLenType::FIGHT_LEN_START);
        double lineLen = GetLineLen(mover->pos(), target->pos());
        if (lineLen > gapLen)
        {
            return false;
        }
        HTLOG_DEBUG("pass CanStartBindMove")
        return true;
    }
    void StartBindMove(PBTowerAOI* towerPtr,
        WritableObjHandle& mover,
        WritableObjHandle& target,
        MoveDataFollowObjInfo* record) override
    {
        auto targetAdaptor = m_adaptorFactory->GetAdaptor(target->aoi_type());
        auto moverAdaptor = m_adaptorFactory->GetAdaptor(mover->aoi_type());
        MoveDataFollowObjInfo* realRecord = record;
        if (realRecord == nullptr)
        {
            for (auto& followerInfo : *targetAdaptor->mutable_follower_objs(target))
            {
                if (followerInfo.follower_id().id() == mover->id() &&
                    followerInfo.follower_id().aoi_type() == mover->aoi_type())
                {
                    realRecord = &followerInfo;
                }
            }
        }
        CALL_IF_TRUE_RETURN_VOID(realRecord == nullptr)
        if (moverAdaptor->is_move_fight_flag_enable(mover, MoveData::MOVE_FIGHT_FLAG_BINDING_MOVE))
        {
            HTLOG_ERROR("already in binding " << mover.Get() << "\t" << target.Get())
        }
        // 设置状态
        moverAdaptor->enable_move_fight_flag(mover, MoveData::MOVE_FIGHT_FLAG_BINDING_MOVE, true);
        realRecord->set_is_binding(true);
        // 调整follower位置
        // 这里不用调用, onarrive后会通知target来调整
    }
    void EndBindMove(PBTowerAOI* towerPtr,
        WritableObjHandle& mover,
        WritableObjHandle& target,
        MoveDataFollowObjInfo* record) override
    {
        auto targetAdaptor = m_adaptorFactory->GetAdaptor(target->aoi_type());
        auto moverAdaptor = m_adaptorFactory->GetAdaptor(mover->aoi_type());
        MoveDataFollowObjInfo* realRecord = record;
        if (realRecord == nullptr)
        {
            for (auto& followerInfo : *targetAdaptor->mutable_follower_objs(target))
            {
                if (followerInfo.follower_id().id() == mover->id() &&
                    followerInfo.follower_id().aoi_type() == mover->aoi_type())
                {
                    realRecord = &followerInfo;
                }
            }
        }
        CALL_IF_TRUE_RETURN_VOID(realRecord == nullptr)
        // 设置状态
        moverAdaptor->enable_move_fight_flag(mover, MoveData::MOVE_FIGHT_FLAG_BINDING_MOVE, false);
        realRecord->set_is_binding(false);
    }
    void OnBindTargetMove(PBTowerAOI* towerPtr, WritableObjHandle& follower, WritableObjHandle& target) override
    {
        HTLOG_DEBUG("bind move " << follower.Get() << "\t" << target.Get())
        auto followerAdaptor = m_adaptorFactory->GetAdaptor(follower->aoi_type());
        double angle = followerAdaptor->move_data(follower).binding_angle();
        auto moveLen = GetPathFindOffsetLen(towerPtr, follower, target);
        // 尝试获取可用的点
        AOIPoint finallyPos{};
        finallyPos.set_x(target->pos().x() + moveLen * std::cos(angle * M_PI / 360));
        finallyPos.set_y(target->pos().y() + moveLen * std::sin(angle * M_PI / 360));
        HTLOG_DEBUG("target pos is " << finallyPos)
        if (m_geography->CheckPosWalkable(towerPtr, finallyPos))
        {
            auto moverAdaptor = m_adaptorFactory->GetAdaptor(follower->aoi_type());
            // 直接移动部队到目标点
            m_moveModule->MoveArmyObjWithRealPos(towerPtr, follower, finallyPos);
            // 原地调用一次移动, 用于战斗控制
            moverAdaptor->OnMoveTimer(towerPtr, follower, GetMng()->GetCorePtr()->GetTimeWheelPtr()->GetTimePoint(),
                0,  // 移动时间为0
                0,  // 没有pathindex
                0,  // 没有pathindex
                follower->pos(),  // 位置不变
                follower->pos()  // 位置不变
            );
            // 通知follower重寻路
            m_moveModule->NotifyFollowerTargetMove(towerPtr, GetMng()->GetCorePtr()->GetTimeWheelPtr()->GetTimePoint(),
                0,  // 瞬间到达, 没有移动时间
                follower,
                true  // 直接到达, 没有移动时间
            );
        }
        else
        {
            HTLOG_DEBUG("target pos not pass CheckPosWalkable " << finallyPos)
            // 发起重寻路
            m_moveModule->MoveTo(BigWorldUtils::MakeIdent(follower.Get()), BigWorldUtils::MakeIdent(target.Get()), 0,
                MoveFinishIntent::MOVE_INTENT_NONE, true);
        }
    }
    /**
     * 卡住脱离
     * 以自身为中心向外画正方形, 找到第一个可用的点为止
     * @param towerPtr
     * @param moverHandle
     * @return
     */
    int EscapeFromBlock(PBTowerAOI* towerPtr,
        WritableObjHandle& moverHandle,
        bool needCheckBuilding,
        const AOIPoint* const targetPos = nullptr) override
    {
        HTLOG_ERROR("try escape from block for " << moverHandle.Get())
        auto moveArmy = [&](int x, int y) -> int {
            if (m_moveModule->MoveArmyObjWithRealPos(towerPtr, moverHandle, MakePoint(x, y)))
            {
                HTLOG_WARN("move army success, escape success " << moverHandle.Get())
                return 0;
            }
            else
            {
                HTLOG_ERROR("move army fail, ignore this pos " << moverHandle.Get());
                return -1;
            }
        };
        return GetEscapePos(towerPtr, m_escapeMaxSize, moverHandle->pos(), needCheckBuilding, moveArmy, targetPos);
    }
    int GetEscapePosByRec(PBTowerAOI* towerPtr,
        int range,
        const AOIPoint& center,
        bool needCheckBuilding,
        const std::function<int(int x, int y)>& onFind)
    {
        HTLOG_DEBUG("try escape from block for " << center)
        auto* staticBlock = m_geography->GetStaticLayer();
        auto buildingImg = m_geography->Get(towerPtr, GeographyLayer::GEOGRAPHY_LAYER_BUILD)->m_centerBin;
        auto checkRectangle = [&](int diff) -> int {
            for (int x = center.x() - diff; x <= center.x() + diff; ++x)
            {
                for (int y = center.y() - diff; y <= center.y() + diff; ++y)
                {
                    // 合法性检查
                    if (!m_geography->CheckPos(x, y))
                    {
                        continue;
                    }
                    // 静态阻挡检查
                    if (staticBlock->m_data[x][y] == 0)
                    {
                        continue;
                    }
                    // 动态阻挡检查
                    if (needCheckBuilding && buildingImg->m_data[x][y].m_blockInfo != 0)
                    {
                        continue;
                    }
                    // 得到了一个可用的点

                    HTLOG_DEBUG("get escape pos " << x << "\t" << y)
                    if (onFind(x, y) == 0)
                    {
                        HTLOG_DEBUG("process success, so return " << x << "\t" << y)
                        return 0;
                    }
                    else
                    {
                        HTLOG_DEBUG("process fail, so ignore this pos " << x << "\t" << y)
                        return -1;
                    }
                }
            }
            HTLOG_DEBUG("cannot find suitable pos in diff " << diff)
            return 1;
        };
        for (int diff = 0; diff <= range; ++diff)
        {
            if (checkRectangle(diff) == 0)
            {
                HTLOG_DEBUG("got finally pos success")
                return 0;
            }
        }
        HTLOG_ERROR("try escape from block fail, reason : cannot find one suitable pos " << center)
        return -1;
    }
    int GetEscapePosByRay(PBTowerAOI* towerPtr,
        int range,
        const AOIPoint& center,
        bool needCheckBuilding,
        const std::function<int(int x, int y)>& onFind,
        const AOIPoint& targetPos)
    {
        auto* staticBlock = m_geography->GetStaticLayer();
        auto buildingImg = m_geography->Get(towerPtr, GeographyLayer::GEOGRAPHY_LAYER_PATH_BLOCK)->m_centerBin;
        int ret{-1};
        // center 向target做一条射线, 栅格化射线上的点, 得到第一个不卡主的点
        UseVisionLine(center.x(), center.y(), targetPos.x(), targetPos.y(), [&](int y, int x) {
            // 合法性检查
            if (!m_geography->CheckPos(x, y))
            {
                return 0;
            }
            // 静态阻挡检查
            if (staticBlock->m_data[x][y] == 0)
            {
                return 0;
            }
            // 动态阻挡检查
            if (needCheckBuilding && buildingImg->m_data[x][y].m_blockInfo != 0)
            {
                return 0;
            }
            // 距离检查
            if (GetLineLen(MakePoint(x, y), center) > range)
            {
                // 超过距离了, 结束
                // 处理成功, 终止栅格化
                HTLOG_DEBUG("over max check size, so break " << x << "\t" << y)
                return 1;
            }
            // 得到了一个可用的点

            HTLOG_DEBUG("get escape pos " << x << "\t" << y)
            if (onFind(x, y) == 0)
            {
                // 处理成功, 终止栅格化
                HTLOG_DEBUG("process success, so return " << x << "\t" << y)
                ret = 0;
                return 1;
            }
            else
            {
                // 处理失败, 接着栅格化
                HTLOG_DEBUG("process fail, so ignore this pos " << x << "\t" << y)
                return 0;
            }
        });
        if (ret)
        {
            HTLOG_DEBUG("escape by ray fail, fall back to rec")
            ret = GetEscapePosByRec(towerPtr, range, center, needCheckBuilding, onFind);
        }
        return ret;
    }
    /**
     * 寻找一个合法点, 找到后就调用 onFind
     * @param towerPtr
     * @param range 卡主脱离最大正方形边长的一半
     * @param center 中心点
     * @param needCheckBuilding
     * @param onFind 返回0 就代表可用了, 直接结束查找, 否则, 则认为找到了可用的点, 但是业务侧不接受, 继续查找
     * @return
     */
    int GetEscapePos(PBTowerAOI* towerPtr,
        int range,
        const AOIPoint& center,
        bool needCheckBuilding,
        const std::function<int(int x, int y)>& onFind,
        const AOIPoint* const targetPos = nullptr) override
    {
        if (targetPos == nullptr)
        {
            return GetEscapePosByRec(towerPtr, range, center, needCheckBuilding, onFind);
        }
        else
        {
            return GetEscapePosByRay(towerPtr, range, center, needCheckBuilding, onFind, *targetPos);
        }
    }
    bool CanObjMove(PBTowerAOI* towerPtr, WritableObjHandle& follower)
    {
        bool canMove = true;
        auto followerAdaptor = m_adaptorFactory->GetAdaptor(follower->aoi_type());
        // 驻守且的军队不可动
        const auto& parasitic = followerAdaptor->parasitic_data(follower);
        if (parasitic.identification().aoi_type() != AOIObjectType::AOI_TYPE_DEFAULT)
        {
            HTLOG_DEBUG("army in parasitic. not need move " << follower.Get())
            canMove = false;
        }
        else
        {
            HTLOG_DEBUG("normal army, can move " << follower.Get())
        }
        return canMove;
    }
    /**
      * 通知target为所有到达自己的follower旋转一个合适的位置
      * @param towerPtr
      * @param processer
      * @return
      */
    int ArrangeFollowersPos(PBTowerAOI* towerPtr,
        WritableObjHandle& processer,
        int maxNum,
        WritableObjHandle& arriveMover) override
    {
        CALL_IF_TRUE_RETURN_DYN(maxNum <= 0, -1)
        int theta = 360 / maxNum;
        auto processerAdaptor = m_adaptorFactory->GetAdaptor(processer->aoi_type());
        //        // 目标还在移动那么就不处理
        //        if (!processerAdaptor->router_path(processer).point_list().empty())
        //        {
        //            return 0;
        //        }
        bool isProcesserMove = !processerAdaptor->router_path(processer).point_list().empty();
        bool useFakeTarget = false;

        AOIIdentification processerTargetID{};
        if (processerAdaptor->has_pursue_target_id(processer))
        {
            processerTargetID.CopyFrom(processerAdaptor->pursue_target_id(processer));
        }
        // 为所有没有在移动且距离小于一定的阈值的单位安排合适的位置
        // 0 号位置: 本次到达的军队
        // 1 号位置: processer 的target, 不管是否存在
        DynArmyPosList processList{};
        auto addToProcessList = [&processList, theta](bool canMove, const std::shared_ptr<WritableObjHandle>& ptr) {
            if (ptr == nullptr || !ptr->IsFind())
            {
                HTLOG_ERROR("ptr == nullptr || !ptr->IsFind()")
                return;
            }
            DynArmyPosItem item{};
            item.m_id = BigWorldUtils::MakeIdent(ptr->Get());
            item.m_canMove = canMove;
            item.m_currCircleR = 5;  // 暂未生效
            item.m_theta = theta;

            CopyPos(&item.m_pos, ptr->Get()->pos());
            item.m_ptr = ptr;
            processList.push_back(item);
        };
        auto moveObject = [&](WritableObjHandle& ptr, const AOIRealPoint& targetPos, bool needFlag = true) {
            HTLOG_DEBUG("+++ will move object " << ptr.Get() << "\tto\t" << targetPos)
            CALL_IF_TRUE_RETURN_VOID(!CanObjMove(towerPtr, ptr))
            auto newPos = MakePoint(round(targetPos.x()), round(targetPos.y()));
            // 检查距离是否够, 不够的做下延长线
            auto needLen = GetPathFindOffsetLen(towerPtr, ptr, processer);
            auto currLen = GetLineLen(newPos, processer->pos());
            // 允许一定的偏差
            if (std::abs(needLen - currLen) >= 2)
            {
                AOIPoint tempPos{};
                // 做下延长线
                GetPointOnRay(processer->pos(), newPos, needLen, &tempPos, true);
                // 检查新的点是否可用
                if (m_geography->CheckPosWalkable(towerPtr, tempPos))
                {
                    HTLOG_DEBUG("change pos by ray " << newPos << tempPos)
                    newPos = tempPos;
                }
            }
            HTLOG_DEBUG("final pos is " << newPos)
            // 检查是否需要移动
            if (ComparePos(ptr->pos(), newPos) == 0)
            {
                HTLOG_DEBUG("not need move " << ptr.Get())
                return;
            }
            // 记录角度
            double moveAngle = DynArmyPos::GetAngle(processer->pos(), GetZeroPoint(), newPos);
            HTLOG_DEBUG("finally angle is " << moveAngle)

            // 记录flag
            if (needFlag)
            {
                auto followerAdaptor = m_adaptorFactory->GetAdaptor(ptr.Get()->aoi_type());
                followerAdaptor->enable_move_fight_flag(ptr, MoveData::MOVE_FIGHT_FLAG_DYNAMIC_MOVE);
            }

            m_moveModule->MoveArmyObjWithRealPos(towerPtr, ptr, newPos);
            auto moverAdaptor = m_adaptorFactory->GetAdaptor(ptr->aoi_type());
            // 设置角度信息
            moverAdaptor->mutable_move_data(ptr)->set_binding_angle(moveAngle);
            // 原地调用一次移动, 用于战斗控制
            moverAdaptor->OnMoveTimer(towerPtr, ptr, GetMng()->GetCorePtr()->GetTimeWheelPtr()->GetTimePoint(),
                0,  // 移动时间为0
                0,  // 没有pathindex
                0,  // 没有pathindex
                ptr->pos(),  // 位置不变
                ptr->pos()  // 位置不变
            );
            // 通知follower重寻路
            m_moveModule->NotifyFollowerTargetMove(towerPtr, GetMng()->GetCorePtr()->GetTimeWheelPtr()->GetTimePoint(),
                0,  // 瞬间到达, 没有移动时间
                ptr,
                true  // 直接到达, 没有移动时间
            );
        };

        // 插入当前到达的军队
        {
            auto arrivePtr = std::make_shared<WritableObjHandle>(
                arriveMover->aoi_type(), arriveMover->id(), arriveMover->pos(), towerPtr);
            CALL_IF_TRUE_RETURN(!arrivePtr->IsFind());
            addToProcessList(CanObjMove(towerPtr, *arrivePtr), arrivePtr);
        }

        // 插入当前processer的目标 , 强制不可移动
        if (IsBindMoveType(processerTargetID.aoi_type()))
        {
            auto targetPtr = std::make_shared<WritableObjHandle>(processerTargetID, towerPtr);
            CALL_IF_TRUE_RETURN(!targetPtr->IsFind())
            addToProcessList(false, targetPtr);
        }
        else
        {
            // 非转圈类的物体插入一个假目标
            WritableObjHandle targetPtr(processerTargetID, towerPtr);
            CALL_IF_TRUE_RETURN(!targetPtr.IsFind())
            // 取射线上一点
            AOIPoint tempPos{};
            GetPointOnRay(processer->pos(), targetPtr->pos(), m_geography->GetObjMoveRadius(towerPtr, processer.Get()),
                &tempPos, true);
            auto fakeTargetPtr =
                std::make_shared<WritableObjHandle>(AOIObjectType ::AOI_TYPE_SPACE, 0, tempPos, towerPtr);
            addToProcessList(false, fakeTargetPtr);
            useFakeTarget = true;
        }

        for (const auto& item : processerAdaptor->follower_objs(processer))
        {
            HTLOG_DEBUG("process " << item)
            if (!NeedArrangePos(item.follower_id().aoi_type()))
            {
                continue;
            }
            // 到达的军队已经加入了, 这里忽略
            if (item.follower_id().aoi_type() == arriveMover->aoi_type() &&
                item.follower_id().id() == arriveMover->id())
            {
                continue;
            }
            // 当前processer的target已经单独加了, 这里忽略
            if (item.follower_id().aoi_type() == processerTargetID.aoi_type() &&
                item.follower_id().id() == processerTargetID.id())
            {
                continue;
            }
            // 当前processer在移动则只处理绑定中的部队
            if (isProcesserMove && !item.is_binding())
            {
                HTLOG_DEBUG("curr process is move and this follower is not binding " << item)
                continue;
            }
            auto follower = std::make_shared<WritableObjHandle>(item.follower_id(), towerPtr);
            if (!follower->IsFind())
            {
                HTLOG_ERROR("cannot find follower " << item)
                continue;
            }
            auto followerId = BigWorldUtils::MakeIdent(follower->Get());
            // 判断移动, 未到达的不参与
            auto followerAdaptor = m_adaptorFactory->GetAdaptor(follower->Get()->aoi_type());
            if (!followerAdaptor->router_path(*follower).point_list().empty())
            {
                continue;
            }
            // 判断距离, 过远的说明还是有问题
            if (GetLineLen(processer->pos(), follower->Get()->pos()) >
                GetFightLen(towerPtr, *follower, processer, FightLenType::FIGHT_LEN_START) * 3)
            {
                continue;
            }
            // 加入到处理列表中
            addToProcessList(CanObjMove(towerPtr, *follower), follower);
        }
        auto processListSize = processList.size();
        if (useFakeTarget)
        {
            --processListSize;
        }
        if (processListSize <= 0)
        {
            HTLOG_DEBUG("do not need process")
        }
        else if (processListSize == 1 && processList[0].m_canMove)
        {
            double finallyLen = GetPathFindOffsetLen(towerPtr, *(processList[0].m_ptr), processer);
            // 调用对follower 位置校验的逻辑
            HTLOG_DEBUG("call move one follower" << processList.ToString() << "\tlen\t" << finallyLen)
            // follower 是后到的, 需要调整站位
            if (std::abs(GetLineLen(processList[0].m_pos, processList[0].m_ptr->Get()->pos()) - finallyLen) >= 1.0)
            {
                AOIRealPoint directionPos = processList[0].m_pos;
                if (ComePairAnyPos(processer->pos(), processList[0].m_pos) == 0)
                {
                    HTLOG_WARN("on the same point , so move to x direction " << processList[0].ToString())
                    directionPos.set_x(directionPos.x() + 1);
                }
                // 过近或者过远都需要调整下站位
                AOIRealPoint suitablePos{};
                GetPointOnRay(processer->pos(), directionPos, finallyLen, &suitablePos, true);
                HTLOG_DEBUG("get suitable pos " << suitablePos)
                auto suitableTempPos = MakePoint(round(suitablePos.x()), round(suitablePos.y()));
                // 检查 目标点是不是可用, 不可用就以目标点到processer点
                if (!m_geography->CheckPosWalkable(towerPtr, suitableTempPos))
                {
                    // 尝试从目标点向processer做一条射线, 找到第一个可行军点
                    UseVisionLine(suitableTempPos.x(), suitablePos.y(), processer->pos().x(), processer->pos().y(),
                        [&](int y, int x) -> int {
                            if (m_geography->CheckPosWalkable(towerPtr, MakePoint(x, y)))
                            {
                                // 找到可用的点了, 退出
                                suitablePos.set_x(x);
                                suitablePos.set_y(y);
                                return 1;
                            }
                            // 这个点不可用, 继续
                            return 0;
                        });
                }
                moveObject(*processList[0].m_ptr, suitablePos, false);
            }
        }
        else if (processListSize > 1)
        {
            HTLOG_DEBUG("will process " << processList.ToString())
            // 调用动态安排位置的逻辑
            // 先使用目标的交战距离计算
            auto len = GetObjMoveRadius(towerPtr, processer.Get()) + 1;
            CALL_IF_TRUE_RETURN(DynArmyPos::DynArmyPosCalculateSingleDirection(processList,
                MakeRealPoint(processer->pos().x(), processer->pos().y()), len, m_geography->GetStaticLayer(),
                *m_geography->Get(towerPtr, GeographyLayer::GEOGRAPHY_LAYER_PATH_BLOCK)));
            HTLOG_DEBUG("after process " << processList.ToString())
            // 对处理结果进行移动
            // 移动的时候会根据半径重算一次距离
            for (const auto& item : processList)
            {
                if (ComePairAnyPos(item.m_pos, item.m_ptr->Get()->pos()) != 0 && item.m_canMove)
                {
                    moveObject(*item.m_ptr, item.m_pos);
                }
                else
                {
                    HTLOG_DEBUG("follower don't need move " << item.m_ptr->Get() << "\t" << item.m_pos)
                }
            }
        }
        return 0;
    }
};
}  // namespace BigWorld