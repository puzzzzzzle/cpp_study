//
// Created by tao on 19-1-17.
//
#include "common_includes.h"
#include "path_find_test_base.h"
#include "union_find_connect.h"
#include "union_find_parent.h"

using ConnectAnalize = UnionFindConnectCluster::UnionFindConnectCluster<
    DataType, Point, UnionFind::UnionFindParent>;

struct ConnectTestBase : public MapDataInit {
  ConnectAnalize conn{};
};
struct IDTest : public ConnectTestBase {
  ConnectAnalize conn{};

  protected:
  void SetUp() override {}
  void check_pos(int x, int y) {
    auto origin = Point(x, y);
    auto id = conn.pos_2_id(x, y);
    auto decode_pos = conn.id_2_pos(id);
    LOG_DEBUG(origin.to_string() << "\t" << decode_pos.to_string())
    ASSERT_TRUE(origin == decode_pos);
  }
};
struct ConnectTest : public ConnectTestBase {};

TEST_F(IDTest, idTest) {
  build_from_file("data/path_find/map_file_10_10.txt");
  conn.init(&data, Point(0, 0), Point(7, 7));
  check_pos(0, 0);
  check_pos(0, 6);
  check_pos(6, 0);
  check_pos(6, 6);
  check_pos(2, 3);
}
TEST_F(IDTest, idTest2) {
  build_from_file("data/path_find/map_file_10_10.txt");
  conn.init(&data, Point(5, 5), Point(10, 10));
  check_pos(5, 5);
  check_pos(5, 9);
  check_pos(9, 5);
  check_pos(9, 9);
  check_pos(6, 8);
}

TEST_F(IDTest, idTest3) {
  build_from_file("data/path_find/map_file_10_10.txt");
  conn.init(&data, Point(5, 5), Point(7, 10));
  check_pos(5, 5);
  check_pos(5, 9);
  check_pos(6, 5);
  check_pos(6, 9);
  check_pos(6, 8);
}
TEST_F(ConnectTest, conn_1) {
  build_from_file("data/path_find/map_file_10_10.txt");
  conn.init(&data, Point(0, 0), Point(7, 6));
  conn.scan_region();
  auto regions = conn.get_valid_regions();
  LOG_DEBUG(MapLikeToString(regions, "\n"))
  ASSERT_TRUE(regions.size() == 2);
}
TEST_F(ConnectTest, conn_2) {
  build_from_file("data/path_find/map_file_10_10.txt");
  conn.init(&data, Point(2, 4), Point(7, 10));
  conn.scan_region();
  auto regions = conn.get_valid_regions();
  LOG_DEBUG(MapLikeToString(regions, "\n"))
  ASSERT_TRUE(regions.size() == 2);
}
TEST_F(ConnectTest, conn_3) {
  build_from_file("data/path_find/map_file_10_10_2.txt");
  conn.init(&data, Point(0, 0), Point(10, 10));
  conn.scan_region();
  auto regions = conn.get_valid_regions();
  LOG_DEBUG(MapLikeToString(regions, "\n"))
  ASSERT_TRUE(regions.size() == 4);
}

int main(int argc, char **argv) {
  std::cerr << strerror(24) << std::endl;
  int iRet = 0;
  iRet = beforeRun();
  if (iRet) {
    std::cerr << "init fail with " << iRet << std::endl;
  }
  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}