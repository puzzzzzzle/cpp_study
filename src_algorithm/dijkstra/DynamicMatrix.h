/************************************************
 * @author khalidzhang
 * @email khalidzhang@tencent.com
 * @desc 部分未初始化的二维矩阵进行初始化的操作
 * @time 2020/8/3
 * @file DynamicMatrix.h
 * @version
 * version        author            desc
 * 1.0            khalidzhang       create
 ************************************************/

#pragma once
#include <cmath>

#include "Dijkstra.h"

namespace Dijkstra {
using Point2d = CPosition;
/**
 * 图的顶点
 */
class DynamicVertex {
  public:
  VertexTypeEnum m_type{};
  std::string m_name{};
  Point2d m_pos{};
  int m_index{};
  DynamicVertex() = default;
  DynamicVertex(VertexTypeEnum type, const std::string & name)
      : m_type(type), m_name(name) {}

  public:
  std::string ToString() const {
    std::ostringstream oss{};
    oss << "{type:" << m_type;
    oss << ";name:" << m_name;
    oss << ";index:" << m_index;
    oss << ";x:" << m_pos.x;
    oss << ";y:" << m_pos.y << "}";
    return oss.str();
  }
};
inline std::ostream& operator<<(std::ostream& oss, const DynamicVertex& value) {
  return oss << value.ToString();
}
using DynamicDijkstra = MatrixUDG<DynamicVertex>;

/**
 * 动态二维矩阵计算类
 */
class DynamicMatrixHelper {
  public:
  static double GetLineLen(const Point2d& lhs, const Point2d& rhs) {
    return std::sqrt(std::pow(rhs.x - lhs.x, 2) + std::pow(rhs.y - lhs.y, 2));
  }
  static int CheckMatrix(const DynamicDijkstra::VertexType& inVertex,
                         const DynamicDijkstra::MatrixType& inMatrix,
                         bool isFinishInit) {
    for (int i = 0; i < inVertex.m_len; ++i) {
      CALL_IF_TRUE_RETURN(inVertex.Get(i).m_type ==
                          VertexTypeEnum::VERTEX_TYPE_UNKNOWN)
    }
    // 检查行列式格式正确
    CALL_IF_TRUE_RETURN(inMatrix.m_col != inMatrix.m_raw)
    CALL_IF_TRUE_RETURN(inMatrix.m_col != inVertex.m_len)
    for (int row = 0; row < inVertex.m_len; ++row) {
      for (int col = 0; col < inVertex.m_len; ++col) {
        // 检查无向图对称性
        CALL_IF_TRUE_RETURN(inMatrix.Get(row, col) != inMatrix.Get(col, row))
        if (row == col) {
          if (inMatrix.Get(row, col) != 0) {
            LOG_ERROR("error" << row << "\t" << col << "\t"
                              << inMatrix.Get(row, col))
          }
          CALL_IF_TRUE_RETURN(inMatrix.Get(row, col) != 0)
          continue;
        }
        // 区域与区域间不应该有连接
        if (inVertex.Get(row).m_type == VertexTypeEnum::VERTEX_TYPE_AREA &&
            inVertex.Get(col).m_type == VertexTypeEnum::VERTEX_TYPE_AREA) {
          CALL_IF_TRUE_RETURN(inMatrix.Get(row, col) != INT_INF)
        }
        // 关隘与关隘间不存在未定义
        if (inVertex.Get(row).m_type == VertexTypeEnum::VERTEX_TYPE_COL &&
            inVertex.Get(col).m_type == VertexTypeEnum::VERTEX_TYPE_COL) {
          CALL_IF_TRUE_RETURN(inMatrix.Get(row, col) == LEN_UNDEFINED)
        }

        // 检查区域与关隘的联通性
        if (!isFinishInit) {
          // 未初始化时区域与关隘间的连接只能是未定义或者断开
          if (inVertex.Get(row).m_type == VertexTypeEnum::VERTEX_TYPE_AREA ||
              inVertex.Get(col).m_type == VertexTypeEnum::VERTEX_TYPE_AREA) {
            CALL_IF_TRUE_RETURN(!(inMatrix.Get(row, col) == INT_INF ||
                                  inMatrix.Get(row, col) == LEN_UNDEFINED))
          }
        } else {
          // 初始化后, 不应该存在未定义
          CALL_IF_TRUE_RETURN(inMatrix.Get(row, col) == LEN_UNDEFINED)
        }
      }
    }

    return 0;
  }
  static int DynamicCalc(const DynamicDijkstra::VertexType& inVertex,
                         const DynamicDijkstra::MatrixType& inMatrix, int from,
                         const Point2d& fromPos, int target,
                         const Point2d& targetPos,
                         const std::vector<int>& openGate,
                         DynamicDijkstra::MatrixType* outMatrix) {
    assert(outMatrix != nullptr);
    CALL_IF_TRUE_RETURN(CheckMatrix(inVertex, inMatrix, false))
    // step1 copy
    (*outMatrix) = inMatrix;
    // 断开某个节点的连接
    auto disconnect = [&](int index) {
      LOG_DEBUG("disconnect " << index)
      for (int i = 0; i < inVertex.m_len; ++i) {
        // 将列置为INF
        outMatrix->Set(i, index, INT_INF);
        // 将行置为INF
        outMatrix->Set(index, i, INT_INF);
      }
      // row == col 处 置为0
      outMatrix->Set(index, index, 0);
    };
    // 初始化区域节点的长度
    auto initUndefinedLen = [&](int index) {
      if (inVertex.Get(index).m_type != VertexTypeEnum::VERTEX_TYPE_AREA) {
        LOG_DEBUG("endpoint is not area, so do not need init len")
        return;
      }
      for (int i = 0; i < inVertex.m_len; ++i) {
        if (outMatrix->Get(i, index) == LEN_UNDEFINED) {
          // 对称性
          assert(outMatrix->Get(index, i) == LEN_UNDEFINED);
          // TODO 暂时使用int近似的表示距离了
          int len = 0;
          if (from == index) {
            len = (int)GetLineLen(fromPos, inVertex.Get(i).m_pos);
          } else if (target == index) {
            len = (int)GetLineLen(targetPos, inVertex.Get(i).m_pos);
          } else {
            assert(false);
          }
          // 初始化列
          outMatrix->Set(i, index, len);
          // 初始化行
          outMatrix->Set(index, i, len);
        }
      }
      // row == col 处 置为0
      assert(outMatrix->Get(index, index) == 0);
      outMatrix->Set(index, index, 0);
    };
    LOG_DEBUG("init \n" << outMatrix->ToString())
    for (int i = 0; i < inVertex.m_len; ++i) {
      // step2 断开玩家未占领关隘的连接
      if (inVertex.Get(i).m_type == VertexTypeEnum::VERTEX_TYPE_COL) {
        if (std::find(openGate.begin(), openGate.end(), i) == openGate.end()) {
          // 当前节点不在openGate中, 断开它的连接
          LOG_DEBUG("disconnect by gate" << i)
          disconnect(i);
          continue;
        }
      }
      // step3 断开无关的区域的连接
      else {
        // 断开无关的区域的连接
        if (i == from || i == target) {
          continue;
        } else {
          LOG_DEBUG("disconnect by unused area" << i)
          disconnect(i);
        }
      }
    }
    LOG_DEBUG("after disconnect \n" << outMatrix->ToString())
    // 初始化相关区域的连接
    initUndefinedLen(from);
    LOG_DEBUG("after init from conn \n" << outMatrix->ToString())
    initUndefinedLen(target);
    LOG_DEBUG("after target from conn \n" << outMatrix->ToString())
    CALL_IF_TRUE_RETURN(CheckMatrix(inVertex, *outMatrix, true))
    return 0;
  }
};
}  // namespace Dijkstra