#pragma once

template <typename value_type>
s21::stack<value_type>::stack() : count_(0), head_(nullptr) {}

template <typename value_type>
s21::stack<value_type>::stack(std::initializer_list<value_type> const &items)
    : stack() {
  for (value_type temp : items) {
    this->push(temp);
  }
}

template <typename value_type>
s21::stack<value_type>::stack(const stack &other) : stack() {
  if (this != &other) {
    *this = other;
  }
}

template <typename value_type>
s21::stack<value_type>::stack(stack &&other) {
  if (this != &other) {
    std::swap(this->head_, other.head_);
    std::swap(this->count_, other.count_);
    other.head_ = nullptr;
  }
}

template <typename value_type>
s21::stack<value_type>::~stack() {
  while (head_ != nullptr) {
    this->pop();
  }
}

template <typename value_type>
s21::stack<value_type> &s21::stack<value_type>::operator=(stack &&other) {
  std::swap(this->head_, other.head_);
  std::swap(this->count_, other.count_);
  return *this;
}

template <typename value_type>
void s21::stack<value_type>::copy_stack(stack<value_type> &other, Node *temp) {
  value_type my_perfect{};
  Node *check = temp;
  if (temp != nullptr) {
    my_perfect = temp->item_;
    temp = temp->prev_;
    copy_stack(other, temp);
  }
  if (check != nullptr) {
    other.push(my_perfect);
  }
}

template <typename value_type>
s21::stack<value_type> &s21::stack<value_type>::operator=(const stack &other) {
  if (this != &other) {
    Node *temp = other.head_;
    this->free_stack();
    copy_stack(*this, temp);
  }
  return *this;
}

template <typename value_type>
const typename s21::stack<value_type>::value_type &
s21::stack<value_type>::top() {
  return head_->item_;
}

template <typename value_type>
bool s21::stack<value_type>::empty() {
  return (head_ == nullptr) ? true : false;
}

template <typename value_type>
size_t s21::stack<value_type>::size() {
  return count_;
}

template <typename value_type>
void s21::stack<value_type>::push(const value_type value) {
  head_ = new Node(value, head_);
  count_++;
}

template <typename value_type>
void s21::stack<value_type>::pop() {
  Node *temp = head_;
  head_ = head_->prev_;
  count_--;
  delete temp;
}

template <typename value_type>
void s21::stack<value_type>::swap(stack &other) {
  if (this != &other) {
    std::swap(this->head_, other.head_);
    std::swap(this->count_, other.count_);
  }
}

template <typename value_type>
void s21::stack<value_type>::emplace_front(value_type const last_value) {
  push(last_value);
};

template <typename value_type>
template <typename... Args>
void s21::stack<value_type>::emplace_front(value_type const value,
                                           Args &&...args) {
  push(value);
  emplace_front(args...);
}

template <typename value_type>
void s21::stack<value_type>::free_stack() {
  while (head_ != nullptr) {
    pop();
  }
}
