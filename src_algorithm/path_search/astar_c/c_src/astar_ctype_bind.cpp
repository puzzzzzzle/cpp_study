//
// Created by khalidzhang on 2023/2/2.
//
#include "astar_ctype_bind.h"

#include <cstring>
#include <sstream>

#include "a_star.h"
struct CPosition {
  int x = 0;
  int y = 0;

  CPosition() = default;
  CPosition(int _x, int _y) {
    x = _x;
    y = _y;
  }
  CPosition(AstarPoint& p) : x(p.x), y(p.y) {}
  std::string to_string() const {
    std::ostringstream oss{};
    oss << "[" << x << "," << y << "]";
    return oss.str();
  }
  static int compare(const CPosition& lhs, const CPosition& rhs) {
    if (lhs.x != rhs.x) {
      return lhs.x - rhs.x;
    }
    return lhs.y - rhs.y;
  }
  friend bool operator<(const CPosition& lhs, const CPosition& rhs) {
    return compare(lhs, rhs) < 0;
  }
  friend bool operator==(const CPosition& lhs, const CPosition& rhs) {
    return compare(lhs, rhs) == 0;
  }
  friend std::ostream& operator<<(std::ostream& os, const CPosition& pos) {
    os << pos.to_string();
    return os;
  }
};
template <typename Payload>
struct PathDataWrapperTemplate {
  private:
  Payload** m_data{};

  public:
  int m_xLen{}, m_yLen{};
  PathDataWrapperTemplate(int x, int y) : m_xLen(x), m_yLen(y) { init(x, y); }
  PathDataWrapperTemplate() {}
  void init(int inX, int inY) {
    m_xLen = inX;
    m_yLen = inY;
    m_data = new Payload*[m_xLen];
    for (int x = 0; x < m_xLen; ++x) {
      m_data[x] = new Payload[m_yLen]{};
    }
  }
  virtual ~PathDataWrapperTemplate() {
    if (m_data != nullptr) {
      for (int x = 0; x < m_xLen; ++x) {
        delete[] m_data[x];
      }
      delete[] m_data;
    }
  }
  inline bool valid_pos(int x, int y) const {
    if (x < 0 || y < 0 || x >= m_xLen || y >= m_yLen) {
      return false;
    }
    return true;
  }
  bool check(int x, int y) const {
    if (!valid_pos(x, y)) {
      return false;
    }
    return m_data[x][y] == 0;
  };
  void set(int x, int y, bool val) {
    if (!valid_pos(x, y)) {
      return;
    }
    m_data[x][y] = val ? 0 : 1;
  }
  std::string to_string() const {
    std::ostringstream oss{};
    oss << m_yLen << "," << m_yLen << "\n";
    for (int y = 0; y < m_yLen; ++y) {
      for (int x = 0; x < m_xLen; ++x) {
        oss << (int)m_data[x][y] << ",";
      }
      oss << "\n";
    }
    return oss.str();
  }
};

using DataType = PathDataWrapperTemplate<uint8_t>;
using Point = CPosition;
using PathFindType = PathSearch::AStar<DataType, Point>;

#ifdef __cplusplus
extern "C" {
#endif
void* astar_new(int inWidth, int inHeight, uint8_t* arr) {
  auto data = new DataType();
  data->init(inWidth, inHeight);
  for (int column = 0; column < inHeight; ++column) {
    for (int row = 0; row < inWidth; ++row) {
      if (arr[inWidth * column + row] != 0) {
        // 非阻挡
        data->set(row, column, true);
      } else {
        data->set(row, column, false);
      }
    }
  }
  return (void*)data;
}
void astar_delete(void* astar) {
  auto data = static_cast<DataType*>(astar);
  if (data == nullptr) {
    return;
  }
  delete data;
}
char* astar_dump_map(void* astar) {
  auto data = static_cast<DataType*>(astar);
  std::string value= "nullptr error : static_cast<DataType*>(astar)";
  if (data != nullptr) {
    try
    {
      value = data->to_string();
    }
    catch(...)
    {
    }
  }
  return strdup(value.c_str());
}
AstarResult astar_search(void* astar, AstarPoint start, AstarPoint end) {
  AstarResult result{};
  auto data = static_cast<DataType*>(astar);
  if (data == nullptr) {
    result.result = -100;
    return result;
  }
  PathFindType finder(CPosition(start), CPosition(end), data);
  int ret = finder.searching();
  if (ret) {
    result.result = ret;
    return result;
  }
  auto path = finder.extract_path();
  result.result = 0;
  result.len = path.size();
  result.path = new AstarPoint[result.len];
  for (int i = 0; i < result.len; ++i) {
    result.path[i].x = path[i].x;
    result.path[i].y = path[i].y;
  }
  return result;
}
void astar_result_delete(AstarResult result) {
  delete result.path;
  result.len = 0;
  result.result = -1;
}
const char* version_info() { return "c astar v1"; }
void free_mem(void* mem){
  free(mem);
}
#ifdef __cplusplus
}
#endif