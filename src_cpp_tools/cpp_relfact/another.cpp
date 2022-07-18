//
// Created by khalidzhang on 2021/12/23.
//
#include "class_def.h"
#include "common_includes.h"


TEST(another, 1) {
  // 使用的地方只有基类的情况
  {
    auto* ptr = (Base*)CppObjectFactory::getInstance().getClassByName("Sub");
    EXPECT_EQ(ptr->Name(), "Sub");
  }

  // 使用的地方同时有子类的情况
  {
    auto ptr = REFLACT(Sub);
    EXPECT_EQ(ptr->Name(), "Sub");
  }

  // 获取所有 类 和它的创建函数
  {
    for (const auto& item :
         CppObjectFactory::getInstance().getAllReflection()) {
      LOG_DEBUG("get ont creator "
                << item.first << "  func ptr address :" << (size_t)item.second)
    }
  }
}