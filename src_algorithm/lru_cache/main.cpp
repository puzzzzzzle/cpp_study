#include "common_includes.h"

#include "lru_cache.h"

using namespace LruStudy;

// ============================================================
// 基本功能
// ============================================================

TEST(LruBasic, put_and_get) {
  LruCache<int, std::string> cache(3);
  cache.put(1, "one");
  cache.put(2, "two");
  cache.put(3, "three");

  EXPECT_EQ(cache.size(), 3u);
  EXPECT_EQ(cache.get(1).value(), "one");
  EXPECT_EQ(cache.get(2).value(), "two");
  EXPECT_EQ(cache.get(3).value(), "three");
}

TEST(LruBasic, get_miss) {
  LruCache<int, int> cache(2);
  cache.put(1, 100);
  EXPECT_FALSE(cache.get(99).has_value());
}

TEST(LruBasic, update_existing_key) {
  LruCache<int, std::string> cache(2);
  cache.put(1, "old");
  cache.put(1, "new");

  EXPECT_EQ(cache.size(), 1u);
  EXPECT_EQ(cache.get(1).value(), "new");
}

TEST(LruBasic, zero_capacity_throws) {
  using IntCache = LruCache<int, int>;
  EXPECT_THROW(IntCache(0), std::invalid_argument);
}

// ============================================================
// 淘汰策略
// ============================================================

TEST(LruEviction, evicts_least_recently_used) {
  LruCache<int, int> cache(3);
  cache.put(1, 10);
  cache.put(2, 20);
  cache.put(3, 30);
  // 此时顺序: 3(最近) -> 2 -> 1(最久)

  // 插入第4个，应淘汰 key=1
  cache.put(4, 40);
  EXPECT_EQ(cache.size(), 3u);
  EXPECT_FALSE(cache.get(1).has_value());
  EXPECT_TRUE(cache.get(2).has_value());
  EXPECT_TRUE(cache.get(3).has_value());
  EXPECT_TRUE(cache.get(4).has_value());
}

TEST(LruEviction, get_refreshes_order) {
  LruCache<int, int> cache(3);
  cache.put(1, 10);
  cache.put(2, 20);
  cache.put(3, 30);

  // 访问 key=1，使其变为最近使用
  cache.get(1);
  // 顺序: 1(最近) -> 3 -> 2(最久)

  // 插入第4个，应淘汰 key=2
  cache.put(4, 40);
  EXPECT_FALSE(cache.get(2).has_value());
  EXPECT_TRUE(cache.get(1).has_value());
}

TEST(LruEviction, put_refreshes_order) {
  LruCache<int, int> cache(3);
  cache.put(1, 10);
  cache.put(2, 20);
  cache.put(3, 30);

  // 更新 key=1 的值，使其变为最近使用
  cache.put(1, 999);
  // 顺序: 1(最近) -> 3 -> 2(最久)

  cache.put(4, 40);
  EXPECT_FALSE(cache.get(2).has_value());
  EXPECT_EQ(cache.get(1).value(), 999);
}

TEST(LruEviction, capacity_one) {
  LruCache<int, int> cache(1);
  cache.put(1, 10);
  EXPECT_EQ(cache.get(1).value(), 10);

  cache.put(2, 20);
  EXPECT_FALSE(cache.get(1).has_value());
  EXPECT_EQ(cache.get(2).value(), 20);
}

// ============================================================
// 删除
// ============================================================

TEST(LruErase, erase_existing) {
  LruCache<int, int> cache(3);
  cache.put(1, 10);
  cache.put(2, 20);

  EXPECT_TRUE(cache.erase(1));
  EXPECT_EQ(cache.size(), 1u);
  EXPECT_FALSE(cache.get(1).has_value());
}

TEST(LruErase, erase_nonexistent) {
  LruCache<int, int> cache(3);
  cache.put(1, 10);
  EXPECT_FALSE(cache.erase(99));
  EXPECT_EQ(cache.size(), 1u);
}

TEST(LruErase, erase_then_insert_no_ghost) {
  LruCache<int, int> cache(2);
  cache.put(1, 10);
  cache.put(2, 20);
  cache.erase(1);

  // 删除后腾出空间，新插入不应淘汰 key=2
  cache.put(3, 30);
  EXPECT_EQ(cache.size(), 2u);
  EXPECT_TRUE(cache.get(2).has_value());
  EXPECT_TRUE(cache.get(3).has_value());
}

// ============================================================
// 内部顺序检查 (keys() 从最近到最久)
// ============================================================

TEST(LruOrder, keys_order) {
  LruCache<int, int> cache(4);
  cache.put(1, 0);
  cache.put(2, 0);
  cache.put(3, 0);
  cache.put(4, 0);
  // 顺序: 4 3 2 1

  cache.get(2);
  // 顺序: 2 4 3 1

  cache.put(3, 99);
  // 顺序: 3 2 4 1

  auto k = cache.keys();
  ASSERT_EQ(k.size(), 4u);
  EXPECT_EQ(k[0], 3);
  EXPECT_EQ(k[1], 2);
  EXPECT_EQ(k[2], 4);
  EXPECT_EQ(k[3], 1);
}

// ============================================================
// contains (不改变顺序)
// ============================================================

TEST(LruContains, does_not_change_order) {
  LruCache<int, int> cache(3);
  cache.put(1, 0);
  cache.put(2, 0);
  cache.put(3, 0);
  // 顺序: 3 2 1

  EXPECT_TRUE(cache.contains(1));
  // 顺序不变: 3 2 1

  cache.put(4, 0);
  // 应淘汰 key=1（仍是最久未使用，contains 不刷新）
  EXPECT_FALSE(cache.get(1).has_value());
}

// ============================================================
// string key
// ============================================================

TEST(LruStringKey, string_keys_work) {
  LruCache<std::string, int> cache(2);
  cache.put("hello", 1);
  cache.put("world", 2);
  EXPECT_EQ(cache.get("hello").value(), 1);

  cache.put("foo", 3);
  // "world" 被淘汰（hello 刚被 get 刷新了）
  EXPECT_FALSE(cache.get("world").has_value());
  EXPECT_TRUE(cache.get("foo").has_value());
}

// ============================================================
// 压力测试
// ============================================================

TEST(LruStress, sequential_eviction) {
  const int CAP = 1000;
  LruCache<int, int> cache(CAP);

  // 插入 0 ~ 1999，前 1000 个应被逐步淘汰
  for (int i = 0; i < 2000; ++i) {
    cache.put(i, i * 10);
  }
  EXPECT_EQ(cache.size(), (std::size_t)CAP);

  for (int i = 0; i < 1000; ++i) {
    EXPECT_FALSE(cache.get(i).has_value()) << "key " << i << " should be evicted";
  }
  for (int i = 1000; i < 2000; ++i) {
    EXPECT_EQ(cache.get(i).value(), i * 10) << "key " << i << " should exist";
  }
}

TEST(LruStress, repeated_access_prevents_eviction) {
  LruCache<int, int> cache(100);
  // 先插入 key 0
  cache.put(0, 0);

  // 不断插入新 key，但每次都访问 key 0 保持活跃
  for (int i = 1; i <= 500; ++i) {
    cache.put(i, i);
    cache.get(0);
  }
  // key 0 始终存在
  EXPECT_TRUE(cache.get(0).has_value());
  EXPECT_EQ(cache.size(), 100u);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
