# 寻路
- 单文件实现
- 算法仅包含std依赖
- 跨平台
# 接口
## 寻路接口
```
template <class PathDataWrapper, class PointT>
class XXXX {
  using PathData = PathDataWrapper;
  using Point = PointT;
  using CPoint = const Point;
  public:
  XXXX(CPoint& start, CPoint& end, const PathData* const data)
  int searching()
  std::vector<Point> extract_path() 
};
```

## 适配器格式(可用默认的)
```
struct PathDataWrapper
{
    int m_xLen{}, m_yLen{};
    bool check(int x, int y) const
};
struct PointT
{
    int x = 0;
    int y = 0;
    PointT() = default;
    PointT(int _x, int _y) : x(_x), y(_y) {}
    friend bool operator<(const CPosition& lhs, const CPosition& rhs)
    friend bool operator==(const CPosition& lhs, const CPosition& rhs)
};
```