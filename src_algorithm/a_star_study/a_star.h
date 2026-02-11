/************************************************
 * @author puzzzzzzle
 * @email 2359173906@qq.com
 * @desc A* pathfinding algorithm — self-contained implementation with
 *       support for 4-way and 8-way connectivity and pluggable heuristics.
 * @time 2026/2/11
 * @file a_star.h
 * @version
 * version        author            desc
 * 1.0            puzzzzzzle       create
 ************************************************/

#pragma once
#include <algorithm>
#include <cmath>
#include <functional>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace AStarStudy {

struct Point {
  int x = 0;
  int y = 0;
  Point() = default;
  Point(int _x, int _y) : x(_x), y(_y) {}
  friend bool operator==(const Point& lhs, const Point& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
  }
  friend bool operator!=(const Point& lhs, const Point& rhs) {
    return !(lhs == rhs);
  }
};

struct PointHash {
  std::size_t operator()(const Point& p) const {
    // 使用大质数混合，减少碰撞
    return std::hash<int>()(p.x) * 100003 + std::hash<int>()(p.y);
  }
};

/// 2D 网格地图，0 = 可通行，非0 = 障碍
class GridMap {
 public:
  GridMap(int width, int height)
      : m_width(width), m_height(height), m_data(width * height, 0) {}

  int width() const { return m_width; }
  int height() const { return m_height; }

  bool validPos(int x, int y) const {
    return x >= 0 && y >= 0 && x < m_width && y < m_height;
  }

  bool walkable(int x, int y) const {
    return validPos(x, y) && m_data[y * m_width + x] == 0;
  }

  void setBlocked(int x, int y) {
    if (validPos(x, y)) {
      m_data[y * m_width + x] = 1;
    }
  }

  void setWalkable(int x, int y) {
    if (validPos(x, y)) {
      m_data[y * m_width + x] = 0;
    }
  }

 private:
  int m_width{};
  int m_height{};
  std::vector<int> m_data;
};

/// 启发函数类型
using HeuristicFunc = std::function<double(const Point&, const Point&)>;

/// 曼哈顿距离
inline double heuristicManhattan(const Point& a, const Point& b) {
  return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

/// 欧几里得距离
inline double heuristicEuclidean(const Point& a, const Point& b) {
  return std::hypot(a.x - b.x, a.y - b.y);
}

/// 切比雪夫距离 (适合8方向)
inline double heuristicChebyshev(const Point& a, const Point& b) {
  return std::max(std::abs(a.x - b.x), std::abs(a.y - b.y));
}

enum class Connectivity { Four, Eight };

/// A* 搜索结果
struct SearchResult {
  int ret = -1;  // 0=成功, 1=起终点无效, 2=无路径
  std::vector<Point> path;
  int nodesExpanded = 0;
};

/// A* 寻路器
class AStar {
 public:
  AStar(const GridMap* map, Connectivity conn = Connectivity::Four,
        HeuristicFunc h = heuristicManhattan)
      : m_map(map), m_conn(conn), m_heuristic(std::move(h)) {}

  SearchResult search(const Point& start, const Point& end) {
    SearchResult result;

    // 起终点相同
    if (start == end) {
      result.ret = 0;
      result.path.push_back(start);
      return result;
    }

    // 校验起终点
    if (!m_map->walkable(start.x, start.y) ||
        !m_map->walkable(end.x, end.y)) {
      result.ret = 1;
      return result;
    }

    // open list: (f值, 点)
    using OpenItem = std::pair<double, Point>;
    auto cmp = [](const OpenItem& a, const OpenItem& b) {
      return a.first > b.first;
    };
    std::priority_queue<OpenItem, std::vector<OpenItem>, decltype(cmp)> open(
        cmp);

    std::unordered_map<Point, double, PointHash> gScore;
    std::unordered_map<Point, Point, PointHash> parent;
    std::unordered_set<Point, PointHash> closed;

    gScore[start] = 0;
    parent[start] = start;
    open.push({m_heuristic(start, end), start});

    while (!open.empty()) {
      auto [currF, curr] = open.top();
      open.pop();

      if (closed.count(curr)) {
        continue;
      }
      closed.insert(curr);
      ++result.nodesExpanded;

      if (curr == end) {
        // 回溯路径
        result.ret = 0;
        result.path = reconstructPath(parent, start, end);
        return result;
      }

      for (auto& nb : getNeighbors(curr)) {
        if (closed.count(nb)) {
          continue;
        }
        double tentativeG = gScore[curr] + moveCost(curr, nb);
        auto it = gScore.find(nb);
        if (it == gScore.end() || tentativeG < it->second) {
          gScore[nb] = tentativeG;
          parent[nb] = curr;
          double f = tentativeG + m_heuristic(nb, end);
          open.push({f, nb});
        }
      }
    }

    result.ret = 2;
    return result;
  }

 private:
  const GridMap* m_map;
  Connectivity m_conn;
  HeuristicFunc m_heuristic;

  inline double moveCost(const Point& from, const Point& to) const {
    int dx = std::abs(from.x - to.x);
    int dy = std::abs(from.y - to.y);
    if (dx + dy == 2) {
      return 1.41421356237;  // sqrt(2)
    }
    return 1.0;
  }

  std::vector<Point> getNeighbors(const Point& pos) const {
    std::vector<Point> result;
    // 四方向
    static const int dx4[] = {0, 1, 0, -1};
    static const int dy4[] = {1, 0, -1, 0};
    for (int i = 0; i < 4; ++i) {
      int nx = pos.x + dx4[i];
      int ny = pos.y + dy4[i];
      if (m_map->walkable(nx, ny)) {
        result.emplace_back(nx, ny);
      }
    }
    if (m_conn == Connectivity::Eight) {
      // 对角方向，需要检查相邻直线方向是否可通行（防止穿墙）
      static const int dx8[] = {1, 1, -1, -1};
      static const int dy8[] = {1, -1, -1, 1};
      for (int i = 0; i < 4; ++i) {
        int nx = pos.x + dx8[i];
        int ny = pos.y + dy8[i];
        if (m_map->walkable(nx, ny) && m_map->walkable(pos.x + dx8[i], pos.y) &&
            m_map->walkable(pos.x, pos.y + dy8[i])) {
          result.emplace_back(nx, ny);
        }
      }
    }
    return result;
  }

  static std::vector<Point> reconstructPath(
      const std::unordered_map<Point, Point, PointHash>& parent,
      const Point& start, const Point& end) {
    std::vector<Point> path;
    Point curr = end;
    while (!(curr == start)) {
      path.push_back(curr);
      curr = parent.at(curr);
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());
    return path;
  }
};

}  // namespace AStarStudy
