//
// Created by khalidzhang on 2023/9/18.
//
#include "book_actor.h"

#include "CommonClass.h"
using namespace generated_test::nn;
TEST(book_actor, create) {
  BookActor ba{};
  ba.set_pageNum(1000);
  LOG_DEBUG("inited at " << ba.get_pageNum())
}