#include "DGAStar.h"
#include "common_funcs.h"
#include "common_includes.h"
using namespace DGAstar;
TEST(test_test, 1) { EXPECT_EQ(1, 1); }
void CheckIterator(AdjacencyListVec &target, uint32_t maxVertex) {
  for (int i = 0; i < maxVertex; ++i) {
    // 普通方式获取的边
    auto targetEdges = target.Get(i);
    // 迭代器方式获取的边
    std::vector<std::pair<uint32_t, uint32_t>> iteratorGot{};
    auto iterator = target.IteratorBegin(i);
    while (target.IteratorNext(iterator)) {
      iteratorGot.emplace_back(iterator.m_targetVertex, iterator.m_weight);
    }
    assert(targetEdges.size() == iteratorGot.size());
    for (auto j = 0; j < targetEdges.size(); ++j) {
      const auto &check = targetEdges[j];
      const auto &beCheck = iteratorGot[j];
      assert(check.first == beCheck.first);
      assert(check.second == beCheck.second);
    }
  }
}
void AssertSame(const AdjacencyList &check, AdjacencyListVec &target,
                uint32_t maxVertex) {
  for (int i = 0; i < maxVertex; ++i) {
    const auto &checkEdges = check.Get(i);
    auto targetEdges = target.Get(i);
    assert(checkEdges.size() == targetEdges.size());
    for (const auto &checkItem : checkEdges) {
      bool found = false;
      for (const auto &targetItem : targetEdges) {
        if (checkItem.first == targetItem.first) {
          assert(checkItem.second == targetItem.second);
          found = true;
          break;
        }
      }
      assert(found);
    }
  }
  CheckIterator(target, maxVertex);
}

TEST(test_vec_adj, 1) {
  AdjacencyList checkAdj{};
  AdjacencyListVec adj{};
  int maxVertex = 1000;
  int maxWeight = 10000;
  // AdjacencyListVec 不支持更新, 不能重复
  std::set<std::pair<int, int>> added{};
  for (int i = 0; i < 50000; ++i) {
    int start = rand() % maxVertex;
    int end = rand() % maxVertex;
    if (start == end) {
      continue;
    }
    int weight = rand() % maxWeight;
    if (InContainer(std::make_pair(start, end), added)) {
      continue;
    }
    added.insert(std::make_pair(start, end));
    checkAdj.Set(start, end, weight);
    adj.Set(start, end, weight);
    LOG_DEBUG("add " << i << "\t" << start << "\t" << end << "\t" << weight)
    AssertSame(checkAdj, adj, maxVertex);
  }
  AssertSame(checkAdj, adj, maxVertex);
}
TEST(test_vec_adj, 2) {
  AdjacencyList checkAdj{};
  AdjacencyListVec adj{};
  int maxVertex = 1000;
  int maxWeight = 10000;
  // AdjacencyListVec 不支持更新, 不能重复
  std::set<std::pair<int, int>> added{};
  for (int i = 0; i < 5000; ++i) {
    int start = (double)i / 5000 * maxVertex;
    int end = rand() % maxVertex;
    if (start == end) {
      continue;
    }
    int weight = rand() % maxWeight;
    if (InContainer(std::make_pair(start, end), added)) {
      continue;
    }
    added.insert(std::make_pair(start, end));
    checkAdj.Set(start, end, weight);
    adj.Set(start, end, weight);
    LOG_DEBUG("add " << i << "\t" << start << "\t" << end << "\t" << weight)
    AssertSame(checkAdj, adj, maxVertex);
  }
  AssertSame(checkAdj, adj, maxVertex);
  LOG_DEBUG(adj.ToString())
  AdjacencyListVec copy = adj;
  AssertSame(checkAdj, copy, maxVertex);
}
TEST(test_vec_adj, 3) {
  AdjacencyList checkAdj{};
  AdjacencyListVec adj{};
  int maxVertex = 1000;
  int maxWeight = 10000;
  // AdjacencyListVec 不支持更新, 不能重复
  std::set<std::pair<int, int>> added{};
  for (int i = 0; i < 5000; ++i) {
    int start = (double)i / 5000 * maxVertex;
    int end = rand() % maxVertex;
    if (start == end) {
      continue;
    }
    int weight = rand() % maxWeight;
    if (InContainer(std::make_pair(start, end), added)) {
      continue;
    }
    added.insert(std::make_pair(start, end));
    checkAdj.Set(start, end, weight);
    adj.Set(start, end, weight);
    LOG_DEBUG("add " << i << "\t" << start << "\t" << end << "\t" << weight)
    AssertSame(checkAdj, adj, maxVertex);
  }
  AssertSame(checkAdj, adj, maxVertex);
  LOG_DEBUG(adj.ToString())
  AdjacencyListVec copy = adj;
  AssertSame(checkAdj, copy, maxVertex);
}
int main(int argc, char **argv) {
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  sleep(1);
  return iRet;
}