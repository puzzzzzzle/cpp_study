//
// Created by khalidzhang on 2023/9/18.
//
#include "CommonClass.h"
#include "book_actor.h"
using namespace generated_test;
TEST(book_actor, create) {
  BookActor ba{};
  LOG_DEBUG("inited at " << &ba)
}