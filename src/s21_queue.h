#pragma once

#include <iostream>

#include "s21_list.h"

namespace s21 {
template <typename T>
class Queue : private List<T> {
 public:
  typedef T value_type;
  typedef T &reference;
  typedef const T &const_reference;
  typedef size_t size_type;

  Queue() : List<value_type>::List() {}
  explicit Queue(std::initializer_list<value_type> const &items)
      : List<value_type>::List(items) {}
  Queue(const Queue &s) : List<value_type>::List(s) {}
  Queue(Queue &&s) : List<value_type>::List(std::move(s)) {}
  ~Queue() {}

  Queue &operator=(const Queue &s) {
    if (this == &s)
      throw std::out_of_range("Coping the same Queue is forbidden!");
    List<value_type>::clear();
    for (auto it = s.cbegin(); it != s.cend(); ++it) this->push_back(*it);
    return *this;
  }
  Queue &operator=(Queue &&s) {
    List<value_type>::operator=(std::move(s));
    return *this;
  }

  const_reference front() {
    if (!size()) throw std::out_of_range("Queue is empty!");
    auto first_node = List<value_type>::begin();
    return *first_node;
  }
  const_reference back() {
    if (!size()) throw std::out_of_range("Queue is empty!");
    auto last_node = List<value_type>::end();
    --last_node;
    return *last_node;
  }

  using List<value_type>::empty;
  using List<value_type>::size;

  void push(const_reference value) { List<value_type>::push_back(value); }
  void pop() { List<value_type>::pop_front(); }
  void swap(Queue &other) noexcept { List<value_type>::swap(other); }

  using List<value_type>::emplace_back;

  void print_from_head() { List<value_type>::print_from_head(); }
};

}  // namespace s21
