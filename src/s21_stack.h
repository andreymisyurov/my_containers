#pragma once
#include <initializer_list>

namespace s21 {
template <typename T>
class stack {
 public:
  typedef T value_type;
  typedef T &reference;
  typedef const T &const_reference;
  typedef size_t size_type;

 private:
  class Node {
   public:
    Node *prev_;
    value_type item_;
    explicit Node(value_type item = value_type(), Node *prev = nullptr) {
      this->item_ = item;
      this->prev_ = prev;
    }
  };
  size_type count_;
  Node *head_;

 public:
  stack();
  stack(const stack &other);
  explicit stack(std::initializer_list<value_type> const &items);
  stack(stack &&other);
  stack<value_type> &operator=(stack &&other);
  stack<value_type> &operator=(const stack &other);
  ~stack();

 public:
  void push(const value_type value);
  void pop();
  void swap(stack &other);
  bool empty();
  size_t size();
  const T &top();
  void emplace_front(value_type const last_value);
  template <class... Args>
  void emplace_front(T const value, Args &&...args);

 public:
  void free_stack();
  static void copy_stack(stack<value_type> &stack, Node *temp);
};
}  // namespace s21

#include "s21_stack.inl"
