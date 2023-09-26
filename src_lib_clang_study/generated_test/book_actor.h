//
// Created by khalidzhang on 2023/9/18.
//
#pragma once
// #include <string>

#include "book_actor.generated.h"

namespace generated_test {

CH_CLASS()
class BookActor {
  CH_GENERATED()
  public:
  CH_PRIORITY()
  double prize_{};
  CH_PRIORITY()
  int page_num_{};
};

}  // namespace generated_test
