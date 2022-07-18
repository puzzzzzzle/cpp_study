//
// Created by tao on 19-1-17.
//
#include "CommonClass.h"
#include "boost/format.hpp"
#include "common_includes.h"
#include "nearest_to_broken_line.h"

void draw_fig(double x0, double y0, double x1, double y1, double x2,
              double y2) {
  auto foot_p = NearestToBrokenLine::get_foot_point(x0, y0, x1, y1, x2, y2);
  double len{}, near_x{}, near_y{};
  std::tie(len, near_x, near_y) =
      NearestToBrokenLine::get_nearest_to_segment(x0, y0, x1, y1, x2, y2);

  LOG_DEBUG(boost::format("%d,%d    %d,%d    %d,%d    %d,%d    %d,%d    ") %
            x0 % y0 % x1 % y1 % x2 % y2 % foot_p.first % foot_p.second %
            near_x % near_y)
}
void broken_line_test(
    double x0, double y0,
    const std::vector<std::pair<double, double>> &broken_line) {
  double len{}, near_x{}, near_y{};
  size_t index{};
  std::tie(len, near_x, near_y, index) =
      NearestToBrokenLine::get_nearest_to_broken_line(x0, y0, broken_line);
  std::ostringstream oss{};
  oss << boost::format("%d,%d    ") % x0 % y0;
  oss << "!    ";
  for (const auto &item : broken_line) {
    oss << boost::format("%d,%d    ") % item.first % item.second;
  }
  oss << "!    ";
  oss << index << "     ";
  oss << boost::format("%d,%d    ") % near_x % near_y;
  LOG_DEBUG(oss.str())
}

TEST(test_test, 1) {
  draw_fig(2, 0, 0, 0, 5, 5);
  draw_fig(2, 0, 0, 0, 5, 0);
  draw_fig(2, 0, 0, 0, 0, 5);
  draw_fig(2, 0, 0, 0, 0, 0);
  draw_fig(2, 3, 0, 0, 5, 3);
  draw_fig(-5, 1, 0, 0, 5, 3);
  draw_fig(-5, 1, 0, 0, 5, 0);
  draw_fig(-5, 1, 0, 4, 0, 5);

  broken_line_test(2, 3, {{0, 0}, {0, 5}, {5, 5}});
  broken_line_test(2, 3, {{10, 10}, {0, 5}, {5, 5}, {10, 10}});
  broken_line_test(10, 3, {{10, 10}, {0, 5}, {5, 5}, {10, 10}});
  broken_line_test(9, 4, {{10, 10}, {0, 5}, {5, 5}, {10, 10}, {10, 0}});
  broken_line_test(9, 3, {{10, 10}, {0, 5}, {5, 5}, {10, 10}, {10, 4}});

  /* matplotlib 中的输出:
[2021-06-15 17:15:18]	[DEBUG]	2,0   0,0    5,5 (1.0, 1.0) (1.0, 1.0)
["G:/projects/study_projects/algorithm_study/algorithm_python/src/nearest_to_broken_line/nearest_to_broken_line.py:112"]
[__main__] [2021-06-15 17:15:18]	[DEBUG]	2,0   0,0    5,0 (2.0, 0.0)
(2.0, 0.0)
["G:/projects/study_projects/algorithm_study/algorithm_python/src/nearest_to_broken_line/nearest_to_broken_line.py:112"]
[__main__] [2021-06-15 17:15:18]	[DEBUG]	2,0   0,0    0,5 (0.0, 0) (0, 0)
["G:/projects/study_projects/algorithm_study/algorithm_python/src/nearest_to_broken_line/nearest_to_broken_line.py:112"]
[__main__] [2021-06-15 17:15:18]	[DEBUG]	2,0   0,0    0,0 (0, 0) (0, 0)
["G:/projects/study_projects/algorithm_study/algorithm_python/src/nearest_to_broken_line/nearest_to_broken_line.py:112"]
[__main__] [2021-06-15 17:15:18]	[DEBUG]	2,3   0,0    5,3
(2.7941176470588234, 1.6764705882352942)
(2.7941176470588234, 1.6764705882352942)
["G:/projects/study_projects/algorithm_study/algorithm_python/src/nearest_to_broken_line/nearest_to_broken_line.py:112"]
[__main__] [2021-06-15 17:15:18]	[DEBUG]	-5,1   0,0    5,3
(-3.235294117647059, -1.9411764705882355) (0, 0)
["G:/projects/study_projects/algorithm_study/algorithm_python/src/nearest_to_broken_line/nearest_to_broken_line.py:112"]
[__main__] [2021-06-15 17:15:18]	[DEBUG]	-5,1   0,0    5,0 (-5.0, 0.0)
(0, 0)
["G:/projects/study_projects/algorithm_study/algorithm_python/src/nearest_to_broken_line/nearest_to_broken_line.py:112"]
[__main__] [2021-06-15 17:15:18]	[DEBUG]	-5,1   0,4    0,5 (0.0, 1) (0,
4)
["G:/projects/study_projects/algorithm_study/algorithm_python/src/nearest_to_broken_line/nearest_to_broken_line.py:112"]
[__main__] [2021-06-15 17:15:19]	[DEBUG]	2,3    [[0, 0], [0, 5], [5, 5]]
(0.0, 3)
["G:/projects/study_projects/algorithm_study/algorithm_python/src/nearest_to_broken_line/nearest_to_broken_line.py:133"]
[__main__] [2021-06-15 17:15:19]	[DEBUG]	2,3    [[10, 10], [0, 5], [5,
5], [10, 10]] (2.0, 5.0)
["G:/projects/study_projects/algorithm_study/algorithm_python/src/nearest_to_broken_line/nearest_to_broken_line.py:133"]
[__main__] [2021-06-15 17:15:19]	[DEBUG]	10,3    [[10, 10], [0, 5], [5,
5], [10, 10]] (6.5, 6.5)
["G:/projects/study_projects/algorithm_study/algorithm_python/src/nearest_to_broken_line/nearest_to_broken_line.py:133"]
[__main__] [2021-06-15 17:15:19]	[DEBUG]	9,4    [[10, 10], [0, 5], [5,
5], [10, 10], [10, 0]] (10.0, 4)
["G:/projects/study_projects/algorithm_study/algorithm_python/src/nearest_to_broken_line/nearest_to_broken_line.py:133"]
[__main__] [2021-06-15 17:15:19]	[DEBUG]	9,3    [[10, 10], [0, 5], [5,
5], [10, 10], [10, 4]] (10, 4)
["G:/projects/study_projects/algorithm_study/algorithm_python/src/nearest_to_broken_line/nearest_to_broken_line.py:133"]
[__main__]
 */
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