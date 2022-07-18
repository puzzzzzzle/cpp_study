//
// Created by khalidzhang on 2021/2/27.
//

#pragma once
#include <string>
#include <ostream>
#include <sstream>
#include <vector>
#include "common_includes.h"
#include "common_funcs.h"
#include "CommonClass.h"

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
    LOG_DEBUG("clean path find data")
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
        oss << m_data[x][y] << ",";
      }
      oss << "\n";
    }
    return oss.str();
  }
};

using DataType = PathDataWrapperTemplate<int>;
using Point = CPosition;

struct PathFindTask {
  std::string mapPath{};
  std::vector<std::pair<Point, Point>> tasks{};
  // TODO 使用json格式
  // TODO 包含预估结果
  PathFindTask() = default;
  int load(const std::string& path) {
    auto allStr = LoadFileStr(path);
    std::vector<std::string> lines{}, currLine{};
    CALL_IF_TRUE_RETURN(allStr == "")
    Split(allStr, "\n", lines);
    CALL_IF_TRUE_RETURN(lines.size() == 0)
    mapPath = lines[0];
    for (int i = 1; i < lines.size(); ++i) {
      if (lines[i] == "") {
        continue;
      }
      Split(lines[i], ",", currLine);
      CALL_IF_TRUE_RETURN(currLine.size() != 4)
      tasks.push_back(std::make_pair(
          Point(atoi(currLine[0].c_str()), atoi(currLine[1].c_str())),
          Point(atoi(currLine[2].c_str()), atoi(currLine[3].c_str()))));
    }
    return 0;
  }
  std::string to_string() const {
    std::ostringstream oss{};
    oss << mapPath << "\n";
    for (auto& item : tasks) {
      oss << item.first.to_string() << "\t" << item.second.to_string() << "\n";
    }
    return oss.str();
  }
  void clear() {
    mapPath = "";
    tasks.clear();
  }
};
struct PathFindResult {
  std::pair<Point, Point> task{};
  std::vector<Point> result{};
  int ret{};
  long time{};
  std::string to_string() const {
    std::ostringstream oss{};
    oss << "task " << task.first.to_string() << "\t" << task.second.to_string()
        << "\tret:" << ret << "\ttime(usec微秒):" << time;
    oss << "\t" << VecLikeToString(result) << "\n";
    return oss.str();
  }
  friend std::ostream& operator<<(std::ostream& os,
                                  const PathFindResult& item) {
    os << item.to_string();
    return os;
  }
};