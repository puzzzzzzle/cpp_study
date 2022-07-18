/************************************************
 * @author khalidzhang
 * @email khalidzhang@tencent.com
 * @desc
 * @time 2021/3/2
 * @file union_find_connect.h
 * @version
 * version        author            desc
 * 1.0            khalidzhang       create
 ************************************************/

#pragma once
#include <map>
#include <vector>
namespace UnionFindConnectCluster {
template <class PathDataWrapperT, class PointT, class UnionFindT>
class UnionFindConnectCluster {
  public:
  using PathData = PathDataWrapperT;
  using Point = PointT;
  using CPoint = const Point;
  using UnionFind = UnionFindT;
  using RegionResult = std::map<int, std::vector<Point>>;

  private:
  PathData* m_data{};
  Point m_start{}, m_end{};
  UnionFind m_unionFind{};

  public:
  UnionFindConnectCluster(PathData* data, CPoint& start, CPoint& end) {
    init(data, start, end);
  }
  UnionFindConnectCluster() = default;
  void init(PathData* data, CPoint& start, CPoint& end) {
    assert(end.x > start.x && end.y > start.y);
    assert(data->valid_pos(start.x, start.y));
    assert(end.x <= data->m_xLen && end.y <= data->m_yLen);
    m_start = start;
    m_end = end;
    m_data = data;
    m_unionFind.init((m_end.x - m_start.x) * (m_end.y - m_start.y));
  }
  UnionFind& get_uf() { return m_unionFind; }
  inline bool in_check_region(int x, int y) {
    return (x >= m_start.x && y >= m_start.y && x < m_end.x && y < m_end.y) &&
           m_data->valid_pos(x, y);
  }
  bool check(int x, int y) {
    if (!in_check_region(x, y)) {
      return false;
    }
    return m_data->check(x, y);
  }

  inline int pos_2_id(int x, int y) {
    assert(in_check_region(x, y));
    return (x - m_start.x) + (y - m_start.y) * (m_end.x - m_start.x);
  }
  Point id_2_pos(int id) {
    Point pos{};
    int x_gap = m_end.x - m_start.x;
    pos.y = id / x_gap + m_start.y;
    pos.x = id % x_gap + m_start.x;
    assert(in_check_region(pos.x, pos.y));
    return pos;
  }

  void scan_region() {
    // 遍历扫描, 每个点负责检查自己右边和上边的点是不是和自己联通
    auto try_union = [this](int x1, int y1, int x2, int y2) {
      if (check(x1, y1) && check(x2, y2)) {
        m_unionFind.union_elements(pos_2_id(x1, y1), pos_2_id(x2, y2));
      }
    };
    for (int x = m_start.x; x < m_end.x - 1; ++x) {
      for (int y = m_start.y; y < m_end.y - 1; ++y) {
        if (!check(x, y)) {
          continue;
        }
        // 右边
        try_union(x, y, x + 1, y);
        // 上边
        try_union(x, y, x, y + 1);
      }
    }
    // 剩了一个点, 额外处理下
    if (check(m_end.x - 1, m_end.y - 1)) {
      try_union(m_end.x - 1, m_end.y - 1, m_end.x - 2, m_end.y - 1);
      try_union(m_end.x - 1, m_end.y - 1, m_end.x - 1, m_end.y - 2);
    }
  }
  RegionResult get_valid_regions() {
    RegionResult results{};
    for (int i = 0; i < m_unionFind.m_count; ++i) {
      auto pos = id_2_pos(i);
      if (!check(pos.x, pos.y)) {
        continue;
      }
      results[m_unionFind.find(i)].push_back(pos);
    }
    return results;
  }
};
}  // namespace UnionFindConnectCluster
