/************************************************
 * @author puzzzzzzle
 * @email 2359173906@qq.com
 * @desc
 * @time 2021/6/15
 * @file nearest_to_broken_line.h
 * @version
 * version        author            desc
 * 1.0            puzzzzzzle       create
 ************************************************/

#pragma once
#include <climits>
#include <cmath>

class NearestToBrokenLine {
  public:
  /**
   * 求垂足
   * Ax+By+C=0
   * @return
   */
  static std::pair<double, double> get_foot_point(double x0, double y0,
                                                  double x1, double y1,
                                                  double x2, double y2) {
    double A = y2 - y1;
    double B = x1 - x2;
    if (A == 0 && B == 0) {
      return {x1, y1};
    }
    double C = x2 * y1 - x1 * y2;
    double D = A * y0 - B * x0;
    double xd = -(B * D + A * C) / (B * B + A * A);
    double yd{};
    if (B == 0) {
      yd = y0;
    } else {
      yd = -(A * xd + C) / B;
    }
    return {xd, yd};
  }
  /**
   * 两点间距离
   * @return
   */
  static double get_line_len(double x1, double y1, double x2, double y2) {
    return std::sqrt(std::pow((x1 - x2), 2) + std::pow((y1 - y2), 2));
  }
  /**
    点是否在线段上
    如果想判断一个点是否在线段上,那么要满足以下两个条件:
    (Q - P1) * (P2 - P1)= 0
    Q在以P1, P2为对角顶点的矩形内
   * @return
   */
  static bool on_segment(double x0, double y0, double x1, double y1, double x2,
                         double y2) {
    return CompareDouble((x0 - x1) * (y2 - y1), (x2 - x1) * (y0 - y1)) == 0 &&
           CompareDouble(std::min(x1, x2), x0) <= 0 &&
           CompareDouble(x0, std::max(x1, x2)) <= 0 &&
           CompareDouble(std::min(y1, y2), y0) <= 0 &&
           CompareDouble(y0, std::max(y1, y2)) <= 0;
  }
  /**
   *     求 点 与线段的最近点
   * @return
   */
  static std::tuple<double, double, double> get_nearest_to_segment(
      double x0, double y0, double x1, double y1, double x2, double y2) {
    // 求垂足
    double xf{}, yf{};
    std::tie(xf, yf) = get_foot_point(x0, y0, x1, y1, x2, y2);

    // 判断 端点 与 垂足的距离哪个近
    double curr_len = std::numeric_limits<double>::max();
    std::pair<double, double> pos{0, 0};
    auto check = [&](double inx, double iny) {
      double temp_len = get_line_len(x0, y0, inx, iny);
      if (temp_len < curr_len) {
        pos = {inx, iny};
        curr_len = temp_len;
      }
    };
    check(x1, y1);
    check(x2, y2);
    if (on_segment(xf, yf, x1, y1, x2, y2)) {
      check(xf, yf);
    }
    return std::make_tuple(curr_len, pos.first, pos.second);
  }
  static std::tuple<double, double, double, size_t> get_nearest_to_broken_line(
      double x0, double y0,
      const std::vector<std::pair<double, double>>& broken_line) {
    if (broken_line.size() < 2) {
      return std::make_tuple(-1, 0, 0, 0);
    }
    double curr_len = std::numeric_limits<double>::max();
    double near_x{}, near_y{};
    size_t curr_index{};
    for (size_t i = 0; i < broken_line.size() - 1; ++i) {
      const auto& curr_pos = broken_line[i];
      const auto& next_pos = broken_line[i + 1];
      double temp_len{}, temp_near_x{}, temp_near_y{};
      std::tie(temp_len, temp_near_x, temp_near_y) =
          get_nearest_to_segment(x0, y0, curr_pos.first, curr_pos.second,
                                 next_pos.first, next_pos.second);
      if (temp_len < curr_len) {
        curr_len = temp_len;
        near_x = temp_near_x;
        near_y = temp_near_y;
        curr_index = i;
      }
    }
    return std::make_tuple(curr_len, near_x, near_y, curr_index);
  }
};