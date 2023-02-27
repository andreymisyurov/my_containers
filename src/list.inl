
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <ostream>
template <typename T>
List<T>::List()
    : m_size_(0), m_head_(nullptr), m_tail_(nullptr), m_last_(new Node()) {}

template <typename T>
List<T>::List(size_type n) : List() {
  value_type value{};
  for (size_t i = 0; i < n; ++i) push_back(value);
}

template <typename T>
List<T>::List(std::initializer_list<value_type> const &items) : List() {
  for (auto &&el : items) push_back(el);
}

template <typename T>
List<T>::List(const List &other) : List() {
  *this = other;
}

template <typename T>
List<T>::List(List &&other) : List() {
  *this = other;
}

template <typename T>
List<T>::~List() {
  clear();
  delete m_last_;
}

template <typename T>
List<T> &List<T>::operator=(const List &other) {
  clear();
  delete m_last_;
  m_last_ = new Node();
  for (auto &&el : other) push_back(el);
  return *this;
}

template <typename T>
List<T> &List<T>::operator=(List &&other) {
  std::swap(m_head_, other.m_head_);
  std::swap(m_tail_, other.m_tail_);
  std::swap(m_last_, other.m_last_);
  std::swap(m_size_, other.m_size_);
  return *this;
}

template <typename T>
void List<T>::clear() {
  while (m_size_) pop_front();
  //   delete m_last_;
}

template <typename value_type>
void List<value_type>::push_back(value_type value) {
  if (!m_size_) {
    m_head_ = m_tail_ = new Node(value, nullptr, nullptr);
    m_tail_->n_next_ = m_last_;
  } else {
    m_tail_->n_next_ = new Node(value, m_tail_, nullptr);
    m_tail_ = m_tail_->n_next_;
    m_tail_->n_next_ = m_last_;
    m_last_->n_prev_ = m_tail_;
  }
  ++m_size_;
}

template <typename value_type>
void List<value_type>::push_front(value_type value) {
  if (!m_size_) {
    m_head_ = m_tail_ = new Node(value, nullptr, nullptr);
    m_tail_->n_next_ = m_last_;
    m_last_->n_prev_ = m_tail_;
  } else {
    m_head_->n_prev_ = new Node(value, nullptr, m_head_);
    m_head_ = m_head_->n_prev_;
  }
  ++m_size_;
}

template <typename value_type>
void List<value_type>::pop_back() {
  Node *temp = m_tail_;
  --m_size_;
  m_tail_ = m_tail_->n_prev_;
  m_last_->n_prev_ = m_tail_;
  if (m_size_) m_tail_->n_next_ = m_last_;
  delete temp;
}

template <typename value_type>
void List<value_type>::pop_front() {
  if (!m_size_) return;

  Node *temp = m_head_;
  m_head_ = m_head_->n_next_;
  m_head_->n_prev_ = nullptr;
  --m_size_;

  delete temp;
}
