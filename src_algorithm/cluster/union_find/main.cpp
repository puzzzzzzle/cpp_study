//
// Created by tao on 19-1-17.
//
#include "common_includes.h"
#include "union_find.h"
#include "union_find_parent.h"
using namespace UnionFind;
TEST(test_test, 1) { EXPECT_EQ(1, 1); }
std::string print_sets(UnionFindParent &uf) {
  std::map<int, std::vector<int>> sets{};
  for (int i = 0; i < uf.m_count; ++i) {
    sets[uf.find(i)].push_back(i);
  }
  std::ostringstream oss{};
  oss << "\n";
  for (auto &item : sets) {
    oss << item.first << "\t" << VecLikeToString(item.second) << "\n";
  }
  return oss.str();
}
TEST(union_find, 1) {
  const int count = 10;
  UnionFindParent uf(count);
  uf.union_elements(0, 2);
  uf.union_elements(0, 3);
  LOG_DEBUG("print set " << print_sets(uf))

  uf.union_elements(8, 5);
  uf.union_elements(9, 6);
  LOG_DEBUG("print set " << print_sets(uf))

  uf.union_elements(8, 2);
  LOG_DEBUG("print set " << print_sets(uf))
}

int main(int argc, char **argv) {
  int iRet = 0;
  iRet = beforeRun();
  if (iRet) {
    std::cerr << "init fail with " << iRet << std::endl;
  }
  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}