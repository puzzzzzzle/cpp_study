/************************************************
* @author khalidzhang
* @email khalidzhang@tencent.com
* @desc
* @time 2022/7/5
* @file SortedMap.h
* @version
* version        author            desc
* 1.0            khalidzhang       create
************************************************/

#pragma once
#include <algorithm>
#include <cassert>
#include <vector>
/**
* 可以按照 _SortCompare 来排序的map
* map的排序和 Sorted 返回的排序无关, Sorted 返回 按照 _SortCompare 排序完的结果
* 直到下一次调用Stored才可以使用 Sorted 的结果会缓存
* 注意 : MutableData 和 Sorted 只有一个返回的数据有效, 调用其中一个后,
* 另一个之前缓存的数据无效
* @tparam _MapType
* @tparam _SortCompare
*/
template <typename MapType,
         typename SortCompare = std::less<typename MapType::key_type>>
class SortedMap {
 public:
 using SortedType = std::vector<typename MapType::const_iterator>;

 private:
 MapType m_data{};
 SortCompare m_sortCompare{};
 bool m_dirty{};
 SortedType m_sorted{};

 public:
 void CopyFrom(const SortedMap<MapType, SortCompare>& rhs) {
   m_data = rhs.m_data;
   m_sortCompare = rhs.m_sortCompare;
   Sorted(true);
 }
 SortedMap() = default;
 SortedMap(const SortedMap<MapType, SortCompare>& rhs) { CopyFrom(rhs); }
 SortedMap<MapType, SortCompare>& operator=(
     const SortedMap<MapType, SortCompare>& rhs) {
   CopyFrom(rhs);
   return *this;
 }

 // 移动复制器暂未实现
 SortedMap(const SortedMap<MapType, SortCompare>&& rhs) = delete;
 SortedMap<MapType, SortCompare>& operator=(
     const SortedMap<MapType, SortCompare>&& rhs) = delete;
 const MapType& Data() const { return m_data; }
 MapType& MutableData() {
   m_dirty = true;
   return m_data;
 }
 const SortedType& Sorted(bool force = false) {
   if (m_dirty || force) {
     m_dirty = false;
     m_sorted.clear();
     for (auto it = m_data.cbegin(); it != m_data.cend(); ++it) {
       m_sorted.push_back(it);
     }
     std::sort(m_sorted.begin(), m_sorted.end(), m_sortCompare);
   }
   return m_sorted;
 }
 const SortedType& SortedCache() const {
   assert(!m_dirty);
   return m_sorted;
 }
};