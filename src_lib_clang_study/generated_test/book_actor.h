//
// Created by khalidzhang on 2023/9/18.
//
#pragma once
#include "book_actor.generated.h"

namespace generated_test {

CH_CLASS()
class BookActor {
  CH_GENERATED()
  public:
  CH_PROPERTY()
  CH_PROPERTY()
  CH_PROPERTY()
  double prize_{};
  CH_PROPERTY(NO_GETTER, NO_SETTER, ALIAS = "pageNum", )
  int page_num_{};
  inline void BookActor_print() {}
};

}  // namespace generated_test
