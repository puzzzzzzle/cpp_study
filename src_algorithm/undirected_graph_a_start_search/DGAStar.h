/************************************************
 * @author khalidzhang
 * @email khalidzhang@tencent.com
 * @desc 有向图A*搜索
 * @time 2023/10/13
 * @file UDGAStarSearch.h
 * @version
 * version        author            desc
 * 1.0            khalidzhang       create
 ************************************************/
#pragma once
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <limits>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "CommonClass.h"
#ifndef FINDING_DETAIL_TIME
#define FINDING_DETAIL_TIME(msg)
#endif
namespace DGAstar {
enum {
  UN_CONNECTED = 0xffffffff,
};
// 定点列表

class VertexNode {
  public:
  uint32_t m_index{};
  // 区域点的位置是-1,-1
  CPosition m_pos{};
  std::string m_name{};
  std::string ToString() const {
    std::ostringstream oss{};
    oss << m_pos << "-" << m_name;
    return oss.str();
  }
};
class VertexList {
  using ValueType = VertexNode;

  private:
  std::vector<ValueType> m_data{};

  public:
  void Init(uint32_t size) { m_data.resize(size); }
  inline const ValueType& Get(uint32_t index) const {
    assert(index < m_data.size());
    return m_data[index];
  }
  inline void Set(uint32_t index, const ValueType& v) {
    assert(index < m_data.size());
    m_data[index] = v;
  }
  inline size_t Size() const { return m_data.size(); }
  std::string ToString() const {
    std::ostringstream oss{};
    for (const auto& item : m_data) {
      oss << item.ToString() << ";";
    }
    return oss.str();
  }
};
// 邻接表
class AdjacencyList {
  private:
  // 起始定点 -> 终止定点 -> 权重
  // 表中没有的就是无穷大
  std::unordered_map<uint32_t, std::unordered_map<uint32_t, uint32_t>> m_data{};

  public:
  inline uint32_t Get(uint32_t x, uint32_t y) const {
    auto start = m_data.find(x);
    if (start == m_data.end()) {
      return UN_CONNECTED;
    }
    auto end = start->second.find(y);
    if (end == start->second.end()) {
      return UN_CONNECTED;
    }
    return end->second;
  }
  inline const std::unordered_map<uint32_t, uint32_t>& Get(uint32_t x) const {
    static const std::unordered_map<uint32_t, uint32_t> empty{};
    auto start = m_data.find(x);
    if (start == m_data.end()) {
      return empty;
    }
    return start->second;
  }
  inline void Set(uint32_t x, uint32_t y, uint32_t value) {
    m_data[x][y] = value;
  }
  std::string ToString() const {
    std::ostringstream oss{};
    oss << "\n";
    for (const auto& start : m_data) {
      oss << start.first << ": ";
      for (const auto& end : start.second) {
        oss << " (index:" << end.first << ",len:" << end.second << "),";
      }
      oss << "\n";
    }
    return oss.str();
  }
};
// 邻接表 数组实现 可以快速拷贝
// 支持快速查找某个节点的所有临边
// 不支持删除/更新
class AdjacencyListVec {
  private:
  struct EdgeItem {
    uint32_t m_from{UINT32_MAX};
    uint32_t m_target{UINT32_MAX};
    uint32_t m_weight{UINT32_MAX};
    EdgeItem() = default;
    EdgeItem(uint32_t from, uint32_t target, uint32_t weight)
        : m_from(from), m_target(target), m_weight(weight) {}
  };
  // 需要满足 trivial layout, 快速复制时直接memcpy
  static_assert(std::is_trivially_copyable_v<EdgeItem>);
  // 所有边
  std::vector<EdgeItem> m_edges{};
  // 节点index -> next表开头
  std::vector<uint32_t> m_first{};
  // 每个节点的所有边在 m_edges 中的记录
  std::vector<uint32_t> m_next{};

  template <class T>
  inline void VecSatisfyImpl(std::vector<T>& vec, uint32_t index) {
    if (index < vec.size()) {
      return;
    }
    static const double EXPAND_GAP = 1.5;
    // 扩张
    assert(index < UINT32_MAX / EXPAND_GAP);
    // 扩张策略: 指定的数量 * 1.5 或者当前容量 * 1.5
    size_t newSize = std::max((size_t)((double)vec.size() * EXPAND_GAP),
                              (size_t)((index + 1) * EXPAND_GAP));
    vec.resize(newSize);
    assert(vec.size() == newSize);
  }
  template <class T>
  inline void VecSatisfy(std::vector<T>& vec, uint32_t index) {
    VecSatisfyImpl(vec, index);
  }
  // uint 数组额外初始化为 int max
  inline void VecSatisfy(std::vector<uint32_t>& vec, uint32_t index) {
    size_t oldSize = vec.size();
    VecSatisfyImpl(vec, index);
    // 初始化
    auto data = vec.data();
    memset(data + oldSize, 0xff, sizeof(uint32_t) * (vec.size() - oldSize));
  }
  template <class T>
  inline static void MemcpyVec(const std::vector<T>& src, std::vector<T>& dst) {
    dst.clear();
    dst.resize(src.size());
    memcpy(dst.data(), src.data(), sizeof(T) * dst.size());
  }
  static void FastCopy(const AdjacencyListVec& src, AdjacencyListVec& dst) {
    MemcpyVec(src.m_first, dst.m_first);
    MemcpyVec(src.m_next, dst.m_next);
    MemcpyVec(src.m_edges, dst.m_edges);
  }

  public:
  AdjacencyListVec() = default;
  AdjacencyListVec(const AdjacencyListVec& other) { FastCopy(other, *this); }
  AdjacencyListVec& operator=(const AdjacencyListVec& other) {
    FastCopy(other, *this);
    return *this;
  }

  public:
  inline void Set(uint32_t from, uint32_t target, uint32_t value) {
    // 记录边
    m_edges.emplace_back(from, target, value);
    auto index = m_edges.size() - 1;
    assert(index < UINT32_MAX);
    // 保证数组大小够用
    VecSatisfy(m_next, index);
    VecSatisfy(m_first, from);
    // 把老的first 记录到next上
    m_next[index] = m_first[from];
    // 更新first
    m_first[from] = index;
  }
  // get 性能较低, 不要用于高频使用的地方
  inline std::vector<std::pair<uint32_t, uint32_t>> Get(uint32_t from) const {
    std::vector<std::pair<uint32_t, uint32_t>> result{};
    if (from >= m_first.size()) {
      return result;
    }
    auto currEdgeIndex = m_first[from];
    // 防止死循环
    int count{0};
    while (currEdgeIndex != UINT32_MAX) {
      ++count;
      assert(count < 100000);
      assert(currEdgeIndex < m_edges.size());
      const auto& edge = m_edges[currEdgeIndex];
      assert(edge.m_from == from);
      result.emplace_back(edge.m_target, edge.m_weight);
      currEdgeIndex = m_next[currEdgeIndex];
    }
    return result;
  }
  inline uint32_t Get(uint32_t from, uint32_t target) const {
    if (from >= m_first.size()) {
      return UINT32_MAX;
    }
    auto currEdgeIndex = m_first[from];
    // 防止死循环
    int count{0};
    while (currEdgeIndex != UINT32_MAX) {
      ++count;
      assert(count < 100000);
      assert(currEdgeIndex < m_edges.size());
      const auto& edge = m_edges[currEdgeIndex];
      assert(edge.m_from == from);
      if (edge.m_target == target) {
        return edge.m_weight;
      }
      currEdgeIndex = m_next[currEdgeIndex];
    }
    return UINT32_MAX;
  }

  // 最低开销的迭代, 调用侧targetVertex初始化为0并不要修改,
  // 每次调用targetVertex修改为下一条边, targetVertex == UINT32_MAX 终止
  struct IteratorEdgeData {
    uint32_t m_fromVertex{UINT32_MAX};
    uint32_t m_currEdgeIndex{UINT32_MAX};
    uint32_t m_targetVertex{UINT32_MAX};
    uint32_t m_weight{};
    bool m_started{false};
    bool m_end{false};
    inline bool Finished() { return m_end; }
  };
  IteratorEdgeData IteratorBegin(uint32_t from) {
    IteratorEdgeData result{};
    result.m_fromVertex = from;
    if (from >= m_first.size()) {
      result.m_end = true;
    }
    return result;
  }
  inline bool IteratorNext(IteratorEdgeData& data) {
    if (data.Finished()) {
      return false;
    }
    // next
    if (!data.m_started) {
      data.m_started = true;
      data.m_currEdgeIndex = m_first[data.m_fromVertex];
    } else {
      data.m_currEdgeIndex = m_next[data.m_currEdgeIndex];
    }
    // check
    if (data.m_currEdgeIndex==UINT32_MAX) {
      data.m_end= true;
      return false;
    }
    assert(data.m_currEdgeIndex < m_edges.size());
    const auto& edge = m_edges[data.m_currEdgeIndex];
    assert(edge.m_from == data.m_fromVertex);
    data.m_targetVertex = edge.m_target;
    data.m_weight = edge.m_weight;
    return true;
  }
  std::string ToString() const {
    std::ostringstream oss{};
    for (int i = 0; i < m_first.size(); ++i) {
      auto edges = Get(i);
      if (edges.empty()) {
        continue;
      }
      oss << i << ": ";
      for (const auto& edge : edges) {
        oss << "(" << edge.first << "," << edge.second << "), ";
      }
      oss << "\n";
    }
    return oss.str();
  }
};

class Astar {
  public:
  enum class ErrorCode {
    OK = 0,
    UN_INITED = 1,
    PARAM_WRONG = 2,
    NO_PATH = 3,
    UNKNOWN = 4,
  };

  private:
  struct OpenList {
    Astar* m_astar{};
    char* m_inOpenList{};
    // f(index) -> index
    struct OpenItem {
      uint32_t m_index{};
      uint32_t m_f{};
      OpenItem() = default;
      OpenItem(uint32_t index, uint64_t f) : m_index(index), m_f(f) {}
      inline friend bool operator<(const OpenItem& lhs, const OpenItem& rhs) {
        return lhs.m_f > rhs.m_f;
      }
      inline friend bool operator==(const OpenItem& lhs, const OpenItem& rhs) {
        return lhs.m_f == rhs.m_f;
      }
    };
    using OpenListType = std::vector<OpenItem>;
    OpenListType m_openList{};
    inline void Push(uint32_t index, uint64_t f) {
      if (m_inOpenList[index]) {
        ReScore(index, f);
        return;
      }
      m_inOpenList[index] = true;
      m_openList.emplace_back(index, (uint32_t)f);
      std::push_heap(m_openList.begin(), m_openList.end());
    }
    inline void ReScore(uint32_t index, uint64_t f) {
      bool find{false};
      for (auto& item : m_openList) {
        if (item.m_index == index) {
          item.m_f = f;
          find = true;
          break;
        }
      }
      if (!find) {
        m_openList.emplace_back(index, (uint32_t)f);
        assert(false);
      }
      std::make_heap(m_openList.begin(), m_openList.end());
    }
    inline uint32_t PopMin() {
      assert(!m_openList.empty());
      std::pop_heap(m_openList.begin(), m_openList.end());
      uint32_t index = m_openList.back().m_index;
      m_openList.pop_back();
      m_inOpenList[index] = false;
      return index;
    }
    inline bool Empty() const { return m_openList.empty(); }
    inline bool InOpenList(uint32_t index) const { return m_inOpenList[index]; }
  };

  // 内存初始化信息
  bool m_inited{false};
  // 地形数据
  const AdjacencyList* m_adj{};
  const VertexList* m_vertex{};
  size_t m_vertexSize{};

  // 临时数据, 全部使用定点index作为下表
  // close 表
  char* m_close{};
  // g值表
  // uint32_t 计算方便些, 使用int了, 目前使用*10000的定点数
  uint32_t* m_g{};
  // parent 表
  uint32_t* m_parent{};
  // open list
  OpenList m_openList{};

  // 起点终点信息
  // 起点index
  uint32_t m_start{};
  // 起点所在位置
  CPosition m_startAreaPos{};
  uint32_t m_end{};
  CPosition m_endAreaPos{};

  // 结果
  ErrorCode m_errorCode{ErrorCode::UN_INITED};
  std::vector<uint32_t> m_result{};

  private:
  void CreateMem() {
    m_close = new char[m_vertexSize];
    m_g = new uint32_t[m_vertexSize];
    m_parent = new uint32_t[m_vertexSize];
    m_openList.m_inOpenList = new char[m_vertexSize];
    m_openList.m_astar = this;
  }
  void ResetMem() {
    // close 表, 全部置为 false
    memset(m_close, 0, m_vertexSize * sizeof(char));
    // g 表 全部置为 uint32 max
    memset(m_g, 0xff, m_vertexSize * sizeof(uint32_t));
    // parent 表 全部置为 uint32 max
    memset(m_parent, 0xff, m_vertexSize * sizeof(uint32_t));
    // m_openList.m_inOpenList 表, 全部置为 false
    memset(m_openList.m_inOpenList, 0, m_vertexSize * sizeof(char));

    // 寻路暂存数据置空
    m_start = -1;
    m_startAreaPos.clear();
    m_end = -1;
    m_endAreaPos.clear();
    m_errorCode = ErrorCode::UN_INITED;
    m_result.clear();
  }
  void FreeMem() {
    delete[] m_close;
    delete[] m_g;
    delete[] m_parent;
    delete[] m_openList.m_inOpenList;
  }

  public:
  Astar() = default;
  Astar(Astar&) = delete;
  Astar& operator=(Astar&) = delete;
  ~Astar() { FreeMem(); }
  void Init(const VertexList* vertex) {
    if (m_inited) {
      assert(m_vertex = vertex);
      assert(m_vertexSize = vertex->Size());
      return;
    }
    m_inited = true;
    // 为了加快计算, 使用数组而非map记录各种数据, 定点列表不能太大
    // 不然数组就太大了
    assert(vertex->Size() < INT16_MAX);
    m_vertex = vertex;
    m_vertexSize = vertex->Size();
    CreateMem();
  }
  void Search(const VertexList* vertex, const AdjacencyList* const adj,
              uint32_t start, const CPosition& startAreaPos, uint32_t end,
              const CPosition& endAreaPos) {
    Init(vertex);
    ResetMem();
    m_adj = adj;
    m_start = start;
    m_startAreaPos = startAreaPos;
    m_end = end;
    m_endAreaPos = endAreaPos;
    if (m_start == m_end) {
      m_result.push_back(m_start);
      m_result.push_back(m_end);
      m_errorCode = ErrorCode::OK;
      return;
    }
    // check
    // pass check start search
    DoSearch();
  }
  std::pair<ErrorCode, const std::vector<uint32_t>*> GetResult() {
    return std::make_pair(m_errorCode, &m_result);
  }

  private:
  // 预测代价
  inline uint32_t h(uint32_t index) {
    const CPosition* targetPos;
    if (index == m_start) {
      targetPos = &m_startAreaPos;
    } else if (index == m_end) {
      targetPos = &m_endAreaPos;
    } else {
      targetPos = &(m_vertex->Get(index).m_pos);
    }
    assert(targetPos->x >= 0);
    assert(targetPos->y >= 0);
    // 使用直线距离预测了
    return (uint32_t)(std::hypot(m_endAreaPos.x - targetPos->x,
                                 m_endAreaPos.y - targetPos->y));
  }
  void DoSearch() {
    // init
    m_parent[m_start] = m_start;
    m_g[m_start] = 0;
    m_openList.Push(m_start, 0);

    // start
    // 防止死循环
    int count = 0;
    while (!m_openList.Empty()) {
      ++count;
      // 跨关隘规划不应该有太多线段
      assert(count < 10000);

      // 当前处理定点
      auto curr = m_openList.PopMin();
      m_close[curr] = true;
      if (curr == m_end) {
        break;
      }
      // 处理每个邻居
      for (const auto& neighbor : m_adj->Get(curr)) {
        // 已经close了, 忽略
        if (m_close[neighbor.first]) {
          continue;
        }

        uint32_t neighborIndex = neighbor.first;
        uint32_t neighborNewCost = m_g[curr] + neighbor.second;

        // neighbor cost 较小, 不在 m_g中的, 全部标记为UINT32_MAX了,
        // 不用判断是否在里面
        if (neighborNewCost < m_g[neighborIndex]) {
          // 更新代价和前驱节点
          m_g[neighborIndex] = neighborNewCost;
          // 放入open list中
          // 如果已经存在, 自动更新f值, 因为前驱节点可能已经变了, f值也要变
          m_openList.Push(neighborIndex, neighborNewCost + h(neighborIndex));
          m_parent[neighborIndex] = curr;
        }
      }
    }

    FINDING_DETAIL_TIME("[ColPlan|StepTime] astar step count " << count)
    // get result
    ExtractPath();
  }
  void ExtractPath() {
    if (m_errorCode != ErrorCode::UN_INITED) {
      m_errorCode = ErrorCode::UNKNOWN;
      return;
    }
    if (m_parent[m_end] == UN_CONNECTED) {
      m_errorCode = ErrorCode::NO_PATH;
      return;
    }
    auto end = m_end;
    m_result.push_back(end);
    // 防止死循环
    int count = 0;
    while (true) {
      ++count;
      // 跨关隘规划不应该有太多线段
      assert(count < 10000);
      end = m_parent[end];
      if (end == UN_CONNECTED) {
        m_errorCode = ErrorCode::UNKNOWN;
        return;
      }
      m_result.push_back(end);
      if (end == m_start) {
        break;
      }
    }
    std::reverse(std::begin(m_result), std::end(m_result));
    m_errorCode = ErrorCode::OK;
  }
};
}  // namespace DGAstar