//
// Created by tao on 19-2-26.
//

#include "stl_common_containor.h"

#include <algorithm>
#include <deque>
#include <list>
#include <vector>

#include "common_includes.h"
#define INFO(msg) LOG_DEBUG(msg)
TEST(iterator_test, deque) {
  std::deque<int> i_ints{};
  std::ostringstream output{};
  for (int i = 0; i < 10; i++) {
    i_ints.push_front(i);
    i_ints.push_back(i);
  }

  std::copy(i_ints.cbegin(), i_ints.cend(),
            std::ostream_iterator<int>(output, "\t"));

  INFO("get :" << output.str())
  output.str("");
  for (std::deque<int>::const_iterator it = i_ints.cbegin();
       it != i_ints.cend(); ++it) {
    output << *it << "\t";
  }
  INFO("get by iterator:\t" << output.str())

  auto mini = std::min_element(i_ints.cbegin(), i_ints.cend());
  INFO("mini:\t" << *mini)
  EXPECT_EQ(*mini, 0);

  auto max = std::max_element(i_ints.cbegin(), i_ints.cend());
  INFO("max:\t" << *max)
  EXPECT_EQ(*max, 9);

  std::sort(i_ints.begin(), i_ints.end());
  output.str("");
  std::copy(i_ints.cbegin(), i_ints.cend(),
            std::ostream_iterator<int>(output, "\t"));
  INFO("after sorted:\t" << output.str())

  auto pos3 = std::find(i_ints.begin(), i_ints.end(), 3);
  std::reverse(pos3, i_ints.end());
  output.str("");
  std::copy(i_ints.cbegin(), i_ints.cend(),
            std::ostream_iterator<int>(output, "\t"));
  INFO("after reverse:\t" << output.str())

  std::deque<int> copyed{};
  auto pos8 = std::find(i_ints.cbegin(), i_ints.cend(), 8);
  std::copy(pos8, i_ints.cend(), std::back_inserter(copyed));
  std::sort(copyed.begin(), copyed.end(),
            [](const int &l, const int &r) { return l < r; });
  output.str("");
  std::copy(copyed.cbegin(), copyed.cend(),
            std::ostream_iterator<int>(output, "\t"));
  INFO("copyed after reverse:\t" << output.str())
  std::sort(copyed.begin(), copyed.end(), std::greater<int>());
  output.str("");
  std::copy(copyed.cbegin(), copyed.cend(),
            std::ostream_iterator<int>(output, "\t"));
  INFO("copyed after reverse:\t" << output.str())

  std::deque<int> muti{};
  std::transform(
      copyed.cbegin(), copyed.cend(), i_ints.cbegin(), std::back_inserter(muti),
      std::bind(
          std::multiplies<int>(), std::placeholders::_1,
          std::placeholders::_2)  //都行
                                  //                   std::multiplies<int>()
  );
  output.str("");
  std::copy(muti.cbegin(), muti.cend(),
            std::ostream_iterator<int>(output, "\t"));
  INFO("muti :\t" << output.str())
}