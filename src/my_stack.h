#ifndef _SRC_MY_STACK_H_
#define _SRC_MY_STACK_H_

#include <initializer_list>

namespace victoriv {

template <typename T>
class stack {
  class Node;

 public:
  typedef T value_type;
  typedef T &reference;
  typedef const T &const_reference;
  typedef size_t size_type;

 public:
  stack();
  explicit stack(std::initializer_list<value_type> const &in_items);
  stack(stack &&move_other);
  stack<value_type> &operator=(stack &&move_other);
  stack(const stack &in_other);
  stack<value_type> &operator=(const stack &in_other);
  ~stack();

 public:
  auto top() const                              -> const value_type &;
  auto size() const                             -> size_t;
  auto empty() const                            -> bool;
  auto push(const value_type &in_value)         -> void;
  auto push(value_type &&move_value)            -> void;
  auto pop()                                    -> void;
  auto swap(stack &inout_other)                 -> void;
  auto emplace_front(value_type &&move_value)   -> void;
  template <class... Args>
  auto emplace_front(value_type &&move_value, Args &&...move_args)         -> void;

 private:
    auto static copy_stack(stack<value_type> &out_stack, Node *inout_temp) -> void;
  size_type m_count;
  Node *m_head;

 private:
  class Node {
   public:
    Node(const value_type &in_item, Node *in_prev)
        : m_item(in_item), m_prev(in_prev) {}
    Node(value_type &&move_item, Node *in_prev)
        : m_item(std::move(move_item)), m_prev(in_prev) {}
    Node *m_prev;
    value_type m_item;
  };
};

template <typename value_type>
stack<value_type>::stack() : m_count(0), m_head(nullptr) {}

template <typename value_type>
stack<value_type>::stack(std::initializer_list<value_type> const &in_items) : stack() {
  for (const_reference &el : in_items) push(el);
}

template <typename value_type>
stack<value_type>::stack(const stack &in_other) : stack() {
  *this = in_other;
}

template <typename value_type>
stack<value_type>::stack(stack &&move_other) : stack() {
  *this = move_other;
}

template <typename value_type>
stack<value_type>::~stack() {
  while (m_head != nullptr) pop();
}

template <typename value_type>
stack<value_type> &stack<value_type>::operator=(stack &&move_other) {
  swap(move_other);
  return *this;
}

template <typename value_type>
void stack<value_type>::copy_stack(stack<value_type> &out_other, Node *inout_temp) {
  value_type deep_elem{};
  Node *check = inout_temp;
  if (inout_temp != nullptr) {
    deep_elem = inout_temp->m_item;
    inout_temp = inout_temp->m_prev;
    copy_stack(out_other, inout_temp);
  }
  if (check != nullptr)
    out_other.push(deep_elem);
}

template <typename value_type>
stack<value_type> &stack<value_type>::operator=(const stack &in_other) {
  stack<value_type> temp;
  copy_stack(temp, in_other.m_head);

  swap(temp);
  return *this;
}

template <typename value_type>
const typename stack<value_type>::value_type &stack<value_type>::top() const {
  return m_head->m_item;
}

template <typename value_type>
bool stack<value_type>::empty() const {
  return m_head == nullptr;
}

template <typename value_type>
size_t stack<value_type>::size() const {
  return m_count;
}

template <typename value_type>
void stack<value_type>::push(const value_type &value) {
  m_head = new Node(value, m_head);
  ++m_count;
}

template <typename value_type>
void stack<value_type>::push(value_type &&move_value) {
  m_head = new Node(std::move(move_value), m_head);
  ++m_count;
}

template <typename value_type>
void stack<value_type>::pop() {
  Node *temp = m_head;
  m_head = m_head->m_prev;
  --m_count;
  delete temp;
}

template <typename value_type>
void stack<value_type>::swap(stack &inout_other) {
  if (this != &inout_other) {
    std::swap(m_head, inout_other.m_head);
    std::swap(m_count, inout_other.m_count);
  }
}

template <typename value_type>
void stack<value_type>::emplace_front(value_type &&in_value) {
  push(std::move(in_value));
}

template <typename value_type>
template <typename... Args>
void stack<value_type>::emplace_front(value_type &&in_value, Args &&...args) {
  push(std::move(in_value));
  emplace_front(std::forward<Args>(args)...);
}

}  // namespace victoriv

#endif  // _SRC_MY_STACK_H_
