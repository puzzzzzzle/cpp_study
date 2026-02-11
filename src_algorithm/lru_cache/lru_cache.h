/************************************************
 * @author puzzzzzzle
 * @email 2359173906@qq.com
 * @desc LRU Cache — O(1) get/put using hash map + doubly linked list.
 * @time 2026/2/11
 * @file lru_cache.h
 * @version
 * version        author            desc
 * 1.0            puzzzzzzle       create
 ************************************************/

#pragma once
#include <list>
#include <optional>
#include <stdexcept>
#include <unordered_map>
#include <vector>

namespace LruStudy {

/// LRU Cache: O(1) get / put，容量满时淘汰最久未使用的条目
template <typename Key, typename Value>
class LruCache {
 public:
  using KeyValue = std::pair<Key, Value>;
  using ListIter = typename std::list<KeyValue>::iterator;

  explicit LruCache(std::size_t capacity) : m_capacity(capacity) {
    if (capacity == 0) {
      throw std::invalid_argument("LruCache capacity must be > 0");
    }
  }

  /// 查询 key，命中则移到最前并返回值；未命中返回 std::nullopt
  std::optional<Value> get(const Key& key) {
    auto it = m_map.find(key);
    if (it == m_map.end()) {
      return std::nullopt;
    }
    // 移到链表头部（最近使用）
    m_list.splice(m_list.begin(), m_list, it->second);
    return it->second->second;
  }

  /// 插入/更新 key-value，容量满时淘汰尾部（最久未使用）
  void put(const Key& key, const Value& value) {
    auto it = m_map.find(key);
    if (it != m_map.end()) {
      // 已存在：更新值并移到头部
      it->second->second = value;
      m_list.splice(m_list.begin(), m_list, it->second);
      return;
    }
    // 不存在：需要插入
    if (m_map.size() >= m_capacity) {
      // 淘汰尾部
      auto& back = m_list.back();
      m_map.erase(back.first);
      m_list.pop_back();
    }
    m_list.emplace_front(key, value);
    m_map[key] = m_list.begin();
  }

  /// 删除 key，返回是否成功
  bool erase(const Key& key) {
    auto it = m_map.find(key);
    if (it == m_map.end()) {
      return false;
    }
    m_list.erase(it->second);
    m_map.erase(it);
    return true;
  }

  /// 是否包含 key（不改变访问顺序）
  bool contains(const Key& key) const { return m_map.count(key) > 0; }

  std::size_t size() const { return m_map.size(); }
  std::size_t capacity() const { return m_capacity; }
  bool empty() const { return m_map.empty(); }

  /// 按从最近到最久的顺序返回所有 key（用于测试/调试）
  std::vector<Key> keys() const {
    std::vector<Key> result;
    result.reserve(m_list.size());
    for (auto& kv : m_list) {
      result.push_back(kv.first);
    }
    return result;
  }

 private:
  std::size_t m_capacity;
  std::list<KeyValue> m_list;                       // 双向链表，头部=最近使用
  std::unordered_map<Key, ListIter> m_map;           // key -> 链表迭代器
};

}  // namespace LruStudy
