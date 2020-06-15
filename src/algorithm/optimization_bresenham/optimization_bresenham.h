//
// Created by khalidzhang on 2020/6/10.
//

#ifndef CPP_STUDY_ALL_OPTIMIZATION_BRESENHAM_H
#define CPP_STUDY_ALL_OPTIMIZATION_BRESENHAM_H
#define POINT(y, x) printf(R"({"x":%d,"y":%d})", (x), (y))
#define PI_ 3.141592653589793
;
//  算法参考  http://eugen.dedu.free.fr/projects/bresenham/
void useVisionLine(int x1, int y1, int x2, int y2,
                   std::function<void(int y, int x)> v) {
  int i;               // loop counter
  int ystep, xstep;    // the step on y and x axis
  int error;           // the error accumulated during the increment
  int errorprev;       // *vision the previous value of the error variable
  int y = y1, x = x1;  // the line points
  int ddy, ddx;        // compulsory variables: the double values of dy and dx
  int dx = x2 - x1;
  int dy = y2 - y1;
  v(y1, x1);  // first point
  // NB the last point can't be here, because of its previous point (which has
  // to be verified)
  if (dy < 0) {
    ystep = -1;
    dy = -dy;
  } else
    ystep = 1;
  if (dx < 0) {
    xstep = -1;
    dx = -dx;
  } else
    xstep = 1;
  ddy = 2 * dy;  // work with double values for full precision
  ddx = 2 * dx;
  if (ddx >= ddy) {  // first octant (0 <= slope <= 1)
    // compulsory initialization (even for errorprev, needed when dx==dy)
    errorprev = error = dx;     // start in the middle of the square
    for (i = 0; i < dx; i++) {  // do not use the first point (already done)
      x += xstep;
      error += ddy;
      if (error > ddx) {  // increment y if AFTER the middle ( > )
        y += ystep;
        error -= ddx;
        // three cases (octant == right->right-top for directions below):
        if (error + errorprev < ddx)  // bottom square also
        {
          v(y - ystep, x);
        } else if (error + errorprev > ddx)  // left square also
        {
          v(y, x - xstep);
        } else {  // corner: bottom and left squares also
          v(y - ystep, x);
          v(y, x - xstep);
        }
      }
      v(y, x);
      errorprev = error;
    }
  } else {  // the same as above
    errorprev = error = dy;
    for (i = 0; i < dy; i++) {
      y += ystep;
      error += ddx;
      if (error > ddy) {
        x += xstep;
        error -= ddy;
        if (error + errorprev < ddy) {
          v(y, x - xstep);
        } else if (error + errorprev > ddy) {
          v(y - ystep, x);

        } else {
          v(y, x - xstep);
          v(y - ystep, x);
        }
      }
      v(y, x);
      errorprev = error;
    }
  }
  // assert ((y == y2) && (x == x2));  // the last point (y2,x2) has to be the
  // same with the last point of the algorithm
}
struct CPosition {
  int x = 0;
  int y = 0;

  CPosition(int _x, int _y) {
    x = _x;
    y = _y;
  }
  friend bool operator<(const CPosition& lhs, const CPosition& rhs) {
    return lhs.x < rhs.x && lhs.y < rhs.y;
  }
  friend bool operator==(const CPosition& lhs, const CPosition& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
  }
};

//------------------------------------------------------------------------------
//  功能:  根据圆弧的圆心, 起点, 终点, 和包含端点在内的n个点将圆弧分为n-1份,
//  输出n个点 说明:  接收输出的n个点的数组 Dots[n]的大小由参数count确定, 说明:
//  Dots_x[0]: 起点x坐标, Dots_x[n-1]: 终点x坐标
//------------------------------------------------------------------------------
bool CalcArcPart(double center_x,  // 圆弧的圆心
                 double center_y,  // 圆弧的圆心
                 double Begin_x,   // 起点
                 double Begin_y,   // 起点
                 double End_x,     // 终点
                 double End_y,     // 终点
                 double Radii,     // 半径
                 int ccw,  // 圆弧旋转方向, 顺时针为-1, 逆时针为1
                 int count,  // 点数量, 包含2个端点在内
                 double Dots_x[],  // 接收输出的n个点x坐标的数组 Dots_x[n]的地址
                 double Dots_y[])  // 接收输出的n个点y坐标的数组 Dots_y[n]的地址
{
  if (count <= 1)  // 包含端点在内, 至少2个点
    return false;
  double vCenterBegin_x = Begin_x - center_x;  // 圆心与起点连线矢量
  double vCenterBegin_y = Begin_y - center_y;  // 圆心与起点连线矢量
  double vCenterEnd_x = End_x - center_x;      // 圆心与终点连线矢量
  double vCenterEnd_y = End_y - center_y;      // 圆心与终点连线矢量
  double Length_Begin =
      sqrt(vCenterBegin_x * vCenterBegin_x + vCenterBegin_y * vCenterBegin_y);
  double Length_End =
      sqrt(vCenterEnd_x * vCenterEnd_x + vCenterEnd_y * vCenterEnd_y);

  vCenterBegin_x = vCenterBegin_x * Radii / Length_Begin;  // 改变模长
  vCenterBegin_y = vCenterBegin_y * Radii / Length_Begin;  // 改变模长
  vCenterEnd_x = vCenterEnd_x * Radii / Length_End;        // 改变模长
  vCenterEnd_y = vCenterEnd_y * Radii / Length_End;        // 改变模长

  double angle;  // 要求的弧度
  double sinangleY =
      vCenterBegin_x * vCenterEnd_y -
      vCenterBegin_y *
          vCenterEnd_x;  // 差乘得sin<a, 乘m_ccw后的到需要的角的sin, 左右对称,
                         // asin弧度范围在 -PI/2 ~ PI/2之间
  double sinangleX =
      vCenterBegin_x * vCenterEnd_x +
      vCenterBegin_y *
          vCenterEnd_y;  // 点乘得cos<a, 乘m_ccw后的到需要的角的cos, 上下对称,
                         // acos弧度范围在 0 ~ PI之间
  if (sinangleY == 0.0 && sinangleX == 0.0)  // 起点在圆心处
    angle = 0.0;                             // 起点弧度
  else                                       // 起点不在圆心处
  {
    angle = atan2(sinangleY,
                  sinangleX);  // [ radianBegin: 起点与圆心连线和x轴的角的弧度
                               // ][ atan2(y,x): 计算y/x的反正切值,
                               // 按照参数的符号计算所在的象限, atan2弧度范围在
                               // -PI ~ PI之间 ]
    if (angle < 0.0)
      angle =
          angle + 2.0 * PI_;  // 弧度范围控制在0 ~ 2*PI之间, 对应角度为0 ~ 360 .
                              // 此处只能用atan2, 不能仅用asin或仅用acos

    if (-1 == ccw) angle = 2.0 * PI_ - angle;  // 取另一边
  }

  double theta =
      angle /
      (double)(count -
               1);  // 要求的点与圆心连线矢量和圆心与起点连线矢量的角的弧度,
                    // 每一小段弧长弧度

  for (int i = 0; i < count; i++) {
    // 得到相对圆心的位置, 用圆心与起点连线矢量来旋转, ccw为1时逆时针旋转,
    // 为－1时正时针旋转
    Dots_x[i] = vCenterBegin_x * cos((double)ccw * theta * (double)i) -
                vCenterBegin_y * sin((double)ccw * theta * (double)i);
    Dots_y[i] = vCenterBegin_x * sin((double)ccw * theta * (double)i) +
                vCenterBegin_y * cos((double)ccw * theta * (double)i);
    Dots_x[i] += center_x;  // 得到相对原点的位置
    Dots_y[i] += center_y;  // 得到相对原点的位置
  }
  return true;
}
struct RealPoint {
  public:
  double m_x = 0;
  double m_y = 0;
  RealPoint() = default;
  RealPoint(double _x, double _y) {
    m_x = _x;
    m_y = _y;
  }
  double x() const { return m_x; }
  double y() const { return m_y; }
};
static void CalcArcPart(const RealPoint& circleCenter,
                        const RealPoint& start, const RealPoint& end,
                        double r, int count,
                        const std::function<void(double x, double y)>& v) {
  assert(count > 1);
  // 圆心与起点连线矢量
  double centerToBeginVectorX = start.x() - circleCenter.x();
  double centerToBeginVectorY = start.y() - circleCenter.y();
  // 圆心与终点连线矢量
  double centerToEndVectorX = end.x() - circleCenter.x();
  double centerToEndVectorY = end.y() - circleCenter.y();
  double lenBegin = sqrt(centerToBeginVectorX * centerToBeginVectorX +
                         centerToBeginVectorY * centerToBeginVectorY);
  double lenEnd = sqrt(centerToEndVectorX * centerToEndVectorX +
                       centerToEndVectorY * centerToEndVectorY);
  // 改变模长, 得到单位矢量
  centerToBeginVectorX = centerToBeginVectorX * r / lenBegin;
  centerToBeginVectorY = centerToBeginVectorY * r / lenBegin;
  centerToEndVectorX = centerToEndVectorX * r / lenEnd;
  centerToEndVectorY = centerToEndVectorY * r / lenEnd;
  // 计算角度
  // 起点与X轴正方向的夹角 [-pi ~ pi]
  double startAngle = atan2(centerToBeginVectorY, centerToBeginVectorX);
  // 终点与X轴正方向的夹角 [-pi ~ pi]
  double endAngle = atan2(centerToEndVectorY, centerToEndVectorX);
  // 总体角度
  double totalAngle = endAngle - startAngle;
  // 寻找劣弧方向
  // 要求的点与圆心连线矢量和圆心与起点连线矢量的角的弧度, 每一小段弧长弧度
  double theta{};

  if (abs(totalAngle) > PI_) {
    //            totalAngle = 2 * PI_ - totalAngle;
    int direction = totalAngle > 0 ? -1 : 1;
    totalAngle = 2 * PI_ - abs(totalAngle);
    count = ceil(abs(totalAngle) * count / (2 * PI_));
    theta = direction * totalAngle / (double)(count - 1);
  } else {
    count = ceil(abs(totalAngle) * count / (2 * PI_));
    theta = totalAngle / (double)(count - 1);
  }
  for (int i = 0; i < count; i++) {
    // 得到相对圆心的位置, 用圆心与起点连线矢量来旋转
    // 得到一个采样点
    double sampleX = centerToBeginVectorX * cos(theta * (double)i) -
                     centerToBeginVectorY * sin(theta * (double)i);
    double sampleY = centerToBeginVectorX * sin(theta * (double)i) +
                     centerToBeginVectorY * cos(theta * (double)i);
    // 得到相对原点的位置
    sampleX += circleCenter.x();
    sampleY += circleCenter.y();
    v(sampleX, sampleY);
  }
}
#endif  // CPP_STUDY_ALL_OPTIMIZATION_BRESENHAM_H
