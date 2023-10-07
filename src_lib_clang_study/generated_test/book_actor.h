//
// Created by khalidzhang on 2023/9/18.
//
#pragma once
#include <string>

#include "book_actor.generated.h"

namespace generated_test {
namespace nn {
CH_CLASS()
class BookActor {
  CH_GENERATED()
  CH_PROPERTY(ALIAS = "prize", )
  double prize_{};

  CH_PROPERTY(ALIAS = "pageNum", )
  int page_num_{};

  // same as defined in one macro
  CH_PROPERTY(NO_GETTER, ALIAS = "useless", )
  // comment is ok
  // empty is ok
  CH_PROPERTY()
  CH_PROPERTY(NO_SETTER)
  int useless_{};

  CH_PROPERTY()
  std::string name_{};
  inline void BookActor_print() {}
};
}  // namespace nn
}  // namespace generated_test
