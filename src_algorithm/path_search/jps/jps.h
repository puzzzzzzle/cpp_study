/************************************************
 * @author puzzzzzzle
 * @email 2359173906@qq.com
 * @desc
 * @time 2021/3/10
 * @file jps.h
 * @version
 * version        author            desc
 * 1.0            puzzzzzzle       create
 ************************************************/

#pragma once

namespace PathSearch {
template <class ItemType>
bool in_container(const ItemType& item,
                  const std::vector<ItemType>& container) {
  return std::find(container.cbegin(), container.cend(), item) !=
         container.cend();
}
template <class ItemType, class FindableContainerType>
bool in_container(const ItemType& item,
                  const FindableContainerType& container) {
  return container.find(item) != container.cend();
}
/*
 * 必须的接口
struct PathDataWrapper
{
    int m_xLen{}, m_yLen{};
    inline bool valid_pos(int x, int y) const
    bool check(int x, int y) const
};
struct PointT
{
    int x = 0;
    int y = 0;
    PointT() = default;
    PointT(int _x, int _y) : x(_x), y(_y) {}
    friend bool operator<(const CPosition& lhs, const CPosition& rhs)
    friend bool operator==(const CPosition& lhs, const CPosition& rhs)
};
 */
#include "path_find_common.h"
template <class PathDataWrapper, class PointT>
class JPS {
  private:
  using PathData = DataType;
  using Point = CPosition;
  using CPoint = const Point;
  Point m_start{}, m_end{};
  const PathData* const m_data{};

  public:
  JPS(CPoint& start, CPoint& end, const PathData* const data)
      : m_start(start), m_end(end), m_data(data) {}
  int searching() {
      return 0;
  }
  std::vector<Point> extract_path() {
    return {};
  }

  private:

};
}  // namespace PathSearch