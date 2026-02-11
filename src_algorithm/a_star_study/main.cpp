#include "common_includes.h"

#include "a_star.h"

using namespace AStarStudy;

// ============================================================
// 辅助函数：打印地图和路径
// ============================================================
static std::string mapToString(const GridMap& map,
                               const std::vector<Point>& path = {}) {
  // 标记路径上的点
  std::unordered_set<Point, PointHash> pathSet(path.begin(), path.end());
  std::ostringstream oss;
  for (int y = 0; y < map.height(); ++y) {
    for (int x = 0; x < map.width(); ++x) {
      if (pathSet.count(Point(x, y))) {
        oss << "* ";
      } else if (!map.walkable(x, y)) {
        oss << "# ";
      } else {
        oss << ". ";
      }
    }
    oss << "\n";
  }
  return oss.str();
}

// ============================================================
// 基础功能测试
// ============================================================

// 空地图：起点到终点直线可达
TEST(AStarBasic, empty_map_4way) {
  GridMap map(10, 10);
  AStar astar(&map, Connectivity::Four, heuristicManhattan);
  auto result = astar.search(Point(0, 0), Point(9, 9));
  ASSERT_EQ(result.ret, 0);
  ASSERT_FALSE(result.path.empty());
  // 起点和终点正确
  EXPECT_EQ(result.path.front(), Point(0, 0));
  EXPECT_EQ(result.path.back(), Point(9, 9));
  // 4方向曼哈顿最短路径长度 = |dx| + |dy| + 1
  EXPECT_EQ((int)result.path.size(), 9 + 9 + 1);
  LOG_INFO("4-way path length: " << result.path.size()
                                 << ", nodes expanded: " << result.nodesExpanded)
}

TEST(AStarBasic, empty_map_8way) {
  GridMap map(10, 10);
  AStar astar(&map, Connectivity::Eight, heuristicChebyshev);
  auto result = astar.search(Point(0, 0), Point(9, 9));
  ASSERT_EQ(result.ret, 0);
  ASSERT_FALSE(result.path.empty());
  EXPECT_EQ(result.path.front(), Point(0, 0));
  EXPECT_EQ(result.path.back(), Point(9, 9));
  // 8方向对角线最短路径长度 = max(|dx|,|dy|) + 1
  EXPECT_EQ((int)result.path.size(), 9 + 1);
  LOG_INFO("8-way path length: " << result.path.size()
                                 << ", nodes expanded: " << result.nodesExpanded)
}

// 起点等于终点
TEST(AStarBasic, start_equals_end) {
  GridMap map(5, 5);
  AStar astar(&map);
  auto result = astar.search(Point(2, 2), Point(2, 2));
  ASSERT_EQ(result.ret, 0);
  ASSERT_EQ((int)result.path.size(), 1);
  EXPECT_EQ(result.path[0], Point(2, 2));
}

// 起点不可通行
TEST(AStarBasic, invalid_start) {
  GridMap map(5, 5);
  map.setBlocked(0, 0);
  AStar astar(&map);
  auto result = astar.search(Point(0, 0), Point(4, 4));
  EXPECT_EQ(result.ret, 1);
  EXPECT_TRUE(result.path.empty());
}

// 终点不可通行
TEST(AStarBasic, invalid_end) {
  GridMap map(5, 5);
  map.setBlocked(4, 4);
  AStar astar(&map);
  auto result = astar.search(Point(0, 0), Point(4, 4));
  EXPECT_EQ(result.ret, 1);
  EXPECT_TRUE(result.path.empty());
}

// ============================================================
// 障碍物测试
// ============================================================

// 完全被墙隔开，无路径
TEST(AStarObstacle, no_path) {
  //  . . . # .
  //  . . . # .
  //  . . . # .
  //  . . . # .
  //  . . . # .
  GridMap map(5, 5);
  for (int y = 0; y < 5; ++y) {
    map.setBlocked(3, y);
  }
  AStar astar(&map);
  auto result = astar.search(Point(0, 0), Point(4, 4));
  EXPECT_EQ(result.ret, 2);
  EXPECT_TRUE(result.path.empty());
  LOG_INFO("no_path map:\n" << mapToString(map))
}

// 墙有缺口，可以绕过
TEST(AStarObstacle, wall_with_gap) {
  //  . . . # .
  //  . . . # .
  //  . . . . .    <- y=2 处有缺口
  //  . . . # .
  //  . . . # .
  GridMap map(5, 5);
  for (int y = 0; y < 5; ++y) {
    map.setBlocked(3, y);
  }
  map.setWalkable(3, 2);  // 打开缺口

  AStar astar(&map, Connectivity::Four, heuristicManhattan);
  auto result = astar.search(Point(0, 0), Point(4, 4));
  ASSERT_EQ(result.ret, 0);
  ASSERT_FALSE(result.path.empty());
  EXPECT_EQ(result.path.front(), Point(0, 0));
  EXPECT_EQ(result.path.back(), Point(4, 4));
  LOG_INFO("wall_with_gap:\n" << mapToString(map, result.path))
}

// U型障碍物，需要绕远路
TEST(AStarObstacle, u_shape_obstacle) {
  //  10x10 地图，在中间放一个U型墙
  GridMap map(10, 10);
  // U 的左边
  for (int y = 2; y <= 7; ++y) {
    map.setBlocked(3, y);
  }
  // U 的底部
  for (int x = 3; x <= 6; ++x) {
    map.setBlocked(x, 7);
  }
  // U 的右边
  for (int y = 2; y <= 7; ++y) {
    map.setBlocked(6, y);
  }

  // 从U内部 (5, 5) 到U外部 (1, 5)
  AStar astar(&map, Connectivity::Four, heuristicManhattan);
  auto result = astar.search(Point(5, 5), Point(1, 5));
  ASSERT_EQ(result.ret, 0);
  ASSERT_FALSE(result.path.empty());
  EXPECT_EQ(result.path.front(), Point(5, 5));
  EXPECT_EQ(result.path.back(), Point(1, 5));
  LOG_INFO("u_shape path length: " << result.path.size()
                                   << ", nodes expanded: " << result.nodesExpanded)
  LOG_INFO("u_shape:\n" << mapToString(map, result.path))
}

// ============================================================
// 路径有效性校验
// ============================================================

// 验证路径上每一步都是合法的相邻移动且可通行
TEST(AStarValidity, path_steps_valid_4way) {
  GridMap map(20, 20);
  // 随机加一些障碍
  map.setBlocked(5, 0);
  map.setBlocked(5, 1);
  map.setBlocked(5, 2);
  map.setBlocked(5, 3);
  map.setBlocked(5, 4);
  map.setBlocked(10, 10);
  map.setBlocked(10, 11);
  map.setBlocked(10, 12);

  AStar astar(&map, Connectivity::Four, heuristicManhattan);
  auto result = astar.search(Point(0, 0), Point(19, 19));
  ASSERT_EQ(result.ret, 0);
  ASSERT_GE((int)result.path.size(), 2);

  for (int i = 1; i < (int)result.path.size(); ++i) {
    auto& prev = result.path[i - 1];
    auto& curr = result.path[i];
    int dx = std::abs(curr.x - prev.x);
    int dy = std::abs(curr.y - prev.y);
    // 4-way: 只允许上下左右移动一格
    EXPECT_EQ(dx + dy, 1) << "invalid step at index " << i << ": ("
                          << prev.x << "," << prev.y << ") -> (" << curr.x
                          << "," << curr.y << ")";
    EXPECT_TRUE(map.walkable(curr.x, curr.y))
        << "step " << i << " lands on blocked cell";
  }
}

TEST(AStarValidity, path_steps_valid_8way) {
  GridMap map(20, 20);
  map.setBlocked(5, 0);
  map.setBlocked(5, 1);
  map.setBlocked(5, 2);
  map.setBlocked(5, 3);
  map.setBlocked(5, 4);

  AStar astar(&map, Connectivity::Eight, heuristicEuclidean);
  auto result = astar.search(Point(0, 0), Point(19, 19));
  ASSERT_EQ(result.ret, 0);
  ASSERT_GE((int)result.path.size(), 2);

  for (int i = 1; i < (int)result.path.size(); ++i) {
    auto& prev = result.path[i - 1];
    auto& curr = result.path[i];
    int dx = std::abs(curr.x - prev.x);
    int dy = std::abs(curr.y - prev.y);
    // 8-way: 允许对角线，但每步最多移动1格
    EXPECT_LE(dx, 1);
    EXPECT_LE(dy, 1);
    EXPECT_GT(dx + dy, 0) << "zero-length step at index " << i;
    EXPECT_TRUE(map.walkable(curr.x, curr.y));
  }
}

// ============================================================
// 不同启发函数对比
// ============================================================

TEST(AStarHeuristic, compare_heuristics) {
  GridMap map(30, 30);
  // 加一道斜墙
  for (int i = 0; i < 25; ++i) {
    map.setBlocked(i + 2, i);
  }

  Point start(0, 15), end(29, 15);

  AStar astarMan(&map, Connectivity::Four, heuristicManhattan);
  auto rMan = astarMan.search(start, end);

  AStar astarEuc(&map, Connectivity::Four, heuristicEuclidean);
  auto rEuc = astarEuc.search(start, end);

  // 都应该找到路
  ASSERT_EQ(rMan.ret, 0);
  ASSERT_EQ(rEuc.ret, 0);

  // 路径长度相同(最优)
  EXPECT_EQ(rMan.path.size(), rEuc.path.size());

  LOG_INFO("manhattan: expanded=" << rMan.nodesExpanded
                                  << " path=" << rMan.path.size())
  LOG_INFO("euclidean: expanded=" << rEuc.nodesExpanded
                                  << " path=" << rEuc.path.size())
}

// ============================================================
// 大地图压力测试
// ============================================================

TEST(AStarStress, large_open_map) {
  GridMap map(200, 200);
  AStar astar(&map, Connectivity::Four, heuristicManhattan);
  auto result = astar.search(Point(0, 0), Point(199, 199));
  ASSERT_EQ(result.ret, 0);
  EXPECT_EQ((int)result.path.size(), 199 + 199 + 1);
  LOG_INFO("200x200 open map: expanded=" << result.nodesExpanded)
}

TEST(AStarStress, large_map_with_maze) {
  // 构造一个梳齿形障碍的大地图
  GridMap map(100, 100);
  for (int x = 10; x < 90; x += 10) {
    for (int y = 0; y < 95; ++y) {
      map.setBlocked(x, y);
    }
    // 交替在上下留缺口
    if ((x / 10) % 2 == 1) {
      for (int y = 90; y < 100; ++y) {
        map.setWalkable(x, y);
      }
    } else {
      for (int y = 0; y < 10; ++y) {
        map.setWalkable(x, y);
      }
    }
  }
  AStar astar(&map, Connectivity::Four, heuristicManhattan);
  auto result = astar.search(Point(0, 50), Point(99, 50));
  ASSERT_EQ(result.ret, 0);
  ASSERT_FALSE(result.path.empty());
  LOG_INFO("100x100 maze: path=" << result.path.size()
                                 << " expanded=" << result.nodesExpanded)
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
