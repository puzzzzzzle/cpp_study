/************************************************
 * @author puzzzzzzle
 * @email 2359173906@qq.com
 * @desc std::array 的变体,
 * 内部存储指针, 访问的时候再创建 ,做到延迟创建
 * 访问为空的槽的时候:
 *      可写访问会创建
 *      只读放完返回默认值
 * 所有接口和std::array 保持一致, 除了data 会返回指针数组, 且有可能为空外
 * @time 2022/9/27
 * @file delay_array.h
 * @version
 * version        author            desc
 * 1.0            puzzzzzzle       create
 ************************************************/

#pragma once
#include <bits/range_access.h>
#include <bits/stl_algobase.h>

#include <stdexcept>

namespace delay_array {
template <typename _Tp, std::size_t _Nm>
struct __array_traits {
  typedef _Tp _Type[_Nm];
  typedef _Tp* _PtrType[_Nm];
};

template <typename _Tp>
struct __array_traits<_Tp, 0> {
  struct _Type {};
  struct _PtrType {};
};

template <typename _Tp, std::size_t _Nm>
struct delay_array {
  typedef _Tp value_type;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;

  // iterators
  struct iterator{

private:
    value_type** _M_Ptr;
  };
  typedef const value_type* const_iterator;
  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

  // Support for zero-sized arrays mandatory.
  typedef ::delay_array::__array_traits<_Tp, _Nm> _AT_Type;
  typename _AT_Type::_PtrType _M_elems{};
  _Tp _M_default{};

  // No explicit construct/copy/destroy for aggregate type.

  // DR 776.
  void fill(const value_type& __u) { std::fill_n(begin(), size(), __u); }

  void swap(delay_array& __other) noexcept(noexcept(swap(std::declval<_Tp&>(),
                                                   std::declval<_Tp&>()))) {
    std::swap_ranges(begin(), end(), __other.begin());
  }

  // Iterators.
  iterator begin() noexcept { return iterator(data()); }

  const_iterator begin() const noexcept { return const_iterator(data()); }

  iterator end() noexcept { return iterator(data() + _Nm); }

  const_iterator end() const noexcept { return const_iterator(data() + _Nm); }

  reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }

  const_reverse_iterator rbegin() const noexcept {
    return const_reverse_iterator(end());
  }

  reverse_iterator rend() noexcept { return reverse_iterator(begin()); }

  const_reverse_iterator rend() const noexcept {
    return const_reverse_iterator(begin());
  }

  const_iterator cbegin() const noexcept { return const_iterator(data()); }

  const_iterator cend() const noexcept { return const_iterator(data() + _Nm); }

  const_reverse_iterator crbegin() const noexcept {
    return const_reverse_iterator(end());
  }

  const_reverse_iterator crend() const noexcept {
    return const_reverse_iterator(begin());
  }

  // Capacity.
  constexpr size_type size() const noexcept { return _Nm; }

  constexpr size_type max_size() const noexcept { return _Nm; }

  constexpr bool empty() const noexcept { return size() == 0; }

  // Element access.
  reference operator[](size_type __n) {
    return _AT_Type::_S_ref(_M_elems, __n);
  }

  constexpr const_reference operator[](size_type __n) const noexcept {
    return _AT_Type::_S_ref(_M_elems, __n);
  }

  reference at(size_type __n) {
    if (__n >= _Nm) std::__throw_out_of_range(__N("array::at"));
    return _AT_Type::_S_ref(_M_elems, __n);
  }

  constexpr const_reference at(size_type __n) const {
    // Result of conditional expression must be an lvalue so use
    // boolean ? lvalue : (throw-expr, lvalue)
    return __n < _Nm ? _AT_Type::_S_ref(_M_elems, __n)
                     : (std::__throw_out_of_range(__N("array::at")),
                        _AT_Type::_S_ref(_M_elems, 0));
  }

  reference front() { return *begin(); }

  constexpr const_reference front() const {
    return _AT_Type::_S_ref(_M_elems, 0);
  }

  reference back() { return _Nm ? *(end() - 1) : *end(); }

  constexpr const_reference back() const {
    return _Nm ? _AT_Type::_S_ref(_M_elems, _Nm - 1)
               : _AT_Type::_S_ref(_M_elems, 0);
  }

  pointer data() noexcept {
    return std::__addressof(_AT_Type::_S_ref(_M_elems, 0));
  }

  const_pointer data() const noexcept {
    return std::__addressof(_AT_Type::_S_ref(_M_elems, 0));
  }
};

// Array comparisons.
template <typename _Tp, std::size_t _Nm>
inline bool operator==(const delay_array<_Tp, _Nm>& __one,
                       const delay_array<_Tp, _Nm>& __two) {
  return std::equal(__one.begin(), __one.end(), __two.begin());
}

template <typename _Tp, std::size_t _Nm>
inline bool operator!=(const delay_array<_Tp, _Nm>& __one,
                       const delay_array<_Tp, _Nm>& __two) {
  return !(__one == __two);
}

template <typename _Tp, std::size_t _Nm>
inline bool operator<(const delay_array<_Tp, _Nm>& __a, const delay_array<_Tp, _Nm>& __b) {
  return std::lexicographical_compare(__a.begin(), __a.end(), __b.begin(),
                                      __b.end());
}

template <typename _Tp, std::size_t _Nm>
inline bool operator>(const delay_array<_Tp, _Nm>& __one,
                      const delay_array<_Tp, _Nm>& __two) {
  return __two < __one;
}

template <typename _Tp, std::size_t _Nm>
inline bool operator<=(const delay_array<_Tp, _Nm>& __one,
                       const delay_array<_Tp, _Nm>& __two) {
  return !(__one > __two);
}

template <typename _Tp, std::size_t _Nm>
inline bool operator>=(const delay_array<_Tp, _Nm>& __one,
                       const delay_array<_Tp, _Nm>& __two) {
  return !(__one < __two);
}
}  // namespace delay_array
