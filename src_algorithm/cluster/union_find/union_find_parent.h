/************************************************
 * @author khalidzhang
 * @email khalidzhang@tencent.com
 * @desc
 * @time 2021/3/2
 * @file union_find.h
 * @version
 * version        author            desc
 * 1.0            khalidzhang       create
 ************************************************/

#pragma once

namespace UnionFind {
// parent 优化
class UnionFindParent {
  public:
  int *m_parent{};
  int m_count{};

  UnionFindParent(int n) : m_count(n) { init(n); }
  UnionFindParent() = default;
  void init(int n) {
    m_count = n;
    m_parent = new int[m_count];
    for (int i = 0; i < m_count; ++i) {
      // 初始化, 每一个parent[i]指向自己, 表示每一个元素自己自成一个集合
      m_parent[i] = i;
    }
  }
  int find(int p) {
    assert(p >= 0 && p < m_count);
    // 不断去查询自己的父亲节点, 直到到达根节点
    // 根节点的特点: parent[p] == p
    while (p != m_parent[p]) {
      p = m_parent[p];
    }
    return p;
  }
  bool is_connected(int p, int q) { return find(p) == find(q); }
  /**
   * 合并元素p和元素q所属的集合
   * @param p
   * @param q
   */
  void union_elements(int p, int q) {
    int p_root = find(p);
    int q_root = find(q);
    if (p_root == q_root) {
      return;
    }
    m_parent[p_root] = q_root;
  }
};
}  // namespace UnionFind