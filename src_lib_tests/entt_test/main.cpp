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
  FLOG_INFO("Entity has component with value: {}", value)
}

TEST(ecs_test, 2)
{
  entt::registry registry;

  // id
  // 位置组件
  struct Position {
    float x, y;
  };
  // 血量组件
  struct Health {
    int value;
  };
  // 颜色
  struct Color {
    int r, g, b;
  };

  // 创建10个实体
  for (int i : std::views::iota(0, 10))
  {
    // 创建一个实体
    auto entity = registry.create();
    // 添加一个组件
    registry.emplace<Position>(entity, rand()%100, rand()%100);
    registry.emplace<Health>(entity, 100);
    if(rand()%2 == 0)
    {
      registry.emplace<Color>(entity, rand()%255, rand()%255, rand()%255);
    }
  }

  // 打印
  FLOG_INFO("before update:")
  registry.view<Position, Health>().each([](auto entity, auto& position, auto& health) {
    FLOG_INFO("Entity has position: ({}, {}), health: {}", position.x, position.y, health.value);
  });
  registry.view<Position,Health,Color>().each([](auto entity, auto& position, auto& health, auto& color) {
    FLOG_INFO("Entity has position: ({}, {}), health: {}, color: ({}, {}, {})", position.x, position.y, health.value, color.r, color.g, color.b);
  });

  // 更新位置
  registry.view<Position>().each([](auto entity, auto& position) {
    position.x += 1.0f;
    position.y += 1.0f;
  });

  // 更新血量
  registry.view<Health>().each([](auto entity, auto& health) {
    health.value -= 1;
  });

  // 打印
  FLOG_INFO("after update:")
  registry.view<Position, Health>().each([](auto entity, auto& position, auto& health) {
    FLOG_INFO("Entity has position: ({}, {}), health: {}", position.x, position.y, health.value);
  });

}
int main(int argc, char** argv) {
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}