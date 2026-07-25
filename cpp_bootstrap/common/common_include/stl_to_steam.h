/************************************************
 * @author puzzzzle
 * @mail 2359173906@qq.com
 * @desc
 * stl 容器 转为字符串 或者 输出到 ostream, 并支持 operator<< 操作符
 *
 * 如果一个stl容器的 value_type 满足以下3个条件之一
 * (关联容器需要K,V分别满足3个条件之一) :
 *
 * 或者: 支持 operator<< 操作符
 *
 * 或者: 提供满足 default_value_to_stream 格式的接口
 *
 * 或者: 自身也是stl容器,并且递归的满足这个条件
 *
 * 那么就可以提供一个to_string函数,和同格式的 operator<< 操作符
 * 主要用于log
 *
 *
 * 以支持
 *
 * 所有stl标准容器:
 * 单值顺序容器: array vector forward_list list
 * 单值关联容器: set unordered_set multiset unordered_multiset
 * 关联容器: map unordered_map multimap unordered_multimap
 *
 * 非容器类:
 *
 * 模板元组类:
 * pair, tuple
 *
 * 所有stl容器适配器:
 * stack, queue, priority_queue
 *
 *
 * 非stl容器如果可以满足 顺序迭代器 格式, 那么也可以被 xxx_to_stream/
 * xxx_to_string 支持
 * 但是 operator<< 函数需要自行提供!
 *
 * @time 2022/3/28
 * @file stl_to_str.h
 * @version
 * version        author            desc
 * 1.0            puzzzzle       create
 ************************************************/

#pragma once
#include <array>
#include <deque>
#include <forward_list>
#include <ios>
#include <list>
#include <map>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// 类似 vec 的输出分割符
#ifndef STL_TO_STR_START
#define STL_TO_STR_START "["
#endif

#ifndef STL_TO_STR_END
#define STL_TO_STR_END "]"
#endif

#ifndef STL_TO_STR_SPLIT
#define STL_TO_STR_SPLIT ","
#endif

// pair/tuple 的输出分割符
#ifndef STL_TO_STR_PAIR_START
#define STL_TO_STR_PAIR_START "("
#endif

#ifndef STL_TO_STR_PAIR_END
#define STL_TO_STR_PAIR_END ")"
#endif

#ifndef STL_TO_STR_PAIR_SPLIT
#define STL_TO_STR_PAIR_SPLIT ","
#endif

// map的输出分隔符
#ifndef STL_TO_STR_MAP_START
#define STL_TO_STR_MAP_START "{"
#endif

#ifndef STL_TO_STR_MAP_END
#define STL_TO_STR_MAP_END "}"
#endif

#ifndef STL_TO_STR_MAP_SPLIT
#define STL_TO_STR_MAP_SPLIT ","
#endif

#ifndef STL_TO_STR_MAP_KEY_START
#define STL_TO_STR_MAP_KEY_START "\""
#endif

#ifndef STL_TO_STR_MAP_KEY_END
#define STL_TO_STR_MAP_KEY_END "\""
#endif

#ifndef STL_TO_STR_MAP_KEY_SPLIT
#define STL_TO_STR_MAP_KEY_SPLIT ":"
#endif

#ifndef STL_TO_STR_MAP_ITEM_START
#define STL_TO_STR_MAP_ITEM_START "{"
#endif

#ifndef STL_TO_STR_MAP_ITEM_END
#define STL_TO_STR_MAP_ITEM_END "}"
#endif

template <typename T>
class default_value_to_stream {
  public:
  static void to_stream(::std::ostream &os, const T &v) { os << v; }
};
// 单值 顺序容器
template <typename T,
          typename TW = default_value_to_stream<
              typename ::std::remove_reference<T>::type::value_type>>
::std::ostream &vec_like_to_stream(
    ::std::ostream &os, const T &vec,
    const ::std::string &start = STL_TO_STR_START,
    const ::std::string &end = STL_TO_STR_END,
    const ::std::string &split = STL_TO_STR_SPLIT) {
  os << start;
  auto it = vec.cbegin();
  // 忽略最后一个数据, 按照json格式, 不能输出分割符
  if (it != vec.cend()) {
    TW::to_stream(os, *it);
    ++it;
  }
  while (it != vec.cend()) {
    os << split;
    TW::to_stream(os, *it);
    ++it;
  }
  os << end;
#ifdef STL_TO_STR_WITH_COUNT
  os << "(" << count << ")";
#endif
  return os;
}
template <typename T,
          typename TW = default_value_to_stream<typename T::value_type>>
::std::string vec_like_to_string(const T &vec) {
  ::std::ostringstream oss{};
  vec_like_to_stream<T, TW>(oss, vec);
  return oss.str();
}

// 关联容器
template <typename K, typename T, typename KW = default_value_to_stream<K>,
          typename TW = default_value_to_stream<T>>
class map_pair_to_stream_trait {
  public:
  static void to_stream(::std::ostream &os, const ::std::pair<K, T> &obj) {
    os << STL_TO_STR_MAP_ITEM_START << STL_TO_STR_MAP_KEY_START;
    KW::to_stream(os, obj.first);
    os << STL_TO_STR_MAP_KEY_END << STL_TO_STR_MAP_KEY_SPLIT;
    TW::to_stream(os, obj.second);
    os << STL_TO_STR_MAP_ITEM_END;
  }
};
template <typename _Tp,
          typename KW = default_value_to_stream<
              typename ::std::remove_reference<_Tp>::type::key_type>,
          typename TW = default_value_to_stream<
              typename ::std::remove_reference<_Tp>::type::mapped_type>>
::std::ostream &map_like_to_stream(::std::ostream &os, const _Tp &map) {
  return vec_like_to_stream<
      _Tp,
      map_pair_to_stream_trait<
          typename ::std::remove_reference<_Tp>::type::key_type,
          typename ::std::remove_reference<_Tp>::type::mapped_type, KW, TW>>(
      os, map, STL_TO_STR_MAP_START, STL_TO_STR_MAP_END, STL_TO_STR_MAP_SPLIT);
}

template <typename _Tp,
          typename KW = default_value_to_stream<typename _Tp::key_type>,
          typename TW = default_value_to_stream<typename _Tp::mapped_type>>
::std::string map_like_to_string(const _Tp &map) {
  ::std::ostringstream oss{};
  map_like_to_stream<_Tp, KW, TW>(oss, map);
  return oss.str();
}
// pair
template <typename K, typename T, typename KW = default_value_to_stream<K>,
          typename TW = default_value_to_stream<T>>
::std::ostream &pair_to_stream(::std::ostream &os,
                               const ::std::pair<K, T> &obj) {
  os << STL_TO_STR_PAIR_START;
  KW::to_stream(os, obj.first);
  os << STL_TO_STR_PAIR_SPLIT;
  TW::to_stream(os, obj.second);
  os << STL_TO_STR_PAIR_END;
  return os;
}
template <typename K, typename T, typename KW = default_value_to_stream<K>,
          typename TW = default_value_to_stream<T>>
::std::string pair_to_string(const ::std::pair<K, T> &obj) {
  ::std::ostringstream oss{};
  pair_to_stream<K, T, KW, TW>(oss, obj);
  return oss.str();
}
// tuple 比较需要模板递归展开, 不能迭代
template <typename Tuple, size_t N>
struct tuple_to_string_trait {
  static void to_stream(::std::ostream &os, const Tuple &t) {
    tuple_to_string_trait<Tuple, N - 1>::to_stream(os, t);
    os << STL_TO_STR_PAIR_SPLIT << ::std::get<N - 1>(t);
  }
};
template <typename Tuple>
struct tuple_to_string_trait<Tuple, 1> {
  static void to_stream(::std::ostream &os, const Tuple &t) {
    os << ::std::get<0>(t);
  }
};
template <typename... _Elements>
::std::ostream &tuple_to_stream(::std::ostream &os,
                                const ::std::tuple<_Elements...> &t) {
  os << STL_TO_STR_PAIR_START;
  tuple_to_string_trait<decltype(t), sizeof...(_Elements)>::to_stream(t, os);
  os << STL_TO_STR_PAIR_END;
  return os;
}
template <typename... _Elements>
::std::string tuple_to_string(const ::std::tuple<_Elements...> &t) {
  ::std::stringstream os{};
  os << STL_TO_STR_PAIR_START;
  tuple_to_string_trait<decltype(t), sizeof...(_Elements)>::to_stream(t, os);
  os << STL_TO_STR_PAIR_END;
  return os.str();
}

// 容器适配器
// stack
template <typename _Tp, typename _Sequence>
const _Sequence &inner_adaptor_container(
    const ::std::stack<_Tp, _Sequence> &stack) {
  struct inner_adaptor_container_impl : public ::std::stack<_Tp, _Sequence> {
    static const _Sequence &container(
        const ::std::stack<_Tp, _Sequence> &stack) {
      return stack.*&inner_adaptor_container_impl::c;
    }
  };
  return inner_adaptor_container_impl::container(stack);
}

// queue
template <class _Tp, class _Sequence>
const _Sequence &inner_adaptor_container(
    const ::std::queue<_Tp, _Sequence> &queue) {
  struct inner_adaptor_container_impl : public ::std::queue<_Tp, _Sequence> {
    static const _Sequence &container(
        const ::std::queue<_Tp, _Sequence> &queue) {
      return queue.*&inner_adaptor_container_impl::c;
    }
  };
  return inner_adaptor_container_impl::container(queue);
}

// priority_queue
template <class _Tp, class _Sequence, typename _Compare>
const _Sequence &inner_adaptor_container(
    const ::std::priority_queue<_Tp, _Sequence, _Compare> &queue) {
  struct inner_adaptor_container_impl
      : public ::std::priority_queue<_Tp, _Sequence, _Compare> {
    static const _Sequence &container(
        const ::std::priority_queue<_Tp, _Sequence, _Compare> &queue) {
      return queue.*&inner_adaptor_container_impl::c;
    }
  };
  return inner_adaptor_container_impl::container(queue);
}

template <class T, typename TW =
                       default_value_to_stream<typename ::std::remove_reference<
                           T>::type::container_type::value_type>>
::std::ostream &adaptor_to_stream(::std::ostream &os, const T &adaptor) {
  return vec_like_to_stream<
      typename ::std::remove_reference<T>::type::container_type, TW>(
      os, inner_adaptor_container(adaptor));
}
template <
    typename T,
    typename TW = default_value_to_stream<
        typename ::std::remove_reference<T>::type::container_type::value_type>>
::std::string adaptor_to_string(const T &adaptor) {
  ::std::ostringstream oss{};
  adaptor_to_stream<T, TW>(oss, adaptor);
  return oss.str();
}

// 运算符重载
// 运算符重载必须与容器本身处于同一namespace， 否则adl规则可能找不到符号
// 参考 adl规则： https://en.cppreference.com/w/cpp/language/adl
namespace std {

// 匹配 单值 顺序容器
template <typename T, typename _Alloc>
::std::ostream &operator<<(::std::ostream &os,
                           const ::std::vector<T, _Alloc> &vec) {
  return vec_like_to_stream<decltype(vec)>(os, vec);
}
template <typename T, ::std::size_t _Nm>
::std::ostream &operator<<(::std::ostream &os,
                           const ::std::array<T, _Nm> &vec) {
  return vec_like_to_stream<decltype(vec)>(os, vec);
}
template <typename T, typename _Alloc>
::std::ostream &operator<<(::std::ostream &os,
                           const ::std::forward_list<T, _Alloc> &vec) {
  return vec_like_to_stream<decltype(vec)>(os, vec);
}

template <typename T, typename _Alloc>
::std::ostream &operator<<(::std::ostream &os,
                           const ::std::list<T, _Alloc> &vec) {
  return vec_like_to_stream<decltype(vec)>(os, vec);
}
template <typename T, typename _Alloc>
::std::ostream &operator<<(::std::ostream &os,
                           const ::std::deque<T, _Alloc> &vec) {
  return vec_like_to_stream<decltype(vec)>(os, vec);
}
// 匹配单值关联容器
template <typename T, typename _Compare, typename _Alloc>
::std::ostream &operator<<(::std::ostream &os,
                           const ::std::set<T, _Compare, _Alloc> &vec) {
  return vec_like_to_stream<decltype(vec)>(os, vec);
}
template <typename T, typename _Compare, typename _Alloc>
::std::ostream &operator<<(::std::ostream &os,
                           const ::std::multiset<T, _Compare, _Alloc> &vec) {
  return vec_like_to_stream<decltype(vec)>(os, vec);
}
template <typename T, typename _Compare, typename _Alloc>
::std::ostream &operator<<(
    ::std::ostream &os,
    const ::std::unordered_multiset<T, _Compare, _Alloc> &vec) {
  return vec_like_to_stream<decltype(vec)>(os, vec);
}
template <typename T, typename _Hash, typename _Pred, typename _Alloc>
::std::ostream &operator<<(
    ::std::ostream &os,
    const ::std::unordered_set<T, _Hash, _Pred, _Alloc> &vec) {
  return vec_like_to_stream<decltype(vec)>(os, vec);
}

// 匹配关联容器
template <typename K, typename T, typename _Compare, typename _Alloc>
::std::ostream &operator<<(::std::ostream &os,
                           const ::std::map<K, T, _Compare, _Alloc> &map) {
  return map_like_to_stream<decltype(map)>(os, map);
}
template <typename K, typename T, typename _Compare, typename _Alloc>
::std::ostream &operator<<(::std::ostream &os,
                           const ::std::multimap<K, T, _Compare, _Alloc> &map) {
  return map_like_to_stream<decltype(map)>(os, map);
}
template <typename K, typename T, typename _Compare, typename _Alloc>
::std::ostream &operator<<(
    ::std::ostream &os,
    const ::std::unordered_multimap<K, T, _Compare, _Alloc> &map) {
  return map_like_to_stream<decltype(map)>(os, map);
}
template <typename K, typename T, class _Hash, class _Pred, class _Alloc>
::std::ostream &operator<<(
    ::std::ostream &os,
    const ::std::unordered_map<K, T, _Hash, _Pred, _Alloc> &map) {
  return map_like_to_stream<decltype(map)>(os, map);
}
// pair
template <typename K, typename T>
::std::ostream &operator<<(::std::ostream &os, const ::std::pair<K, T> &obj) {
  return pair_to_stream<K, T>(os, obj);
}
// tuple
template <typename... _Elements>
::std::ostream &operator<<(::std::ostream &os,
                           const ::std::tuple<_Elements...> &t) {
  os << STL_TO_STR_PAIR_START;
  tuple_to_string_trait<decltype(t), sizeof...(_Elements)>::to_stream(os, t);
  os << STL_TO_STR_PAIR_END;
  return os;
}

// 匹配容器适配器

// stack
template <typename T, typename _Sequence>
::std::ostream &operator<<(::std::ostream &os,
                           const ::std::stack<T, _Sequence> &t) {
  return adaptor_to_stream(os, t);
}
// queue
template <typename T, typename _Sequence>
::std::ostream &operator<<(::std::ostream &os,
                           const ::std::queue<T, _Sequence> &t) {
  return adaptor_to_stream(os, t);
}
// priority_queue
template <typename T, typename _Sequence, typename _Compare>
::std::ostream &operator<<(
    ::std::ostream &os,
    const ::std::priority_queue<T, _Sequence, _Compare> &t) {
  return adaptor_to_stream(os, t);
}
}  // namespace std