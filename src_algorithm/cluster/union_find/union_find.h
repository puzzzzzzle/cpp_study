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
// 遍历版本的实现
class UnionFind {
  private:
  int *m_id{};
  int m_count{};

  public:
  UnionFind(int n) : m_count(n) { init(n); }
  UnionFind() = default;
  void init(int n) {
    m_count = n;
    m_id = new int[m_count];
    for (int i = 0; i < m_count; ++i) {
      // 初始化, 每一个id[i]指向自己, 没有合并的元素
      m_id[i] = i;
    }
  }

  public:
  int find(int p) {
    assert(p >= 0 && p < m_count);
    return m_id[p];
  }
  bool is_connected(int p, int q) { return find(p) == find(q); }
  /**
   * 合并元素p和元素q所属的集合
   * @param p
   * @param q
   */
  void union_elements(int p, int q) {
    int p_id = find(p);
    int q_id = find(q);
    if (p_id == q_id) {
      return;
    }
    // 合并过程需要遍历一遍所有元素, 将两个元素的所属集合编号合并
    for (int i = 0; i < m_count; i++) {
      if (m_id[i] == p_id) {
        m_id[i] = q_id;
      }
    }
  }
};
}