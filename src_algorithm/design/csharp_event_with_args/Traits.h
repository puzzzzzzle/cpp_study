//
// Created by khalidzhang on 2020/1/21.
//

#pragma once
template <typename... T>
struct Continuation {
  using type = std::function<void(T...)>;
};

template <>
struct Continuation<void> {
  using type = std::function<void()>;
};