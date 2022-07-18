/************************************************
 * @author khalidzhang
 * @email khalidzhang@tencent.com
 * @desc Dijkstra算法, 用于在简单无向图中查找最短路径
 * @time 2020/8/3
 * @file Dijkstra.h
 * @version
 * version        author            desc
 * 1.0            khalidzhang       create
 ************************************************/
#pragma once

#include <algorithm>
#include <cassert>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

namespace Dijkstra {
enum {
  LEN_UNDEFINED = -100,
  INT_INF = std::numeric_limits<int>::max(),
};

template <class T>
std::ostream &printArr(std::ostream &os, size_t len, const T value[]) {
  os << "values :\t[" << std::endl;
  for (int i = 0; i < len; ++i) {
    os << value[i] << ", ";
  }
  os << "]" << std::endl;
  return os;
}
/**
 * 一维矩阵
 * @tparam T
 */
template <typename T>
class SDArray {
  public:
  T *m_data{};
  const int m_len;
  SDArray() = delete;
  void CopyData(T *data) {
    for (int i = 0; i < m_len; ++i) {
      m_data[i] = data[i];
    }
  }
  SDArray(int len) : m_len(len) { m_data = new T[m_len]{}; }
  SDArray(int len, T *data) : m_len(len) {
    m_data = new T[m_len]{};
    CopyData(data);
  }
  SDArray(const SDArray &arr) : m_len(arr.m_len) {
    m_data = new T[m_len]{};
    CopyData(arr.m_data);
  }
  SDArray &operator=(const SDArray &another) {
    assert(m_len == another.m_len);
    CopyData(another.m_data);
    return *this;
  }
  ~SDArray() {
    delete[] m_data;
    m_data = nullptr;
  }
  inline const T &Get(int index) const {
    assert(index < m_len);
    return m_data[index];
  }
  inline void Set(int index, const T &val) {
    assert(index < m_len);
    m_data[index] = val;
  }
  // 打印矩阵队列图
  void Print(std::ostream &oss, const std::string &gap) {
    for (int curr_index = 0; curr_index < m_len - 1; ++curr_index) {
      oss << m_data[curr_index].ToString() << gap;
    }
    oss << m_data[m_len - 1];
  }
  void Print() {
    std::cout << "print single array" << std::endl;
    Print(std::cout, "\t");
    std::cout << "\nend print single array" << std::endl;
  }
  std::string ToString() {
    std::ostringstream oss{};
    Print(oss, "\t");
    return oss.str();
  }
};

/**
 * 二维矩阵
 * 注意这里是行列式的表述方式, 原点在右上方
 * 先行, 后列
 * !!!! 注意, 这个为了速度使用了memcpy, 只能使用不包含析构函数的结构体,
 * 不然会导致二次析构
 * @tparam T
 */
template <typename T>
class TDArray {
  public:
  T **m_data{};
  const int m_raw, m_col;
  TDArray() = delete;
  TDArray(int raw, int col) : m_raw(raw), m_col(col) {
    m_data = new T *[m_raw] {};
    for (int curr_raw = 0; curr_raw < m_raw; ++curr_raw) {
      m_data[curr_raw] = new T[m_col]{};
    }
  }
  TDArray(int raw, int col, T *data) : m_raw(raw), m_col(col) {
    m_data = new T *[m_raw] {};
    for (int curr_raw = 0; curr_raw < m_raw; ++curr_raw) {
      m_data[curr_raw] = new T[m_col]{};
      memcpy(m_data[curr_raw], &data[curr_raw * m_col], sizeof(T) * m_col);
      //            for (int curr_col = 0; curr_col < m_col; ++curr_col)
      //            {
      //                m_data[curr_raw][curr_col] = data[curr_raw * m_col +
      //                curr_col];
      //            }
    }
  }
  TDArray(const TDArray &arr) : m_raw(arr.m_raw), m_col(arr.m_col) {
    m_data = new T *[m_raw] {};
    for (int curr_raw = 0; curr_raw < m_raw; ++curr_raw) {
      m_data[curr_raw] = new T[m_col]{};
      memcpy(m_data[curr_raw], arr.m_data[curr_raw], sizeof(T) * m_col);
      //            for (int curr_col = 0; curr_col < m_col; ++curr_col)
      //            {
      //                m_data[curr_raw][curr_col] =
      //                arr.m_data[curr_raw][curr_col];
      //            }
    }
  }
  ~TDArray() {
    for (int curr_index = 0; curr_index < m_raw; ++curr_index) {
      delete[] m_data[curr_index];
    }
    delete[] m_data;
    m_data = nullptr;
  }
  TDArray &operator=(const TDArray &another) {
    assert(m_raw == another.m_raw);
    assert(m_col == another.m_col);
    assert(m_data != nullptr);
    for (int curr_raw = 0; curr_raw < m_raw; ++curr_raw) {
      memcpy(m_data[curr_raw], another.m_data[curr_raw], sizeof(T) * m_col);
    }
    return *this;
  }
  inline const T &Get(int row, int col) const {
    assert(row < m_raw);
    assert(col < m_col);
    return m_data[row][col];
  }
  inline void Set(int row, int col, const T &val) {
    assert(row < m_raw);
    assert(col < m_col);
    m_data[row][col] = val;
  }
  // 打印矩阵队列图
  void Print(std::ostream &oss, const std::string &rawGap,
             const std::string &colGap) {
    for (int curr_raw = 0; curr_raw < m_raw; ++curr_raw) {
      for (int curr_col = 0; curr_col < m_col; ++curr_col) {
        oss << m_data[curr_raw][curr_col] << colGap;
      }
      oss << "\n";
    }
  }
  void Print() {
    std::cout << "print double dim array" << std::endl;
    Print(std::cout, "\n", "\t");
    std::cout << "\n"
              << "end print double dim array" << std::endl;
  }
  std::string ToString() {
    std::ostringstream oss{};
    Print(oss, "\n", "\t");
    return oss.str();
  }
};
template <typename VERTEX>
static std::string GetNodeName(int index, VERTEX *nodes) {
  std::ostringstream oss{};
  oss << nodes->Take(index) << "(" << index << ")";
  return oss.str();
}

class DijkstraResultType {
  public:
  std::vector<int> m_shortestPath{};
  int from{}, target{};
  int cost{};
  template <typename VERTEX>
  std::string ToString(const std::string &prefix, VERTEX *vertex) const {
    std::ostringstream oss{};
    oss << prefix << "from:\t" << GetNodeName(from, vertex) << std::endl;
    oss << prefix << "target:\t" << GetNodeName(target, vertex) << std::endl;
    oss << prefix << "cost:\t" << cost << std::endl;
    oss << prefix << "to target path :\t";
    for (const auto &pathItem : m_shortestPath) {
      oss << GetNodeName(pathItem, vertex) << "\t";
    }
    oss << prefix << std::endl;
    return oss.str();
  }
};
#define DIJKSTRA_PRINT_DETAIL
/**
 * 无向简单图
 */
template <typename VERTEX>
class MatrixUDG {
  public:
  using MatrixType = TDArray<int>;
  using VertexType = SDArray<VERTEX>;
  using VertexItemType = VERTEX;

  public:
  VertexType m_vertex;  // 顶点集合
                        // 邻接矩阵每次动态传入
                        //    MatrixType m_matrix;  // 邻接矩阵

  public:
  /** 创建图(用已提供的矩阵)
   * @param vertex 顶点数组
   * @param vlen 顶点数组的长度
   * @param matrix 矩阵(数据)
   */
  MatrixUDG(const VertexType &vertex) : m_vertex(vertex) {}

  ~MatrixUDG() {}

  /**
   * Dijkstra最短路径。
   * 即，统计图中"顶点vs"到其它各个顶点的最短路径。
   * @param start 始顶点(start vertex)。即计算"顶点vs"到其它顶点的最短路径。
   */
  int dijkstra(int start, std::vector<DijkstraResultType> *result,
               MatrixType &matrix, int target = -1) {
    int vexNum = m_vertex.m_len;
    int flag[vexNum], prev[vexNum], dist[vexNum];
    matrix.Print();
    // 初始化
    for (int i = 0; i < vexNum; i++) {
      flag[i] = false;  // 顶点i的最短路径还没获取到。
      dist[i] =
          matrix.m_data[start][i];  // 顶点i的最短路径为"顶点vs"到"顶点i"的权。
      if (dist[i] != INT_INF) {
        prev[i] = start;
      } else {
        prev[i] = -1;  // 顶点i的前驱顶点为0。
      }
    }
    // 对"顶点vs"自身进行初始化
    flag[start] = 1;
    dist[start] = 0;
    prev[start] = -1;
#ifdef DIJKSTRA_PRINT_DETAIL
    LOG_DEBUG("print vertex dist")
    printArr(std::cout, vexNum, dist);
    LOG_DEBUG("end print vertex dist")
    LOG_DEBUG("print vertex dist")
    printArr(std::cout, vexNum, prev);
    printArr(std::cout, vexNum, flag);
#endif
    // 遍历mVexNum-1次；每次找出一个顶点的最短路径。
    for (int i = 1; i < vexNum; i++) {
      // 寻找当前最小的路径；
      // 即，在未获取最短路径的顶点中，找到离vs最近的顶点(k)。
      int min = INT_INF;
      int k = -1;
      for (int j = 0; j < vexNum; j++) {
        if (flag[j] == 0 && dist[j] < min) {
          min = dist[j];
          k = j;
        }
      }
      if (k == -1) {
#ifdef DIJKSTRA_PRINT_DETAIL
        LOG_DEBUG("print vertex dist")
        printArr(std::cout, vexNum, dist);
        LOG_DEBUG("end print vertex dist")
        LOG_DEBUG("print vertex dist")
        printArr(std::cout, vexNum, prev);
        printArr(std::cout, vexNum, flag);
#endif
        // 找不到最小路径了, 可以理解为剩下的点都是孤立点
        for (int j = 0; j < vexNum; j++) {
          if (flag[j] == 0) {
            flag[j] = 1;
            dist[j] = INT_INF;
            prev[j] = -1;
          }
        }
        break;
      }
      // 标记"顶点k"为已经获取到最短路径
      flag[k] = 1;
#ifdef DIJKSTRA_PRINT_DETAIL
      LOG_DEBUG("set k to 1   " << k)
#endif

      // 修正当前最短路径和前驱顶点
      // 即，当已经"顶点k的最短路径"之后，更新"未获取最短路径的顶点的最短路径和前驱顶点"。
      for (int j = 0; j < vexNum; j++) {
        int tmp =
            (matrix.m_data[k][j] == INT_INF ? INT_INF
                                            : (min + matrix.m_data[k][j]));
        if (flag[j] == 0 && (tmp < dist[j])) {
          dist[j] = tmp;
          prev[j] = k;
        }
      }
    }
#ifdef DIJKSTRA_PRINT_DETAIL
    LOG_DEBUG("print vertex dist")
    printArr(std::cout, vexNum, dist);
    printArr(std::cout, vexNum, prev);
    printArr(std::cout, vexNum, flag);
    // 打印到各个顶点的最短路径长度
    {
      std::ostringstream oss{};
      oss << "\n"
          << GetNodeName(start, &m_vertex) << " to path lens :"
          << "\n";
      for (int i = 0; i < m_vertex.m_len; ++i) {
        oss << "\t"
            << "index:\t" << GetNodeName(i, &m_vertex) << "\tdist:\t" << dist[i]
            << std::endl;
      }
      oss << "\n";
      LOG_DEBUG(oss.str())
    }
#endif
    auto addOneTargetPathToResult = [&](int currTarget,
                                        DijkstraResultType *item) {
      // 构建结果
      item->from = start;
      item->target = currTarget;
      // 构建到目标顶点的最短路径
      {
        auto &path = item->m_shortestPath;
        int checkNum = 99999;
        for (int t = currTarget; prev[t] != -1; t = prev[t]) {
          --checkNum;
          if (checkNum < 0) {
            LOG_ERROR("cannot get to start")
            break;
          }
          LOG_DEBUG("will push t " << t << "\tprev is \t" << prev[t])
          path.push_back(t);
          if (prev[t] == start) {
            LOG_DEBUG("prev[t] get to start , t= " << t)
            path.push_back(start);

            break;
          }
        }
        std::reverse(path.begin(), path.end());

        if (!path.empty()) {
          if (path[0] != start) {
            LOG_ERROR("get a path but start is not the same"
                      << item->ToString("\t", &m_vertex))
            item->cost = INT_INF;
            item->m_shortestPath.clear();
          }
        } else {
          item->cost = INT_INF;
        }
      }
    };
    if (target >= 0) {
      DijkstraResultType resultItem{};
      addOneTargetPathToResult(target, &resultItem);
      result->push_back(resultItem);
    } else {
      for (int i = 0; i < m_vertex.m_len; ++i) {
        DijkstraResultType resultItem{};
        addOneTargetPathToResult(i, &resultItem);
        result->push_back(resultItem);
      }
    }
    return 0;
  }
};
}  // namespace Dijkstra