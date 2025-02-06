#include "common_includes.h"
#include "entt/entt.hpp"

TEST(ecs_test, 1) {

  entt::registry registry;

  // 创建一个实体
  auto entity = registry.create();

  // 添加一个组件
  registry.emplace<int>(entity, 42);

  // 获取并打印组件
  auto& value = registry.get<int>(entity);
  std::cout << "Entity has component with value: " << value << std::endl;

}

int main(int argc, char **argv) {
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}